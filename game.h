#ifndef _GAME_H_
#define _GAME_H_

#include <cmath>
#include <SDL/SDL.h>

const float fov = M_PI/3;
const int mapw = 16;
const int maph = 16;
char map[maph*mapw+1];

const int lootCount = 5;

typedef struct Loot Loot;
struct Loot
{
    int x;
    int y;
    Loot *next;
};

class Game {
public:
    Game();
    //void generateLoot();
    void clean(); 
    bool init_sdl(const char* title, int width, int height, int bpp);
    void handle_events();
    void draw();
    bool running();
    void readFile(char file[]);
    void putpixel(int x, int y, Uint32 pixel);
    Uint32 getpixel(int itex, int x, int y);
    
    int randomInt(int min, int max);

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

