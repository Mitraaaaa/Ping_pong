#version 130 
attribute vec4 vp; 
uniform vec3 offset1;
uniform vec3 offset2;
uniform vec3 offset3;
 void main() 
 { 
       
	mat4 rx = mat4( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
			
	if(vp.w == 1.01){		
            rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			offset1.x, offset1.y, offset1.z, 1.0 );
			}
	if(vp.w == 1.02){		
             rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			offset2.x, offset2.y, offset2.z, 1.0 );
			}
        if(vp.w == 1.03){		
             rx = mat4( 1.0, 0.0, 0.0, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			offset3.x, offset3.y, offset3.z, 1.0 );
			}

 	gl_Position = rx*vp;
 
 }
