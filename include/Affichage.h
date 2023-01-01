// Class Singleton qui va initier la fenêtre SDL et la mettre a jour
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#include "Joueur.h"
#include "Environement.h"
#include "Element.h"
#include "MeshMaker.h"
#include "AllMath.h"

class Affichage {
    // Attributs
    public:
        static const int ECRAN_LARGEUR = 1000;
        static const int ECRAN_HAUTEUR = 600;

        const int SPRITE_LARGEUR = 2340;
        const int SPRITE_HAUTEUR = 1400;

        SDL_Surface* image;
        SDL_Texture* sprite;
        SDL_Texture* win;
    
        static Affichage* instance;
        static bool estInitialiser;
        SDL_Window* fenetre;
        SDL_Renderer * renderer;
        Joueur* joueur;
        Environement* environement;

        std::vector<Element> renderList;
        mat4x4 matriceProj;

        vec3d lumiere = {-0.5f,-1.0f,-0.5f};

        float n = 0;

        bool murVisible;

    // Constructeur et Méthodes
    public:
        static Affichage* getInstance();
        static bool initialiser();
        static void detruire();

        void afficher();
        void drawTimeRectangle(int n, float y, float h);
        void displayTri(std::vector<triangle> lTri);
        void display(std::vector<triangle>* Ltri, mesh Mesh, mat4x4 matW, mat4x4 matView, int red, int green, int blue, bool castShadow);
        void drawnSpritePinguin(SDL_Rect rec, int speed);
        void perdu();
        void gagner();

        void setJoueur(Joueur* j);
        void setEnv(Environement* env);
        SDL_Window* getFenetre();

    private:
        Affichage();
        ~Affichage();
        bool Init();
};