#include "Jeu.h"


int main(int argv, char** args){
    Jeu *jeu = Jeu::getInstance();
    jeu->run();
    
    Jeu::detruire();
    jeu = NULL;
    
    return 0;
}