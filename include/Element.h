#ifndef ELEMENT
#define ELEMENT

#include <iostream>

class Element {
    // Attributs
    protected:
        float posX, posY, posZ;

    // Constructeur et Méthodes
    public:
        Element();
        Element(float x, float y, float z);
        void setPos(float x, float y, float z);
        void translate(float x, float y, float z);
        float getX();
        float getY();
        float getZ();
};

#endif
