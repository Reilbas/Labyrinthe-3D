#include "Affichage.h"

Affichage* Affichage::instance = NULL;
bool Affichage::estInitialiser = false;

Affichage* Affichage::getInstance(){
    if(instance == NULL){
        instance = new Affichage();
    }
    return instance;
}

void Affichage::detruire(){
    delete instance;
    instance = NULL;
    estInitialiser = false;
}

Affichage::Affichage(){
    renderer = NULL;
    estInitialiser = Init();
}

Affichage::~Affichage(){
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(fenetre);
    fenetre = NULL;

    SDL_Quit();
}

bool Affichage::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Erreur d'initialisation de la SDL :" << SDL_GetError() << std::endl;
        return false;
    }

    fenetre = SDL_CreateWindow("Labyrinthe 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ECRAN_LARGEUR, ECRAN_HAUTEUR, SDL_WINDOW_SHOWN);

    if (fenetre == NULL){
        std::cout << "Erreur de creation de la fenetre :" << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(fenetre, -1, 0);

    return true;
}

void Affichage::afficher(){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    //dessine tout ce qui est dans la liste de truc a dessiner
    /*
        pour tt objets a dessiner -> le dessine
    */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 50, 50, 100, 100);

    //render window
    SDL_RenderPresent(renderer);

}

bool Affichage::initialiser(){
    return estInitialiser;
}
