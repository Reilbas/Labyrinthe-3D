// Class Singleton qui va initier la fenêtre SDL et la mettre a jour
#include <iostream>
#include <SDL2/SDL.h>

class Affichage {

    // Attributs
    public:
        static const int ECRAN_LARGEUR = 1000;
        static const int ECRAN_HAUTEUR = 1000;
    
    private:
        static Affichage* instance;
        static bool estInitialiser;
        SDL_Window* fenetre;
        SDL_Surface* surface;

    // Constructeur et Méthodes
    public:
        static Affichage* getInstance();
        static void detruire();
        void afficher();

    private:
        Affichage();
        ~Affichage();

        bool Init();
};