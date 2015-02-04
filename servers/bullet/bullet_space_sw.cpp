/*************************************************************************/
/*  bullet_space_sw.cpp                                                */
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

#include "bullet_space_sw.h"


void BulletSpaceSW::add_object(BulletBodySW *p_object) {

	ERR_FAIL_COND( objects.has(p_object) );
	objects.insert(p_object);
}

void BulletSpaceSW::remove_object(BulletBodySW *p_object) {

	ERR_FAIL_COND( !objects.has(p_object) );
	objects.erase(p_object);
}

void BulletSpaceSW::sync() {

	Transform transform;
	btTransform btTrans;
	btDefaultMotionState *motionState;

	for (Set<BulletBodySW*>::Element *E=objects.front();E;E=E->next()) {
		BulletBodySW *body = E->get();

		PhysicsBodyHelper *obj = (PhysicsBodyHelper *)ObjectDB::get_instance(body->id);

		if (obj) {

			motionState = (btDefaultMotionState*) body->body->getMotionState();

			motionState->getWorldTransform(btTrans);

			btVector3 origin = btTrans.getOrigin();
			btMatrix3x3 basis = btTrans.getBasis();

			transform.set_origin(Vector3(origin.x(), origin.y(), origin.z()));
			transform.set_basis(Matrix3(basis[0].x(), basis[0].y(), basis[0].z(),
										basis[1].x(), basis[1].y(), basis[1].z(),
										basis[2].x(), basis[2].y(), basis[2].z()));

			btVector3 v = body->body->getLinearVelocity();
			btVector3 av = body->body->getAngularVelocity();
			Vector3 linear_velovity = Vector3(v.x(), v.y(), v.z());
			Vector3 angular_velovity = Vector3(av.x(), av.y(), av.z());
			bool is_sleeping = !body->body->isActive();

			obj->_update_state(transform, linear_velovity, angular_velovity, is_sleeping);
		}
	}
}

void BulletSpaceSW::set_param(PhysicsServer::SpaceParameter p_param, real_t p_value) {

	switch(p_param) {

		case PhysicsServer::SPACE_PARAM_CONTACT_RECYCLE_RADIUS: /*contact_recycle_radius=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_CONTACT_MAX_SEPARATION: /*contact_max_separation=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_BODY_MAX_ALLOWED_PENETRATION: /*contact_max_allowed_penetration=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_BODY_LINEAR_VELOCITY_SLEEP_TRESHOLD: /*body_linear_velocity_sleep_threshold=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_BODY_ANGULAR_VELOCITY_SLEEP_TRESHOLD: /*body_angular_velocity_sleep_threshold=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_BODY_TIME_TO_SLEEP: /*body_time_to_sleep=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_BODY_ANGULAR_VELOCITY_DAMP_RATIO: /*body_angular_velocity_damp_ratio=p_value;*/ break;
		case PhysicsServer::SPACE_PARAM_CONSTRAINT_DEFAULT_BIAS: /*constraint_bias=p_value;*/ break;
	}
}

real_t BulletSpaceSW::get_param(PhysicsServer::SpaceParameter p_param) const {

	switch(p_param) {

		case PhysicsServer::SPACE_PARAM_CONTACT_RECYCLE_RADIUS: /*return contact_recycle_radius;*/
		case PhysicsServer::SPACE_PARAM_CONTACT_MAX_SEPARATION: /*return contact_max_separation;*/
		case PhysicsServer::SPACE_PARAM_BODY_MAX_ALLOWED_PENETRATION: /*return contact_max_allowed_penetration;*/
		case PhysicsServer::SPACE_PARAM_BODY_LINEAR_VELOCITY_SLEEP_TRESHOLD: /*return body_linear_velocity_sleep_threshold;*/
		case PhysicsServer::SPACE_PARAM_BODY_ANGULAR_VELOCITY_SLEEP_TRESHOLD: /*return body_angular_velocity_sleep_threshold;*/
		case PhysicsServer::SPACE_PARAM_BODY_TIME_TO_SLEEP: /*return body_time_to_sleep;*/
		case PhysicsServer::SPACE_PARAM_BODY_ANGULAR_VELOCITY_DAMP_RATIO: /*return body_angular_velocity_damp_ratio;*/
		case PhysicsServer::SPACE_PARAM_CONSTRAINT_DEFAULT_BIAS: /*return constraint_bias;*/
			break;
	}
	return 0;
}
