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

#include "bullet_server_sw.h"
#include "bullet_space_sw.h"

void BulletBodySW::_set_transform(const Transform& p_transform) {

	Vector3 origin = p_transform.get_origin();
	Matrix3 basis = p_transform.get_basis();

	Vector3 scale = basis.get_scale();
	basis.scale(scale.inverse());

	btTransform transform = btTransform();
	transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
	transform.setBasis(btMatrix3x3(basis[0].x, basis[0].y, basis[0].z,
								   basis[1].x, basis[1].y, basis[1].z,
								   basis[2].x, basis[2].y, basis[2].z));

	printf(">>>setting transform for body (%p)\n", body);

	body->getCollisionShape()->setLocalScaling(btVector3(btScalar(scale.x), btScalar(scale.y), btScalar(scale.z)));

#if 0
	body->getMotionState()->setWorldTransform(transform);
#else
	body->setWorldTransform(transform);
#endif

	_update_inertia();
}

Transform BulletBodySW::get_transform() const {

#if 0
	btMotionState *motionState = (btDefaultMotionState*) body->getMotionState();
	btTransform btTrans;
	motionState->getWorldTransform(btTrans);
#else
	btTransform btTrans = body->getWorldTransform();
#endif

	btVector3 origin = btTrans.getOrigin();
	btMatrix3x3 basis = btTrans.getBasis();

	btVector3 scale = body->getCollisionShape()->getLocalScaling();
	basis = basis.scaled(scale);

	Transform transform;
	transform.set_origin(Vector3(origin.x(), origin.y(), origin.z()));
	transform.set_basis(Matrix3(basis[0].x(), basis[0].y(), basis[0].z(),
								basis[1].x(), basis[1].y(), basis[1].z(),
								basis[2].x(), basis[2].y(), basis[2].z()));

	return transform;
}

Transform BulletBodySW::get_shape_transform(int p_index) const {

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();
	btTransform btTrans = shape->getChildTransform(p_index);

	btVector3 origin = btTrans.getOrigin();
	btMatrix3x3 basis = btTrans.getBasis();

	btVector3 scale = shape->getChildShape(p_index)->getLocalScaling();
	basis = basis.scaled(scale);

	Transform transform;
	transform.set_origin(Vector3(origin.x(), origin.y(), origin.z()));
	transform.set_basis(Matrix3(basis[0].x(), basis[0].y(), basis[0].z(),
								basis[1].x(), basis[1].y(), basis[1].z(),
								basis[2].x(), basis[2].y(), basis[2].z()));

	return transform;
}

BulletShapeSW *BulletBodySW::get_shape(int p_index) const {
	return shapes[p_index];
}


void BulletBodySW::_set_space(BulletSpaceSW *p_space) {

	if (space) {

		space->remove_object(this);
		space->discreteDynamicsWorld->removeRigidBody(body);
	}

	space=p_space;

	if (space) {

		space->add_object(this);
		space->discreteDynamicsWorld->addRigidBody(body);
	}	
}

void BulletBodySW::_update_inertia() {

	if (get_space() && !inertia_update_list.in_list())
		get_space()->body_add_to_inertia_update_list(&inertia_update_list);

}

void BulletBodySW::set_force_integration_callback(ObjectID p_id,const StringName& p_method,const Variant& p_udata) {

	if (fi_callback) {

		memdelete(fi_callback);
		fi_callback=NULL;
	}

	if (p_id!=0) {

		fi_callback=memnew(ForceIntegrationCallback);
		fi_callback->id=p_id;
		fi_callback->method=p_method;
		fi_callback->udata=p_udata;
	}
}

void BulletBodySW::set_mode(PhysicsServer::BodyMode p_mode) {

	PhysicsServer::BodyMode prev=mode;
	mode=p_mode;

	switch(p_mode) {
			//CLEAR UP EVERYTHING IN CASE IT NOT WORKS!
		case PhysicsServer::BODY_MODE_STATIC:
		case PhysicsServer::BODY_MODE_KINEMATIC: {
/*
			_set_inv_transform(get_transform().affine_inverse());
			_inv_mass=0;
			_set_static(p_mode==PhysicsServer::BODY_MODE_STATIC);
			//set_active(p_mode==PhysicsServer::BODY_MODE_KINEMATIC);
			set_active(p_mode==PhysicsServer::BODY_MODE_KINEMATIC && contacts.size());
			linear_velocity=Vector3();
			angular_velocity=Vector3();
			if (mode==PhysicsServer::BODY_MODE_KINEMATIC && prev!=mode) {
				first_time_kinematic=true;
			}
*/
		} break;
		case PhysicsServer::BODY_MODE_RIGID:
		case PhysicsServer::BODY_MODE_CHARACTER: {

			//_inv_mass=mass>0?(1.0/mass):0;
			//_set_static(false);
		} break;
	}

	_update_inertia();
	//if (get_space())
	//		_update_queries();
}

void BulletBodySW::call_queries() {

	if (fi_callback) {

		BulletDirectBodyStateSW *dbs = BulletDirectBodyStateSW::singleton;
		dbs->body=this;

		Variant v=dbs;

		Object *obj = ObjectDB::get_instance(fi_callback->id);
		if (!obj) {

			set_force_integration_callback(0,StringName());
		} else {
			const Variant *vp[2]={&v,&fi_callback->udata};

			Variant::CallError ce;
			int argc=(fi_callback->udata.get_type()==Variant::NIL)?1:2;
			obj->call(fi_callback->method,vp,argc,ce);
		}
	}
}

BulletSpaceSW *BulletBodySW::get_space() {
	return space;
}

void BulletBodySW::set_space(BulletSpaceSW *p_space){

	if (get_space()) {

		if (inertia_update_list.in_list())
			get_space()->body_remove_from_inertia_update_list(&inertia_update_list);
//		if (active_list.in_list())
//			get_space()->body_remove_from_active_list(&active_list);
//		if (direct_state_query_list.in_list())
//			get_space()->body_remove_from_state_query_list(&direct_state_query_list);

	}

	_set_space(p_space);

	if (get_space()) {

		_update_inertia();
//		if (active)
//			get_space()->body_add_to_active_list(&active_list);
		
//		_update_queries();
		//if (is_active()) {
		//	active=false;
		//	set_active(true);
		//}
		
	}
	
}

void BulletBodySW::add_shape(BulletShapeSW *p_shape,const Transform& p_transform) {

	shapes.push_back(p_shape);

	Vector3 origin = p_transform.get_origin();
	Matrix3 basis = p_transform.get_basis();

	Vector3 scale = basis.get_scale();
	basis.scale(scale.inverse());

	btTransform transform = btTransform();
	transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
	transform.setBasis(btMatrix3x3(basis[0].x, basis[0].y, basis[0].z,
								   basis[1].x, basis[1].y, basis[1].z,
								   basis[2].x, basis[2].y, basis[2].z));

	printf(">>>setting transform for shape (%p)\n", p_shape->shape);

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();

	p_shape->shape->setLocalScaling(btVector3(btScalar(scale.x), btScalar(scale.y), btScalar(scale.z)));
	shape->addChildShape(transform, p_shape->shape);

	_update_inertia();
}

void BulletBodySW::remove_shape(int p_shape_idx) {

	shapes.remove(p_shape_idx);

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();
	shape->removeChildShapeByIndex(p_shape_idx);

	_update_inertia();
}

int BulletBodySW::get_shape_count() {

	btCompoundShape *shape = (btCompoundShape *)body->getCollisionShape();
	return shape->getNumChildShapes();
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
			_update_inertia();
		} break;
		default:{}
	}
}

Variant BulletBodySW::get_state(PhysicsServer::BodyState p_state) const {

	switch(p_state)	{
		case PhysicsServer::BODY_STATE_TRANSFORM: {
			return get_transform();
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

	if (btFuzzyZero(mass))
		mass = btScalar(0.0f);

	btVector3 inertia;
	shape->calculateLocalInertia(mass,inertia);
	body->setMassProps(mass,inertia);

	if (space)
		space->discreteDynamicsWorld->addRigidBody(body);
}

BulletBodySW::BulletBodySW() : inertia_update_list(this) {

	fi_callback=NULL;
}

BulletBodySW::~BulletBodySW() {

	if (fi_callback)
		memdelete(fi_callback);
}

BulletDirectBodyStateSW *BulletDirectBodyStateSW::singleton=NULL;
