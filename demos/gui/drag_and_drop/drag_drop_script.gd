
extends ColorPickerButton

# member variables here, example:
# var a=2
# var b="textvar"
func get_drag_data(pos):
	
	#use another control as drag preview
	var cpb = ColorPickerButton.new()
	cpb.set_color( get_color() )
	cpb.set_size(Vector2(50,50))
	set_drag_preview(cpb)
	#return color as drag data
	return get_color()
	
func can_drop_data(pos, data):
	return typeof(data)==TYPE_COLOR
	
func drop_data(pos, data):
	set_color(data)
		
func _ready():
	# Initialization here
	pass


