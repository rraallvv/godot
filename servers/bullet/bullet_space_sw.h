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

	class PhysicsBodyHelper : public PhysicsBody {
	public:
		_FORCE_INLINE_ void set_ignore_transform_notification(bool p_ignore) { PhysicsBody::set_ignore_transform_notification(p_ignore); };
	};

public:
	btDiscreteDynamicsWorld *discreteDynamicsWorld;
	btCollisionDispatcher *collisionDispatcher;
	btDefaultCollisionConfiguration *collisionConfig;
	btSequentialImpulseConstraintSolver *constraintSolver;
	btDbvtBroadphase *broadphase;
	List<BulletBodySW*> body_list;

	bool add_body(BulletBodySW *p_body);

	void remove_body(BulletBodySW *p_body);

	void sync();
};


#endif

