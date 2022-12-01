# Labyrinthe 3d

This is a school project where you can make a 3D maze that is built with an input file, you have to find the exit by moving with the mouse and keyboard. In this maze you will find objects and enemies.

Implemented features:


Incomming features:
- Building an Environment (2D view)
- Management of keyboard events
- Proper Maze reader
- Integration of a 3D view
- Management of mouse events
- Collectibles and Enemies in maze
- Maze maker or Saving your progress
- Main menu with options

## Build Project
*Makefile update comming soon* 

build (linux): ``$ g++ -L lib -I include ./src/*.cpp -o main -lSDL2main -lSDL2``

build (windows): ``$ g++ -L lib -I include ./src/*.cpp -o main -lmingw32 -lSDL2main -lSDL2  -mwindows``

launch app: ``$ ./main``


## Create a maze
***TODO**
