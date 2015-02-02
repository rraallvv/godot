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


bool BulletSpaceSW::add_body(BulletBodySW *p_body) {
	return body_list.push_back(p_body);
}

void BulletSpaceSW::remove_body(BulletBodySW *p_body) {
	body_list.erase(p_body);
}

void BulletSpaceSW::sync() {

	Transform transform;
	btTransform btTrans;
	btDefaultMotionState *motionState;

	for (List<BulletBodySW*>::Element *E=body_list.front();E;E=E->next()) {
		BulletBodySW *body = E->get();

		PhysicsBodyHelper *obj = (PhysicsBodyHelper *)ObjectDB::get_instance(body->id);

		if (obj) {

			///printf(">>>(%p)\n", body->body);

			motionState = (btDefaultMotionState*) body->body->getMotionState();

			motionState->getWorldTransform(btTrans);

			btVector3 origin = btTrans.getOrigin();
			btMatrix3x3 basis = btTrans.getBasis();

			//printf(">>>%f\n", origin.y());

			transform.set_origin(Vector3(origin.x(), origin.y(), origin.z()));
			transform.set_basis(Matrix3(basis[0].x(), basis[0].y(), basis[0].z(),
										basis[1].x(), basis[1].y(), basis[1].z(),
										basis[2].x(), basis[2].y(), basis[2].z()));

			obj->set_ignore_transform_notification(true);
			obj->set_transform(transform);
			obj->set_ignore_transform_notification(false);
		}
	}
}
