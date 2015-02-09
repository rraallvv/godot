/*************************************************************************/
/*  bullet_shape_sw.cpp                                                */
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


#include "bullet_shape_sw.h"


Variant BulletShapeSW::get_data() const {

	ERR_FAIL_COND_V(!shape, Variant());

	switch (type) {
		case PhysicsServer::SHAPE_PLANE: {
			btPlaneShape *btShape = (btPlaneShape *)shape;
			btVector3 planeNormal;
			btScalar planeConstant;
			btShape->getImplicitShapeDimensions(planeNormal, planeConstant);
			Plane planeData;
			planeData.normal = Vector3(planeNormal.x(), planeNormal.y(), planeNormal.z());
			planeData.d = planeConstant;
			return planeData;
		}
			break;

		case PhysicsServer::SHAPE_BOX: {
			btBoxShape *btShape = (btBoxShape *)shape;
			btVector3 v = btShape->getLocalScaling();
			Vector3 halfExtents = Vector3(v.x(), v.y(), v.z());
			return halfExtents;
		}
			break;

		default:
			break;
	}

	return Variant();
}

void BulletShapeSW::set_data(const Variant& p_data) {

	ERR_FAIL_COND(!shape);

	switch (type) {
		case PhysicsServer::SHAPE_PLANE: {
			btPlaneShape *btShape = (btPlaneShape *)shape;
			Plane planeData = p_data;
			Vector3 planeNormal = planeData.normal;
			real_t planeConstant = planeData.d;
			btShape->setImplicitShapeDimensions(btVector3(planeNormal.x, planeNormal.y, planeNormal.z), btScalar(planeConstant));
			printf(">>>setting shape data for type %d (%p)\n", type, btShape);
		}
			break;

		case PhysicsServer::SHAPE_BOX: {
			btBoxShape *btShape = (btBoxShape *)shape;

			Vector3 v = p_data;
			btVector3 halfExtents = btVector3(v.x, v.y, v.z);

			//btShape->setSafeMargin(halfExtents);

			//btVector3 margin(btShape->getMargin(),btShape->getMargin(),btShape->getMargin());
			//btVector3 implicitShapeDimensions = (halfExtents * btShape->getLocalScaling()) - margin;
			btShape->setLocalScaling(halfExtents);
			//btShape->setImplicitShapeDimensions(implicitShapeDimensions);

			printf(">>>setting shape data for type %d (%p)\n", type, btShape);
		}
			break;

		default:
			break;
	}
}
