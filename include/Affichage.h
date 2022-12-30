// Class Singleton qui va initier la fenêtre SDL et la mettre a jour
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#include "Joueur.h"
#include "Element.h"
#include "MeshMaker.h"
#include "AllMath.h"

class Affichage {
    // Attributs
    public:
        static const int ECRAN_LARGEUR = 1000;
        static const int ECRAN_HAUTEUR = 600;
    
    public:
        static Affichage* instance;
        static bool estInitialiser;
        SDL_Window* fenetre;
        SDL_Renderer * renderer;
        Joueur* joueur;

        std::vector<Element> renderList;
        mat4x4 matriceProj;

        vec3d lumiere = {0.0f,-1.0f,0.0f};

        float n = 0;

    // Constructeur et Méthodes
    public:
        static Affichage* getInstance();
        static bool initialiser();
        static void detruire();
        void setJoueur(Joueur* j);
        void afficher();
        SDL_Window* getFenetre();
        void drawRect(float x, float y, float l, float h, SDL_Color &color);

    private:
        Affichage();
        ~Affichage();
        bool Init();
};