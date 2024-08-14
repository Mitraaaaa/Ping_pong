#include <iostream>
#include <GL/glut.h>

// game properties
int windowWidth = 1700;
int windowHeight = 850;
const float frame_per_second = 60;
const float background_color[4] = {0.3593f,0.3242f,0.2734f,0.0f};
const int GAME_DURATION = 120;
int frameCount = 0;

// centerline properties
const float centerline_color[3] = {0.7929f,0.6367f,0.1562f};
const int factor = 15; 
const int pattern = 0xAAAA;

// paddles properties
float paddle1Y = 0.0f;
float paddle2Y = 0.0f;
const float paddle1s_color[3] = {0.7929f,0.6367f,0.1562f};
const float paddle2s_color[3] = {0.7929f,0.6367f,0.1562f};
const float paddleSpeed = 0.02f;
float paddleWidth = 0.01f;
float paddleHeight = 0.3f;

// balls properties
float ballSpeedX = 0.006f;
float ballSpeedY = 0.006f;
float ballSpeed = 0.003f;
float ballSize = 0.01f;
float ballX = -0.5f;
float ballY = 0.0f;
const int angles_number = 60;
const float balls_color[3] = {0.7929f,0.6367f,0.1562f};

// players score properties
int player1Score = 0;
int player2Score = 0;
const float playersScores_color[3] = {0.7929f,0.6367f,0.1562f};
const float player1pos_color[2] = {-0.1f, 0.8f};
const float player2pos_color[2] = {0.1f, 0.8f};

// timer properties
const float timers_color[3] = {0.7929f,0.6367f,0.1562f};
const float timers_pos[2] = {-0.8f, 0.8f};

//  control paddles not to go out of the window
bool paddle1Up = false;
bool paddle1Down = false;
bool paddle2Up = false;
bool paddle2Down = false;

void drawTimer() {    
    glColor3f(timers_color[0], timers_color[1], timers_color[2]);
    
    // Calculate elapsed time, frameCount dividing  FPS
    int elapsedTime = (frameCount) / frame_per_second;
    // Calculate remaining time, game duration minus elapsed time
    int remainedTime = GAME_DURATION - elapsedTime;

    // Convert remained time to string
    std::string timerString = "Time: " + std::to_string(remainedTime) + "s";

    // Set the position for drawing text
    glRasterPos2f(timers_pos[0], timers_pos[1]);

    // Draw the timer text
    for (char c : timerString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
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
        glColor3f(centerline_color[0],centerline_color[1],centerline_color[2]);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(factor, pattern);
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
    glColor3f(paddle1s_color[0], paddle1s_color[1], paddle1s_color[2]);
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
    glColor3f(paddle2s_color[0], paddle2s_color[1], paddle2s_color[2]);
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
    glColor3f(balls_color[0],balls_color[1],balls_color[2]); // set the balls color
    glPushMatrix();
    glTranslatef(x, y, 0); // move the ball
    glScalef(1, 2, 1);// scale the ball through y axis in order to preventing it to became an oval
    
    // Draw a round ball , with the radius of ballsize
    gluDisk(gluNewQuadric(), 0, ballSize, angles_number, 1);
    
    glPopMatrix();
}

void Draw_player1_score(){
       // draw player1 score on the screen
       glRasterPos2f(player1pos_color[0], player1pos_color[1]);
       std::string player1ScoreStr = std::to_string(player1Score);
       for (char c : player1ScoreStr) {
           glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
       }
}

void Draw_player2_score(){
       // draw player2 score on the screen
       glRasterPos2f(player2pos_color[0], player2pos_color[1]);
       std::string player2ScoreStr = std::to_string(player2Score);
       for (char c : player2ScoreStr) {
           glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
       }
}

void check_the_time(){
         // check if the time is up End the game
         if (frameCount / frame_per_second >= GAME_DURATION) {
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


void updateBall() { 
    // Update balls speed
    ballX += ballSpeedX;
    ballY += ballSpeedY;
       
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
        ballX = -0.6f;
        ballY = 0.0f;
        ballSpeedX = -ballSpeedX;
    }
 
    // Check if the ball goes out of bounds
    if (ballX + ballSize > 1.0f) {
        player1Score++;
        ballX = 0.6f;
        ballY = 0.0f;
        ballSpeedX = -ballSpeedX;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    
    glClearColor(background_color[0],background_color[1],background_color[2], background_color[3]);
    // Set background color
    
    glColor3f(playersScores_color[0],playersScores_color[1],playersScores_color[2]);
    // Set score text color
         
    Draw_player1_score(); // Draw player2 score
    Draw_player2_score(); // Draw player2 score
    drawCenterLines(); // Create center lines
    drawPaddles(); // Draw the paddles
    drawBall(ballX, ballY); // Draw the ball
    drawTimer(); // Draw the timer
    glutSwapBuffers(); // Swap the buffers
}

void update(int value) {
    updatePaddles(); //Update the paddles   
    updateBall(); //Update the position of the ball        
    frameCount++;// Update the elapsed time        
    check_the_time();// Check if the game duration has been reached        
    glutPostRedisplay();// Redraw the game    
      
    glutTimerFunc(1000.0f/frame_per_second, update, 0); 
    // Call the update function every (1/frame_per_second) miliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);// Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set init display mode
    glutInitWindowSize(windowWidth, windowHeight); // Set init display mode
    glutCreateWindow("Ping-Pong"); // Set windows name
    glutDisplayFunc(display); // Set up the display function
    
    glutTimerFunc(1000.0f/frame_per_second, update, 0);
    // Call the update function every (1/frame_per_second) miliseconds
    
    glutKeyboardFunc(keyboard); // Set Keyboard Funcion call
    glutKeyboardUpFunc(keyboardUp); // Set Keyboard up Funcion call
    glutMainLoop(); // Enter the main loop
    return 0;
}

