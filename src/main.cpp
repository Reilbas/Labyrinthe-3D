#include "Jeu.h"


int main(int argv, char** args){
    if(argv > 1){
        Jeu *jeu = Jeu::getInstance();
        jeu->run(args, argv);
        
        Jeu::detruire();
        jeu = NULL;  
    } else {
        std::cout << "Veuillez renseigner un ou plusieur niveau en argument\n";
    }

    return 0;
}