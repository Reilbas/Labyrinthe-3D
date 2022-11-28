#include <SDL/SDL.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include "game.h"

Uint32 createColor(int r, int g, int b) {
    Uint32 r1 = 255 * r;
    Uint32 b1 = 255 * b;
    Uint32 g1 = 255 * g;

    return 0xFF000000 | r1 | (b1 << 16) | (g1 << 8);
}

/*void Game::generateLoot() {
	for(int i = 0; i < lootCount; i++) {
		int rX = randomInt(1, mapw - 2);
		int rY = randomInt(1, maph - 2);
		while(map[int(rX)+int(rY)*mapw] == 'X') {
			map[int(rX)+int(rY)*mapw] = 'B';
		}
	}
}*/

int Game::randomInt(int min, int max) {
	int range = max - min + 1;
	int num = rand() % range + min;
	return num;
}

void Game::readFile(char file[]) {
	std::fstream f;
	f.open(file, std::ios::in);
	if (!f) {
		std::cout << "No such file";
	}
	else {
		char ch;
		int i = 0;
		while (1) {
			i++;
			f >> ch;
			if (f.eof())
				break;
			char w[1] = {ch};
			strcat(map, w);
		}
	}
	f.close();
}

void Game::draw() {
    SDL_FillRect(sdl_screen_, NULL, SDL_MapRGB(sdl_screen_->format, 255, 255, 255));

    int w = sdl_screen_->w;
    
    for (int i=0; i<w; i++) {
        float ca = (1.-i/float(w)) * (angle_-fov/2.) + i/float(w)*(angle_+fov/2.);
        for (float t=0; t<20; t+=.05) {
            float cx = x_+cos(ca)*t;
            float cy = y_+sin(ca)*t;
            int idx = int(cx)+int(cy)*mapw;
            int h = sdl_screen_->h/t;
            if(map[idx] != 'B') {
		        if(map[idx] != 'X') {
		            cx -= floor(cx+.5);
		            cy -= floor(cy+.5);
		            for (int ty=0; ty<h; ty++) { 
		                putpixel(i, ty+(sdl_screen_->h-h)/2, 16721545);
		            }
		            break;
		        }
			} else {
	            for (int ty=-50; ty<10; ty++) { 
	                putpixel(i, ty+(sdl_screen_->h-h)/2, 12141545);
	            }			
			}
        }
    }
    
    for(int i = 0; i < 160; i++) {
    	for(int j = 0; j < 160; j++) {
    		putpixel(i, j, 16760102);
    	}
    }
    
   for(int i = 0; i < 10; i++) {
    	for(int j = 0; j < 10; j++) {
    		int x = x_ * (mapw / 2);
    		int y = y_ * (maph / 2);
    		putpixel(x + i, y + j, 14775102);
    	}
    }

    SDL_Flip(sdl_screen_);
}

void Game::handle_events() {

    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        game_running_ = !(SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym));
        if (SDL_KEYUP==event.type) {
            if ('z'==event.key.keysym.sym  || 's' ==event.key.keysym.sym) walk_ = 0;
            if ('q'==event.key.keysym.sym || 'd' ==event.key.keysym.sym) turn_ = 0;
        }
        if (SDL_KEYDOWN==event.type) {
            if ('q'==event.key.keysym.sym) turn_ = -1;
            if ('d'==event.key.keysym.sym) turn_ =  1;
            if ('z'==event.key.keysym.sym) walk_ =  1;
            if ('s'==event.key.keysym.sym) walk_ = -1;
        }
        if(SDL_MOUSEBUTTONDOWN == event.type && SDL_BUTTON_LEFT == event.button.button) {


        }
    }

    angle_ += float(turn_)*.005;
    float nx = x_ + walk_*cos(angle_)*.01;
    float ny = y_ + walk_*sin(angle_)*.01;

    if (int(nx)>=0 && int(nx)<mapw && int(ny)>=0 && int(ny)<maph && map[int(nx)+int(ny)*mapw]=='X') {
        x_ = nx;
        y_ = ny;
    }
}

Game::Game() : x_(2), y_(2), angle_(0), turn_(0), walk_(0), 
    sdl_screen_(NULL), textures_(NULL), ntextures(0), texsize(0), game_running_(false) {
}

bool Game::init_sdl(const char* title, int width, int height, int bpp) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "SDL_Init failed, SDL_GetError()=" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_WM_SetCaption(title, NULL);
    sdl_screen_ = SDL_SetVideoMode(width, height, 8*bpp, 0);
    if (!sdl_screen_) {
        std::cerr << "SDL_SetVideoMode failed, SDL_GetError()=" << SDL_GetError() << std::endl;
        return false;
    }
    game_running_ = true;

    SDL_ShowCursor(SDL_DISABLE);

    textures_ = SDL_LoadBMP("walltext.bmp");
    if (!textures_) {
        std::cerr << "Couldn't load texture file " << SDL_GetError() << std::endl;
        return false;
    }
    if (textures_->format->BytesPerPixel!=bpp) {
        std::cerr << "Game screen bpp does not match textures bpp" << std::endl;
        return false;
    }
    texsize = textures_->h;
    ntextures = textures_->w / texsize;
    if (textures_->w != ntextures*texsize) {
        std::cerr << "Incorrect textures file: its width must be a multiple of its height" << std::endl;
    }
    std::cout << "Successfully read " << ntextures << " textures of " << texsize << "x" << texsize << " pixels" << std::endl;

    return true;
}

bool Game::running() {
    return game_running_;
}

void Game::clean() {
    if (sdl_screen_) SDL_FreeSurface(sdl_screen_);
    if (textures_  ) SDL_FreeSurface(textures_  );
    SDL_Quit();
}

Uint32 Game::getpixel(int itex, int x, int y) {
    int texsize = textures_->h;
    if (itex<0 || itex>=ntextures || x<0 || y<0 || x>=texsize || y>=texsize) return 0;
    Uint8 *p = (Uint8 *)textures_->pixels + y*textures_->pitch + (x+texsize*itex)*textures_->format->BytesPerPixel;
    return p[0] | p[1] << 8 | p[2] << 16; 
}

void Game::putpixel(int x, int y, Uint32 pixel) {
    if (x<0 || y<0 || x>=sdl_screen_->w || y>=sdl_screen_->h) return;
    int bpp = sdl_screen_->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)sdl_screen_->pixels + y*sdl_screen_->pitch + x*bpp;
    for (int i=0; i<bpp; i++) {
        p[i] = ((Uint8*)&pixel)[i];
    }
}

