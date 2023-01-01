#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include <math.h>
#include "MeshMaker.h"
#include "AllMath.h"

class Joueur {
    // Attributs
    public:
        int tempsRestant;
        vec3d vCam;
        float rotY;

        vec3d vUp = {0.0f,1.0f,0.0f};
        vec3d vTarget = {0.0f,0.0f,1.0f};

        mat4x4 matCamRot;
        vec3d vlookDir, vForward, vRight;
        
    // Constructeur et Méthodes
    public:
        Joueur();
        Joueur(float x, float y, float z);
        void maj();
        void avancer(bool** env, int L, int l);
        void reculer(bool** env, int L, int l);
        void droite(bool** env, int L, int l);
        void gauche(bool** env, int L, int l);
        void rotationY(float a);
        void setPos(float nX, float nY, float nZ);
        bool plusDeTemps();
        void print();
};

#endif
