
extends Spatial

# This demo is an example of creating 3d body physics in GDScript.

const CUBE_COUNT = 10
const WIDTH = 10
	
var cubes=[]
var shape

class Cube:
	extends TestCube
	var body = RID()


func _process(delta):
	for cube in cubes:
		var trans = PhysicsServer.body_get_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM)
		cube.set_transform(trans)


func _ready():
	shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_BOX)
	PhysicsServer.shape_set_data(shape,Vector3(1,1,1)) # half extents
	
	for i in range(CUBE_COUNT):
		var cube = Cube.new()
		cube.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
		PhysicsServer.body_set_space(cube.body,get_world().get_space())
		PhysicsServer.body_add_shape(cube.body,shape)
		
		var trans = Transform()
		trans.origin=Vector3(rand_range(-WIDTH,WIDTH),rand_range(5,10),rand_range(-WIDTH,WIDTH))
		#if randf() > 0.5:
		#	trans = trans.rotated(Vector3(1,1,1), 45)
		
		cube.set_transform(trans)
		PhysicsServer.body_set_state(cube.body,PhysicsServer.BODY_STATE_TRANSFORM,trans)
		
		"""
		if randf() > 0.5:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,0.0)
		else:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_BOUNCE,1.0)
		"""
		
		"""
		if randf() > 0.5:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,0)
		else:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_MASS,0.01)
		"""
		
		"""
		if randf() > 0.5:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_FRICTION,0.0)
		else:
			PhysicsServer.body_set_param(cube.body,PhysicsServer.BODY_PARAM_FRICTION,1.0)
		"""
		
		cubes.append(cube)
		add_child(cube)
		
	set_process(true)


func _exit_tree():
	for cube in cubes:
		PhysicsServer.free_rid(cube.body)
	
	PhysicsServer.free_rid(shape)
	
	cubes.clear()
