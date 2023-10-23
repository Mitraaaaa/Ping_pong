# Ping_pong
 C++ program that implements the classic game Pong using the OpenGL library

# Overall explanation:

This project creates a two-player Pong game where each player controls a paddle to hit a ball back and forth. The project utilizes graphic programming techniques to render the game elements, handle user input for paddle movement, and detect ball and paddle collisions. The code is structured with functions for updating the game state and rendering graphics.

# How to Run the Program:

To run the program, execute the following command in the file where the code is located:
``` 
g++ -framework OpenGL -framework GLUT main.cpp -o main
./main
```
# Version 1 vs version 2

Version 2 of the code introduces the following notable changes compared to Version 1:

1. **Dynamic Ball Speed:** The Pong game now supports dynamic adjustments to the ball's speed. Players can modify the ball's velocity during gameplay, offering greater control and enhancing gameplay variety.

2. **Game Timer:** A mandatory game timer is displayed on the screen. After a predetermined duration, it restricts further gameplay, adding a time-based element to the game experience.


## Version1
![Version 1](https://github.com/Mitraaaaa/Ping_pong/tree/main/version1/giff.giff)

Functions:

# updatePaddles: 
This function updates the position of each paddle when changes occur. The extent of this change will be based on the speed defined for the paddle initially.

# drawCenterLines: 
This function is used to draw the dashed line in the middle of the display window to separate the game area for both players.

# keyboard: 
The keys used in this game for the right paddle are "i" and "k," and for the left paddle are "w" and "s". In this function, boolean variables are set according to the direction and movement of the paddle. In other words, when the left paddle is moving upwards, the rest of the variables for other directions and sides will have a value of false.

# keyboardUp: 
After the movement of the desired paddle, this function sets the boolean value to false so that it cannot be moved again until the next movement. In other words, for example, when the right paddle is moving upwards, this value should be locked or, in other words, set to false for the left paddle.

# drawPaddles: 
In this function, based on the values including the size and position of the paddle, the current positions of the right and left paddles are drawn.

# drawBall: 
This function draws the ball as a circle based on its size and position.

# updateBall: 
In this function, the collision of the ball with either of the paddles or the walls is checked, and the ball's position is updated accordingly. For example, if there's a collision, the ball's speed is reversed because its direction will change.

# display: 
In this function, in addition to the visual details of the game, such as the line between the two players, the position of the ball and paddles, and the scores of each player on their respective sides, are written using the fonts provided by the GLUT library.

# update: 
In this function, all updates related to the ball and paddles are performed.

# main: 
In the main part of the program, details such as window size are selected, and the display and keyboard functions are called. This part is repeated regularly.
