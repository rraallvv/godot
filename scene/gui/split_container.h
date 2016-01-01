/*************************************************************************/
/*  split_container.h                                                    */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2016 Juan Linietsky, Ariel Manzur.                 */
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
#ifndef SPLIT_CONTAINER_H
#define SPLIT_CONTAINER_H

#include "scene/gui/container.h"


class SplitContainer : public Container {

	OBJ_TYPE(SplitContainer,Container);

	bool vertical;
	int expand_ofs;
	int middle_sep;
	bool dragging;
	int drag_from;
	int drag_ofs;
	bool collapsed;
	bool dragger_visible;
	bool mouse_inside;


	Control *_getch(int p_idx) const;

	void _resort();
protected:


	void _input_event(const InputEvent& p_event);
	void _notification(int p_what);
	static void _bind_methods();
public:



	void set_split_offset(int p_offset);
	int get_split_offset() const;

	void set_collapsed(bool p_collapsed);
	bool is_collapsed() const;

	void set_dragger_visible(bool p_true);
	bool is_dragger_visible() const;

	virtual CursorShape get_cursor_shape(const Point2& p_pos=Point2i());

	virtual Size2 get_minimum_size() const;

	SplitContainer(bool p_vertical=false);
};


class HSplitContainer : public SplitContainer {

	OBJ_TYPE(HSplitContainer,SplitContainer);

public:

	HSplitContainer() : SplitContainer(false) {set_default_cursor_shape(CURSOR_HSPLIT);}
};


class VSplitContainer : public SplitContainer {

	OBJ_TYPE(VSplitContainer,SplitContainer);

public:

	VSplitContainer() : SplitContainer(true) {set_default_cursor_shape(CURSOR_VSPLIT);}
};

#endif // SPLIT_CONTAINER_H
