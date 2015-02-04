/*************************************************************************/
/*  bullet_space_sw.h                                                  */
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
#ifndef BULLET_SPACE_SW
#define BULLET_SPACE_SW


#include "scene/3d/physics_body.h"
#include "bullet_body_sw.h"
#include "core/list.h"
#include "bullet/btBulletDynamicsCommon.h"


class BulletBodySW;

class BulletSpaceSW {
	RID self;

	SelfList<BulletBodySW>::List inertia_update_list;

	class PhysicsBodyHelper : public RigidBody {
	public:
		void _update_state(const Transform& p_transform, const Vector3& p_linear_velocity, const Vector3& p_angular_velocity, bool p_is_sleeping) {
			set_ignore_transform_notification(true);
			set_global_transform(p_transform);
			set_linear_velocity(p_linear_velocity);
			set_angular_velocity(p_angular_velocity);
			set_sleeping(p_is_sleeping);
			//if (get_script_instance())
			//	get_script_instance()->call("_integrate_forces",state);
			set_ignore_transform_notification(false);
		}
	};

public:
	btDiscreteDynamicsWorld *discreteDynamicsWorld;
	btCollisionDispatcher *collisionDispatcher;
	btDefaultCollisionConfiguration *collisionConfig;
	btSequentialImpulseConstraintSolver *constraintSolver;
	btDbvtBroadphase *broadphase;
	Set<BulletBodySW*> objects;

	void add_object(BulletBodySW *p_object);
	void remove_object(BulletBodySW *p_object);

	void body_add_to_inertia_update_list(SelfList<BulletBodySW>* p_body);
	void body_remove_from_inertia_update_list(SelfList<BulletBodySW>* p_body);

	void sync();
	void setup();
	void step(float p_delta,int p_iterations);

	void set_param(PhysicsServer::SpaceParameter p_param, real_t p_value);
	real_t get_param(PhysicsServer::SpaceParameter p_param) const;
};


#endif

