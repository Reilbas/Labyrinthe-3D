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
    mouseLock = false;
    lastMx = evenements.motion.x; // position de la souris au lancement de la fenetre
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
    char** data = ReaderWriter::retrievingLevel("test.txt", &L, &l);
    if(data != nullptr){
        Joueur* joueur = new Joueur();
        Environement* env = new Environement(joueur, data, L, l);

        affichage->setJoueur(joueur);
        affichage->setEnv(env);
        free(data);
        while(!quitter){
            // Mise à jour de l'horloge
            horloge->update();
            // Gestion des evenements
            while(SDL_PollEvent(&evenements) != 0){
                switch (evenements.type){
                case SDL_QUIT:
                    quitter = true;
                    break;
                case SDL_KEYDOWN:
                    switch (evenements.key.keysym.sym){
                        // deplacement horizontal
                        case SDLK_q:
                            joueur->gauche(env->getMurs(), env->getLongueur(), env->getLargeur());
                            //joueur->print();
                            break;
                        case SDLK_d:
                            joueur->droite(env->getMurs(), env->getLongueur(), env->getLargeur());
                            //joueur->print();
                            break;
                        case SDLK_z:
                            joueur->avancer(env->getMurs(), env->getLongueur(), env->getLargeur());
                            //joueur->print();
                            break;
                        case SDLK_s:
                            joueur->reculer(env->getMurs(), env->getLongueur(), env->getLargeur());
                            //joueur->print();
                            break;

                        case SDLK_w:
                            if(mouseLock == true){
                                SDL_SetRelativeMouseMode(SDL_FALSE);
                                mouseLock = false;
                            }else{
                                SDL_SetRelativeMouseMode(SDL_TRUE);
                                mouseLock = true;
                            }
                            break;
                        // deplacement vertical
                        case SDLK_SPACE:
                            joueur->vCam.y -= 0.5f;
                            joueur->maj();
                            joueur->print();
                            break;
                        case SDLK_LCTRL:
                            joueur->vCam.y += 0.5f;
                            joueur->maj();
                            joueur->print();
                            break;

                        case SDLK_a:
                            joueur->rotationY(0.5f);
                            break;
                        case SDLK_e:
                            joueur->rotationY(-0.5f);
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (mouseLock){
                        if(evenements.motion.x >= affichage->ECRAN_LARGEUR - 1){
                            SDL_WarpMouseInWindow(affichage->getFenetre(), 1, evenements.motion.y);
                            lastMx = evenements.motion.x;
                        }
                        if(evenements.motion.x <= 0){
                            SDL_WarpMouseInWindow(affichage->getFenetre(), affichage->ECRAN_LARGEUR - 2, evenements.motion.y);
                            lastMx = evenements.motion.x;
                        }
                        joueur->rotationY((lastMx - evenements.motion.x)/150);
                        lastMx = evenements.motion.x;
                    }
                    break;
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