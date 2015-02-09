
extends Spatial

# This demo is an example of creating 3d body physics in GDScript.

var cubes=[]
var box_shape
var container_shapes=[]

class VisibleBody:
	extends TestCube
	var body = RID()
	var shape = 0


class TrasparentBody:
	extends Spatial
	var body = RID()
	var shape = 0


func create_container():
	var body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
	PhysicsServer.body_set_space(body,get_world().get_space())
	PhysicsServer.body_set_state(body,PhysicsServer.BODY_STATE_TRANSFORM,Transform())
	PhysicsServer.body_set_param(body,PhysicsServer.BODY_PARAM_BOUNCE,1.0)
	PhysicsServer.body_set_param(body,PhysicsServer.BODY_PARAM_MASS,1.0)
	
	create_wall(Vector3(-10,0,0), Vector3(1,11,11), body)
	create_wall(Vector3(10,0,0), Vector3(1,11,11), body)
	create_wall(Vector3(0,-10,0), Vector3(11,1,11), body)
	create_wall(Vector3(0,10,0), Vector3(11,1,11), body)
	create_wall(Vector3(0,0,-10), Vector3(11,11,1), body, true)
	create_wall(Vector3(0,0,10), Vector3(11,11,1), body, true)


func create_wall(origin, dimensions, body, transparent=false):	
	var cube
	if transparent:
		cube = TrasparentBody.new()
	else:
		cube = VisibleBody.new()
	cube.body = body
	cube.shape = PhysicsServer.body_get_shape_count(cube.body)
	
	var trans = Transform()
	
	trans.origin = origin
	trans.basis = Matrix3(Vector3(dimensions.x,0,0), Vector3(0,dimensions.y,0), Vector3(0,0,dimensions.z))
	cube.set_transform(trans)
	
	var shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(shape,dimensions) # half extents
	PhysicsServer.body_add_shape(cube.body,shape,trans)
	
	cubes.append(cube)
	container_shapes.append(shape)
	add_child(cube)


func create_matrix(position, shape):
	var separation = 3.0
	for i in range(3):
		for j in range(3):
			for k in range(3):
				var origin = separation * (Vector3(-1,-1,-1) + Vector3(i, j, k)) + position
				
				var cube = VisibleBody.new()
				cube.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
				PhysicsServer.body_set_space(cube.body,get_world().get_space())
				PhysicsServer.body_add_shape(cube.body,shape)
				
				var trans = Transform()
				trans.origin = origin
				cube.set_transform(trans)
				
				PhysicsServer.body_set_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM,trans)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,1.0)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,0.01)
				
				cubes.append(cube)
				add_child(cube)


func _process(delta):
	for cube in cubes:
		var trans = PhysicsServer.body_get_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM)
		var shape_trans = PhysicsServer.body_get_shape_transform(cube.body, cube.shape)
		cube.set_transform(trans*shape_trans)


func _ready():
	box_shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(box_shape,Vector3(1,1,1)) # half extents
	
	create_container()
	create_matrix(Vector3(-4.5,0,0), box_shape)
	create_matrix(Vector3(4.5,0,0), box_shape)
	set_process(true)


func _exit_tree():
	for cube in cubes:
		PhysicsServer.free_rid(cube.body)
	
	for shape in container_shapes:
		PhysicsServer.free_rid(shape)
	
	PhysicsServer.free_rid(box_shape)
	
	cubes.clear()
