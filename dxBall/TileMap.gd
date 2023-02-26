extends TileMap



var pedal= Vector2(13, 0)
var ball= Vector2(9,14)
var ball_angle= Vector2(2,-1)
var pedal_direction=0
var Render = []
var brick =[]
var Wall= []
var temp_pos = Vector2(0,0)

var counter=0
var two_dot=true
var two_dot_frame=0



func _ready() -> void:
	for x in range(31):
		Render.append([])
		Render[x]=[]
		for y in range(23):
			Render[x].append([])
			Render[x][y]=0
				
	for x in range(32):
		brick.append([])
		brick[x]=[]
		for y in range(24):
			brick[x].append([])
			if(y<6 and y>0 and x>0 and x<31):
				brick[x][y]=1
			else:
				brick[x][y]=0	
				
	for x in range(32):
		Wall.append([])
		Wall[x]=[]
		for y in range(24):
			Wall[x].append([])
			if(y==0 or x==0 or x==31):
				Wall[x][y]=1
			else:
				Wall[x][y]=0
			
	for x in range(32):
		for y in range(24):
			if(Wall[x][y]==1 or brick[x][y]==1): #or brick[x][y]==1
				set_cell(x,y,1)


func _process(delta: float) -> void:
	
	#refresh
	set_cell(ball.x,ball.y,-1)
	
	set_cell(pedal.x,23,-1)
	set_cell(pedal.x+1,23,-1)
	set_cell(pedal.x+2,23,-1)
	set_cell(pedal.x+3,23,-1)
	set_cell(pedal.x+4,23,-1)
	set_cell(pedal.x+5,23,-1)
	set_cell(pedal.x+6,23,-1)
	
		
	#controlling pedal
	if(Input.is_action_pressed("ui_left")):
		if(pedal.x>1):
			pedal_direction=-1
		else:
			pedal_direction=0
	elif(Input.is_action_pressed("ui_right")):
		if(pedal.x<24):
			pedal_direction=1
		else:
			pedal_direction=0
	elif(Input.is_action_pressed("ui_right") and Input.is_action_pressed("ui_left")):
		pedal_direction=0
	else:
		pedal_direction=0
	
	
	counter=counter+1
	if(counter==1000):
		counter=0
	if(counter%5==0):#physics
		two_dot_frame=two_dot_frame+1
		if(two_dot_frame%10==0):
			two_dot_frame=0
		
		pedal.x=pedal.x+pedal_direction
		
		#ground collision
		if(ball.y==23):
			ball=Vector2(pedal.x+3,22)
			ball_angle= Vector2(-1,-1)
			print('es')
			
		#pedal collision
		if(ball.x>=pedal.x and ball.x<(pedal.x+6) and ball.y==22):	
			if(ball.x==pedal.x or ball.x==pedal.x+6):
				if(ball_angle.x>=0):
					ball_angle=Vector2(2, -1)
					two_dot=true
				else:
					ball_angle=Vector2(-2, -1)
					two_dot=true	
			if(ball.x==(pedal.x+1) or ball.x==(pedal.x+5) ):
				if(ball_angle.x>=0):
					ball_angle=Vector2(1, -1)
					two_dot=false
				else:
					ball_angle=Vector2(-1, -1)
					two_dot=false
			if(ball.x==(pedal.x+2) or ball.x==(pedal.x+4)):
				if(ball_angle.x>=0):
					ball_angle=Vector2(1, -2)
					two_dot=true
				else:
					ball_angle=Vector2(-1, -2)
					two_dot=true
			if(ball.x==(pedal.x+3)):
				if(ball_angle.x>=0):
					ball_angle=Vector2(0, -1)
					two_dot=false
				else:
					ball_angle=Vector2(0, -1)
					two_dot=false
					
		print("-----------------------")
		#wall collision detection
		if(ball.x==30):
			if(ball_angle.x>0):
				ball_angle.x=-ball_angle.x
		if(ball.x==1):
			if(ball_angle.x<0):
				ball_angle.x=-ball_angle.x	
				
		if(ball.y==1):
			if(ball_angle.y<0):
				ball_angle.y=-ball_angle.y
			
		if(ball.x==30):
			print("problem")
		
		#ball physics
		if(two_dot==true):
			if(two_dot_frame%2==1):
				if(abs(ball_angle.x)==2):
					ball.x=ball.x+ball_angle.x/2			
				if(abs(ball_angle.y)==2):
					ball.y=ball.y+ball_angle.y/2
			else:
				if(abs(ball_angle.x)==2):
					ball.x=ball.x+ball_angle.x/2
					ball.y=ball.y+ball_angle.y			
				if(abs(ball_angle.y)==2):
					ball.y=ball.y+ball_angle.y/2
					ball.x=ball.x+ball_angle.x
		else:
			ball=ball+ball_angle

	#rendering
	
	set_cell(ball.x,ball.y,1) #ball render
	
	#Brick_render()
	
	set_cell(pedal.x,23,1)
	set_cell(pedal.x+1,23,1)
	set_cell(pedal.x+2,23,1)
	set_cell(pedal.x+3,23,1)
	set_cell(pedal.x+4,23,1)
	set_cell(pedal.x+5,23,1)
	set_cell(pedal.x+6,23,1)	
	
func Brick_render():
	for x in range(32):
		for y in range(24):
			if(brick[x][y]==1):
				set_cell(x,y,1)
		

