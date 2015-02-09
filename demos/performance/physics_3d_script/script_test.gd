
extends Spatial

# This demo is an example of creating 3d body physics in GDScript.

var cubes=[]
var box_shape
var container_shapes=[]

class VisibleBody:
	extends TestCube
	var body = RID()
	var shape = 0
	func _init():
		var material = FixedMaterial.new()
		material.set_parameter(VisualServer.FIXED_MATERIAL_PARAM_DIFFUSE, Color(0.1,0.1,1))
		material.set_parameter(VisualServer.FIXED_MATERIAL_PARAM_SPECULAR, Color(0.5,0.5,0.5))
		material.set_parameter(VisualServer.FIXED_MATERIAL_PARAM_SPECULAR_EXP, 50.0)
		set_material_override(material)


class TrasparentBody:
	extends Spatial
	var body = RID()
	var shape = 0


func create_container():
	var body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
	PhysicsServer.body_set_space(body,get_world().get_space())
	PhysicsServer.body_set_state(body,PhysicsServer.BODY_STATE_TRANSFORM,Transform())
	PhysicsServer.body_set_param(body,PhysicsServer.BODY_PARAM_BOUNCE,0.0)
	PhysicsServer.body_set_param(body,PhysicsServer.BODY_PARAM_MASS,1.0)
	PhysicsServer.body_set_param(body,PhysicsServer.BODY_PARAM_FRICTION,0.5)
	
	create_wall(Vector3(-10,0,0), Vector3(1,11,11), body) #left
	create_wall(Vector3(10,0,0), Vector3(1,11,11), body) #right
	create_wall(Vector3(0,10,0), Vector3(11,1,11), body) #top
	create_wall(Vector3(0,-10,0), Vector3(11,1,11), body) #bottom
	create_wall(Vector3(0,0,10), Vector3(11,11,1), body, false) #front
	create_wall(Vector3(0,0,-10), Vector3(11,11,1), body, false) #back
	
	var joint = PhysicsServer.joint_create_hinge(body, Transform(), RID(), Transform())
	PhysicsServer.hinge_joint_set_param(joint, PhysicsServer.HINGE_JOINT_MOTOR_TARGET_VELOCITY, -2.0*PI/30)
	PhysicsServer.hinge_joint_set_param(joint, PhysicsServer.HINGE_JOINT_MOTOR_MAX_IMPULSE, 1024)
	PhysicsServer.hinge_joint_set_flag(joint, PhysicsServer.HINGE_JOINT_FLAG_ENABLE_MOTOR, true)


func create_wall(origin, dimensions, body, visible=true):
	var cube
	if visible:
		cube = VisibleBody.new()
	else:
		cube = TrasparentBody.new()
	cube.body = body
	cube.shape = PhysicsServer.body_get_shape_count(cube.body)
	
	var transform = Transform()
	
	transform.origin = origin
	cube.set_transform(transform)
	
	var shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(shape,dimensions) # half extents
	PhysicsServer.body_add_shape(cube.body,shape,transform)
	
	cubes.append(cube)
	container_shapes.append(shape)
	add_child(cube)


func create_matrix(position):
	var separation = 3.0
	for i in range(3):
		for j in range(3):
			for k in range(3):
				var origin = separation * (Vector3(-1,-1,-1) + Vector3(i, j, k)) + position
				
				var cube = VisibleBody.new()
				cube.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
				PhysicsServer.body_set_space(cube.body,get_world().get_space())
				PhysicsServer.body_add_shape(cube.body,box_shape)
				
				var transform = Transform()
				transform.origin = origin
				cube.set_transform(transform)
				
				PhysicsServer.body_set_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM,transform)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,0.0)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,0.01)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_FRICTION,0.5)
				
				cubes.append(cube)
				add_child(cube)


func _process(delta):
	for cube in cubes:
		var transform = PhysicsServer.body_get_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM)
		var shape_transform = PhysicsServer.body_get_shape_transform(cube.body, cube.shape)
		cube.set_transform(transform * shape_transform)
		var shape_scale = PhysicsServer.shape_get_data(PhysicsServer.body_get_shape(cube.body,cube.shape))
		cube.set_scale(shape_scale)


func _ready():
	box_shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(box_shape,Vector3(1,1,1)) # half extents
	
	create_container()
	create_matrix(Vector3(-4.5,0,0))
	create_matrix(Vector3(4.5,0,0))
	set_process(true)


func _exit_tree():
	for cube in cubes:
		PhysicsServer.free_rid(cube.body)
	
	for shape in container_shapes:
		PhysicsServer.free_rid(shape)
	
	PhysicsServer.free_rid(box_shape)
	
	cubes.clear()
