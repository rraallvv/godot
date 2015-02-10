/*************************************************************************/
/*  bullet_server_sw.cpp                                                */
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

#include "bullet_server_sw.h"
#include "bullet_space_sw.h"
#include "bullet_shape_sw.h"


#pragma mark - Shape API

/* SHAPE API */



RID BulletServerSW::shape_create(ShapeType p_shape) {

	btCollisionShape* btShape = NULL;
	
	switch (p_shape) {
		case SHAPE_PLANE:
			btShape = new btPlaneShape(btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f));
			break;
			
		case SHAPE_BOX:
			btShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
			break;
			
		default:
			ERR_FAIL_V(RID());
			break;
	}
	
	printf(">>>creating shape type %d (%p)\n", p_shape, btShape);

	BulletShapeSW *shape = memnew( BulletShapeSW );
	shape->shape = btShape;
	shape->type = p_shape;

	RID id = shape_owner.make_rid(shape);
	shape->set_self(id);
	
	return id;
}

void BulletServerSW::shape_set_data(RID p_shape, const Variant& p_data) {

	BulletShapeSW *shape = shape_owner.get(p_shape);
	ERR_FAIL_COND(!shape);
	shape->set_data(p_data);
}

void BulletServerSW::shape_set_custom_solver_bias(RID p_shape, real_t p_bias) {

}

PhysicsServer::ShapeType BulletServerSW::shape_get_type(RID p_shape) const {

	return SHAPE_CUSTOM;
}

Variant BulletServerSW::shape_get_data(RID p_shape) const {

	const BulletShapeSW *shape = shape_owner.get(p_shape);
	ERR_FAIL_COND_V(!shape,Variant());
	//ERR_FAIL_COND_V(!shape->is_configured(),Variant());
	return shape->get_data();
}

real_t BulletServerSW::shape_get_custom_solver_bias(RID p_shape) const {

	return 0;
}



#pragma mark - Space API

/* SPACE API */



RID BulletServerSW::space_create() {

	printf(">>>creating space\n");

	if (shared_space)
		return shared_space->get_self();

	shared_space = memnew( BulletSpaceSW );

	shared_space->broadphase = new btDbvtBroadphase();
	shared_space->constraintSolver = new btSequentialImpulseConstraintSolver;
	shared_space->collisionConfig = new btDefaultCollisionConfiguration();
	shared_space->collisionDispatcher = new btCollisionDispatcher(shared_space->collisionConfig);
	shared_space->discreteDynamicsWorld = new btDiscreteDynamicsWorld(shared_space->collisionDispatcher, shared_space->broadphase, shared_space->constraintSolver, shared_space->collisionConfig);
	
	shared_space->discreteDynamicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));

	RID rid = space_owner.make_rid(shared_space);
	shared_space->set_self(rid);

	return rid;
}

void BulletServerSW::space_set_active(RID p_space,bool p_active) {

	BulletSpaceSW *space = space_owner.get(p_space);
	ERR_FAIL_COND(!space);
	if (p_active)
		active_spaces.insert(space);
	else
		active_spaces.erase(space);
}

bool BulletServerSW::space_is_active(RID p_space) const {

	const BulletSpaceSW *space = space_owner.get(p_space);
	ERR_FAIL_COND_V(!space,false);

	return active_spaces.has(space);
}

void BulletServerSW::space_set_param(RID p_space,SpaceParameter p_param, real_t p_value) {

	BulletSpaceSW *space = space_owner.get(p_space);
	ERR_FAIL_COND(!space);

	space->set_param(p_param,p_value);
}

real_t BulletServerSW::space_get_param(RID p_space,SpaceParameter p_param) const {

	const BulletSpaceSW *space = space_owner.get(p_space);
	ERR_FAIL_COND_V(!space,0);
	return space->get_param(p_param);
}

PhysicsDirectSpaceState* BulletServerSW::space_get_direct_state(RID p_space) {

	return NULL;
}



#pragma mark - Area API

/* AREA API */



RID BulletServerSW::area_create() {

	return RID();
}

void BulletServerSW::area_set_space(RID p_area, RID p_space) {

}

RID BulletServerSW::area_get_space(RID p_area) const {

	return RID();
}

void BulletServerSW::area_set_space_override_mode(RID p_area, AreaSpaceOverrideMode p_mode) {

}

PhysicsServer::AreaSpaceOverrideMode BulletServerSW::area_get_space_override_mode(RID p_area) const {

	return AREA_SPACE_OVERRIDE_DISABLED;
}


void BulletServerSW::area_add_shape(RID p_area, RID p_shape, const Transform& p_transform) {

}

void BulletServerSW::area_set_shape(RID p_area, int p_shape_idx,RID p_shape) {

}

void BulletServerSW::area_set_shape_transform(RID p_area, int p_shape_idx, const Transform& p_transform) {

}

int BulletServerSW::area_get_shape_count(RID p_area) const {

	return -1;
}

RID BulletServerSW::area_get_shape(RID p_area, int p_shape_idx) const {

	return RID();
}

Transform BulletServerSW::area_get_shape_transform(RID p_area, int p_shape_idx) const {

	return Transform();
}

void BulletServerSW::area_remove_shape(RID p_area, int p_shape_idx) {

}

void BulletServerSW::area_clear_shapes(RID p_area) {

}

void BulletServerSW::area_attach_object_instance_ID(RID p_area,ObjectID p_ID) {

}

ObjectID BulletServerSW::area_get_object_instance_ID(RID p_area) const {

	return 0;
}

void BulletServerSW::area_set_param(RID p_area,AreaParameter p_param,const Variant& p_value) {

}

void BulletServerSW::area_set_transform(RID p_area, const Transform& p_transform) {

}

Variant BulletServerSW::area_get_param(RID p_area,AreaParameter p_param) const {

	return Variant();
}

Transform BulletServerSW::area_get_transform(RID p_area) const {

	return Transform();
}

void BulletServerSW::area_set_monitor_callback(RID p_area,Object *p_receiver,const StringName& p_method) {

}

void BulletServerSW::area_set_ray_pickable(RID p_area,bool p_enable) {

}

bool BulletServerSW::area_is_ray_pickable(RID p_area) const{

	return false;
}



#pragma mark - Body API

/* BODY API */



RID BulletServerSW::body_create(BodyMode p_mode,bool p_init_sleeping) {

	btScalar mass(0.0f);

	if (p_mode == BODY_MODE_RIGID)
		mass = btScalar(1.0f);

	btVector3 localInertia;
	
	btCompoundShape* btShape = new btCompoundShape;
	btShape->calculateLocalInertia(mass,localInertia);
	
	BulletShapeSW *shape = memnew( BulletShapeSW );
	shape->shape = btShape;
	shape->type = SHAPE_CUSTOM;
	
	shape_owner.make_rid(shape);
	
	
	btTransform transform = btTransform::getIdentity();
	
	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,btShape,localInertia);
	
	btRigidBody* btBody = new btRigidBody(rbInfo);
	
	BulletBodySW *body = memnew( BulletBodySW );
	body->body = btBody;
	body->mode = p_mode;
	body->mass = mass;

	printf(">>>creating body mode %d (%p)\n", p_mode, btBody);

	return body_owner.make_rid(body);
}

void BulletServerSW::body_set_space(RID p_body, RID p_space) {
	
	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);
	BulletSpaceSW *space=NULL;
	
	if (p_space.is_valid()) {
		space = space_owner.get(p_space);
		ERR_FAIL_COND(!space);
	}

	if (body->get_space()==space)
		return; //pointles
	
	printf(">>>setting space (%p) for body (%p)\n", space, body->body);

	body->set_space(space);
}

RID BulletServerSW::body_get_space(RID p_body) const {

	return RID();
}

void BulletServerSW::body_set_mode(RID p_body, BodyMode p_mode) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	body->set_mode(p_mode);
}

PhysicsServer::BodyMode BulletServerSW::body_get_mode(RID p_body, BodyMode p_mode) const {

	return BODY_MODE_STATIC;
}

void BulletServerSW::body_add_shape(RID p_body, RID p_shape, const Transform& p_transform) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	BulletShapeSW *shape = shape_owner.get(p_shape);
	ERR_FAIL_COND(!shape);

	body->add_shape(shape,p_transform);

	printf(">>>adding shape (%p) to body (%p) total %d\n", shape->shape, body->body, body->get_shape_count());
}

void BulletServerSW::body_set_shape(RID p_body, int p_shape_idx,RID p_shape) {

}

void BulletServerSW::body_set_shape_transform(RID p_body, int p_shape_idx, const Transform& p_transform) {

}

int BulletServerSW::body_get_shape_count(RID p_body) const {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND_V(!body,-1);

	return body->get_shape_count();
}

RID BulletServerSW::body_get_shape(RID p_body, int p_shape_idx) const {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND_V(!body,RID());

	BulletShapeSW *shape = body->get_shape(p_shape_idx);
	ERR_FAIL_COND_V(!shape,RID());

	return shape->get_self();
}

void BulletServerSW::body_set_shape_as_trigger(RID p_body, int p_shape_idx,bool p_enable) {

}

bool BulletServerSW::body_is_shape_set_as_trigger(RID p_body, int p_shape_idx) const{

	return false;
}

Transform BulletServerSW::body_get_shape_transform(RID p_body, int p_shape_idx) const {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND_V(!body,Transform());

	return body->get_shape_transform(p_shape_idx);
}

void BulletServerSW::body_remove_shape(RID p_body, int p_shape_idx) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	body->remove_shape(p_shape_idx);
}

void BulletServerSW::body_clear_shapes(RID p_body) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	while(body->get_shape_count())
		body->remove_shape(0);
	
}

void BulletServerSW::body_set_enable_continuous_collision_detection(RID p_body,bool p_enable) {

}

bool BulletServerSW::body_is_continuous_collision_detection_enabled(RID p_body) const {

	return false;
}

void BulletServerSW::body_set_layer_mask(RID p_body, uint32_t p_mask) {

}

uint32_t BulletServerSW::body_get_layer_mask(RID p_body, uint32_t p_mask) const{

	return 0;
}

void BulletServerSW::body_attach_object_instance_ID(RID p_body,uint32_t p_ID) {

}

uint32_t BulletServerSW::body_get_object_instance_ID(RID p_body) const {

	return 0;
}


void BulletServerSW::body_set_user_flags(RID p_body, uint32_t p_flags) {

}

uint32_t BulletServerSW::body_get_user_flags(RID p_body, uint32_t p_flags) const {

	return 0;
}

void BulletServerSW::body_set_param(RID p_body, BodyParameter p_param, float p_value) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	printf(">>>setting body parameter (%p)\n", body->body);

	body->set_param(p_param,p_value);
}

float BulletServerSW::body_get_param(RID p_body, BodyParameter p_param) const {

	return 0;
}

void BulletServerSW::body_set_state(RID p_body, BodyState p_state, const Variant& p_variant) {

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	//printf(">>>setting body state (%p)\n", body->body);

	body->set_state(p_state,p_variant);
}

Variant BulletServerSW::body_get_state(RID p_body, BodyState p_state) const {

	//printf(">>>getting body state\n");

	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND_V(!body,Variant());

	return body->get_state(p_state);
}

void BulletServerSW::body_set_applied_force(RID p_body, const Vector3& p_force) {

}

Vector3 BulletServerSW::body_get_applied_force(RID p_body) const {

	return Vector3();
}

void BulletServerSW::body_set_applied_torque(RID p_body, const Vector3& p_torque) {

}

Vector3 BulletServerSW::body_get_applied_torque(RID p_body) const {

	return Vector3();
}

void BulletServerSW::body_apply_impulse(RID p_body, const Vector3& p_pos, const Vector3& p_impulse) {

}

void BulletServerSW::body_set_axis_velocity(RID p_body, const Vector3& p_axis_velocity) {

}

void BulletServerSW::body_set_axis_lock(RID p_body,BodyAxisLock p_lock) {

}

BulletServerSW::BodyAxisLock BulletServerSW::body_get_axis_lock(RID p_body) const{

	return BODY_AXIS_LOCK_DISABLED;
}

void BulletServerSW::body_add_collision_exception(RID p_body, RID p_body_b) {

}

void BulletServerSW::body_remove_collision_exception(RID p_body, RID p_body_b) {

}

void BulletServerSW::body_get_collision_exceptions(RID p_body, List<RID> *p_exceptions) {

}

void BulletServerSW::body_set_contacts_reported_depth_treshold(RID p_body, float p_treshold) {

}

float BulletServerSW::body_get_contacts_reported_depth_treshold(RID p_body) const {

	return 0;
}

void BulletServerSW::body_set_omit_force_integration(RID p_body,bool p_omit) {

}

bool BulletServerSW::body_is_omitting_force_integration(RID p_body) const {

	return false;
}

void BulletServerSW::body_set_max_contacts_reported(RID p_body, int p_contacts) {

}

int BulletServerSW::body_get_max_contacts_reported(RID p_body) const {

	return -1;
}

void BulletServerSW::body_set_force_integration_callback(RID p_body,Object *p_receiver,const StringName& p_method,const Variant& p_udata) {


	BulletBodySW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);
	body->set_force_integration_callback(p_receiver?p_receiver->get_instance_ID():ObjectID(0),p_method,p_udata);
	
}

void BulletServerSW::body_set_ray_pickable(RID p_body,bool p_enable) {

}

bool BulletServerSW::body_is_ray_pickable(RID p_body) const{

	return false;
}



#pragma mark - Joint API

/* JOINT API */


#pragma mark Pin Joint


RID BulletServerSW::joint_create_pin(RID p_body_A,const Vector3& p_local_A,RID p_body_B,const Vector3& p_local_B) {

	return RID();
}

void BulletServerSW::pin_joint_set_param(RID p_joint,PinJointParam p_param, float p_value){

}

float BulletServerSW::pin_joint_get_param(RID p_joint,PinJointParam p_param) const{

	return 0;
}

void BulletServerSW::pin_joint_set_local_A(RID p_joint, const Vector3& p_A){

}

Vector3 BulletServerSW::pin_joint_get_local_A(RID p_joint) const{

	return Vector3();
}

void BulletServerSW::pin_joint_set_local_B(RID p_joint, const Vector3& p_B){

}

Vector3 BulletServerSW::pin_joint_get_local_B(RID p_joint) const{

	return Vector3();
}


#pragma mark Hinge Joint


RID BulletServerSW::joint_create_hinge(RID p_body_A,const Transform& p_frame_A,RID p_body_B,const Transform& p_frame_B) {

	return RID();
}

RID BulletServerSW::joint_create_hinge_simple(RID p_body_A,const Vector3& p_pivot_A,const Vector3& p_axis_A,RID p_body_B,const Vector3& p_pivot_B,const Vector3& p_axis_B) {

	return RID();
}

void BulletServerSW::hinge_joint_set_param(RID p_joint,HingeJointParam p_param, float p_value){

}

float BulletServerSW::hinge_joint_get_param(RID p_joint,HingeJointParam p_param) const{

	return 0;
}

void BulletServerSW::hinge_joint_set_flag(RID p_joint,HingeJointFlag p_flag, bool p_value){

}

bool BulletServerSW::hinge_joint_get_flag(RID p_joint,HingeJointFlag p_flag) const{

	return false;
}


#pragma mark Slider Joint


RID BulletServerSW::joint_create_slider(RID p_body_A,const Transform& p_local_frame_A,RID p_body_B,const Transform& p_local_frame_B) {

	return RID();
}

void BulletServerSW::slider_joint_set_param(RID p_joint,SliderJointParam p_param, float p_value){

}

float BulletServerSW::slider_joint_get_param(RID p_joint,SliderJointParam p_param) const{

	return 0;
}


#pragma mark Twist Joint


RID BulletServerSW::joint_create_cone_twist(RID p_body_A,const Transform& p_local_frame_A,RID p_body_B,const Transform& p_local_frame_B) {

	return RID();
}

void BulletServerSW::cone_twist_joint_set_param(RID p_joint,ConeTwistJointParam p_param, float p_value) {

}

float BulletServerSW::cone_twist_joint_get_param(RID p_joint,ConeTwistJointParam p_param) const {

	return 0;
}


#pragma mark 6DOF Joint


RID BulletServerSW::joint_create_generic_6dof(RID p_body_A,const Transform& p_local_frame_A,RID p_body_B,const Transform& p_local_frame_B) {

	return RID();
}

void BulletServerSW::generic_6dof_joint_set_param(RID p_joint,Vector3::Axis p_axis,G6DOFJointAxisParam p_param, float p_value){

}

float BulletServerSW::generic_6dof_joint_get_param(RID p_joint,Vector3::Axis p_axis,G6DOFJointAxisParam p_param){

	return 0;
}

void BulletServerSW::generic_6dof_joint_set_flag(RID p_joint,Vector3::Axis p_axis,G6DOFJointAxisFlag p_flag, bool p_enable){

}

bool BulletServerSW::generic_6dof_joint_get_flag(RID p_joint,Vector3::Axis p_axis,G6DOFJointAxisFlag p_flag){

	return false;
}


#pragma mark Misc


void BulletServerSW::joint_set_solver_priority(RID p_joint,int p_priority) {
	
}

int BulletServerSW::joint_get_solver_priority(RID p_joint) const{
	
	return 0;
}

BulletServerSW::JointType BulletServerSW::joint_get_type(RID p_joint) const {
	
	return JOINT_PIN;
}


#pragma mark (unused methods)


#if 0
void BulletServerSW::joint_set_param(RID p_joint, JointParam p_param, real_t p_value) {

}

real_t BulletServerSW::joint_get_param(RID p_joint,JointParam p_param) const {

	return 0;
}

RID BulletServerSW::pin_joint_create(const Vector3& p_pos,RID p_body_a,RID p_body_b) {

	return RID();
}

RID BulletServerSW::groove_joint_create(const Vector3& p_a_groove1,const Vector3& p_a_groove2, const Vector3& p_b_anchor, RID p_body_a,RID p_body_b) {

	return RID();
}

RID BulletServerSW::damped_spring_joint_create(const Vector3& p_anchor_a,const Vector3& p_anchor_b,RID p_body_a,RID p_body_b) {

	return RID();
}

void BulletServerSW::damped_string_joint_set_param(RID p_joint, DampedStringParam p_param, real_t p_value) {

}

real_t BulletServerSW::damped_string_joint_get_param(RID p_joint, DampedStringParam p_param) const {

	return 0;
}

#endif


#pragma mark - Other methods


void BulletServerSW::free(RID p_rid) {
	
}

void BulletServerSW::set_active(bool p_active) {

	active=p_active;
}

void BulletServerSW::init() {

	doing_sync=true;
	//last_step=0.001;
	//iterations=8;// 8?
	//stepper = memnew( StepSW );
	direct_state = memnew( BulletDirectBodyStateSW );
}

void BulletServerSW::step(float p_step) {


	if (!active)
		return;


	doing_sync=false;

	last_step=p_step;

	island_count=0;
	active_objects=0;
	collision_pairs=0;
	for( Set<const BulletSpaceSW*>::Element *E=active_spaces.front();E;E=E->next()) {

		BulletSpaceSW *space = (BulletSpaceSW*)E->get();
		space->step(1.f/60, 0);
		//island_count+=E->get()->get_island_count();
		//active_objects+=E->get()->get_active_objects();
		//collision_pairs+=E->get()->get_collision_pairs();
	}
	
}

void BulletServerSW::sync() {

	if (!active)
		return;

	doing_sync=true;
	for( Set<const BulletSpaceSW*>::Element *E=active_spaces.front();E;E=E->next()) {

		BulletSpaceSW *space=(BulletSpaceSW *)E->get();
		space->sync();
	}
}

void BulletServerSW::flush_queries() {

	if (!active)
		return;

	doing_sync=true;
	for( Set<const BulletSpaceSW*>::Element *E=active_spaces.front();E;E=E->next()) {

		BulletSpaceSW *space=(BulletSpaceSW *)E->get();
		space->call_queries();
	}
	
}

void BulletServerSW::finish() {

	memdelete(direct_state);
}

int BulletServerSW::get_process_info(ProcessInfo p_info) {

	return 0;
}

void BulletServerSW::_shape_col_cbk(const Vector3& p_point_A,const Vector3& p_point_B,void *p_userdata) {

}

BulletServerSW::BulletServerSW() {

	island_count=0;
	active_objects=0;
	collision_pairs=0;

	active=true;

	shared_space=NULL;
}

BulletServerSW::~BulletServerSW() {

}
