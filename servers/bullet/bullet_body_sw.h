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


class BulletSpaceSW;
class BulletShapeSW;

class BulletBodySW {
	RID self;
	BulletSpaceSW *space = NULL;

	void _set_transform(const Transform& p_transform);
	Transform _get_transform() const;
	void _set_space(BulletSpaceSW *p_space);

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

};

#endif

