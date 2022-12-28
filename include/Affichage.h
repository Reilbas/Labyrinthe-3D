// Class Singleton qui va initier la fenêtre SDL et la mettre a jour
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#include "Joueur.h"
#include "MeshMaker.h"

struct mat4x4
{
	float m[4][4] = { 0 };
};

class Affichage {
    // Attributs
    public:
        static const int ECRAN_LARGEUR = 1000;
        static const int ECRAN_HAUTEUR = 1000;
    
    private:
        static Affichage* instance;
        static bool estInitialiser;
        SDL_Window* fenetre;
        SDL_Renderer * renderer;
        Joueur* joueur;
        std::vector<Element> renderList;
        mat4x4 matriceProj;

    // Constructeur et Méthodes
    public:
        static Affichage* getInstance();
        static bool initialiser();
        static void detruire();
        void setJoueur(Joueur* j);
        void afficher();
        void dessinerMur(int x, int y);
        //void dessinerMesh(mesh m);

    private:
        Affichage();
        ~Affichage();
        bool Init();
        void MultiplyMatrixVector(vertex &i, vertex &o, mat4x4 &m);
};