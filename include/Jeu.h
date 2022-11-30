// Class Singleton qui va gerer l'état du jeu (gerer la boucle d'affichage, etc...)
#include <SDL2/SDL.h>
#include "Affichage.h"

class Jeu {

    // Attributs
    private:
        static Jeu* instance;
        bool quitter;
        Affichage* af;
        SDL_Event evenements;

    // Constructeur et Méthodes
    public:
        static Jeu* getInstance();
        static void detruire();
        void run();

    private:
        Jeu();
        ~Jeu();
};