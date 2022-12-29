#ifndef JOUEUR
#define JOUEUR

#include <iostream>
#include "Element.h"

class Joueur : public Element {
    // Attributs
    public:
        int pv; // point de vie
        float rotX, rotY;
        
    // Constructeur et Méthodes
    public:
        Joueur();
        Joueur(float x, float y, float z);
        ~Joueur();
        void rotate(float x, float y);
        void print();
};

#endif
