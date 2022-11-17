#include "game.h"
#include <cmath>


int main() {
    Game game;
    game.readFile();
    game.init_sdl("stroll stub", 512, 512, 0);
    while (game.running()) {
        game.handle_events(); // TODO make x_,y_,angle_ increments depend on the dt
        game.draw();          // TODO call draw() 25 times per second only
    }
    game.clean();
    return 0;
}

