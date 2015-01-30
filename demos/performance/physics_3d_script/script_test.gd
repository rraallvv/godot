
extends Spatial

# This demo is an example of controling a high number of 2D objects with logic and collision without using scene nodes.
# This technique is a lot more efficient than using instancing and nodes, but requires more programming and is less visual

const BULLET_COUNT = 10
const SPEED_MIN = 1.0
const SPEED_MAX = 10.0
const width = 10
	
var bullets=[]
var cubes=[]
var shape

class Bullet:
	extends TestCube
	var pos = Vector3()
	var speed = 1.0
	var body = RID()


func _process(delta):
	for i in range(BULLET_COUNT):
		var b = bullets[i]
		var trans = PhysicsServer.body_get_state(b.body,PhysicsServer.BODY_STATE_TRANSFORM)
		b.set_transform(trans)


func _ready():

	shape = PhysicsServer.shape_create(PhysicsServer.SHAPE_SPHERE)
	PhysicsServer.shape_set_data(shape,1.0) #radius
	
	for i in range(BULLET_COUNT):
		var b = Bullet.new()
		b.speed=rand_range(SPEED_MIN,SPEED_MAX)
		b.body = PhysicsServer.body_create(PhysicsServer.BODY_MODE_RIGID)
		PhysicsServer.body_set_space(b.body,get_world().get_space())
		PhysicsServer.body_add_shape(b.body,shape)
		
		var trans = Transform()
		trans.origin=Vector3(rand_range(-width,width),10,rand_range(-width,width))
		
		b.set_transform(trans)
		PhysicsServer.body_set_state(b.body,PhysicsServer.BODY_STATE_TRANSFORM,trans)
		PhysicsServer.body_set_param(b.body,PhysicsServer.BODY_PARAM_BOUNCE,1.0)
		
		bullets.append(b)
		add_child(b)
		
	set_process(true)


func _exit_tree():
	for b in bullets:
		PhysicsServer.free_rid(b.body)
	
	PhysicsServer.free_rid(shape)

	bullets.clear()
	cubes.clear()
	
	pass
	