/*************************************************************************/
/*  bullet_body_sw.h                                                  */
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
#ifndef BULLET_BODY_SW
#define BULLET_BODY_SW


#include "servers/physics_server.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/self_list.h"


class BulletSpaceSW;
class BulletShapeSW;

class BulletBodySW {
	RID self;
	BulletSpaceSW *space = NULL;

	SelfList<BulletBodySW> inertia_update_list;

	void _set_transform(const Transform& p_transform);
	Transform _get_transform() const;
	void _set_space(BulletSpaceSW *p_space);
	void _update_inertia();

public:

	ObjectID id;

	PhysicsServer::BodyMode mode;
	btRigidBody *body;
	btScalar mass;

	BulletSpaceSW *get_space();
	void set_space(BulletSpaceSW *p_space);
	void add_shape(BulletShapeSW *p_shape,const Transform& p_transform);
	void remove_shape(int p_shape_idx);
	int get_shape_count();
	void set_state(PhysicsServer::BodyState p_state, const Variant& p_variant);
	void set_param(PhysicsServer::BodyParameter p_param, float p_value);
	Variant get_state(PhysicsServer::BodyState p_state) const;
	void update_inertias();
	void set_force_integration_callback(ObjectID p_id,const StringName& p_method,const Variant& p_udata);

	BulletBodySW();
};

class BulletDirectBodyStateSW : public PhysicsDirectBodyState {

	OBJ_TYPE( BulletDirectBodyStateSW, PhysicsDirectBodyState );

public:

	static BulletDirectBodyStateSW *singleton;
	BulletBodySW *body;
	real_t step;

	virtual Vector3 get_total_gravity() const {
		return Vector3();
//		return body->get_gravity();
	} // get gravity vector working on this body space/area
	virtual float get_total_density() const {
		return 1.0;
//		return body->get_density();
	} // get density of this body space/area

	virtual float get_inverse_mass() const {
		return 0.0;
//		return body->get_inv_mass();
	} // get the mass
	virtual Vector3 get_inverse_inertia() const {
		return Vector3();
//		return body->get_inv_inertia();
	} // get density of this body space
	virtual Matrix3 get_inverse_inertia_tensor() const {
		return Matrix3();
//		return body->get_inv_inertia_tensor();
	} // get density of this body space

	virtual void set_linear_velocity(const Vector3& p_velocity) {
		return;
//		body->set_linear_velocity(p_velocity);
	}
	virtual Vector3 get_linear_velocity() const {
		Vector3();
//		return body->get_linear_velocity();
	}

	virtual void set_angular_velocity(const Vector3& p_velocity) {
		return;
//		body->set_angular_velocity(p_velocity);
	}
	virtual Vector3 get_angular_velocity() const {
		return Vector3();
//		return body->get_angular_velocity();
	}

	virtual void set_transform(const Transform& p_transform) {
		return;
//		body->set_state(PhysicsServer::BODY_STATE_TRANSFORM,p_transform);
	}
	virtual Transform get_transform() const {
		return Transform();
//		return body->get_transform();
	}

	virtual void add_force(const Vector3& p_force, const Vector3& p_pos) {
		return;
//		body->add_force(p_force,p_pos);
	}
	virtual void apply_impulse(const Vector3& p_pos, const Vector3& p_j) {
		return;
//		body->apply_impulse(p_pos,p_j);
	}

	virtual void set_sleep_state(bool p_enable) {
		return;
//		body->set_active(!p_enable);
	}
	virtual bool is_sleeping() const {
		return true;
//		return !body->is_active();
	}

	virtual int get_contact_count() const {
		return 0;
//		return body->contact_count;
	}

	virtual Vector3 get_contact_local_pos(int p_contact_idx) const {
		return Vector3();
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,Vector3());
//		return body->contacts[p_contact_idx].local_pos;
	}
	virtual Vector3 get_contact_local_normal(int p_contact_idx) const {
		return Vector3();
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,Vector3());
//		return body->contacts[p_contact_idx].local_normal;
	}
	virtual int get_contact_local_shape(int p_contact_idx) const {
		return -1;
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,-1);
//		return body->contacts[p_contact_idx].local_shape;
	}

	virtual RID get_contact_collider(int p_contact_idx) const {
		return RID();
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,RID());
//		return body->contacts[p_contact_idx].collider;
	}
	virtual Vector3 get_contact_collider_pos(int p_contact_idx) const {
		return Vector3();
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,Vector3());
//		return body->contacts[p_contact_idx].collider_pos;
	}
	virtual ObjectID get_contact_collider_id(int p_contact_idx) const {
		return 0;
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,0);
//		return body->contacts[p_contact_idx].collider_instance_id;
	}
	virtual int get_contact_collider_shape(int p_contact_idx) const {
		return 0;
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,0);
//		return body->contacts[p_contact_idx].collider_shape;
	}
	virtual Vector3 get_contact_collider_velocity_at_pos(int p_contact_idx) const {
		return Vector3();
//		ERR_FAIL_INDEX_V(p_contact_idx,body->contact_count,Vector3());
//		return body->contacts[p_contact_idx].collider_velocity_at_pos;
	}

	virtual PhysicsDirectSpaceState* get_space_state() {
		return NULL;
//		return body->get_space()->get_direct_state();
	}


	virtual real_t get_step() const { return step; }
	BulletDirectBodyStateSW() {
		singleton=this;
		body=NULL;
	}
};

#endif
