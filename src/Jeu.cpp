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
    int L, l;
    char** data = ReaderWriter::retrievingData("test.txt", &L, &l);
    if(data != nullptr){
        Joueur* joueur = new Joueur();
        Environement* env = new Environement(joueur, data, L, l);
        free(data);
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
            /*
                Gestion des donnéees
            */
            // Affichage
            if(horloge->getDelta() >= (1.0f / FRAMERATE)){
                affichage->afficher();
                horloge->reset();
            }
        }
        delete joueur;
        delete env;
    }
    else{
        free(data);
        std::cout << "Le premier niveau n'a pas pu etre charger\n";
    }
}