#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <vector>
#include "MeshMaker.h"

class Element {
    // Attributs
    protected:
        float posX, posY, posZ;
        mesh geometry;

    // Constructeur et Méthodes
    public:
        Element(mesh m);
        Element(float x, float y, float z, mesh m);
        void setPos(float x, float y, float z);
        void translate(float x, float y, float z);
        float getX();
        float getY();
        float getZ();
};

#endif
