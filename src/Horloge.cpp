#include "Horloge.h"

Horloge* Horloge::instance = NULL;

Horloge* Horloge::getInstance(){
    if(instance == NULL){
        instance = new Horloge();
    }
    return instance;
}

void Horloge::detruire(){
    delete instance;
    instance = NULL;
}

Horloge::Horloge(){
    reset();
}

Horloge::~Horloge(){
    
}

void Horloge::reset(){
    tickDepart = SDL_GetTicks();
    tickPasser = 0;
    delta = 0.000f;
}

float Horloge::getDelta(){
    return delta;
}

void Horloge::update(){
    tickPasser = SDL_GetTicks() - tickDepart;
    delta = tickPasser * 0.001f;
}