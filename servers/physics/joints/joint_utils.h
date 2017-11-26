/*************************************************************************/
/*  joint_utils.h                                                        */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
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

/*
Adapted to Godot from the Bullet library.
*/

/*
Bullet Continuous Collision Detection and Physics Library
ConeTwistJointSW is Copyright (c) 2007 Starbreeze Studios

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Written by: Marcus Hennix
*/

#ifndef JOINT_UTILS_H
#define JOINT_UTILS_H

static void plane_space(const Vector3 &n, Vector3 &p, Vector3 &q) {

	if (Math::abs(n.z) > 0.707106781186547524400844362) {
		// choose p in y-z plane
		real_t a = n[1] * n[1] + n[2] * n[2];
		real_t k = 1.0 / Math::sqrt(a);
		p = Vector3(0, -n[2] * k, n[1] * k);
		// set q = n x p
		q = Vector3(a * k, -n[0] * p[2], n[0] * p[1]);
	} else {
		// choose p in x-y plane
		real_t a = n.x * n.x + n.y * n.y;
		real_t k = 1.0 / Math::sqrt(a);
		p = Vector3(-n.y * k, n.x * k, 0);
		// set q = n x p
		q = Vector3(-n.z * p.y, n.z * p.x, a * k);
	}
}

static _FORCE_INLINE_ real_t atan2fast(real_t y, real_t x) {
	real_t coeff_1 = Math_PI / 4.0f;
	real_t coeff_2 = 3.0f * coeff_1;
	real_t abs_y = Math::abs(y);
	real_t angle;
	if (x >= 0.0f) {
		real_t r = (x - abs_y) / (x + abs_y);
		angle = coeff_1 - coeff_1 * r;
	} else {
		real_t r = (x + abs_y) / (abs_y - x);
		angle = coeff_2 - coeff_1 * r;
	}
	return (y < 0.0f) ? -angle : angle;
}

#endif // JOINT_UTILS_H
