# Labyrinthe 3d

This is a school project where you can make a 3D maze that is built with an input file, you must pick up all the floating orbs that are scattered in the labyrinth before the time runs out.

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

## Problem with previous linux versions 
Some functions of the SDL library are not on the school's computers
https://stackoverflow.com/questions/74965014/sdl-vertex-and-sdl-rendergeometry-not-found

## Build Project
build : ``$ make``

clean : ``$ make mrproper``

launch app: ``$ ./main {levels in order}``

## Play the game
you must pick up all the floating orbs that are scattered in the labyrinth
before the time runs out.

The game controls are as follows:
- Z to move foward
- S to move backward
- Q to move to your left
- D to move to your right

- A allows you to turn the camera to the left
- E allows you to turn the camera to the right
- W allows you to lock your mouse and turn the camera with it

- There is also a secret key that allows you to see through walls

## Create a maze
create a text file, then fill it with the following characters:
- X : for a wall
- O : for a floor tile
- P : the place where the player will be placed
- I : the objects to pick up
