/*************************************************************************/
/*  bullet_body_sw.cpp                                                */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include "bullet_body_sw.h"
#include "bullet_server_sw.h"

void BulletBodySW::_set_transform(const Transform& p_transform) {
	Vector3 origin = p_transform.get_origin();
	Matrix3 basis = p_transform.get_basis();

	btTransform transform = btTransform();
	transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
	transform.setBasis(btMatrix3x3(basis[0].x, basis[0].y, basis[0].z,
								   basis[1].x, basis[1].y, basis[1].z,
								   basis[2].x, basis[2].y, basis[2].z));

	body->setWorldTransform(transform);
}

Transform BulletBodySW::_get_transform() const {

	btTransform bodyTransform = body->getWorldTransform();

	btVector3 origin = bodyTransform.getOrigin();
	btMatrix3x3 basis = bodyTransform.getBasis();

	Transform transform = Transform();
	transform.set_origin(Vector3(origin.x(), origin.y(), origin.z()));
	transform.set_basis(Matrix3(basis[0].x(), basis[0].y(), basis[0].z(),
								basis[1].x(), basis[1].y(), basis[1].z(),
								basis[2].x(), basis[2].y(), basis[2].z()));

	//if (mode == PhysicsServer::BODY_MODE_RIGID)
	//	print_line(Vector3(origin.x(), origin.y(), origin.z()));

	return transform;
}

void BulletBodySW::set_force_integration_callback(ObjectID p_id,const StringName& p_method,const Variant& p_udata) {

	id=p_id;
}

BulletSpaceSW *BulletBodySW::get_space() {
	return space;
}

void BulletBodySW::set_space(BulletSpaceSW *p_space) {
	if (p_space==space)
		return;

	if (space) {
		space->discreteDynamicsWorld->removeRigidBody(body);
		space->remove_body(this);
	}
	if (p_space) {
		p_space->discreteDynamicsWorld->addRigidBody(body);
		p_space->add_body(this);
	}

	space=p_space;
}

void BulletBodySW::add_shape(BulletShapeSW *p_shape,const Transform& p_transform) {

	if (space)
		space->discreteDynamicsWorld->removeRigidBody(body);

	Vector3 origin = p_transform.get_origin();
	Matrix3 basis = p_transform.get_basis();

	btTransform transform = btTransform();
	transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
	transform.setBasis(btMatrix3x3(basis[0].x, basis[0].y, basis[0].z,
								   basis[1].x, basis[1].y, basis[1].z,
								   basis[2].x, basis[2].y, basis[2].z));

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();
	shape->addChildShape(transform, p_shape->shape);

	if (space) {
		if (mode==BulletServerSW::BODY_MODE_RIGID) {
			mass = btScalar(0.01f);
			update_inertias();
		}
		space->discreteDynamicsWorld->addRigidBody(body);
	}
}

void BulletBodySW::set_state(PhysicsServer::BodyState p_state, const Variant& p_variant) {

	if (p_state == PhysicsServer::BODY_STATE_TRANSFORM) {
		_set_transform(p_variant);
	}
}

void BulletBodySW::set_param(PhysicsServer::BodyParameter p_param, float p_value) {

	switch(p_param) {
		case PhysicsServer::BODY_PARAM_BOUNCE: {

			body->setRestitution(btScalar(p_value));
		} break;
		case PhysicsServer::BODY_PARAM_FRICTION: {

			body->setFriction(btScalar(p_value));
		} break;
		case PhysicsServer::BODY_PARAM_MASS: {

			mass = btScalar(p_value);
			update_inertias();
		} break;
		default:{}
	}
}

Variant BulletBodySW::get_state(PhysicsServer::BodyState p_state) const {

	switch(p_state)	{
		case PhysicsServer::BODY_STATE_TRANSFORM: {
			return _get_transform();
		} break;
		case PhysicsServer::BODY_STATE_LINEAR_VELOCITY: {
		} break;
		case PhysicsServer::BODY_STATE_ANGULAR_VELOCITY: {
		} break;
		case PhysicsServer::BODY_STATE_SLEEPING: {
		} break;
		case PhysicsServer::BODY_STATE_CAN_SLEEP: {
		} break;
	}

	return Variant();
}

void BulletBodySW::update_inertias() {

	if (space)
		space->discreteDynamicsWorld->removeRigidBody(body);

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();

	btVector3 inertia;
	shape->calculateLocalInertia(mass,inertia);
	body->setMassProps(mass,inertia);

	if (space)
		space->discreteDynamicsWorld->addRigidBody(body);
}
