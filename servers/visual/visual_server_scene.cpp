#include "visual_server_scene.h"
#include "visual_server_global.h"

/* CAMERA API */


RID VisualServerScene::camera_create() {

	Camera * camera = memnew( Camera );
	return camera_owner.make_rid( camera );

}

void VisualServerScene::camera_set_perspective(RID p_camera,float p_fovy_degrees, float p_z_near, float p_z_far) {

	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);
	camera->type=Camera::PERSPECTIVE;
	camera->fov=p_fovy_degrees;
	camera->znear=p_z_near;
	camera->zfar=p_z_far;

}

void VisualServerScene::camera_set_orthogonal(RID p_camera,float p_size, float p_z_near, float p_z_far) {

	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);
	camera->type=Camera::ORTHOGONAL;
	camera->size=p_size;
	camera->znear=p_z_near;
	camera->zfar=p_z_far;
}

void VisualServerScene::camera_set_transform(RID p_camera,const Transform& p_transform) {

	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);
	camera->transform=p_transform.orthonormalized();


}

void VisualServerScene::camera_set_cull_mask(RID p_camera,uint32_t p_layers) {


	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);

	camera->visible_layers=p_layers;

}

void VisualServerScene::camera_set_environment(RID p_camera,RID p_env) {

	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);
	camera->env=p_env;

}


void VisualServerScene::camera_set_use_vertical_aspect(RID p_camera,bool p_enable) {

	Camera *camera = camera_owner.get( p_camera );
	ERR_FAIL_COND(!camera);
	camera->vaspect=p_enable;

}



/* ENVIRONMENT API */

RID VisualServerScene::environment_create(){

	return RID();
}

void VisualServerScene::environment_set_background(RID p_env,VS::EnvironmentBG p_bg){

}
void VisualServerScene::environment_set_skybox(RID p_env,RID p_skybox,float p_energy){

}
void VisualServerScene::environment_set_bg_color(RID p_env,const Color& p_color){

}
void VisualServerScene::environment_set_canvas_max_layer(RID p_env,int p_max_layer){

}
void VisualServerScene::environment_set_ambient_light(RID p_env,const Color& p_color,float p_energy){

}

void VisualServerScene::environment_set_glow(RID p_env,bool p_enable,int p_radius,float p_intensity,float p_strength,float p_bloom_treshold,VS::EnvironmentGlowBlendMode p_blend_mode){

}
void VisualServerScene::environment_set_fog(RID p_env,bool p_enable,float p_begin,float p_end,RID p_gradient_texture){

}

void VisualServerScene::environment_set_tonemap(RID p_env,bool p_enable,float p_exposure,float p_white,float p_min_luminance,float p_max_luminance,float p_auto_exp_speed,VS::EnvironmentToneMapper p_tone_mapper){

}
void VisualServerScene::environment_set_brightness(RID p_env,bool p_enable,float p_brightness){

}
void VisualServerScene::environment_set_contrast(RID p_env,bool p_enable,float p_contrast){

}
void VisualServerScene::environment_set_saturation(RID p_env,bool p_enable,float p_saturation){

}
void VisualServerScene::environment_set_color_correction(RID p_env,bool p_enable,RID p_ramp){

}


/* SCENARIO API */



void* VisualServerScene::_instance_pair(void *p_self, OctreeElementID, Instance *p_A,int, OctreeElementID, Instance *p_B,int) {

//	VisualServerScene *self = (VisualServerScene*)p_self;
	Instance *A = p_A;
	Instance *B = p_B;

	//instance indices are designed so greater always contains lesser
	if (A->base_type > B->base_type) {
		SWAP(A,B); //lesser always first
	}

	if (B->base_type==VS::INSTANCE_LIGHT && (1<<A->base_type)&VS::INSTANCE_GEOMETRY_MASK) {

		InstanceLightData * light = static_cast<InstanceLightData*>(B->base_data);
		InstanceGeometryData * geom = static_cast<InstanceGeometryData*>(A->base_data);


		InstanceLightData::PairInfo pinfo;
		pinfo.geometry=A;
		pinfo.L = geom->lighting.push_back(B);

		List<InstanceLightData::PairInfo>::Element *E = light->geometries.push_back(pinfo);

		light->shadow_sirty=true;
		geom->lighting_dirty=true;

		return E; //this element should make freeing faster
	}

#if 0
	if (A->base_type==INSTANCE_PORTAL) {

		ERR_FAIL_COND_V( B->base_type!=INSTANCE_PORTAL,NULL );

		A->portal_info->candidate_set.insert(B);
		B->portal_info->candidate_set.insert(A);

		self->_portal_attempt_connect(A);
		//attempt to conncet portal A (will go through B anyway)
		//this is a little hackish, but works fine in practice

	} else if (A->base_type==INSTANCE_BAKED_LIGHT || B->base_type==INSTANCE_BAKED_LIGHT) {

		if (B->base_type==INSTANCE_BAKED_LIGHT) {
			SWAP(A,B);
		}

		ERR_FAIL_COND_V(B->base_type!=INSTANCE_BAKED_LIGHT_SAMPLER,NULL);
		B->baked_light_sampler_info->baked_lights.insert(A);

	} else if (A->base_type==INSTANCE_ROOM || B->base_type==INSTANCE_ROOM) {

		if (B->base_type==INSTANCE_ROOM)
			SWAP(A,B);

		ERR_FAIL_COND_V(! ((1<<B->base_type)&INSTANCE_GEOMETRY_MASK ),NULL);

		B->auto_rooms.insert(A);
		A->room_info->owned_autoroom_geometry.insert(B);

		self->_instance_validate_autorooms(B);


	} else {

		if (B->base_type==INSTANCE_LIGHT) {

			SWAP(A,B);
		} else if (A->base_type!=INSTANCE_LIGHT) {
			return NULL;
		}


		A->light_info->affected.insert(B);
		B->lights.insert(A);
		B->light_cache_dirty=true;


	}
#endif

	return NULL;

}
void VisualServerScene::_instance_unpair(void *p_self, OctreeElementID, Instance *p_A,int, OctreeElementID, Instance *p_B,int,void* udata) {

//	VisualServerScene *self = (VisualServerScene*)p_self;
	Instance *A = p_A;
	Instance *B = p_B;

	//instance indices are designed so greater always contains lesser
	if (A->base_type > B->base_type) {
		SWAP(A,B); //lesser always first
	}



	if (B->base_type==VS::INSTANCE_LIGHT && (1<<A->base_type)&VS::INSTANCE_GEOMETRY_MASK) {

		InstanceLightData * light = static_cast<InstanceLightData*>(B->base_data);
		InstanceGeometryData * geom = static_cast<InstanceGeometryData*>(A->base_data);

		List<InstanceLightData::PairInfo>::Element *E = reinterpret_cast<List<InstanceLightData::PairInfo>::Element*>(udata);

		geom->lighting.erase(E->get().L);
		light->geometries.erase(E);

		light->shadow_sirty=true;
		geom->lighting_dirty=true;


	}
#if 0
	if (A->base_type==INSTANCE_PORTAL) {

		ERR_FAIL_COND( B->base_type!=INSTANCE_PORTAL );


		A->portal_info->candidate_set.erase(B);
		B->portal_info->candidate_set.erase(A);

		//after disconnecting them, see if they can connect again
		self->_portal_attempt_connect(A);
		self->_portal_attempt_connect(B);

	} else if (A->base_type==INSTANCE_BAKED_LIGHT || B->base_type==INSTANCE_BAKED_LIGHT) {

		if (B->base_type==INSTANCE_BAKED_LIGHT) {
			SWAP(A,B);
		}

		ERR_FAIL_COND(B->base_type!=INSTANCE_BAKED_LIGHT_SAMPLER);
		B->baked_light_sampler_info->baked_lights.erase(A);

	} else if (A->base_type==INSTANCE_ROOM || B->base_type==INSTANCE_ROOM) {

		if (B->base_type==INSTANCE_ROOM)
			SWAP(A,B);

		ERR_FAIL_COND(! ((1<<B->base_type)&INSTANCE_GEOMETRY_MASK ));

		B->auto_rooms.erase(A);
		B->valid_auto_rooms.erase(A);
		A->room_info->owned_autoroom_geometry.erase(B);

	}else {



	if (B->base_type==INSTANCE_LIGHT) {

			SWAP(A,B);
		} else if (A->base_type!=INSTANCE_LIGHT) {
			return;
		}


		A->light_info->affected.erase(B);
		B->lights.erase(A);
		B->light_cache_dirty=true;

	}
#endif
}

RID VisualServerScene::scenario_create() {

	Scenario *scenario = memnew( Scenario );
	ERR_FAIL_COND_V(!scenario,RID());
	RID scenario_rid = scenario_owner.make_rid( scenario );
	scenario->self=scenario_rid;

	scenario->octree.set_pair_callback(_instance_pair,this);
	scenario->octree.set_unpair_callback(_instance_unpair,this);

	return scenario_rid;
}

void VisualServerScene::scenario_set_debug(RID p_scenario,VS::ScenarioDebugMode p_debug_mode) {

	Scenario *scenario = scenario_owner.get(p_scenario);
	ERR_FAIL_COND(!scenario);
	scenario->debug=p_debug_mode;
}

void VisualServerScene::scenario_set_environment(RID p_scenario, RID p_environment) {

	Scenario *scenario = scenario_owner.get(p_scenario);
	ERR_FAIL_COND(!scenario);
	scenario->environment=p_environment;

}

void VisualServerScene::scenario_set_fallback_environment(RID p_scenario, RID p_environment) {


	Scenario *scenario = scenario_owner.get(p_scenario);
	ERR_FAIL_COND(!scenario);
	scenario->fallback_environment=p_environment;


}



/* INSTANCING API */

void VisualServerScene::_instance_queue_update(Instance *p_instance,bool p_update_aabb,bool p_update_materials) {

	if (p_update_aabb)
		p_instance->update_aabb=true;
	if (p_update_materials)
		p_instance->update_materials=true;

	if (p_instance->update_item.in_list())
		return;

	_instance_update_list.add(&p_instance->update_item);


}

// from can be mesh, light,  area and portal so far.
RID VisualServerScene::instance_create(){

	Instance *instance = memnew( Instance );
	ERR_FAIL_COND_V(!instance,RID());

	RID instance_rid = instance_owner.make_rid(instance);
	instance->self=instance_rid;


	return instance_rid;


}

void VisualServerScene::instance_set_base(RID p_instance, RID p_base){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	Scenario *scenario = instance->scenario;

	if (instance->base_type!=VS::INSTANCE_NONE) {
		//free anything related to that base

		VSG::storage->instance_remove_dependency(instance->base,instance);

		if (scenario && instance->octree_id) {
			scenario->octree.erase(instance->octree_id); //make dependencies generated by the octree go away
			instance->octree_id=0;
		}

		switch(instance->base_type) {
			case VS::INSTANCE_LIGHT: {

				InstanceLightData *light = static_cast<InstanceLightData*>(instance->base_data);

				if (instance->scenario && light->D) {
					instance->scenario->directional_lights.erase( light->D );
					light->D=NULL;
				}
				VSG::scene_render->free(light->instance);

			}
		}

		if (instance->base_data) {
			memdelete( instance->base_data );
			instance->base_data=NULL;
		}

		instance->morph_values.clear();
		instance->materials.clear();

#if 0
		if (instance->light_info) {

			if (instance->scenario && instance->light_info->D)
				instance->scenario->directional_lights.erase( instance->light_info->D );
			rasterizer->free(instance->light_info->instance);
			memdelete(instance->light_info);
			instance->light_info=NULL;
		}



		if ( instance->room ) {

			instance_set_room(p_instance,RID());
			/*
			if((1<<instance->base_type)&INSTANCE_GEOMETRY_MASK)
				instance->room->room_info->owned_geometry_instances.erase(instance->RE);
			else if (instance->base_type==INSTANCE_PORTAL) {
				print_line("freeing portal, is it there? "+itos(instance->room->room_info->owned_portal_instances.(instance->RE)));
				instance->room->room_info->owned_portal_instances.erase(instance->RE);
			} else if (instance->base_type==INSTANCE_ROOM)
				instance->room->room_info->owned_room_instances.erase(instance->RE);
			else if (instance->base_type==INSTANCE_LIGHT)
				instance->room->room_info->owned_light_instances.erase(instance->RE);

			instance->RE=NULL;*/
		}






		if (instance->portal_info) {

			_portal_disconnect(instance,true);
			memdelete(instance->portal_info);
			instance->portal_info=NULL;

		}

		if (instance->baked_light_info) {

			while(instance->baked_light_info->owned_instances.size()) {

				Instance *owned=instance->baked_light_info->owned_instances.front()->get();
				owned->baked_light=NULL;
				owned->data.baked_light=NULL;
				owned->data.baked_light_octree_xform=NULL;
				owned->BLE=NULL;
				instance->baked_light_info->owned_instances.pop_front();
			}

			memdelete(instance->baked_light_info);
			instance->baked_light_info=NULL;

		}

		if (instance->scenario && instance->octree_id) {
			instance->scenario->octree.erase( instance->octree_id );
			instance->octree_id=0;
		}


		if (instance->room_info) {

			for(List<Instance*>::Element *E=instance->room_info->owned_geometry_instances.front();E;E=E->next()) {

				Instance *owned = E->get();
				owned->room=NULL;
				owned->RE=NULL;
			}
			for(List<Instance*>::Element *E=instance->room_info->owned_portal_instances.front();E;E=E->next()) {

				_portal_disconnect(E->get(),true);
				Instance *owned = E->get();
				owned->room=NULL;
				owned->RE=NULL;
			}

			for(List<Instance*>::Element *E=instance->room_info->owned_room_instances.front();E;E=E->next()) {

				Instance *owned = E->get();
				owned->room=NULL;
				owned->RE=NULL;
			}

			if (instance->room_info->disconnected_child_portals.size()) {
				ERR_PRINT("BUG: Disconnected portals remain!");
			}
			memdelete(instance->room_info);
			instance->room_info=NULL;

		}

		if (instance->particles_info) {

			rasterizer->free( instance->particles_info->instance );
			memdelete(instance->particles_info);
			instance->particles_info=NULL;

		}

		if (instance->baked_light_sampler_info) {

			while (instance->baked_light_sampler_info->owned_instances.size()) {

				instance_geometry_set_baked_light_sampler(instance->baked_light_sampler_info->owned_instances.front()->get()->self,RID());
			}

			if (instance->baked_light_sampler_info->sampled_light.is_valid()) {
				rasterizer->free(instance->baked_light_sampler_info->sampled_light);
			}
			memdelete( instance->baked_light_sampler_info );
			instance->baked_light_sampler_info=NULL;
		}
#endif

	}


	instance->base_type=VS::INSTANCE_NONE;
	instance->base=RID();


	if (p_base.is_valid()) {

		instance->base_type=VSG::storage->get_base_type(p_base);
		ERR_FAIL_COND(instance->base_type==VS::INSTANCE_NONE);

		switch(instance->base_type) {
			case VS::INSTANCE_LIGHT: {

				InstanceLightData *light = memnew( InstanceLightData );

				if (scenario && VSG::storage->light_get_type(p_base)==VS::LIGHT_DIRECTIONAL) {
					light->D = scenario->directional_lights.push_back(instance);
				}

				light->instance = VSG::scene_render->light_instance_create(p_base);

				instance->base_data=light;
			}
			case VS::INSTANCE_MESH: {

				InstanceGeometryData *geom = memnew( InstanceGeometryData );
				instance->base_data=geom;
			}

		}

		VSG::storage->instance_add_dependency(p_base,instance);

		instance->base=p_base;

		if (scenario)
			_instance_queue_update(instance,true,true);


#if 0
		if (rasterizer->is_mesh(p_base)) {
			instance->base_type=INSTANCE_MESH;
			instance->data.morph_values.resize( rasterizer->mesh_get_morph_target_count(p_base));
			instance->data.materials.resize( rasterizer->mesh_get_surface_count(p_base));
		} else if (rasterizer->is_multimesh(p_base)) {
			instance->base_type=INSTANCE_MULTIMESH;
		} else if (rasterizer->is_immediate(p_base)) {
			instance->base_type=INSTANCE_IMMEDIATE;
		} else if (rasterizer->is_particles(p_base)) {
			instance->base_type=INSTANCE_PARTICLES;
			instance->particles_info=memnew( Instance::ParticlesInfo );
			instance->particles_info->instance = rasterizer->particles_instance_create( p_base );
		} else if (rasterizer->is_light(p_base)) {

			instance->base_type=INSTANCE_LIGHT;
			instance->light_info = memnew( Instance::LightInfo );
			instance->light_info->instance = rasterizer->light_instance_create(p_base);
			if (instance->scenario && rasterizer->light_get_type(p_base)==LIGHT_DIRECTIONAL) {

				instance->light_info->D = instance->scenario->directional_lights.push_back(instance->self);
			}

		} else if (room_owner.owns(p_base)) {
			instance->base_type=INSTANCE_ROOM;
			instance->room_info  = memnew( Instance::RoomInfo );
			instance->room_info->room=room_owner.get(p_base);
		} else if (portal_owner.owns(p_base)) {

			instance->base_type=INSTANCE_PORTAL;
			instance->portal_info = memnew(Instance::PortalInfo);
			instance->portal_info->portal=portal_owner.get(p_base);
		} else if (baked_light_owner.owns(p_base)) {

			instance->base_type=INSTANCE_BAKED_LIGHT;
			instance->baked_light_info=memnew(Instance::BakedLightInfo);
			instance->baked_light_info->baked_light=baked_light_owner.get(p_base);

			//instance->portal_info = memnew(Instance::PortalInfo);
			//instance->portal_info->portal=portal_owner.get(p_base);
		} else if (baked_light_sampler_owner.owns(p_base)) {


			instance->base_type=INSTANCE_BAKED_LIGHT_SAMPLER;
			instance->baked_light_sampler_info=memnew( Instance::BakedLightSamplerInfo);
			instance->baked_light_sampler_info->sampler=baked_light_sampler_owner.get(p_base);

			//instance->portal_info = memnew(Instance::PortalInfo);
			//instance->portal_info->portal=portal_owner.get(p_base);

		} else {
			ERR_EXPLAIN("Invalid base RID for instance!")
			ERR_FAIL();
		}

		instance_dependency_map[ p_base ].insert( instance->self );
#endif


	}
}
void VisualServerScene::instance_set_scenario(RID p_instance, RID p_scenario){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	if (instance->scenario) {

		instance->scenario->instances.remove( &instance->scenario_item );

		if (instance->octree_id) {
			instance->scenario->octree.erase(instance->octree_id); //make dependencies generated by the octree go away
			instance->octree_id=0;
		}


		switch(instance->base_type) {

			case VS::INSTANCE_LIGHT: {


				InstanceLightData *light = static_cast<InstanceLightData*>(instance->base_data);

				if (light->D) {
					instance->scenario->directional_lights.erase( light->D );
					light->D=NULL;
				}
			}
		}

		instance->scenario=NULL;
	}


	if (p_scenario.is_valid()) {

		Scenario *scenario = scenario_owner.get( p_scenario );
		ERR_FAIL_COND(!scenario);

		instance->scenario=scenario;

		scenario->instances.add( &instance->scenario_item );


		switch(instance->base_type) {

			case VS::INSTANCE_LIGHT: {


				InstanceLightData *light = static_cast<InstanceLightData*>(instance->base_data);

				if (VSG::storage->light_get_type(instance->base)==VS::LIGHT_DIRECTIONAL) {
					light->D = scenario->directional_lights.push_back(instance);
				}
			}
		}

		_instance_queue_update(instance,true,true);
	}
}
void VisualServerScene::instance_set_layer_mask(RID p_instance, uint32_t p_mask){


	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	instance->layer_mask=p_mask;
}
void VisualServerScene::instance_set_transform(RID p_instance, const Transform& p_transform){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	if (instance->transform==p_transform)
		return; //must be checked to avoid worst evil

	instance->transform=p_transform;
	_instance_queue_update(instance,true);
}
void VisualServerScene::instance_attach_object_instance_ID(RID p_instance,ObjectID p_ID){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	instance->object_ID=p_ID;

}
void VisualServerScene::instance_set_morph_target_weight(RID p_instance,int p_shape, float p_weight){

}
void VisualServerScene::instance_set_surface_material(RID p_instance,int p_surface, RID p_material){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	_update_dirty_instance(instance);

	ERR_FAIL_INDEX(p_surface,instance->materials.size());

	instance->materials[p_surface]=p_material;

}

void VisualServerScene::instance_attach_skeleton(RID p_instance,RID p_skeleton){

	Instance *instance = instance_owner.get( p_instance );
	ERR_FAIL_COND( !instance );

	instance->skeleton=p_skeleton;

	_instance_queue_update(instance,true);
}

void VisualServerScene::instance_set_exterior( RID p_instance, bool p_enabled ){

}
void VisualServerScene::instance_set_room( RID p_instance, RID p_room ){

}

void VisualServerScene::instance_set_extra_visibility_margin( RID p_instance, real_t p_margin ){

}

// don't use these in a game!
Vector<ObjectID> VisualServerScene::instances_cull_aabb(const AABB& p_aabb, RID p_scenario) const{

	return Vector<ObjectID>();
}

Vector<ObjectID> VisualServerScene::instances_cull_ray(const Vector3& p_from, const Vector3& p_to, RID p_scenario) const{

	return Vector<ObjectID>();
}
Vector<ObjectID> VisualServerScene::instances_cull_convex(const Vector<Plane>& p_convex, RID p_scenario) const {

	return Vector<ObjectID>();
}


void VisualServerScene::instance_geometry_set_flag(RID p_instance,VS::InstanceFlags p_flags,bool p_enabled){

}
void VisualServerScene::instance_geometry_set_cast_shadows_setting(RID p_instance, VS::ShadowCastingSetting p_shadow_casting_setting) {

}
void VisualServerScene::instance_geometry_set_material_override(RID p_instance, RID p_material){

}


void VisualServerScene::instance_geometry_set_draw_range(RID p_instance,float p_min,float p_max,float p_min_margin,float p_max_margin){

}
void VisualServerScene::instance_geometry_set_as_instance_lod(RID p_instance,RID p_as_lod_of_instance){

}


void VisualServerScene::_update_instance(Instance *p_instance) {

	p_instance->version++;

	if (p_instance->base_type == VS::INSTANCE_LIGHT) {

		InstanceLightData *light = static_cast<InstanceLightData*>(p_instance->base_data);

		VSG::scene_render->light_instance_set_transform( light->instance, p_instance->transform );

	}


	if (p_instance->aabb.has_no_surface())
		return;

#if 0
	if (p_instance->base_type == VS::INSTANCE_PARTICLES) {

		rasterizer->particles_instance_set_transform( p_instance->particles_info->instance, p_instance->data.transform );
	}

#endif
	if ((1<<p_instance->base_type)&VS::INSTANCE_GEOMETRY_MASK) {

		InstanceGeometryData *geom = static_cast<InstanceGeometryData*>(p_instance->base_data);
		//make sure lights are updated

		for (List<Instance*>::Element *E=geom->lighting.front();E;E=E->next()) {
			InstanceLightData *light = static_cast<InstanceLightData*>(E->get()->base_data);
			light->shadow_sirty=true;
		}

	}
#if 0
	else if (p_instance->base_type == INSTANCE_ROOM) {

		p_instance->room_info->affine_inverse=p_instance->data.transform.affine_inverse();
	} else if (p_instance->base_type == INSTANCE_BAKED_LIGHT) {

		Transform scale;
		scale.basis.scale(p_instance->baked_light_info->baked_light->octree_aabb.size);
		scale.origin=p_instance->baked_light_info->baked_light->octree_aabb.pos;
		//print_line("scale: "+scale);
		p_instance->baked_light_info->affine_inverse=(p_instance->data.transform*scale).affine_inverse();
	}


#endif

	p_instance->mirror = p_instance->transform.basis.determinant() < 0.0;

	AABB new_aabb;
#if 0
	if (p_instance->base_type==INSTANCE_PORTAL) {

		//portals need to be transformed in a special way, so they don't become too wide if they have scale..
		Transform portal_xform = p_instance->data.transform;
		portal_xform.basis.set_axis(2,portal_xform.basis.get_axis(2).normalized());

		p_instance->portal_info->plane_cache=Plane( p_instance->data.transform.origin, portal_xform.basis.get_axis(2));
		int point_count=p_instance->portal_info->portal->shape.size();
		p_instance->portal_info->transformed_point_cache.resize(point_count);

		AABB portal_aabb;

		for(int i=0;i<point_count;i++) {

			Point2 src = p_instance->portal_info->portal->shape[i];
			Vector3 point = portal_xform.xform(Vector3(src.x,src.y,0));
			p_instance->portal_info->transformed_point_cache[i]=point;
			if (i==0)
				portal_aabb.pos=point;
			else
				portal_aabb.expand_to(point);
		}

		portal_aabb.grow_by(p_instance->portal_info->portal->connect_range);

		new_aabb = portal_aabb;

	} else {
#endif
		new_aabb = p_instance->transform.xform(p_instance->aabb);
#if 0
	}
#endif


	p_instance->transformed_aabb=new_aabb;

	if (!p_instance->scenario) {

		return;
	}



	if (p_instance->octree_id==0) {

		uint32_t base_type = 1<<p_instance->base_type;
		uint32_t pairable_mask=0;
		bool pairable=false;

		if (p_instance->base_type == VS::INSTANCE_LIGHT) {

			pairable_mask=p_instance->visible?VS::INSTANCE_GEOMETRY_MASK:0;
			pairable=true;
		}
#if 0

		if (p_instance->base_type == VS::INSTANCE_PORTAL) {

			pairable_mask=(1<<INSTANCE_PORTAL);
			pairable=true;
		}

		if (p_instance->base_type == VS::INSTANCE_BAKED_LIGHT_SAMPLER) {

			pairable_mask=(1<<INSTANCE_BAKED_LIGHT);
			pairable=true;
		}


		if (!p_instance->room && (1<<p_instance->base_type)&VS::INSTANCE_GEOMETRY_MASK) {

			base_type|=VS::INSTANCE_ROOMLESS_MASK;
		}

		if (p_instance->base_type == VS::INSTANCE_ROOM) {

			pairable_mask=INSTANCE_ROOMLESS_MASK;
			pairable=true;
		}
#endif

		// not inside octree
		p_instance->octree_id = p_instance->scenario->octree.create(p_instance,new_aabb,0,pairable,base_type,pairable_mask);

	} else {

	//	if (new_aabb==p_instance->data.transformed_aabb)
	//		return;

		p_instance->scenario->octree.move(p_instance->octree_id,new_aabb);
	}
#if 0
	if (p_instance->base_type==INSTANCE_PORTAL) {

		_portal_attempt_connect(p_instance);
	}

	if (!p_instance->room && (1<<p_instance->base_type)&INSTANCE_GEOMETRY_MASK) {

		_instance_validate_autorooms(p_instance);
	}

	if (p_instance->base_type == INSTANCE_ROOM) {

		for(Set<Instance*>::Element *E=p_instance->room_info->owned_autoroom_geometry.front();E;E=E->next())
			_instance_validate_autorooms(E->get());
	}
#endif

}

void VisualServerScene::_update_instance_aabb(Instance *p_instance) {

	AABB new_aabb;

	ERR_FAIL_COND(p_instance->base_type!=VS::INSTANCE_NONE && !p_instance->base.is_valid());

	switch(p_instance->base_type) {
		case VisualServer::INSTANCE_NONE: {

			// do nothing
		} break;
		case VisualServer::INSTANCE_MESH: {

			new_aabb = VSG::storage->mesh_get_aabb(p_instance->base,p_instance->skeleton);

		} break;
#if 0
		case VisualServer::INSTANCE_MULTIMESH: {

			new_aabb = rasterizer->multimesh_get_aabb(p_instance->base);

		} break;
		case VisualServer::INSTANCE_IMMEDIATE: {

			new_aabb = rasterizer->immediate_get_aabb(p_instance->base);


		} break;
		case VisualServer::INSTANCE_PARTICLES: {

			new_aabb = rasterizer->particles_get_aabb(p_instance->base);


		} break;
#endif
		case VisualServer::INSTANCE_LIGHT: {

			new_aabb = VSG::storage->light_get_aabb(p_instance->base);

		} break;
#if 0
		case VisualServer::INSTANCE_ROOM: {

			Room *room = room_owner.get( p_instance->base );
			ERR_FAIL_COND(!room);
			new_aabb=room->bounds.get_aabb();

		} break;
		case VisualServer::INSTANCE_PORTAL: {

			Portal *portal = portal_owner.get( p_instance->base );
			ERR_FAIL_COND(!portal);
			for (int i=0;i<portal->shape.size();i++) {

				Vector3 point( portal->shape[i].x, portal->shape[i].y, 0 );
				if (i==0) {

					new_aabb.pos=point;
					new_aabb.size.z=0.01; // make it not flat for octree
				} else {

					new_aabb.expand_to(point);
				}
			}

		} break;
		case VisualServer::INSTANCE_BAKED_LIGHT: {

			BakedLight *baked_light = baked_light_owner.get( p_instance->base );
			ERR_FAIL_COND(!baked_light);
			new_aabb=baked_light->octree_aabb;

		} break;
		case VisualServer::INSTANCE_BAKED_LIGHT_SAMPLER: {

			BakedLightSampler *baked_light_sampler = baked_light_sampler_owner.get( p_instance->base );
			ERR_FAIL_COND(!baked_light_sampler);
			float radius = baked_light_sampler->params[VS::BAKED_LIGHT_SAMPLER_RADIUS];

			new_aabb=AABB(Vector3(-radius,-radius,-radius),Vector3(radius*2,radius*2,radius*2));

		} break;
#endif
		default: {}
	}

	if (p_instance->extra_margin)
		new_aabb.grow_by(p_instance->extra_margin);

	p_instance->aabb=new_aabb;

}



void VisualServerScene::render_camera(RID p_camera, RID p_scenario,Size2 p_viewport_size) {



	Camera *camera = camera_owner.getornull(p_camera);
	ERR_FAIL_COND(!camera);

	Scenario *scenario = scenario_owner.getornull(p_scenario);

	render_pass++;
	uint32_t camera_layer_mask=camera->visible_layers;


	/* STEP 1 - SETUP CAMERA */
	CameraMatrix camera_matrix;
	bool ortho=false;

	switch(camera->type) {
		case Camera::ORTHOGONAL: {

			camera_matrix.set_orthogonal(
				camera->size,
				p_viewport_size.width / (float)p_viewport_size.height,
				camera->znear,
				camera->zfar,
				camera->vaspect

			);
			ortho=true;
		} break;
		case Camera::PERSPECTIVE: {

			camera_matrix.set_perspective(
				camera->fov,
				p_viewport_size.width / (float)p_viewport_size.height,
				camera->znear,
				camera->zfar,
				camera->vaspect

			);
			ortho=false;

		} break;
	}


//	rasterizer->set_camera(camera->transform, camera_matrix,ortho);

	Vector<Plane> planes = camera_matrix.get_projection_planes(camera->transform);

	Plane near_plane(camera->transform.origin,-camera->transform.basis.get_axis(2).normalized());

	/* STEP 2 - CULL */
	int cull_count = scenario->octree.cull_convex(planes,instance_cull_result,MAX_INSTANCE_CULL);
	light_cull_count=0;
//	light_samplers_culled=0;

/*	print_line("OT: "+rtos( (OS::get_singleton()->get_ticks_usec()-t)/1000.0));
	print_line("OTO: "+itos(p_scenario->octree.get_octant_count()));
//	print_line("OTE: "+itos(p_scenario->octree.get_elem_count()));
	print_line("OTP: "+itos(p_scenario->octree.get_pair_count()));
*/

	/* STEP 3 - PROCESS PORTALS, VALIDATE ROOMS */


	// compute portals
#if 0
	exterior_visited=false;
	exterior_portal_cull_count=0;

	if (room_cull_enabled) {
		for(int i=0;i<cull_count;i++) {

			Instance *ins = instance_cull_result[i];
			ins->last_render_pass=render_pass;

			if (ins->base_type!=INSTANCE_PORTAL)
				continue;

			if (ins->room)
				continue;

			ERR_CONTINUE(exterior_portal_cull_count>=MAX_EXTERIOR_PORTALS);
			exterior_portal_cull_result[exterior_portal_cull_count++]=ins;

		}

		room_cull_count = p_scenario->octree.cull_point(camera->transform.origin,room_cull_result,MAX_ROOM_CULL,NULL,(1<<INSTANCE_ROOM)|(1<<INSTANCE_PORTAL));


		Set<Instance*> current_rooms;
		Set<Instance*> portal_rooms;
		//add to set
		for(int i=0;i<room_cull_count;i++) {

			if (room_cull_result[i]->base_type==INSTANCE_ROOM) {
				current_rooms.insert(room_cull_result[i]);
			}
			if (room_cull_result[i]->base_type==INSTANCE_PORTAL) {
				//assume inside that room if also inside the portal..
				if (room_cull_result[i]->room) {
					portal_rooms.insert(room_cull_result[i]->room);
				}

				SWAP(room_cull_result[i],room_cull_result[room_cull_count-1]);
				room_cull_count--;
				i--;
			}
		}

		//remove from set if it has a parent room or BSP doesn't contain
		for(int i=0;i<room_cull_count;i++) {
			Instance *r = room_cull_result[i];

			//check inside BSP
			Vector3 room_local_point = r->room_info->affine_inverse.xform( camera->transform.origin );

			if (!portal_rooms.has(r) && !r->room_info->room->bounds.point_is_inside(room_local_point)) {

				current_rooms.erase(r);
				continue;
			}

			//check parent
			while (r->room) {// has parent room

				current_rooms.erase(r);
				r=r->room;
			}

		}

		if (current_rooms.size()) {
			//camera is inside a room
			// go through rooms
			for(Set<Instance*>::Element *E=current_rooms.front();E;E=E->next()) {
				_cull_room(camera,E->get());
			}

		} else {
			//start from exterior
			_cull_room(camera,NULL);

		}
	}

#endif
	/* STEP 4 - REMOVE FURTHER CULLED OBJECTS, ADD LIGHTS */

	for(int i=0;i<cull_count;i++) {

		Instance *ins = instance_cull_result[i];

		bool keep=false;


		if ((camera_layer_mask&ins->layer_mask)==0) {

			//failure
		} else if (ins->base_type==VS::INSTANCE_LIGHT && ins->visible) {

			if (light_cull_count<MAX_LIGHTS_CULLED) {

				InstanceLightData * light = static_cast<InstanceLightData*>(ins->base_data);

				if (!light->geometries.empty()) {
					//do not add this light if no geometry is affected by it..
					light_cull_result[light_cull_count]=ins;
					light_instance_cull_result[light_cull_count]=light->instance;

					light_cull_count++;
				}

//				rasterizer->light_instance_set_active_hint(ins->light_info->instance);
			}

		} else if ((1<<ins->base_type)&VS::INSTANCE_GEOMETRY_MASK && ins->visible && ins->cast_shadows!=VS::SHADOW_CASTING_SETTING_SHADOWS_ONLY) {

			keep=true;
#if 0
			bool discarded=false;

			if (ins->draw_range_end>0) {

				float d = cull_range.nearp.distance_to(ins->data.transform.origin);
				if (d<0)
					d=0;
				discarded=(d<ins->draw_range_begin || d>=ins->draw_range_end);


			}

			if (!discarded) {

				// test if this geometry should be visible

				if (room_cull_enabled) {


					if (ins->visible_in_all_rooms) {
						keep=true;
					} else if (ins->room) {

						if (ins->room->room_info->last_visited_pass==render_pass)
							keep=true;
					} else if (ins->auto_rooms.size()) {


						for(Set<Instance*>::Element *E=ins->auto_rooms.front();E;E=E->next()) {

							if (E->get()->room_info->last_visited_pass==render_pass) {
								keep=true;
								break;
							}
						}
					} else if(exterior_visited)
						keep=true;
				} else {

					keep=true;
				}


			}


			if (keep) {
				// update cull range
				float min,max;
				ins->transformed_aabb.project_range_in_plane(cull_range.nearp,min,max);

				if (min<cull_range.min)
					cull_range.min=min;
				if (max>cull_range.max)
					cull_range.max=max;

				if (ins->sampled_light && ins->sampled_light->baked_light_sampler_info->last_pass!=render_pass) {
					if (light_samplers_culled<MAX_LIGHT_SAMPLERS) {
						light_sampler_cull_result[light_samplers_culled++]=ins->sampled_light;
						ins->sampled_light->baked_light_sampler_info->last_pass=render_pass;
					}
				}
			}
#endif


			InstanceGeometryData * geom = static_cast<InstanceGeometryData*>(ins->base_data);

			if (geom->lighting_dirty) {
				int l=0;
				//only called when lights AABB enter/exit this geometry
				ins->light_instances.resize(geom->lighting.size());

				for (List<Instance*>::Element *E=geom->lighting.front();E;E=E->next()) {

					InstanceLightData * light = static_cast<InstanceLightData*>(E->get()->base_data);

					ins->light_instances[l++]=light->instance;
				}

				geom->lighting_dirty=false;
			}

		}

		if (!keep) {
			// remove, no reason to keep
			cull_count--;
			SWAP( instance_cull_result[i], instance_cull_result[ cull_count ] );
			i--;
			ins->last_render_pass=0; // make invalid
		} else {

			ins->last_render_pass=render_pass;
		}
	}

	/* STEP 5 - PROCESS LIGHTS */

	RID *directional_light_ptr=&light_instance_cull_result[light_cull_count];
	int directional_light_count=0;

	// directional lights
	{
		for (List<Instance*>::Element *E=scenario->directional_lights.front();E;E=E->next()) {

			if (light_cull_count+directional_light_count>=MAX_LIGHTS_CULLED) {
				break;
			}

			if (!E->get()->visible)
				continue;

			InstanceLightData * light = static_cast<InstanceLightData*>(E->get()->base_data);


			//check shadow..


/*			if (light && light->light_info->enabled && rasterizer->light_has_shadow(light->base_rid)) {
				//rasterizer->light_instance_set_active_hint(light->light_info->instance);
				_light_instance_update_shadow(light,p_scenario,camera,cull_range);
			}
*/

			//add to list


			directional_light_ptr[directional_light_count++]=light->instance;

		}
	}

#if 0
	{ //this should eventually change to
		//assign shadows by distance to camera
		SortArray<Instance*,_InstanceLightsort> sorter;
		sorter.sort(light_cull_result,light_cull_count);
		for (int i=0;i<light_cull_count;i++) {

			Instance *ins = light_cull_result[i];

			if (!rasterizer->light_has_shadow(ins->base_rid) || !shadows_enabled)
				continue;

			/* for far shadows?
			if (ins->version == ins->light_info->last_version && rasterizer->light_instance_has_far_shadow(ins->light_info->instance))
				continue; // didn't change
			*/

			_light_instance_update_shadow(ins,p_scenario,camera,cull_range);
			ins->light_info->last_version=ins->version;
		}
	}
#endif
	/* ENVIRONMENT */

	RID environment;
	if (camera->env.is_valid()) //camera has more environment priority
		environment=camera->env;
	else if (scenario->environment.is_valid())
		environment=scenario->environment;
	else
		environment=scenario->fallback_environment;

#if 0
	/* STEP 6 - SAMPLE BAKED LIGHT */

	bool islinear =false;
	if (environment.is_valid()) {
		islinear = rasterizer->environment_is_fx_enabled(environment,VS::ENV_FX_SRGB);
	}

	for(int i=0;i<light_samplers_culled;i++) {

		_process_sampled_light(camera->transform,light_sampler_cull_result[i],islinear);
	}
#endif
	/* STEP 7 - PROCESS GEOMETRY AND DRAW SCENE*/

#if 0
	// add lights

	{
		List<RID>::Element *E=p_scenario->directional_lights.front();


		for(;E;E=E->next()) {
			Instance  *light = E->get().is_valid()?instance_owner.get(E->get()):NULL;

			ERR_CONTINUE(!light);
			if (!light->light_info->enabled)
				continue;

			rasterizer->add_light(light->light_info->instance);
			light->light_info->last_add_pass=render_pass;
		}

		for (int i=0;i<light_cull_count;i++) {

			Instance *ins = light_cull_result[i];
			rasterizer->add_light(ins->light_info->instance);
			ins->light_info->last_add_pass=render_pass;
		}
	}
		// add geometry
#endif


	VSG::scene_render->render_scene(camera->transform, camera_matrix,ortho,(RasterizerScene::InstanceBase**)instance_cull_result,cull_count,light_instance_cull_result,light_cull_count,directional_light_ptr,directional_light_count,environment);

}



void VisualServerScene::_update_dirty_instance(Instance *p_instance) {


	if (p_instance->update_aabb)
		_update_instance_aabb(p_instance);

	if (p_instance->update_materials) {
		if (p_instance->base_type==VS::INSTANCE_MESH) {
			p_instance->materials.resize(VSG::storage->mesh_get_surface_count(p_instance->base));
		}
	}

	_update_instance(p_instance);

	p_instance->update_aabb=false;
	p_instance->update_materials=false;

	_instance_update_list.remove( &p_instance->update_item );
}


void VisualServerScene::update_dirty_instances() {

	while(_instance_update_list.first()) {

		_update_dirty_instance( _instance_update_list.first()->self() );
	}
}

bool VisualServerScene::free(RID p_rid) {

	if (camera_owner.owns(p_rid)) {

		Camera *camera = camera_owner.get( p_rid );

		camera_owner.free(p_rid);
		memdelete(camera);

	} else if (scenario_owner.owns(p_rid)) {

		Scenario *scenario = scenario_owner.get( p_rid );

		while(scenario->instances.first()) {
			instance_set_scenario(scenario->instances.first()->self()->self,RID());
		}

		scenario_owner.free(p_rid);
		memdelete(scenario);

	} else if (instance_owner.owns(p_rid)) {
		// delete the instance

		update_dirty_instances();

		Instance *instance = instance_owner.get(p_rid);

		instance_set_room(p_rid,RID());
		instance_set_scenario(p_rid,RID());
		instance_set_base(p_rid,RID());

		if (instance->skeleton.is_valid())
			instance_attach_skeleton(p_rid,RID());

		instance_owner.free(p_rid);
		memdelete(instance);
	} else {
		return false;
	}


	return true;
}

VisualServerScene *VisualServerScene::singleton=NULL;

VisualServerScene::VisualServerScene() {


	render_pass=1;
	singleton=this;

}
