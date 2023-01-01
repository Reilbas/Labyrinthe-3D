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
    nbFrame = 0;
    quitter = false;
    mouseLock = false;
    perdu = false;
    lastMx = evenements.motion.x; // position de la souris au lancement de la fenetre
    affichage = Affichage::getInstance();
    if(!Affichage::initialiser()){
        quitter = true;
    }
    horloge = Horloge::getInstance();
    joueur = new Joueur();
}

Jeu::~Jeu(){
    Horloge::detruire();
    horloge = NULL;
    Affichage::detruire();
    affichage = NULL;
    delete joueur;
    SDL_Quit();
}

void Jeu::run(char** niveaux, int nbNiveau){
    int niveauActuel = 1;
    while(!quitter && !perdu && niveauActuel < nbNiveau ){
        int L, l;
        char** data = ReaderWriter::retrievingLevel(niveaux[niveauActuel], &L, &l);
        if(data != nullptr){
            gagner = false;
            Environement* env = new Environement(joueur, data, L, l);
            free(data);

            affichage->setJoueur(joueur);
            affichage->setEnv(env);

            while(!quitter && !perdu && !gagner){
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
                                this->checkItems(joueur, env);
                                break;
                            case SDLK_d:
                                joueur->droite(env->getMurs(), env->getLongueur(), env->getLargeur());
                                this->checkItems(joueur, env);
                                break;
                            case SDLK_z:
                                joueur->avancer(env->getMurs(), env->getLongueur(), env->getLargeur());
                                this->checkItems(joueur, env);
                                break;
                            case SDLK_s:
                                joueur->reculer(env->getMurs(), env->getLongueur(), env->getLargeur());
                                this->checkItems(joueur, env);
                                break;

                            case SDLK_w:
                                if(mouseLock){
                                    SDL_SetRelativeMouseMode(SDL_FALSE);
                                    mouseLock = false;
                                }else{
                                    SDL_SetRelativeMouseMode(SDL_TRUE);
                                    mouseLock = true;
                                }
                                break;

                            case SDLK_a:
                                joueur->rotationY(0.5f);
                                break;
                            case SDLK_e:
                                joueur->rotationY(-0.5f);
                                break;

                            case SDLK_j:
                                if(affichage->murVisible){
                                    affichage->murVisible = false;
                                }else{
                                    affichage->murVisible = true;
                                }
                                break;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        if (mouseLock){
                            if(evenements.motion.x >= affichage->ECRAN_LARGEUR - 1){
                                SDL_WarpMouseInWindow(affichage->getFenetre(), 1, evenements.motion.y);
                            }
                            if(evenements.motion.x <= 0){
                                SDL_WarpMouseInWindow(affichage->getFenetre(), affichage->ECRAN_LARGEUR - 2, evenements.motion.y);
                            }
                            joueur->rotationY((lastMx - evenements.motion.x)/150);
                            lastMx = evenements.motion.x;
                        }
                        break;
                    }
                }
                // Mise a jour et Affichage
                if(horloge->getDelta() >= (1.0f / FRAMERATE)){
                    joueur->tempsRestant--;
                    nbFrame++;
                    if(env->getObjets().size() == 0){
                        gagner = true;
                        niveauActuel++;
                    }
                    if(joueur->plusDeTemps()){
                        perdu = true;
                    }
                    affichage->afficher();
                    horloge->reset();
                }
            }
            delete env;
        }
        else{
            free(data);
            std::cout << "Le niveau n'a pas pu etre charge\n";
            break;
        }
    }
    if(perdu){
        affichage->perdu();
        std::cout << "AHAHA T'ES TROP NUL\nTemps de jeu: " << nbFrame/60 << "secondes \n";
        SDL_Delay(3000);
    } else if(gagner){
        affichage->gagner();
        std::cout << "BIEN JOUER MON REUF\nTemps de jeu: " << nbFrame/60 << "secondes \n";
        SDL_Delay(3000);
    }
}

void Jeu::checkItems(Joueur* j, Environement* env){
    std::vector<Element> obj = env->getObjets();
    for(int i = 0 ; i < obj.size() ; i++){
        if((std::floor(obj[i].posX) == std::floor(j->vCam.x)) && (std::floor(obj[i].posZ) == std::floor(j->vCam.z))){
            env->removeObj(i);
            if(j->tempsRestant+120 > 600){
                j->tempsRestant = 600; 
            } else{
                j->tempsRestant += 120;
            }
        }
    }
}
