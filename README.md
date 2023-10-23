# Ping_pong
 C++ program that implements the classic game Pong using the OpenGL library

## Overall explanation:

This project creates a two-player Pong game where each player controls a paddle to hit a ball back and forth. The project utilizes graphic programming techniques to render the game elements, handle user input for paddle movement, and detect ball and paddle collisions. The code is structured with functions for updating the game state and rendering graphics.

## How to Run the Program:

To run the program, execute the following command in the file where the code is located:
``` 
g++ -framework OpenGL -framework GLUT main.cpp -o main
./main
```
## Version 1 vs version 2

Version 2 of the code introduces the following notable changes compared to Version 1:

1. **Dynamic Ball Speed:** The Pong game now supports dynamic adjustments to the ball's speed. Players can modify the ball's velocity during gameplay, offering greater control and enhancing gameplay variety.

2. **Game Timer:** A mandatory game timer is displayed on the screen. After a predetermined duration, it restricts further gameplay, adding a time-based element to the game experience.


## Version 1
![Version 1](https://github.com/Mitraaaaa/Ping_pong/version%201/giff.gif)

## Version 2
![Version 2](https://github.com/Mitraaaaa/Ping_pong/version%202/giff2.gif)


## Functions in Version 1:

### updatePaddles: 
This function updates the position of each paddle when changes occur. The extent of this change will be based on the speed defined for the paddle initially.

### drawCenterLines: 
This function is used to draw the dashed line in the middle of the display window to separate the game area for both players.

### keyboard: 
The keys used in this game for the right paddle are "i" and "k," and for the left paddle are "w" and "s". In this function, boolean variables are set according to the direction and movement of the paddle. In other words, when the left paddle is moving upwards, the rest of the variables for other directions and sides will have a value of false.

### keyboardUp: 
After the movement of the desired paddle, this function sets the boolean value to false so that it cannot be moved again until the next movement. In other words, for example, when the right paddle is moving upwards, this value should be locked or, in other words, set to false for the left paddle.

### drawPaddles: 
In this function, based on the values including the size and position of the paddle, the current positions of the right and left paddles are drawn.

### drawBall: 
This function draws the ball as a circle based on its size and position.

### updateBall: 
In this function, the collision of the ball with either of the paddles or the walls is checked, and the ball's position is updated accordingly. For example, if there's a collision, the ball's speed is reversed because its direction will change.

### display: 
In this function, in addition to the visual details of the game, such as the line between the two players, the position of the ball and paddles, and the scores of each player on their respective sides, are written using the fonts provided by the GLUT library.

### update: 
In this function, all updates related to the ball and paddles are performed.

### main: 
In the main part of the program, details such as window size are selected, and the display and keyboard functions are called. This part is repeated regularly.


## Added and Modified Functions in Version 2:

### draw_timer:
In this function, frameCount is divided by 60 to calculate the elapsed time, and then it is displayed at the top-left of the screen.

### draw_speed_button:
In this function, two buttons, one with the "-" sign to decrease speed and the other with the "+" sign to increase speed, are drawn. The background color and the positions of these buttons are specified using global variables. The type of connections between points depends on whether we are drawing a sign or a button (GL_QUADS and GL_LINES).

### mouse:
In this function, the mouse's position is determined. If the click is on the "+" button, the speed increases by 0.005f; otherwise, it decreases.

* Note: In the default state, the coordinates provided by x and y are not in the -1 to 1 range. Therefore, to make accurate and consistent comparisons, they are normalized to match the initial values of buttonX and buttonY.

Additionally, it's important to consider the speed sign, as it determines the direction, and adjusting the values accordingly. The sign is crucial for determining the coordinates of a point at any given moment.

### display:
This function is responsible for drawing the timer and the added button, retaining its previous functionality.

### update:
This function handles all updates related to the ball and paddles. It also calculates the time to reach the specified competition duration. If the time runs out, the game window is closed.

### main:
In the main part of the program, details such as window size are determined. Functions such as display and keyboard actions are called. This section is repeatedly executed. Additionally, the mouse function is added to this part of the code.
