# Ping_pong
 C++ program that implements the classic game Pong using the OpenGL library

## Overall explanation:

This project creates a two-player Pong game where each player controls a paddle to hit a ball back and forth. The project utilizes graphic programming techniques to render the game elements, handle user input for paddle movement, and detect ball and paddle collisions. The code is structured with functions for updating the game state and rendering graphics.

## How to Run the Program:

To run the program, execute the following commands in the file where the code is located:
```
for windows user: 
g++ -framework OpenGL -framework GLUT main.cpp -o mitra-pong
./mitra-pong

for linux user:
g++ Pong_MitraOmrani_5.cpp -o mitra-pong -lGL -lGLU -lglut -lGLEW -lglfw
./mitra-pong
```
## Versions differences

### version 1
its a very simple implemention of the game.
### version 2
A little enhancement has been done to version 1, like:
1. **Dynamic Ball Speed:** The Pong game now supports dynamic adjustments to the ball's speed. Players can modify the ball's velocity during gameplay, offering greater control and enhancing gameplay variety.

2. **Game Timer:** A mandatory game timer is displayed on the screen. After a predetermined duration, it restricts further gameplay, adding a time-based element to the game experience.

### version 3
A little code clearance has been done to version 2.

### version 4 (incomplete)
trying to use advanced mode to run rendering code on gpu using Glut & glsl language.

### version 5
this version run rendering code on gpu on advanced mode using glfw & glsl language.
in addition you can render the score line with your favorite font thanks to [OTR library](https://github.com/capnramses/opengl_text_rendering)
## Version 1
![giff](https://github.com/Mitraaaaa/Ping_pong/assets/83425856/aef36a37-a5b4-4b92-9442-4c835241d87c)


## Version 2
![giff2_1](https://github.com/Mitraaaaa/Ping_pong/assets/83425856/78b1c302-acd9-463b-bf3c-bbb9aa812c19)


## Note
Read the attached document for each version for further informations.
