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
    affichage = Affichage::getInstance();
    if(!Affichage::initialiser()){
        quitter = true;
    }
    horloge = Horloge::getInstance();
}

Jeu::~Jeu(){
    Horloge::detruire();
    horloge = NULL;
    Affichage::detruire();
    affichage = NULL;
    SDL_Quit();
}

void Jeu::run(){
    while(!quitter){
        // Mise à jour de l'horloge
        horloge->update();
        // Gestion des evenements
        while(SDL_PollEvent(&evenements) != 0){
            if(evenements.type == SDL_QUIT){
                quitter = true;
            }
        }
        // Mise a jour des valeurs (interne)

        // Affichage
        if(horloge->getDelta() >= (1.0f / FRAMERATE)){
            affichage->afficher();
            horloge->reset();
        }
    }
}