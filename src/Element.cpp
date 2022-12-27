#include "Element.h"

Element::Element(){
    posX = 0.0f;
    posY = 0.0f;
    posZ = 0.0f;
}

Element::Element(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}

void Element::setPos(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}

void Element::translate(float x, float y, float z){
    posX += x;
    posY += y;
    posZ += z;
}

float Element::getX(){
    return posX; 
}

float Element::getY(){
    return posX; 
}

float Element::getZ(){
    return posX; 
}
