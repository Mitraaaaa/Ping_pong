
// Mitra Omrani
// student number : 993613047

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION // there were some errors on my system and were removed adding this definition O_O
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/*
 HOW TO PLAY:
 
 GO UP WITH PADDLE LEFT : w
 GO DOWN WITH PADDLE LEFT : s
 GO UP WITH PADDLE RIGHT : i
 GO DOWN WITH PADDLE RIGHT : k
 
 MAKE SURE YOUR KEYBOARD IS IN **ENGLISH** MODE
 */

int windowWidth = 800;
int windowHeight = 600;

// Define the initial position of the ball
float ballX = -0.5f;
float ballY = 0.0f;

const float paddleSpeed = 0.03f; // Increase this value to make the paddles move faster

// Define the initial position of the paddles
float paddle1Y = 0.0f;
float paddle2Y = 0.0f;

// Define the size of the paddles
float paddleWidth = 0.03f;
float paddleHeight = 0.3f;

// Define the size of the ball
float ballSize = 0.04f;

// Define the speed of the ball
float ballSpeedX = 0.01f;
float ballSpeedY = 0.01f;
float ballSpeed = 0.01f;

// Define the score of the players
int player1Score = 0;
int player2Score = 0;

// These booleans are defined in order to lock the paddle when it hits the end of the window ( not to cross the boarder)
bool paddle1Up = false;
bool paddle1Down = false;
bool paddle2Up = false;
bool paddle2Down = false;

const int GAME_DURATION = 60; // seconds
int frameCount = 0;

// Button position and size
float buttonX = -0.8f;
float buttonY = -0.8f;
float buttonSize = 0.1f;


void drawTimer() {
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Calculate elapsed time in seconds
    int elapsedTime = (frameCount) / 60;

    // Convert elapsed time to string
    std::string timerString = "Time: " + std::to_string(elapsedTime) + "s";

    // Set the position for drawing text
    glRasterPos2f(-0.8f, 0.8f);

    // Draw the timer text
    for (char c : timerString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
void draw_speed_button(){
    // Draw the button
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(buttonX, buttonY);
        glVertex2f(buttonX + buttonSize, buttonY);
        glVertex2f(buttonX + buttonSize, buttonY + buttonSize);
        glVertex2f(buttonX, buttonY + buttonSize);
        glEnd();

        // Draw the '-' sign
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(buttonX + buttonSize / 4, buttonY + buttonSize / 2);
        glVertex2f(buttonX + buttonSize * 3 / 4, buttonY + buttonSize / 2);
        glEnd();

        buttonX += buttonSize+0.01;
        // Draw the '+' sign
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(buttonX, buttonY);
        glVertex2f(buttonX + buttonSize, buttonY);
        glVertex2f(buttonX + buttonSize, buttonY + buttonSize);
        glVertex2f(buttonX, buttonY + buttonSize);
        glEnd();
    
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(buttonX + buttonSize / 4, buttonY + buttonSize / 2);
        glVertex2f(buttonX + buttonSize * 3 / 4, buttonY + buttonSize / 2);
        glVertex2f(buttonX + buttonSize / 2, buttonY + buttonSize / 4);
        glVertex2f(buttonX + buttonSize / 2, buttonY + buttonSize * 3 / 4);

        buttonX -= buttonSize+0.01;
        glEnd();
}

void mouse(int button, int state, int x, int y) {
    // Check if the left mouse button is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Check if the click is within the '+' button
        float normalizedX = ((float)x / (windowWidth/2)) - 1.0f;
        float normalizedY =  1.0f -((float)y / (windowHeight/2));
        
        if (normalizedX >= buttonX + buttonSize + 0.01 && normalizedX <= buttonX + 2 * buttonSize + 0.01 &&
            normalizedY >= buttonY && normalizedY <= buttonY + buttonSize) {
            // Increase the value
            if (ballSpeedX>=0)
                ballSpeedX += 0.005f;
            else ballSpeedX-=  0.005f;
            
            if (ballSpeedY>=0)
                ballSpeedY += 0.005f;
            else ballSpeedY-=  0.005f;
        }
        // Check if the click is within the '-' button
        else if (normalizedX >= buttonX && normalizedX <= buttonX + buttonSize &&
                 normalizedY >= buttonY && normalizedY <= buttonY + buttonSize) {
            // Decrease the value
            if (ballSpeedX>=0)
                ballSpeedX -= 0.005f;
            else ballSpeedX+=  0.005f;
            
            if (ballSpeedY>=0)
                ballSpeedY -= 0.005f;
            else ballSpeedY +=  0.005f;
        }
    }
}

void updatePaddles() {
    // Update the position of the left paddle
    if (paddle1Up && paddle1Y + paddleHeight / 2 < 1.0f) {
        paddle1Y += paddleSpeed;
    }
    if (paddle1Down && paddle1Y - paddleHeight / 2 > -1.0f) {
        paddle1Y -= paddleSpeed;
    }

    // Update the position of the right paddle
    if (paddle2Up && paddle2Y + paddleHeight / 2 < 1.0f) {
        paddle2Y += paddleSpeed;
    }
    if (paddle2Down && paddle2Y - paddleHeight / 2 > -1.0f) {
        paddle2Y -= paddleSpeed;
    }
}

void drawCenterLines() {
    // Draw the dotted line
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(15, 0xAAAA);
        glBegin(GL_LINES);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
}


void keyboard(unsigned char key, int x, int y) {
    // Handle keyboard input for paddle movement
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
    // Handle keyboard input for stopping paddle movement
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

void drawPaddles() {
    // Draw the left paddle
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.0f + paddleWidth / 2, paddle1Y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, paddleHeight / 2);
    glVertex2f(paddleWidth, paddleHeight / 2);
    glVertex2f(paddleWidth, -paddleHeight / 2);
    glVertex2f(0.0f, -paddleHeight / 2);
    glEnd();
    glPopMatrix();

    // Draw the right paddle
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(1.0f - paddleWidth / 2, paddle2Y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, paddleHeight / 2);
    glVertex2f(-paddleWidth, paddleHeight / 2);
    glVertex2f(-paddleWidth, -paddleHeight / 2);
    glVertex2f(0.0f, -paddleHeight / 2);
    glEnd();
    glPopMatrix();
}


void drawBall(float x, float y) {
    glColor3f(1.0f, 1.0, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    // Draw the ball round not square , with the radius of ballsize
    gluDisk(gluNewQuadric(), 0.0f, ballSize, 32, 1);
    glPopMatrix();
}


void updateBall() {
    // Update the position of the ball
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    
    /* Check the collision */
    
    // Check if the ball hits the top or bottom wall
    if (ballY + ballSize > 1.0f || ballY - ballSize < -1.0f) {
        ballSpeedY = -ballSpeedY;
    }
    /*
     The paddleHeight is divided by 2 because the paddle's Y position (paddle1Y and paddle2Y) is typically set to the center of the paddle. By dividing the height by 2, we can calculate the top and bottom edges of the paddle relative to its center position.
     For example, if the paddle's height is 0.2 units and its center Y position is 0.5 units, then the top edge of the paddle would be at 0.5 + (0.2 / 2) = 0.6 units, and the bottom edge would be at 0.5 - (0.2 / 2) = 0.4 units.
     */
    
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
        ballX = -0.6f;
        ballY = 0.0f;
        ballSpeedX = -ballSpeedX;
    }

    if (ballX + ballSize > 1.0f) {
        player1Score++;
        ballX = 0.6f;
        ballY = 0.0f;
        ballSpeedX = -ballSpeedX;
    }
}

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // create center lines
    drawCenterLines();
    
    // Draw the player scores
       glColor3f(1.0f, 1.0f, 1.0f);
       glRasterPos2f(-0.1f, 0.8f);
       std::string player1ScoreStr = std::to_string(player1Score);
       for (char c : player1ScoreStr) {
           glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
       }
       glRasterPos2f(0.1f, 0.8f);
       std::string player2ScoreStr = std::to_string(player2Score);
       for (char c : player2ScoreStr) {
           glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
       }

    // Draw the paddles
    drawPaddles();

    // Draw the ball
    drawBall(ballX, ballY);
    
    // Draw the timer
    drawTimer();
    
    draw_speed_button();
    
    // Swap the buffers
    glutSwapBuffers();
}

void update(int value) {
    // Update the paddles
    updatePaddles();

    // Update the position of the ball
    updateBall();

    
    // Update the elapsed time
    frameCount++;
    // Check if the game duration has been reached
    if (frameCount / 60 >= GAME_DURATION) {
            std::cout << "Game over! Time's up." << std::endl;
            exit(0);
        }
    // Redraw the game
   glutPostRedisplay();
    // Call the update function again after 16 milliseconds
   glutTimerFunc(16, update, 0); // Assuming 60 FPS
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pong");
    // Set up the display, update, and keyboard functions
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);

    // Enter the main loop
    glutMainLoop();

    return 0;
}
