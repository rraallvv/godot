extends RigidBody

const TORQUE=1.0

func _fixed_process(dt):
	set_applied_torque(Vector3(0,0,-TORQUE))

func _ready():
	set_fixed_process(false)
