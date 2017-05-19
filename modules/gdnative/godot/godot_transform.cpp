/*************************************************************************/
/*  godot_transform.cpp                                                  */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
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
#include "godot_transform.h"
#include "core/variant.h"

#include "core/math/transform.h"

#ifdef __cplusplus
extern "C" {
#endif

void _transform_api_anchor() {}

void GDAPI godot_transform_new_with_axis_origin(godot_transform *r_dest, const godot_vector3 *p_x_axis, const godot_vector3 *p_y_axis, const godot_vector3 *p_z_axis, const godot_vector3 *p_origin) {
	const Vector3 *x_axis = (const Vector3 *)p_x_axis;
	const Vector3 *y_axis = (const Vector3 *)p_y_axis;
	const Vector3 *z_axis = (const Vector3 *)p_z_axis;
	const Vector3 *origin = (const Vector3 *)p_origin;
	Transform *dest = (Transform *)r_dest;
	dest->basis.set_axis(0, *x_axis);
	dest->basis.set_axis(1, *y_axis);
	dest->basis.set_axis(2, *z_axis);
	dest->origin = *origin;
}

void GDAPI godot_transform_new(godot_transform *r_dest, const godot_basis *p_basis, const godot_vector3 *p_origin) {
	const Basis *basis = (const Basis *)p_basis;
	const Vector3 *origin = (const Vector3 *)p_origin;
	Transform *dest = (Transform *)r_dest;
	*dest = Transform(*basis, *origin);
}

godot_string GDAPI godot_transform_as_string(const godot_transform *p_self) {
	godot_string ret;
	const Transform *self = (const Transform *)p_self;
	memnew_placement(&ret, String(*self));
	return ret;
}

godot_transform GDAPI godot_transform_inverse(const godot_transform *p_self) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->inverse();
	return dest;
}

godot_transform GDAPI godot_transform_affine_inverse(const godot_transform *p_self) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->affine_inverse();
	return dest;
}

godot_transform GDAPI godot_transform_orthonormalized(const godot_transform *p_self) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	*((Transform *)&dest) = self->orthonormalized();
	return dest;
}

godot_transform GDAPI godot_transform_rotated(const godot_transform *p_self, const godot_vector3 *p_axis, const godot_real p_phi) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *axis = (const Vector3 *)p_axis;
	*((Transform *)&dest) = self->rotated(*axis, p_phi);
	return dest;
}

godot_transform GDAPI godot_transform_scaled(const godot_transform *p_self, const godot_vector3 *p_scale) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *scale = (const Vector3 *)p_scale;
	*((Transform *)&dest) = self->scaled(*scale);
	return dest;
}

godot_transform GDAPI godot_transform_translated(const godot_transform *p_self, const godot_vector3 *p_ofs) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *ofs = (const Vector3 *)p_ofs;
	*((Transform *)&dest) = self->translated(*ofs);
	return dest;
}

godot_transform GDAPI godot_transform_looking_at(const godot_transform *p_self, const godot_vector3 *p_target, const godot_vector3 *p_up) {
	godot_transform dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *target = (const Vector3 *)p_target;
	const Vector3 *up = (const Vector3 *)p_up;
	*((Transform *)&dest) = self->looking_at(*target, *up);
	return dest;
}

godot_plane GDAPI godot_transform_xform_plane(const godot_transform *p_self, const godot_plane *p_v) {
	godot_plane raw_dest;
	Plane *dest = (Plane *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Plane *v = (const Plane *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

godot_plane GDAPI godot_transform_xform_inv_plane(const godot_transform *p_self, const godot_plane *p_v) {
	godot_plane raw_dest;
	Plane *dest = (Plane *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Plane *v = (const Plane *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

void GDAPI godot_transform_new_identity(godot_transform *r_dest) {
	Transform *dest = (Transform *)r_dest;
	*dest = Transform();
}

godot_bool GDAPI godot_transform_operator_equal(const godot_transform *p_self, const godot_transform *p_b) {
	const Transform *self = (const Transform *)p_self;
	const Transform *b = (const Transform *)p_b;
	return *self == *b;
}

godot_transform GDAPI godot_transform_operator_multiply(const godot_transform *p_self, const godot_transform *p_b) {
	godot_transform raw_dest;
	Transform *dest = (Transform *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Transform *b = (const Transform *)p_b;
	*dest = *self * *b;
	return raw_dest;
}

godot_vector3 GDAPI godot_transform_xform_vector3(const godot_transform *p_self, const godot_vector3 *p_v) {
	godot_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

godot_vector3 GDAPI godot_transform_xform_inv_vector3(const godot_transform *p_self, const godot_vector3 *p_v) {
	godot_vector3 raw_dest;
	Vector3 *dest = (Vector3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Vector3 *v = (const Vector3 *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

godot_rect3 GDAPI godot_transform_xform_rect3(const godot_transform *p_self, const godot_rect3 *p_v) {
	godot_rect3 raw_dest;
	Rect3 *dest = (Rect3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Rect3 *v = (const Rect3 *)p_v;
	*dest = self->xform(*v);
	return raw_dest;
}

godot_rect3 GDAPI godot_transform_xform_inv_rect3(const godot_transform *p_self, const godot_rect3 *p_v) {
	godot_rect3 raw_dest;
	Rect3 *dest = (Rect3 *)&raw_dest;
	const Transform *self = (const Transform *)p_self;
	const Rect3 *v = (const Rect3 *)p_v;
	*dest = self->xform_inv(*v);
	return raw_dest;
}

#ifdef __cplusplus
}
#endif
