#ifndef _GAME_H_
#define _GAME_H_

#include <cmath>
#include <SDL/SDL.h>

const float fov = M_PI/3;
const int mapw = 16;
const int maph = 16;
char map[maph*mapw+1];

class Game {
public:
    Game();
    void clean(); // could be moved to the destructor, however shared_ptr would be needed for the member pointers (c11)
    bool init_sdl(const char* title, int width, int height, int bpp);
    void handle_events();
    void draw();
    bool running();
    void readFile();
    void putpixel(int x, int y, Uint32 pixel);
    Uint32 getpixel(int itex, int x, int y);

private:

    float x_,y_,angle_;
    int turn_, walk_;

    SDL_Surface* sdl_screen_;
    SDL_Surface* textures_;
    int ntextures;
    int texsize;

    bool game_running_;
};

#endif

