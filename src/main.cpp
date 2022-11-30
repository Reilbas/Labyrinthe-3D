#include <iostream>
#include <SDL2/SDL.h>
#include "Affichage.h"


int main(int argv, char** args){
    Affichage *af = Affichage::getInstance();
    while(1){
        af->afficher();
    }
}