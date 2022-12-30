#include "Joueur.h"
#define speed 0.5f

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

void Joueur::avancer(bool** env, int L, int l){
    vec3d proj = AllMath::addVector(vCam, vForward);
    if((proj.x >= 0) && (proj.x < L+1) && (proj.z >= 0) && (proj.z < l+1)){
        if(!env[(int)std::floor(proj.x)][(int)std::floor(proj.z)]){
            vCam = proj;
        }
    }
    this->maj();
}

void Joueur::reculer(bool** env, int L, int l){
    vec3d proj = AllMath::subVector(vCam, vForward);
    if((proj.x >= 0) && (proj.x < L+1) && (proj.z >= 0) && (proj.z < l+1)){
        if(!env[(int)std::floor(proj.x)][(int)std::floor(proj.z)]){
            vCam = proj;
        }
    }
    this->maj();
}

void Joueur::droite(bool** env, int L, int l){
    vec3d proj = AllMath::addVector(vCam, vRight);
    if((proj.x >= 0) && (proj.x < L+1) && (proj.z >= 0) && (proj.z < l+1)){
        if(!env[(int)std::floor(proj.x)][(int)std::floor(proj.z)]){
            vCam = proj;
        }
    }
    this->maj();
}

void Joueur::gauche(bool** env, int L, int l){
    vec3d proj = AllMath::subVector(vCam, vRight);
    if((proj.x >= 0) && (proj.x < L+1) && (proj.z >= 0) && (proj.z < l+1)){
        if(!env[(int)std::floor(proj.x)][(int)std::floor(proj.z)]){
            vCam = proj;
        }
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
