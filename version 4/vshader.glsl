#version 130 
 in vec4 points; 
 in vec4 Vcolors; 
 out vec4 color; 
 uniform vec3 theta1;
 uniform vec3 theta2;
 uniform vec3 theta3;
 void main() 
 { 
       
	mat4 rx = mat4( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
			
	if(points.w == 1.01){		
             rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			theta1.x, theta1.y, 0.0, 1.0 );
			}
	if(points.w == 1.02){		
             rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			theta2.x, theta2.y, 0.0, 1.0 );
			}
        if(points.w == 1.03){		
             rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			theta3.x, theta3.y, 0.0, 1.0 );
			}

 	gl_Position = rx * points;
 	color=Vcolors;
 }
