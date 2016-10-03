/*************************************************************************/
/*  style_box.cpp                                                        */
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
#include "style_box.h"

bool StyleBox::test_mask(const Point2& p_point, const Rect2& p_rect) const {

	return true;
}

void StyleBox::set_default_margin(Margin p_margin, float p_value) {

	margin[p_margin]=p_value;
	emit_changed();

}
float StyleBox::get_default_margin(Margin p_margin) const{

	return margin[p_margin];
}

float StyleBox::get_margin(Margin p_margin) const {

	if (margin[p_margin]<0)
		return get_style_margin(p_margin);
	else
		return margin[p_margin];
}

Size2 StyleBox::get_minimum_size() const {

	return Size2( get_margin( MARGIN_LEFT) + get_margin( MARGIN_RIGHT ) , get_margin( MARGIN_TOP) + get_margin( MARGIN_BOTTOM ) );
}


Point2 StyleBox::get_offset() const {

	return Point2( get_margin( MARGIN_LEFT), get_margin( MARGIN_TOP) );
}

Size2 StyleBox::get_center_size() const {

	return Size2();
}

void StyleBox::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("test_mask","point","rect"),&StyleBox::test_mask);

	ObjectTypeDB::bind_method(_MD("set_default_margin","margin","offset"),&StyleBox::set_default_margin);
	ObjectTypeDB::bind_method(_MD("get_default_margin","margin"),&StyleBox::get_default_margin);

//	ObjectTypeDB::bind_method(_MD("set_default_margin"),&StyleBox::set_default_margin);
//	ObjectTypeDB::bind_method(_MD("get_default_margin"),&StyleBox::get_default_margin);

	ObjectTypeDB::bind_method(_MD("get_margin","margin"),&StyleBox::get_margin);
	ObjectTypeDB::bind_method(_MD("get_minimum_size"),&StyleBox::get_minimum_size);
	ObjectTypeDB::bind_method(_MD("get_center_size"),&StyleBox::get_center_size);
	ObjectTypeDB::bind_method(_MD("get_offset"),&StyleBox::get_offset);

	ObjectTypeDB::bind_method(_MD("draw","canvas_item","rect"),&StyleBox::draw);

	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "content_margin/left", PROPERTY_HINT_RANGE,"-1,2048,1" ), _SCS("set_default_margin"),_SCS("get_default_margin"), MARGIN_LEFT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "content_margin/right", PROPERTY_HINT_RANGE,"-1,2048,1" ), _SCS("set_default_margin"),_SCS("get_default_margin"), MARGIN_RIGHT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "content_margin/top", PROPERTY_HINT_RANGE,"-1,2048,1" ), _SCS("set_default_margin"),_SCS("get_default_margin"), MARGIN_TOP);
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "content_margin/bottom", PROPERTY_HINT_RANGE,"-1,2048,1" ), _SCS("set_default_margin"),_SCS("get_default_margin"), MARGIN_BOTTOM );


}

StyleBox::StyleBox() {

	for (int i=0;i<4;i++) {

		margin[i]=-1;
	}
}


void StyleBoxTexture::set_texture(RES p_texture) {

	if (texture==p_texture)
		return;
	texture=p_texture;
	emit_signal("texture_changed");
	emit_changed();

}
RES StyleBoxTexture::get_texture() const {

	return texture;
}

void StyleBoxTexture::set_margin_size(Margin p_margin,float p_size) {

	margin[p_margin]=p_size;
	emit_changed();

}
float StyleBoxTexture::get_margin_size(Margin p_margin) const {

	return margin[p_margin];
}

float StyleBoxTexture::get_style_margin(Margin p_margin) const {

	return margin[p_margin];
}

void StyleBoxTexture::draw(RID p_canvas_item,const Rect2& p_rect) const {
	if (texture.is_null())
		return;

	Rect2 r=p_rect;
	r.pos.x-=expand_margin[MARGIN_LEFT];
	r.pos.y-=expand_margin[MARGIN_TOP];
	r.size.x+=expand_margin[MARGIN_LEFT]+expand_margin[MARGIN_RIGHT];
	r.size.y+=expand_margin[MARGIN_TOP]+expand_margin[MARGIN_BOTTOM];
	VisualServer::get_singleton()->canvas_item_add_nine_patch( p_canvas_item,r,region_rect,texture->get_rid(),Vector2(margin[MARGIN_LEFT],margin[MARGIN_TOP]),Vector2(margin[MARGIN_RIGHT],margin[MARGIN_BOTTOM]),VS::NINE_PATCH_STRETCH,VS::NINE_PATCH_STRETCH,draw_center,modulate);
}

void StyleBoxTexture::set_draw_center(bool p_draw) {

	draw_center=p_draw;
	emit_changed();

}

bool StyleBoxTexture::get_draw_center() const {

	return draw_center;
}

Size2 StyleBoxTexture::get_center_size() const {

	if (texture.is_null())
		return Size2();

	return texture->get_size() - get_minimum_size();
}

void StyleBoxTexture::set_expand_margin_size(Margin p_expand_margin,float p_size) {

	ERR_FAIL_INDEX(p_expand_margin,4);
	expand_margin[p_expand_margin]=p_size;
	emit_changed();

}

float StyleBoxTexture::get_expand_margin_size(Margin p_expand_margin) const {

	ERR_FAIL_INDEX_V(p_expand_margin,4,0);
	return expand_margin[p_expand_margin];
}

void StyleBoxTexture::set_region_rect(const Rect2& p_region_rect) {

	if (region_rect==p_region_rect)
		return;

	region_rect=p_region_rect;
	emit_changed();
}

Rect2 StyleBoxTexture::get_region_rect() const {

	return region_rect;
}


void StyleBoxTexture::set_modulate(const Color& p_modulate) {
	if (modulate==p_modulate)
		return;
	modulate=p_modulate;
	emit_changed();
}

Color StyleBoxTexture::get_modulate() const {

	return modulate;
}


void StyleBoxTexture::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("set_texture","texture:Texture"),&StyleBoxTexture::set_texture);
	ObjectTypeDB::bind_method(_MD("get_texture:Texture"),&StyleBoxTexture::get_texture);

	ObjectTypeDB::bind_method(_MD("set_margin_size","margin","size"),&StyleBoxTexture::set_margin_size);
	ObjectTypeDB::bind_method(_MD("get_margin_size","margin"),&StyleBoxTexture::get_margin_size);

	ObjectTypeDB::bind_method(_MD("set_expand_margin_size","margin","size"),&StyleBoxTexture::set_expand_margin_size);
	ObjectTypeDB::bind_method(_MD("get_expand_margin_size","margin"),&StyleBoxTexture::get_expand_margin_size);

	ObjectTypeDB::bind_method(_MD("set_region_rect","region"),&StyleBoxTexture::set_region_rect);
	ObjectTypeDB::bind_method(_MD("get_region_rect"),&StyleBoxTexture::get_region_rect);

	ObjectTypeDB::bind_method(_MD("set_draw_center","enable"),&StyleBoxTexture::set_draw_center);
	ObjectTypeDB::bind_method(_MD("get_draw_center"),&StyleBoxTexture::get_draw_center);

	ObjectTypeDB::bind_method(_MD("set_modulate","color"),&StyleBoxTexture::set_modulate);
	ObjectTypeDB::bind_method(_MD("get_modulate"),&StyleBoxTexture::get_modulate);


	ADD_SIGNAL(MethodInfo("texture_changed"));

	ADD_PROPERTY( PropertyInfo( Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture" ), _SCS("set_texture"),_SCS("get_texture") );
	ADD_PROPERTYNZ( PropertyInfo( Variant::RECT2, "region_rect"), _SCS("set_region_rect"),_SCS("get_region_rect"));
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "margin/left", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_margin_size"),_SCS("get_margin_size"), MARGIN_LEFT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "margin/right", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_margin_size"),_SCS("get_margin_size"), MARGIN_RIGHT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "margin/top", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_margin_size"),_SCS("get_margin_size"), MARGIN_TOP);
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "margin/bottom", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_margin_size"),_SCS("get_margin_size"), MARGIN_BOTTOM );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "expand_margin/left", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_expand_margin_size"),_SCS("get_expand_margin_size"), MARGIN_LEFT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "expand_margin/right", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_expand_margin_size"),_SCS("get_expand_margin_size"), MARGIN_RIGHT );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "expand_margin/top", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_expand_margin_size"),_SCS("get_expand_margin_size"), MARGIN_TOP );
	ADD_PROPERTYI( PropertyInfo( Variant::REAL, "expand_margin/bottom", PROPERTY_HINT_RANGE,"0,2048,1" ), _SCS("set_expand_margin_size"),_SCS("get_expand_margin_size"), MARGIN_BOTTOM );
	ADD_PROPERTY( PropertyInfo( Variant::COLOR, "modulate/color" ), _SCS("set_modulate"),_SCS("get_modulate"));
	ADD_PROPERTY( PropertyInfo( Variant::BOOL, "draw_center" ) , _SCS("set_draw_center"),_SCS("get_draw_center"));

}

StyleBoxTexture::StyleBoxTexture() {


	for (int i=0;i<4;i++) {
		margin[i]=0;
		expand_margin[i]=0;
	}
	draw_center=true;
	modulate=Color(1,1,1,1);

}
StyleBoxTexture::~StyleBoxTexture() {


}

////////////////

void StyleBoxFlat::set_bg_color(const Color& p_color) {

	bg_color=p_color;
	emit_changed();

}

void StyleBoxFlat::set_light_color(const Color& p_color) {

	light_color=p_color;
	emit_changed();

}
void StyleBoxFlat::set_dark_color(const Color& p_color) {

	dark_color=p_color;
	emit_changed();

}

Color StyleBoxFlat::get_bg_color() const {

	return bg_color;
}
Color StyleBoxFlat::get_light_color() const {

	return light_color;
}
Color StyleBoxFlat::get_dark_color() const {

	return dark_color;
}


void StyleBoxFlat::set_border_size(int p_size) {

	border_size=p_size;
	emit_changed();

}
int StyleBoxFlat::get_border_size() const {

	return border_size;

}

void StyleBoxFlat::set_border_blend(bool p_blend) {

	blend=p_blend;
	emit_changed();

}

bool StyleBoxFlat::get_border_blend() const {

	return blend;

}

void StyleBoxFlat::set_draw_center(bool p_draw) {

	draw_center=p_draw;
	emit_changed();

}
bool StyleBoxFlat::get_draw_center() const {

	return draw_center;
}
Size2 StyleBoxFlat::get_center_size() const {

	return Size2();
}


void StyleBoxFlat::draw(RID p_canvas_item,const Rect2& p_rect) const {

	VisualServer *vs = VisualServer::get_singleton();
	Rect2i r = p_rect;

	for (int i=0;i<border_size;i++) {



		Color color_upleft=light_color;
		Color color_downright=dark_color;

		if (blend) {

			color_upleft.r=(border_size-i)*color_upleft.r/border_size + i*bg_color.r/border_size;
			color_upleft.g=(border_size-i)*color_upleft.g/border_size + i*bg_color.g/border_size;
			color_upleft.b=(border_size-i)*color_upleft.b/border_size + i*bg_color.b/border_size;

			color_downright.r=(border_size-i)*color_downright.r/border_size + i*bg_color.r/border_size;
			color_downright.g=(border_size-i)*color_downright.g/border_size + i*bg_color.g/border_size;
			color_downright.b=(border_size-i)*color_downright.b/border_size + i*bg_color.b/border_size;

		}

		vs->canvas_item_add_rect(p_canvas_item, Rect2(Point2i( r.pos.x,r.pos.y+r.size.y-1), Size2(r.size.x ,1 )),color_downright);
		vs->canvas_item_add_rect(p_canvas_item, Rect2(Point2i( r.pos.x+r.size.x-1,r.pos.y ), Size2( 1 ,r.size.y )), color_downright);

		vs->canvas_item_add_rect(p_canvas_item, Rect2( r.pos, Size2(r.size.x ,1 )), color_upleft);
		vs->canvas_item_add_rect(p_canvas_item, Rect2( r.pos, Size2( 1 ,r.size.y )), color_upleft);


		r.pos.x++;
		r.pos.y++;
		r.size.x-=2;
		r.size.y-=2;
	}

	if (draw_center)
		vs->canvas_item_add_rect(p_canvas_item, Rect2( r.pos, r.size) , bg_color );


}

float StyleBoxFlat::get_style_margin(Margin p_margin) const {

	return border_size;
}
void StyleBoxFlat::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("set_bg_color","color"),&StyleBoxFlat::set_bg_color);
	ObjectTypeDB::bind_method(_MD("get_bg_color"),&StyleBoxFlat::get_bg_color);
	ObjectTypeDB::bind_method(_MD("set_light_color","color"),&StyleBoxFlat::set_light_color);
	ObjectTypeDB::bind_method(_MD("get_light_color"),&StyleBoxFlat::get_light_color);
	ObjectTypeDB::bind_method(_MD("set_dark_color","color"),&StyleBoxFlat::set_dark_color);
	ObjectTypeDB::bind_method(_MD("get_dark_color"),&StyleBoxFlat::get_dark_color);
	ObjectTypeDB::bind_method(_MD("set_border_size","size"),&StyleBoxFlat::set_border_size);
	ObjectTypeDB::bind_method(_MD("get_border_size"),&StyleBoxFlat::get_border_size);
	ObjectTypeDB::bind_method(_MD("set_border_blend","blend"),&StyleBoxFlat::set_border_blend);
	ObjectTypeDB::bind_method(_MD("get_border_blend"),&StyleBoxFlat::get_border_blend);
	ObjectTypeDB::bind_method(_MD("set_draw_center","size"),&StyleBoxFlat::set_draw_center);
	ObjectTypeDB::bind_method(_MD("get_draw_center"),&StyleBoxFlat::get_draw_center);

	ADD_PROPERTY( PropertyInfo( Variant::COLOR, "bg_color"), _SCS("set_bg_color"),_SCS("get_bg_color") );
	ADD_PROPERTY( PropertyInfo( Variant::COLOR, "light_color"),_SCS("set_light_color"),_SCS("get_light_color"));
	ADD_PROPERTY( PropertyInfo( Variant::COLOR, "dark_color"),_SCS("set_dark_color"),_SCS("get_dark_color"));
	ADD_PROPERTY( PropertyInfo( Variant::INT, "border_size",PROPERTY_HINT_RANGE,"0,4096"),_SCS("set_border_size"),_SCS("get_border_size"));
	ADD_PROPERTY( PropertyInfo( Variant::BOOL, "border_blend"),_SCS("set_border_blend"),_SCS("get_border_blend"));
	ADD_PROPERTY( PropertyInfo( Variant::BOOL, "draw_bg"),_SCS("set_draw_center"),_SCS("get_draw_center"));

}

StyleBoxFlat::StyleBoxFlat() {

	bg_color=Color(0.6,0.6,0.6);
	light_color=Color(0.8,0.8,0.8);
	dark_color=Color(0.8,0.8,0.8);
	draw_center=true;
	blend=true;
	border_size=0;

}
StyleBoxFlat::~StyleBoxFlat() {


}

