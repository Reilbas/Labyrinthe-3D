#include "Joueur.h"
//#define speed 2.0f

Joueur::Joueur(){
    vCam = {0.0f, 0.0f, 0.0f};
    rotY = 0.0f;
    this->maj();
}

Joueur::Joueur(float x, float y, float z){
    vCam = {x, y, z};
    rotY = 0.0f;
    this->maj();
}

void Joueur::setPos(float nX, float nY, float nZ){
    vCam.x = nX;
    vCam.y = nY;
    vCam.z = nZ;
}

void Joueur::maj(){
    vUp = {0.0f,1.0f,0.0f};
    vTarget = {0.0f,0.0f,1.0f};

    matCamRot = AllMath::rotMatY(rotY);

    vlookDir =  AllMath::matrixMultVector(matCamRot, vTarget);
    vTarget = AllMath::addVector(vCam, vlookDir);

    vForward = AllMath::mulVector(vlookDir, speed);
    vRight = {vForward.z, 0, -vForward.x};
}

void Joueur::avancer(){
    vCam = AllMath::addVector(vCam, vForward);
    if(speed < maxSpeed){
        speed += 0.03f;
    }
    this->maj();
}

void Joueur::reculer(){
    vCam = AllMath::subVector(vCam, vForward);
        if(speed < maxSpeed){
        speed += 0.03f;
    }
    this->maj();
}

void Joueur::droite(){
    vCam = AllMath::addVector(vCam, vRight);
        if(speed < maxSpeed){
        speed += 0.03f;
    }
    this->maj();
}

void Joueur::gauche(){
    vCam = AllMath::subVector(vCam, vRight);
    if(speed < maxSpeed){
        speed += 0.03f;
    }
    this->maj();
}

void Joueur::rotationY(float a){
    rotY += a;
    this->maj();
}

void Joueur::print(){
    std::cout << "X:" << vCam.x << " Y:" << vCam.y << " Z:" << vCam.z << " Ry:" << rotY << std::endl;
}

Joueur::~Joueur(){
    //delete la cam
}