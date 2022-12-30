#ifndef ENVIRONEMENT
#define ENVIRONEMENT

#include <iostream>
#include <vector>
#include "Element.h"
#include "Joueur.h"

class Environement {
    // Attributs
    private:
        bool** murs;
        int L,l;
        std::vector<Element> objets;
        // liste de d'ennemis

    // Constructeur et Méthodes
    public:
        Environement(Joueur* joueur);
        Environement(Joueur* joueur, char** env, int Long, int larg);
        ~Environement();
        std::vector<Element> getObjets();
        bool** getMurs();
        int getLongueur();
        int getLargeur();
        void removeObj(int e);
        void print();
};

#endif
