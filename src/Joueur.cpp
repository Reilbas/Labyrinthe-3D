#include "Joueur.h"

Joueur::Joueur(){
    rotX = 0.0f;
    rotY = 0.0f;
}

Joueur::Joueur(float x, float y, float z) : Element(x, y, z) {
    rotX = 0.0f;
    rotY = 0.0f;
}

void Joueur::print(){
    std::cout << "X:" << posX << " Y:" << posY << " Z:" << posZ << " Rx:" << rotX << " Ry:" << rotY << std::endl;
}

void Joueur::rotate(float x, float y){
    rotX += x;
    rotY += y;
}

Joueur::~Joueur(){
    //delete la cam
}