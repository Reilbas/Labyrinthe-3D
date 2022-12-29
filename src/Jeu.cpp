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
    char** data = ReaderWriter::retrievingLevel("test.txt", &L, &l);
    if(data != nullptr){
        Joueur* joueur = new Joueur();
        Environement* env = new Environement(joueur, data, L, l);

        joueur->setPos(0.0f,0.0f,-1.0f);

        affichage->setJoueur(joueur);
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
                            joueur->posX -= 0.5f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;
                        case SDLK_d:
                            joueur->posX += 0.5f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;
                        case SDLK_z:
                            joueur->posY += 0.5f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;
                        case SDLK_s:
                            joueur->posY -= 0.5f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;

                        // deplacement vertical
                        /*
                        case SDLK_z:
                            joueur->posY += 1.0f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;
                        case SDLK_s:
                            joueur->posY -= 1.0f;
                            std::cout << "X:" << joueur->posX << " Y:" << joueur->posY << " Z:" << joueur->posZ << "\n";
                            break;
                        */
                        // deplacement orientation
                        case SDLK_a:
                            joueur->rotY += 0.5f;
                            std::cout << "rotY:" << joueur->rotY << "\n";
                            break;
                        case SDLK_e:
                            joueur->rotY -= 0.5f;
                            std::cout << "rotY:" << joueur->rotY << "\n";
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    //std::cout << "X:" << evenements.motion.x << " Y:" << evenements.motion.y << "\n"; 
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