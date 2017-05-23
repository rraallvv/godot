/*************************************************************************/
/*  godot_array.h                                                        */
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

#ifndef GODOT_ARRAY_H
#define GODOT_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef GODOT_CORE_API_GODOT_ARRAY_TYPE_DEFINED
typedef struct godot_array {
	uint8_t _dont_touch_that[8];
} godot_array;
#endif

#include "godot_pool_arrays.h"
#include "godot_variant.h"

#include "../godot.h"

void GDAPI godot_array_new(godot_array *p_arr);
void GDAPI godot_array_new_pool_color_array(godot_array *p_arr, const godot_pool_color_array *p_pca);
void GDAPI godot_array_new_pool_vector3_array(godot_array *p_arr, const godot_pool_vector3_array *p_pv3a);
void GDAPI godot_array_new_pool_vector2_array(godot_array *p_arr, const godot_pool_vector2_array *p_pv2a);
void GDAPI godot_array_new_pool_string_array(godot_array *p_arr, const godot_pool_string_array *p_psa);
void GDAPI godot_array_new_pool_real_array(godot_array *p_arr, const godot_pool_real_array *p_pra);
void GDAPI godot_array_new_pool_int_array(godot_array *p_arr, const godot_pool_int_array *p_pia);
void GDAPI godot_array_new_pool_byte_array(godot_array *p_arr, const godot_pool_byte_array *p_pba);

void GDAPI godot_array_set(godot_array *p_arr, const godot_int p_idx, const godot_variant *p_value);

godot_variant GDAPI *godot_array_get(const godot_array *p_arr, const godot_int p_idx);

void GDAPI godot_array_append(godot_array *p_arr, const godot_variant *p_value);

void GDAPI godot_array_clear(godot_array *p_arr);

godot_int GDAPI godot_array_count(const godot_array *p_arr, const godot_variant *p_value);

godot_bool GDAPI godot_array_empty(const godot_array *p_arr);

void GDAPI godot_array_erase(godot_array *p_arr, const godot_variant *p_value);

godot_variant GDAPI godot_array_front(const godot_array *p_arr);

godot_variant GDAPI godot_array_back(const godot_array *p_arr);

godot_int GDAPI godot_array_find(const godot_array *p_arr, const godot_variant *p_what, const godot_int p_from);

godot_int GDAPI godot_array_find_last(const godot_array *p_arr, const godot_variant *p_what);

godot_bool GDAPI godot_array_has(const godot_array *p_arr, const godot_variant *p_value);

uint32_t GDAPI godot_array_hash(const godot_array *p_arr);

void GDAPI godot_array_insert(godot_array *p_arr, const godot_int p_pos, const godot_variant *p_value);

void GDAPI godot_array_invert(godot_array *p_arr);

godot_variant GDAPI godot_array_pop_back(godot_array *p_arr);

godot_variant GDAPI godot_array_pop_front(godot_array *p_arr);

void GDAPI godot_array_push_back(godot_array *p_arr, const godot_variant *p_value);

void GDAPI godot_array_push_front(godot_array *p_arr, const godot_variant *p_value);

void GDAPI godot_array_remove(godot_array *p_arr, const godot_int p_idx);

void GDAPI godot_array_resize(godot_array *p_arr, const godot_int p_size);

godot_int GDAPI godot_array_rfind(const godot_array *p_arr, const godot_variant *p_what, const godot_int p_from);

godot_int GDAPI godot_array_size(const godot_array *p_arr);

void GDAPI godot_array_sort(godot_array *p_arr);

void GDAPI godot_array_sort_custom(godot_array *p_arr, godot_object *p_obj, const godot_string *p_func);

void GDAPI godot_array_destroy(godot_array *p_arr);

#ifdef __cplusplus
}
#endif

#endif // GODOT_ARRAY_H
