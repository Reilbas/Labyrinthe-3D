// structure utiliser pour créer et gerer des liste chainées
#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H

#include <iostream>
#include "ListeChainee.h"

/*
    TODO utilisé des templates
    template<typename T>
*/
struct noeud{
    int valeur;
    noeud* prochain;
};

class ListeChainee
{
    private:
        struct noeud* tete;
        struct noeud* queue;
        
    public:
        ListeChainee();
        ~ListeChainee();
        void ajouterTete(int nb);
        noeud* getTete();
        void printL();
        //void ajouterQueue(int nb);
        //int getQueue(int nb);
        //void ajouter(int i, int nb);
        //int retirerQueue(int i, int nb);

};

#endif