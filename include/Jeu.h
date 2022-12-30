// Class Singleton qui va gerer l'état du jeu (gerer la boucle d'affichage, etc...)
#include <SDL2/SDL.h>
#include "Affichage.h"
#include "Horloge.h"
#include "Joueur.h"
#include "Environement.h"
#include "ReaderWriter.h"

class Jeu {
    // Attributs
    public:
        static const int FRAMERATE = 60;

    private:
        static Jeu* instance;
        bool quitter, mouseLock;
        Affichage* affichage;
        Horloge* horloge;
        SDL_Event evenements;
        float lastMx;

    // Constructeur et Méthodes
    public:
        static Jeu* getInstance();
        static void detruire();
        void run();
        void checkItems(Joueur* j, Environement* env);

    private:
        Jeu();
        ~Jeu();
};