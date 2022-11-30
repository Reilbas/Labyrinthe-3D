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
    surface = NULL;
    estInitialiser = Init();
}

Affichage::~Affichage(){
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

    surface = SDL_GetWindowSurface(fenetre);

    return true;
}

void Affichage::afficher(){
    SDL_UpdateWindowSurface(fenetre);
}


