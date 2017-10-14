/*************************************************************************/
/*  arvr_interface_gdnative.cpp                                          */
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

#include "arvr_interface_gdnative.h"
#include "main/input_default.h"
#include "servers/arvr/arvr_positional_tracker.h"
#include "servers/visual/visual_server_global.h"

ARVRInterfaceGDNative::ARVRInterfaceGDNative() {
	// testing
	printf("Construct gdnative interface\n");

	// we won't have our data pointer until our library gets set
	data = NULL;
}

ARVRInterfaceGDNative::~ARVRInterfaceGDNative() {
	printf("Destruct gdnative interface\n");

	if (is_initialized()) {
		uninitialize();
	};

	// cleanup after ourselves
	cleanup();
}

void ARVRInterfaceGDNative::cleanup() {
	if (data != NULL) {
		// library->call_native_raw("arvr_call_destructor", "godot_arvr_destructor", data, 0, NULL, NULL);
		data = NULL;
	};

	if (library.is_valid()) {
		library->terminate();
	};
};

void ARVRInterfaceGDNative::set_gdnative_library(Ref<GDNativeLibrary> p_library) {
	if (library.is_null()) {
		library.instance();
	} else {
		cleanup();
	};

	library->set_library(p_library);
	library->initialize();

	// Now we do our constructing...
	void *parameters[1];
	parameters[0] = (void *)this;
	// library->call_native_raw("arvr_call_constructor", "godot_arvr_constructor", NULL, 1, parameters, &data);
}

StringName ARVRInterfaceGDNative::get_name() const {
	StringName name;

	ERR_FAIL_COND_V(data == NULL, StringName());

	// const_cast<GDNative *>(library.ptr())->call_native_raw("arvr_return_string", "godot_arvr_get_name", data, 0, NULL, &name);

	return name;
}

int ARVRInterfaceGDNative::get_capabilities() const {
	int capabilities;

	ERR_FAIL_COND_V(data == NULL, 0); // 0 = None

	// const_cast<GDNative *>(library.ptr())->call_native_raw("arvr_return_int", "godot_arvr_get_capabilities", data, 0, NULL, &capabilities);

	return capabilities;
};

bool ARVRInterfaceGDNative::get_anchor_detection_is_enabled() const {
	bool enabled;

	ERR_FAIL_COND_V(data == NULL, false);

	// const_cast<GDNative *>(library.ptr())->call_native_raw("arvr_return_bool", "godot_arvr_get_anchor_detection_is_enabled", data, 0, NULL, &enabled);

	return enabled;
};

void ARVRInterfaceGDNative::set_anchor_detection_is_enabled(bool p_enable) {
	void *parameters[1];

	ERR_FAIL_COND(data == NULL);

	parameters[0] = (void *)&p_enable;
	// library->call_native_raw("arvr_set_bool", "godot_arvr_set_anchor_detection_is_enabled", data, 1, parameters, NULL);
};

bool ARVRInterfaceGDNative::is_stereo() {
	bool stereo;

	ERR_FAIL_COND_V(data == NULL, false);

	// library->call_native_raw("arvr_return_bool", "godot_arvr_is_stereo", data, 0, NULL, &stereo);

	return stereo;
};

bool ARVRInterfaceGDNative::is_initialized() {
	bool initialized;

	ERR_FAIL_COND_V(data == NULL, false);

	// library->call_native_raw("arvr_return_bool", "godot_arvr_is_initialized", data, 0, NULL, &initialized);

	return initialized;
};

bool ARVRInterfaceGDNative::initialize() {
	bool initialized;

	ERR_FAIL_COND_V(data == NULL, false);

	// library->call_native_raw("arvr_return_bool", "godot_arvr_initialize", data, 0, NULL, &initialized);

	if (initialized) {
		// if we successfully initialize our interface and we don't have a primary interface yet, this becomes our primary interface

		ARVRServer *arvr_server = ARVRServer::get_singleton();
		if ((arvr_server != NULL) && (arvr_server->get_primary_interface() == NULL)) {
			arvr_server->set_primary_interface(this);
		};
	};

	return initialized;
}

void ARVRInterfaceGDNative::uninitialize() {
	ERR_FAIL_COND(data == NULL);

	ARVRServer *arvr_server = ARVRServer::get_singleton();
	if (arvr_server != NULL) {
		// Whatever happens, make sure this is no longer our primary interface
		arvr_server->clear_primary_interface_if(this);
	}

	// library->call_native_raw("arvr_call_method", "godot_arvr_uninitialize", data, 0, NULL, NULL);
}

Size2 ARVRInterfaceGDNative::get_recommended_render_targetsize() {
	Size2 size;

	ERR_FAIL_COND_V(data == NULL, Size2());

	// library->call_native_raw("arvr_return_vector2", "godot_arvr_get_recommended_render_targetsize", data, 0, NULL, &size);

	return size;
}

Transform ARVRInterfaceGDNative::get_transform_for_eye(ARVRInterface::Eyes p_eye, const Transform &p_cam_transform) {
	void *parameters[2];
	Transform ret;

	ERR_FAIL_COND_V(data == NULL, Transform());

	parameters[0] = (void *)&p_eye;
	parameters[1] = (void *)&p_cam_transform;
	// library->call_native_raw("arvr_return_transform_for_eye", "godot_arvr_get_transform_for_eye", data, 2, parameters, &ret);

	return ret;
}

CameraMatrix ARVRInterfaceGDNative::get_projection_for_eye(ARVRInterface::Eyes p_eye, real_t p_aspect, real_t p_z_near, real_t p_z_far) {
	void *parameters[5];
	CameraMatrix cm;

	ERR_FAIL_COND_V(data == NULL, CameraMatrix());

	parameters[0] = (void *)cm.matrix;
	parameters[1] = (void *)&p_eye;
	parameters[2] = (void *)&p_aspect;
	parameters[3] = (void *)&p_z_near;
	parameters[4] = (void *)&p_z_far;
	// library->call_native_raw("arvr_call_fill_projection_for_eye", "godot_arvr_fill_projection_for_eye", data, 5, parameters, NULL);

	return cm;
}

void ARVRInterfaceGDNative::commit_for_eye(ARVRInterface::Eyes p_eye, RID p_render_target, const Rect2 &p_screen_rect) {
	void *parameters[3];

	ERR_FAIL_COND(data == NULL);

	parameters[0] = (void *)&p_eye;
	parameters[1] = (void *)&p_render_target;
	parameters[2] = (void *)&p_screen_rect;
	// library->call_native_raw("arvr_call_commit_for_eye", "godot_arvr_commit_for_eye", data, 3, parameters, NULL);
}

void ARVRInterfaceGDNative::process() {
	ERR_FAIL_COND(data == NULL);

	// library->call_native_raw("arvr_call_method", "godot_arvr_process", data, 0, NULL, NULL);
}

void ARVRInterfaceGDNative::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_gdnative_library", "library"), &ARVRInterfaceGDNative::set_gdnative_library);
}

/////////////////////////////////////////////////////////////////////////////////////
// some helper callbacks

godot_real GDAPI godot_arvr_get_worldscale() {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL_V(arvr_server, 1.0);

	return arvr_server->get_world_scale();
};

godot_transform GDAPI godot_arvr_get_reference_frame() {
	godot_transform reference_frame;
	Transform *reference_frame_ptr = (Transform *)&reference_frame;

	ARVRServer *arvr_server = ARVRServer::get_singleton();
	if (arvr_server != NULL) {
		*reference_frame_ptr = arvr_server->get_reference_frame();
	} else {
		godot_transform_new_identity(&reference_frame);
	};

	return reference_frame;
};

void GDAPI godot_arvr_blit(godot_int p_eye, godot_rid *p_render_target, godot_rect2 *p_rect) {
	// blits out our texture as is, handy for preview display of one of the eyes that is already rendered with lens distortion on an external HMD
	ARVRInterface::Eyes eye = (ARVRInterface::Eyes)p_eye;
	RID *render_target = (RID *)p_render_target;
	Rect2 screen_rect = *(Rect2 *)p_rect;

	if (eye == ARVRInterface::EYE_LEFT) {
		screen_rect.size.x /= 2.0;
	} else if (p_eye == ARVRInterface::EYE_RIGHT) {
		screen_rect.size.x /= 2.0;
		screen_rect.position.x += screen_rect.size.x;
	}

	VSG::rasterizer->set_current_render_target(RID());
	VSG::rasterizer->blit_render_target_to_screen(*render_target, screen_rect, 0);
};

godot_int GDAPI godot_arvr_get_texid(godot_rid *p_render_target) {
	// In order to send off our textures to display on our hardware we need the opengl texture ID instead of the render target RID
	// This is a handy function to expose that.
	RID *render_target = (RID *)p_render_target;

	RID eye_texture = VSG::storage->render_target_get_texture(*render_target);
	uint32_t texid = VS::get_singleton()->texture_get_texid(eye_texture);

	return texid;
};

godot_int GDAPI godot_arvr_add_controller(char *p_device_name, godot_int p_hand, godot_bool p_tracks_orientation, godot_bool p_tracks_position) {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL_V(arvr_server, 0);

	InputDefault *input = (InputDefault *)Input::get_singleton();
	ERR_FAIL_NULL_V(input, 0);

	ARVRPositionalTracker *new_tracker = memnew(ARVRPositionalTracker);
	new_tracker->set_name(p_device_name);
	new_tracker->set_type(ARVRServer::TRACKER_CONTROLLER);
	if (p_hand == 1) {
		new_tracker->set_hand(ARVRPositionalTracker::TRACKER_LEFT_HAND);
	} else if (p_hand == 2) {
		new_tracker->set_hand(ARVRPositionalTracker::TRACKER_RIGHT_HAND);
	};

	// also register as joystick...
	int joyid = input->get_unused_joy_id();
	if (joyid != -1) {
		new_tracker->set_joy_id(joyid);
		input->joy_connection_changed(joyid, true, p_device_name, "");
	};

	if (p_tracks_orientation) {
		Basis orientation;
		new_tracker->set_orientation(orientation);
	};
	if (p_tracks_position) {
		Vector3 position;
		new_tracker->set_position(position);
	};

	// add our tracker to our server and remember its pointer
	arvr_server->add_tracker(new_tracker);

	// note, this ID is only unique within controllers!
	return new_tracker->get_tracker_id();
};

void GDAPI godot_arvr_remove_controller(godot_int p_controller_id) {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL(arvr_server);

	InputDefault *input = (InputDefault *)Input::get_singleton();
	ERR_FAIL_NULL(input);

	ARVRPositionalTracker *remove_tracker = arvr_server->find_by_type_and_id(ARVRServer::TRACKER_CONTROLLER, p_controller_id);
	if (remove_tracker != NULL) {
		// unset our joystick if applicable
		int joyid = remove_tracker->get_joy_id();
		if (joyid != -1) {
			input->joy_connection_changed(joyid, false, "", "");
			remove_tracker->set_joy_id(-1);
		};

		// remove our tracker from our server
		arvr_server->remove_tracker(remove_tracker);
		memdelete(remove_tracker);
	};
};

void GDAPI godot_arvr_set_controller_transform(godot_int p_controller_id, godot_transform *p_transform, godot_bool p_tracks_orientation, godot_bool p_tracks_position) {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL(arvr_server);

	ARVRPositionalTracker *tracker = arvr_server->find_by_type_and_id(ARVRServer::TRACKER_CONTROLLER, p_controller_id);
	if (tracker != NULL) {
		Transform *transform = (Transform *)p_transform;
		if (p_tracks_orientation) {
			tracker->set_orientation(transform->basis);
		};
		if (p_tracks_position) {
			tracker->set_position(transform->origin);
		};
	};
};

void GDAPI godot_arvr_set_controller_button(godot_int p_controller_id, godot_int p_button, godot_bool p_is_pressed) {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL(arvr_server);

	InputDefault *input = (InputDefault *)Input::get_singleton();
	ERR_FAIL_NULL(input);

	ARVRPositionalTracker *tracker = arvr_server->find_by_type_and_id(ARVRServer::TRACKER_CONTROLLER, p_controller_id);
	if (tracker != NULL) {
		int joyid = tracker->get_joy_id();
		if (joyid != -1) {
			input->joy_button(joyid, p_button, p_is_pressed);
		};
	};
};

void GDAPI godot_arvr_set_controller_axis(godot_int p_controller_id, godot_int p_axis, godot_real p_value, godot_bool p_can_be_negative) {
	ARVRServer *arvr_server = ARVRServer::get_singleton();
	ERR_FAIL_NULL(arvr_server);

	InputDefault *input = (InputDefault *)Input::get_singleton();
	ERR_FAIL_NULL(input);

	ARVRPositionalTracker *tracker = arvr_server->find_by_type_and_id(ARVRServer::TRACKER_CONTROLLER, p_controller_id);
	if (tracker != NULL) {
		int joyid = tracker->get_joy_id();
		if (joyid != -1) {
			InputDefault::JoyAxis jx;
			jx.min = p_can_be_negative ? -1 : 0;
			jx.value = p_value;
			input->joy_axis(joyid, p_axis, jx);
		};
	};
};
