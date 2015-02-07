
extends Spatial

# This demo is an example of creating 3d body physics in GDScript.

var cubes=[]
var shape


class VisibleBody:
	extends TestCube
	var body = RID()


class TrasparentBody:
	extends Spatial
	var body = RID()


func create_container():
	create_wall(Vector3(-10,0,0), Vector3(1,11,11))
	create_wall(Vector3(10,0,0), Vector3(1,11,11))
	create_wall(Vector3(0,-10,0), Vector3(11,1,11))
	create_wall(Vector3(0,10,0), Vector3(11,1,11))
	create_wall(Vector3(0,0,-10), Vector3(11,11,1), true)
	create_wall(Vector3(0,0,10), Vector3(11,11,1), true)


func create_wall(origin, scale, transparent=false):
	var cube = RID()
	if transparent:
		cube = TrasparentBody.new()
	else:
		cube = VisibleBody.new()
	cube.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_STATIC)
	PhysicsServer.body_set_space(cube.body,get_world().get_space())
	PhysicsServer.body_add_shape(cube.body,shape)
	
	var trans = Transform()
	trans.origin = origin
	trans.basis = Matrix3().scaled(Vector3(1,1,1))
	cube.set_transform(trans)
		
	PhysicsServer.body_set_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM,trans)
	PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,0.0)
	#PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,1.0)
	cubes.append(cube)
	add_child(cube)


func create_matrix(position):
	var separation = 3.0
	for i in range(3):
		for j in range(3):
			for k in range(3):
				var cube = VisibleBody.new()
				cube.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
				PhysicsServer.body_set_space(cube.body,get_world().get_space())
				PhysicsServer.body_add_shape(cube.body,shape)
				
				var trans = Transform()
				trans.origin = separation * (Vector3(-1,-1,-1) + Vector3(i, j, k)) + position
				
				cube.set_transform(trans)
				PhysicsServer.body_set_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM,trans)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,0.0)
				PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,0.01)
				
				cubes.append(cube)
				add_child(cube)


func _process(delta):
	for cube in cubes:
		var trans = PhysicsServer.body_get_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM)
		cube.set_transform(trans)


func _ready():
	shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(shape,Vector3(1,1,1)) # half extents
	create_container()
	create_matrix(Vector3(-4.5,0,0))
	create_matrix(Vector3(4.5,0,0))
	set_process(true)


func _exit_tree():
	for cube in cubes:
		PhysicsServer.free_rid(cube.body)
	
	PhysicsServer.free_rid(shape)
	
	cubes.clear()
