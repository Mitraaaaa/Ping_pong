// mehrdad ghassabi
// student number : 4023614029
// Run with: g++ Pong_MitraOmrani_5.cpp -o mitra-pong -lGL -lGLU -lglut -lGLEW -lglfw

#include <iostream>
#include "text1.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include<math.h> 

// files to use for font
const char* atlas_image = "freemono.png";
const char* atlas_meta = "freemono.meta";

// game properties
int windowWidth = 1700;
int windowHeight = 850;
GLFWwindow* gl_window;
const int GAME_DURATION = 120;
const float pi = 3.14159265359;
const float num_triangle = 16.0f;
const float background_color[4] = {0.0f,0.0f,0.0f,0.0f};
const float scoreboard_color[4] = {1.0f,1.0f,1.0f,1.0f};

// centerline properties
const float centerline_color[3] = {0.7929f,0.6367f,0.1562f};
const int factor = 15; 
const int pattern = 0xAAAA;

// paddles properties
float paddle1Y = 0.0f;
float paddle2Y = 0.0f;
float paddleWidth = 0.03f;
float paddleHeight = 0.3f;
const float paddleSpeed = 0.02f;


// uniform variable to be passed to shaders		
float offset1[3] = { 0.0, 0.0,0.0 };
float offset2[3] = { 0.0, 0.0,0.0 };
float offset3[3] = { 0.0, 0.0,0.0 };

//  control paddles not to go out of the window
bool paddle1Up = false;
bool paddle1Down = false;
bool paddle2Up = false;
bool paddle2Down = false;

// balls properties
float ballSpeedX = 0.006f;
float ballSpeedY = 0.008f;
float ballSize = 0.02f;
float ballX = 0.0f;
float ballY = 0.0f;

// players score properties
int player1Score = 0;
int player2Score = 0;

float points[] = {
-0.96, paddleHeight / 2, 0, 1.01, 
-paddleWidth-0.96, paddleHeight / 2, 0, 1.01,
-paddleWidth-0.96, -paddleHeight / 2, 0, 1.01,
/************/
-0.96, paddleHeight / 2, 0, 1.01,
-paddleWidth-0.96, -paddleHeight / 2, 0, 1.01,
-0.96, -paddleHeight / 2, 0, 1.01,
//////////////////////////////////////////////////////			  
1.00, paddleHeight / 2, 0, 1.02,
-paddleWidth+1.00, paddleHeight / 2, 0, 1.02,
-paddleWidth+1.00, -paddleHeight / 2, 0, 1.02,
/************/
1.00, paddleHeight / 2, 0, 1.02,
-paddleWidth+1.00, -paddleHeight / 2, 0, 1.02,
1.00, -paddleHeight / 2, 0, 1.02,
//////////////////////////////////////////////////////
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(0), ballSize*sin(0), 0.0, 1.03,
ballSize*cos(pi/6), ballSize*sin(pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(pi/6), ballSize*sin(pi/6), 0.0, 1.03,
ballSize*cos(2*pi/6), ballSize*sin(2*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(2*pi/6), ballSize*sin(2*pi/6), 0.0, 1.03,
ballSize*cos(3*pi/6), ballSize*sin(3*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(3*pi/6), ballSize*sin(3*pi/6), 0.0, 1.03,
ballSize*cos(4*pi/6), ballSize*sin(4*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(4*pi/6), ballSize*sin(4*pi/6), 0.0, 1.03,
ballSize*cos(5*pi/6), ballSize*sin(5*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(5*pi/6), ballSize*sin(5*pi/6), 0.0, 1.03,
ballSize*cos(6*pi/6), ballSize*sin(6*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(6*pi/6), ballSize*sin(6*pi/6), 0.0, 1.03,
ballSize*cos(7*pi/6), ballSize*sin(7*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(7*pi/6), ballSize*sin(7*pi/6), 0.0, 1.03,
ballSize*cos(8*pi/6), ballSize*sin(8*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(8*pi/6), ballSize*sin(8*pi/6), 0.0, 1.03,
ballSize*cos(9*pi/6), ballSize*sin(9*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(9*pi/6), ballSize*sin(9*pi/6), 0.0, 1.03,
ballSize*cos(10*pi/6), ballSize*sin(10*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(10*pi/6), ballSize*sin(10*pi/6), 0.0, 1.03,
ballSize*cos(11*pi/6), ballSize*sin(11*pi/6), 0.0, 1.03,
/************/
0.0, 0.0, 0.0, 1.03,	  
ballSize*cos(11*pi/6), ballSize*sin(11*pi/6), 0.0, 1.03,
ballSize*cos(12*pi/6), ballSize*sin(12*pi/6), 0.0, 1.03,
};

// check if the time is up End the game
void check_the_time(double t){
         bool time_is_over = 0 >= t;
         if (time_is_over) {
            if ( player1Score > player2Score ){
            std::cout << "player1 is the winner" << std::endl;
            }
            if ( player1Score < player2Score ){
            std::cout << "player2 is the winner" << std::endl;
            }
            if ( player1Score < player2Score ){
            std::cout << "game finished as a draw" << std::endl;
            }
            exit(0);
        }
}

// Draw the dotted line
void drawCenterLines() {
        glColor3f(centerline_color[0],centerline_color[1],centerline_color[2]);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(factor, pattern);
        glBegin(GL_LINES);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
}

// Reading shader source from given file
static char * ReadShaderSource(char * ShaderFile)
{
	FILE *fp;
	fp = fopen(ShaderFile, "rt");
	if (!fp) return NULL;
	long size = 0;
	while (!feof(fp))
	{
		fgetc(fp);
		size++;
	}
	size--;
	fseek(fp, 0, SEEK_SET);
	char * buf = new char[size + 1];
	fread(buf, 1, size, fp);
	buf[size] = 0;
	fclose(fp);
	return buf;
}

 // call back function to manage inputs from keyboard
// moving the paddles
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{  
   // if a button got press
    if (action == GLFW_PRESS)
    {
        switch (key) {
        case 87: //87 is for pressing w
            paddle1Up = true;
            break;
        case 83: //83 is for pressing s
            paddle1Down = true;
            break;
        case 73: //73 is for pressing i
            paddle2Up = true;
            break;
        case 75://75 is for pressing k
            paddle2Down = true;
            break;
    }
    }
     // if a button got release
    else if(action == GLFW_RELEASE)
    {
        switch (key) {
        case 87: // 87 is for releasing w
            paddle1Up = false;
            break;
        case 83: //83 is for releasing s
            paddle1Down = false;
            break;
        case 73://73 is for releasing i
            paddle2Up = false;
            break;
        case 75://75 is for releasing k
            paddle2Down = false;
            break;
    }
    }
}

// function for updating ball position
void updateBall() { 

       offset3[0] += ballSpeedX;
	offset3[1] += ballSpeedY;
	ballY +=ballSpeedY;
	ballX +=ballSpeedX;     
     //  Check the collision !!
    // Check if the ball hits the top or bottom wall
     if (ballY + ballSize > 1.0f || ballY - ballSize < -1.0f) {
        ballSpeedY = -ballSpeedY;
    }
   
    // Check if the ball hits the left paddle
    if (ballX - ballSize < -1.0f + paddleWidth && ballY + ballSize  > paddle1Y - paddleHeight/2 && ballY - ballSize < paddle1Y + paddleHeight/2 ) {
        ballSpeedX = -ballSpeedX;
    }

    // Check if the ball hits the right paddle
    if (ballX + ballSize > 1.0f - paddleWidth && ballY + ballSize > paddle2Y - paddleHeight/2 && ballY - ballSize < paddle2Y + paddleHeight/2 ) {
       ballSpeedX = -ballSpeedX;
    }

    // Check if the ball goes out of bounds
    if (ballX - ballSize < -1.0f) {
          player2Score++;
          ballSpeedX = -ballSpeedX;
    }
 
    // Check if the ball goes out of bounds
    if (ballX + ballSize > 1.0f) {
       player1Score++;
        ballSpeedX = -ballSpeedX;
    }
}

// function for updating paddles position
void updatePaddle()
{
   if (paddle1Up && paddle1Y + paddleHeight / 2 < 1.0f) {
        offset1[1] += paddleSpeed;
        paddle1Y += paddleSpeed;
    }
     if (paddle1Down && paddle1Y - paddleHeight / 2 > -1.0f) {
        offset1[1] -= paddleSpeed;
        paddle1Y -= paddleSpeed;
    }
    if (paddle2Up && paddle2Y + paddleHeight / 2 < 1.0f) {
        offset2[1] += paddleSpeed;
        paddle2Y += paddleSpeed;
    }
    if (paddle2Down && paddle2Y - paddleHeight / 2 > -1.0f) {
        offset2[1] -= paddleSpeed;
        paddle2Y -= paddleSpeed;
    }
}


int main() {
        // init the window
	GLuint vao;
	GLuint shader_programme;
	assert (glfwInit());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	gl_window = glfwCreateWindow(windowHeight, windowHeight, "Text Example", NULL, NULL);
	assert (gl_window);
	glfwMakeContextCurrent(gl_window);
	glewExperimental = GL_TRUE;
	glewInit();
	
	// init the bufferobject and send points data
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glClearColor(background_color[0],background_color[1],background_color[2],background_color[3]);
	glViewport(0, 0, windowHeight, windowHeight);
			
	// read shaders code
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_triangle * 12 * sizeof(float), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	// read shaders code
	const char* vertex_shader = ReadShaderSource("vshader.glsl");
	const char* fragment_shader = ReadShaderSource("fshader.glsl");
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	shader_programme = glCreateProgram(); 
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
		
	//set uniform location of shaders (used for transformation)
	GLint offsetLoc1 = glGetUniformLocation(shader_programme, "offset1");
	GLint offsetLoc2 = glGetUniformLocation(shader_programme, "offset2");
	GLint offsetLoc3 = glGetUniformLocation(shader_programme, "offset3");
	
	//add text to the window using OTR library
	assert (init_text_rendering (atlas_image, atlas_meta, windowHeight, windowHeight));
	int time_id = add_text (
		"time:",
		-1.0f, 1.0f, 30.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	glfwSetKeyCallback(gl_window, key_callback);
	long i=0;
	while (!glfwWindowShouldClose (gl_window)) { 
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawCenterLines();
		//render the text
		if(i%2==0){
		double t = GAME_DURATION - glfwGetTime ();
		check_the_time(t);
		char tmp[256];
		sprintf (tmp, "Scoreboard:  %i-%i %f\n",player1Score,player2Score,t);
		update_text (time_id, tmp);
		change_text_colour (time_id, scoreboard_color[0], scoreboard_color[1], scoreboard_color[2], scoreboard_color[3]);
		draw_texts ();
		}
		
		//render the objects
               glUniform3fv(offsetLoc1, 1, offset1);
               glUniform3fv(offsetLoc2, 1, offset2);
               glUniform3fv(offsetLoc3, 1, offset3);
		glUseProgram (shader_programme);
		glBindVertexArray (vao);
		glDrawArrays (GL_TRIANGLES, 0, num_triangle*3);
		updateBall();
		updatePaddle();			
		glfwPollEvents ();
		glfwSwapBuffers (gl_window);
		i++;
	}
	
	
	glfwTerminate();
	return 0;
}
