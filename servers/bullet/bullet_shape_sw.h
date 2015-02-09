/*************************************************************************/
/*  bullet_shape_sw.h                                                  */
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
#ifndef BULLET_SHAPE_SW
#define BULLET_SHAPE_SW


#include "bullet_body_sw.h"


class btPlaneShape : public btStaticPlaneShape {
public:
	void setImplicitShapeDimensions(const btVector3& planeNormal,btScalar planeConstant) {
		m_planeNormal = planeNormal;
		m_planeConstant = planeConstant;
	}
	void getImplicitShapeDimensions(btVector3& planeNormal,btScalar &planeConstant) {
		planeNormal = m_planeNormal;
		planeConstant = m_planeConstant;
	}
	btPlaneShape(const btVector3& planeNormal,btScalar planeConstant) : btStaticPlaneShape(planeNormal, planeConstant) {}
};


class BulletShapeSW {
	RID self;

	Transform xform;
	Variant data;

	void _update();

public:
	PhysicsServer::ShapeType type;
	btCollisionShape *shape;

	_FORCE_INLINE_ void set_self(const RID& p_self) { self=p_self; }
	_FORCE_INLINE_ RID get_self() const { return self; }

	Variant get_data() const;
	void set_data(const Variant& p_data);

	const Transform& get_transform() const;
	void set_transform(const Transform& p_data);
};


#endif

