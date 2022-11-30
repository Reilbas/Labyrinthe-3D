#include "Jeu.h"

Jeu* Jeu::instance = NULL;

Jeu* Jeu::getInstance(){
    if(instance == NULL){
        instance = new Jeu();
    }
    return instance;
}

void Jeu::detruire(){
    delete instance;
    instance = NULL;
}

Jeu::Jeu(){
    quitter = false;
    af = Affichage::getInstance();
    if(!Affichage::initialiser()){
        quitter = true;
    }
}

Jeu::~Jeu(){
    Affichage::detruire();
    af = NULL;
    SDL_Quit();
}

void Jeu::run(){
    while(!quitter){
        while(SDL_PollEvent(&evenements) != 0){
            if(evenements.type == SDL_QUIT){
                quitter = true;
            }

            af->afficher();
        }
    }
}