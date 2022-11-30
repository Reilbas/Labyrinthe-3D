#include <iostream>
#include <SDL2/SDL.h>

int main(int argv, char** args){
    SDL_Window *window = NULL;
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Erreur d'initialisation de la SDL :" << SDL_GetError() << std::endl;
        return -1;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
    if(NULL == window)
        std::cout << "Erreur de creation de la fenetre :" << SDL_GetError() << std::endl;
    else
    {
        SDL_Delay(500);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
