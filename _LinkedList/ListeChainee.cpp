// structure utiliser pour créer et gerer des liste chainées
#include "ListeChainee.h"

ListeChainee::ListeChainee(){
    tete = NULL;
    queue = tete;
    tete->valeur = 0;
    tete->prochain = NULL;

};

ListeChainee::~ListeChainee(){
    noeud* nActu = tete;
    while(nActu->prochain!=NULL){
        noeud* pro = (nActu->prochain);
        free(nActu);
        nActu = pro;
    }
    tete = NULL;
    queue = NULL;
};

void ListeChainee::ajouterTete(int nb){
    noeud* nouveau = (noeud*) malloc(sizeof(noeud));
    nouveau->valeur = nb;
    nouveau->prochain = tete;
    tete = nouveau;
};

noeud* ListeChainee::getTete(){
    return tete;
};

void ListeChainee::printL(){
    noeud* dep = tete;
    while(dep->prochain!=NULL){
        std::cout << dep->valeur << " -> ";
        dep = (dep->prochain);
    }
    std::cout << dep->valeur << std::endl;
}
