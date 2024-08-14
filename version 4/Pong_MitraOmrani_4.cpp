// mehrdad ghassabi
// student number : 4023614029
// Run with: g++ Pong_MitraOmrani_4.cpp -o mitra-pong -lGL -lGLU -lglut -lGLEW -lglfw
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

//#pragma comment(lib,"glew32.lib")
#define NoP 50
using namespace std;

float paddle1Y = 0.0f;
float paddle2Y = 0.0f;

GLuint InitShader(char *, char *);
void mydisplay();
void updateBall();
void drawCenterLines();
GLuint thetaHandle1;  // theta1 uniform location
GLuint thetaHandle2;  // theta2 uniform location
GLuint thetaHandle3;  // theta2 uniform location

float paddleWidth = 0.03f;
float paddleHeight = 0.3f;
const float paddleSpeed = 0.02f;
GLfloat Theta1[3] = { 0.0,0.0,0.0 };//determins the movement aroun x, y and z axes
GLfloat Theta2[3] = { 0.0,0.0,0.0 };//determins the movement aroun x, y and z axes
GLfloat Theta3[3] = { 0.0,0.0,0.0 };//determins the movement aroun x, y and z axes
GLuint windowid1;

// centerline properties
const float centerline_color[3] = {0.0, 0.0, 1.0};
const int factor = 15; 
const int pattern = 0xAAAA;

//  control paddles not to go out of the window
bool paddle1Up = false;
bool paddle1Down = false;
bool paddle2Up = false;
bool paddle2Down = false;

// players score properties
int player1Score = 0;
int player2Score = 0;
const float playersScores_color[3] = {0.7929f,0.6367f,0.1562f};


class points
{
public:
	GLfloat	x, y, z, w;
	points()
	{
		x = y = z = 0;
		w = 1;
	}
	points(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat iw)
	{
		x = ix; y = iy; z = iz; w = iw;
	}
	points(GLfloat ix, GLfloat iy, GLfloat iz)
	{
		x = ix; y = iy; z = iz; w = 1;
	}

};
class Vcolors
{
public:
	GLfloat r, g, b, a;
	Vcolors()
	{
		r = g = b = 0; a = 1;
	}
	Vcolors(GLfloat ir, GLfloat ig, GLfloat ib, GLfloat ia)
	{
		r = ir; g = ig; b = ib; a = ia;
	}
	Vcolors(GLfloat ir, GLfloat ig, GLfloat ib)
	{
		r = ir; g = ig; b = ib;
	}
};
void Creat2Triangle(int, int, int, int);
void colorcube();
void init();
void CubePoints(points[], Vcolors[]);
points Tpoints[NoP];
Vcolors Tcolors[NoP];
int Index = 0;
points	vertex_positions[12];
Vcolors	vertex_colors[12];
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;
float step = 0.5;
void idle();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
void keyboardUp(unsigned char, int, int);

// balls properties
float ballSpeedX = 0.006f;
float ballSpeedY = 0.006f;
float ballSpeed = 0.003f;
float ballSize = 0.02f;
float ballX = 0.0f;
float ballY = 0.0f;

const float balls_color[3] = {0.7929f,0.6367f,0.1562f};


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple OpenGL example");
	glewInit();
	init();
	glutDisplayFunc(mydisplay);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMainLoop();
}


void init()
{
	GLuint buffer;
	CubePoints(vertex_positions, vertex_colors);

	GLuint program;
	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tpoints) + sizeof(Tcolors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Tpoints), Tpoints);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Tpoints), sizeof(Tcolors), Tcolors);

	GLuint loc = glGetAttribLocation(program, "points");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_TRUE, 0, 0);//BUFFER_OFFSET(0));
	GLuint vc = glGetAttribLocation(program, "Vcolors");
	glEnableVertexAttribArray(vc);
	glVertexAttribPointer(vc, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) sizeof(Tpoints));

	thetaHandle1 = glGetUniformLocation(program, "theta1");
	thetaHandle2 = glGetUniformLocation(program, "theta2");
	thetaHandle3 = glGetUniformLocation(program, "theta3");
	
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}


void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the clear call will affect the color buffer
	glUniform3fv(thetaHandle1, 1, Theta1);
	glUniform3fv(thetaHandle2, 1, Theta2);
	glUniform3fv(thetaHandle3, 1, Theta3);
	glDrawArrays(GL_TRIANGLES, 0, NoP);  //Rendering
	drawCenterLines();
        glPopMatrix();    
	glutSwapBuffers();  //Swap front and back buffers
}

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
GLuint InitShader(char * vShaderFile, char * fShaderFile)
{
	char * svs, *sfs;
	GLuint program, VertexShader, FragmentShader;

	program = glCreateProgram();
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	svs = ReadShaderSource(vShaderFile);
	printf("\n %s", svs);
	glShaderSource(VertexShader, 1, (const GLchar **)&svs, NULL);
	glCompileShader(VertexShader);
	glAttachShader(program, VertexShader);

	GLint compiled;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printf("/n failed to compile");
		GLint logSize;
		glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &logSize);
		char * logMsg = new char[logSize];
		glGetShaderInfoLog(VertexShader, logSize, NULL, logMsg);
		printf("\n  %s", logMsg);
		getchar();
		delete[] logMsg;
		exit(EXIT_FAILURE);
	}

	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	sfs = ReadShaderSource(fShaderFile);
	printf("\n  %s", sfs);
	glShaderSource(FragmentShader, 1, (const GLchar **)&sfs, NULL);
	glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printf("\n failed to compile");
		GLint logSize2;
		glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &logSize2);
		char logMsg2[161];// = new char[162];//logSize2];
		glGetShaderInfoLog(FragmentShader, logSize2, NULL, logMsg2);
		printf("\n  %s", logMsg2);
		getchar();
		delete[] logMsg2;
		exit(EXIT_FAILURE);
	}

	glAttachShader(program, FragmentShader);
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		printf("/n failed to link");
		GLint logSize;
		glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &logSize);
		char * logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		printf("\n  %s", logMsg);
		delete[] logMsg;
		exit(EXIT_FAILURE);
	}

	glUseProgram(program);
	return program;
}
void CubePoints(points vertex_positions[], Vcolors vertex_colors[])
{

	vertex_positions[0] = points(-0.96, paddleHeight / 2, 0, 1.01);
	vertex_positions[1] = points(-paddleWidth-0.96, paddleHeight / 2, 0, 1.01);
	vertex_positions[2] = points(-paddleWidth-0.96, -paddleHeight / 2, 0, 1.01);
	vertex_positions[3] = points(-0.96, -paddleHeight / 2, 0, 1.01);
	paddle1Y = (vertex_positions[0].y + vertex_positions[1].y + vertex_positions[2].y + vertex_positions[3].y)/4 ;
	
	vertex_positions[4] = points(1.00, paddleHeight / 2, 0, 1.02);
	vertex_positions[5] = points(-paddleWidth+1.00, paddleHeight / 2, 0, 1.02);
	vertex_positions[6] = points(-paddleWidth+1.00, -paddleHeight / 2, 0, 1.02);
	vertex_positions[7] = points(1.00, -paddleHeight / 2, 0, 1.02);
	paddle2Y = (vertex_positions[4].y + vertex_positions[5].y + vertex_positions[6].y + vertex_positions[7].y)/4 ;
	
	vertex_positions[8] = points(0.02, 0.02, 0.0, 1.03);
	vertex_positions[9] = points(-0.02, 0.02, 0.0, 1.03);
	vertex_positions[10] = points(-0.02, -0.02, 0.0, 1.03);
	vertex_positions[11] = points(0.02, -0.02, 0.0, 1.03);
	ballX =  (vertex_positions[8].x + vertex_positions[9].x + vertex_positions[10].x + vertex_positions[11].x)/4 ;
        ballY =  (vertex_positions[8].y + vertex_positions[9].y + vertex_positions[10].y + vertex_positions[11].y)/4 ;


	vertex_colors[0] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[1] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[2] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[3] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
		
	vertex_colors[4] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[5] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[6] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[7] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	
	vertex_colors[8] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[9] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[10] = Vcolors(0.0,0.0, 1.0, 1.0);  // blue
	vertex_colors[11] = Vcolors(0.0,0.0, 1.0, 1.0);  // blue	

	colorcube();
}
void colorcube()
{
	Creat2Triangle(1, 0, 3, 2);
	Creat2Triangle(5, 4, 7, 6);
	Creat2Triangle(9, 8, 11, 10);

}
void Creat2Triangle(int a, int b, int c, int d)
{
	Tcolors[Index] = vertex_colors[a]; Tpoints[Index] = vertex_positions[a]; Index++;
	Tcolors[Index] = vertex_colors[b]; Tpoints[Index] = vertex_positions[b]; Index++;
	Tcolors[Index] = vertex_colors[c]; Tpoints[Index] = vertex_positions[c]; Index++;
	Tcolors[Index] = vertex_colors[a]; Tpoints[Index] = vertex_positions[a]; Index++;
	Tcolors[Index] = vertex_colors[c]; Tpoints[Index] = vertex_positions[c]; Index++;
	Tcolors[Index] = vertex_colors[d]; Tpoints[Index] = vertex_positions[d]; Index++;
}
void idle()
{
   if (paddle1Up && paddle1Y + paddleHeight / 2 < 1.0f) {
        Theta1[1] += paddleSpeed;
        paddle1Y += paddleSpeed;
    }
     if (paddle1Down && paddle1Y - paddleHeight / 2 > -1.0f) {
        Theta1[1] -= paddleSpeed;
        paddle1Y -= paddleSpeed;
    }
    if (paddle2Up && paddle2Y + paddleHeight / 2 < 1.0f) {
        Theta2[1] += paddleSpeed;
        paddle2Y += paddleSpeed;
    }
    if (paddle2Down && paddle2Y - paddleHeight / 2 > -1.0f) {
        Theta2[1] -= paddleSpeed;
        paddle2Y -= paddleSpeed;
    }

	Theta3[0] += ballSpeedX;
	Theta3[1] += ballSpeedY;
	ballY +=ballSpeedY;
	ballX +=ballSpeedX;
	updateBall();

	glutPostRedisplay();
}

void updateBall() {     
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


void keyboard(unsigned char key, int x, int y)
{
switch (key) {
        case 'w':
            paddle1Up = true;
            break;
        case 's':
            paddle1Down = true;
            break;
        case 'i':
            paddle2Up = true;
            break;
        case 'k':
            paddle2Down = true;
            break;
    }	
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            paddle1Up = false;
            break;
        case 's':
            paddle1Down = false;
            break;
        case 'i':
            paddle2Up = false;
            break;
        case 'k':
            paddle2Down = false;
            break;
    }
}

void drawCenterLines() {
    // Draw the dotted line
        glColor3f(centerline_color[0],centerline_color[1],centerline_color[2]);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(factor, pattern);
        glBegin(GL_LINES);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
}

