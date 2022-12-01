// Class Singleton horloge qui controle les "ticks" du jeu (rafraichissement de l'écran par secondes) 
#include <iostream>
#include <SDL2/SDL.h>

class Horloge {

    // Attributs
    private:
        static Horloge* instance;
        unsigned int tickDepart;
        unsigned int tickPasser;
        float delta;

    // Constructeur et Méthodes
    public:
        static Horloge* getInstance();
        static void detruire();
        void reset();
        float getDelta();
        void update();

    private:
        Horloge();
        ~Horloge();
};