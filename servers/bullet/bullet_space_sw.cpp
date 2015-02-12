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

#define SAVE_BULLET

#ifdef SAVE_BULLET
	#include <fstream>
	#include <vector>
#endif

void BulletSpaceSW::add_object(BulletBodySW *p_object) {

	ERR_FAIL_COND( objects.has(p_object) );
	objects.insert(p_object);
}

void BulletSpaceSW::remove_object(BulletBodySW *p_object) {

	ERR_FAIL_COND( !objects.has(p_object) );
	objects.erase(p_object);
}

void BulletSpaceSW::sync() {

}

void BulletSpaceSW::setup() {

	while(inertia_update_list.first()) {
		inertia_update_list.first()->self()->update_inertias();
		inertia_update_list.remove(inertia_update_list.first());
	}
}

void BulletSpaceSW::step(float p_delta,int p_iterations) {

	setup();

	discreteDynamicsWorld->stepSimulation(p_delta, 0);

#ifdef SAVE_BULLET
	static int steps = 1;
	if (steps++ == 100) {
		int maxSerializeBufferSize = 1024*1024*5;
		btDefaultSerializer*	serializer = new btDefaultSerializer(maxSerializeBufferSize);
		//serializer->setSerializationFlags(BT_SERIALIZE_NO_DUPLICATE_ASSERT);

		int i=1;
		std::vector<char*> names;
		for (Set<BulletBodySW*>::Element *E=objects.front();E;E=E->next()) {
			BulletBodySW *body = E->get();
			if (body && body->body) {
				char *name = (char*)malloc(sizeof(char)*32);
				sprintf(name, "body%d", i);
				serializer->registerNameForPointer(body->body,name);
				names.push_back(name);
				printf("%s %s %X %X %X\n", name,  body->body->isStaticObject()?"static":"dynamic", body->body->getBroadphaseHandle()->m_collisionFilterGroup, body->body->getBroadphaseHandle()->m_collisionFilterMask,  body->body->getCollisionFlags());
				i++;
			}
		}
		discreteDynamicsWorld->serialize(serializer);
		size_t size = serializer->getCurrentBufferSize();

		std::ofstream out("saved.bullet");
		out.write((char*)serializer->getBufferPointer(), size);
		out.close();

		printf(">>>saved!\n");

		delete serializer;
		for (auto name=names.begin(); name!=names.end(); ++name)
			free(*name);
	}
#endif
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

void BulletSpaceSW::body_add_to_inertia_update_list(SelfList<BulletBodySW>* p_body) {

	inertia_update_list.add(p_body);
}
void BulletSpaceSW::body_remove_from_inertia_update_list(SelfList<BulletBodySW>* p_body) {

	inertia_update_list.remove(p_body);
}

void BulletSpaceSW::call_queries() {

	for (Set<BulletBodySW*>::Element *E=objects.front();E;E=E->next()) {
		BulletBodySW *body = E->get();
		body->call_queries();
	}

	/*
	while(state_query_list.first()) {

		BulletBodySW * b = state_query_list.first()->self();
		b->call_queries();
		state_query_list.remove(state_query_list.first());
	}

	while(monitor_query_list.first()) {

		AreaSW * a = monitor_query_list.first()->self();
		a->call_queries();
		monitor_query_list.remove(monitor_query_list.first());
	}
	*/
}
