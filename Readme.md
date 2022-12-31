# Labyrinthe 3d

This is a school project where you can make a 3D maze that is built with an input file, you have to find the exit by moving with the mouse and keyboard. In this maze you will find objects and enemies.

Implemented features:
- Building an Environment
- Management of keyboard events
- Proper Maze reader
- Integration of a 3D view
- Management of mouse events
- Collectibles in maze
- Play multiple maze

Possible features:
- Main menu with options

## Build Project
*Makefile update comming soon* 

build (linux): ``$ g++ -o main -I include src/*.cpp $(sdl2-config --cflags --libs)``

build (windows): ``$ g++ -o main -L lib -I include ./src/*.cpp -lmingw32 -lSDL2main -lSDL2 ;``

launch app: ``$ ./main {levels in order}``

## Create a maze
create a text file, then fill it with the following characters:
- X : for a wall
- O : for a floor tile
- P : the place where the player will be placed
- I : the objects to pick up