#include <iostream>
#include "ListeChainee.h"

int main(){
        std::cout << "Creation d'une liste chainee" << std::endl;
        ListeChainee l;
        l.ajouterTete(57);
        l.ajouterTete(96);
        l.ajouterTete(19);
        l.ajouterTete(36);
        l.ajouterTete(24);
        l.printL();
    return 0;
}