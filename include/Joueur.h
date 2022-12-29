#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include "MeshMaker.h"
#include "AllMath.h"

class Joueur {
    // Attributs
    public:
        int pv; // point de vie
        vec3d vCam;
        float rotY;

        vec3d vUp = {0.0f,1.0f,0.0f};//---
        vec3d vTarget = {0.0f,0.0f,1.0f};//---

        mat4x4 matCamRot;
        vec3d vlookDir, vForward, vRight;
        
    // Constructeur et Méthodes
    public:
        Joueur();
        Joueur(float x, float y, float z);
        ~Joueur();
        void maj();
        void avancer();
        void reculer();
        void droite();
        void gauche();
        void setPos(float nX, float nY, float nZ);
        void print();
};

#endif
