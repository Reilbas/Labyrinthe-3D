#include "Affichage.h"

#define PI 3.14159265f

Affichage* Affichage::instance = NULL;
bool Affichage::estInitialiser = false;

Affichage* Affichage::getInstance(){
    if(instance == NULL){
        instance = new Affichage();
    }
    return instance;
}

void Affichage::detruire(){
    delete instance;
    instance = NULL;
    estInitialiser = false;
}

Affichage::Affichage(){
    joueur = nullptr;
    renderer = NULL;
    estInitialiser = Init();
}

Affichage::~Affichage(){
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(fenetre);
    fenetre = NULL;

    SDL_Quit();
}

bool Affichage::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Erreur d'initialisation de la SDL :" << SDL_GetError() << std::endl;
        return false;
    }

    fenetre = SDL_CreateWindow("Labyrinthe 3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ECRAN_LARGEUR, ECRAN_HAUTEUR, SDL_WINDOW_SHOWN);

    if (fenetre == NULL){
        std::cout << "Erreur de creation de la fenetre :" << SDL_GetError() << std::endl;
        return false;
    }

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)ECRAN_HAUTEUR / (float)ECRAN_LARGEUR;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * PI);

    matriceProj.m[0][0] = fAspectRatio * fFovRad;
    matriceProj.m[1][1] = fFar / (fFar - fNear);
    matriceProj.m[2][2] = fFovRad;
    matriceProj.m[3][1] = (-fFar * fNear) / (fFar - fNear);
    matriceProj.m[1][3] = 1.0f;
    matriceProj.m[3][3] = 0.0f;

    renderer = SDL_CreateRenderer(fenetre, -1, 0);

    return true;
}

void Affichage::dessinerMur(int x, int y){
    mesh cube = MeshMaker::Cube((float)x, (float)y, 0.0f);
    for (auto tri : cube.tris){
    }
}

void Affichage::afficher(){
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    //dessine tout ce qui est dans la liste de truc a dessiner
    /*
        pour tt objets a dessiner -> le dessine
    */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    mesh cube = MeshMaker::Cube(0.0f, 0.0f, 0.0f);
    for(auto tri : cube.tris) {
        triangle triProjected, triTranslated;

        triTranslated = tri;
        triTranslated.p[0].y = tri.p[0].y + 3.0f;
        triTranslated.p[1].y = tri.p[1].y + 3.0f;
        triTranslated.p[2].y = tri.p[2].y + 3.0f;

        MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matriceProj);
        MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matriceProj);
        MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matriceProj);

        triProjected.p[0].x += 1.0f;
        triProjected.p[0].z += 1.0f;

        triProjected.p[1].x += 1.0f;
        triProjected.p[1].z += 1.0f;

        triProjected.p[2].x += 1.0f;
        triProjected.p[2].z += 1.0f;
        
        triProjected.p[0].x *= 0.5f * (float)ECRAN_LARGEUR;
        triProjected.p[0].z *= 0.5f * (float)ECRAN_HAUTEUR;
        triProjected.p[1].x *= 0.5f * (float)ECRAN_LARGEUR;
        triProjected.p[1].z *= 0.5f * (float)ECRAN_HAUTEUR;
        triProjected.p[2].x *= 0.5f * (float)ECRAN_LARGEUR;
        triProjected.p[2].z *= 0.5f * (float)ECRAN_HAUTEUR;

        SDL_RenderDrawLine(renderer, triProjected.p[0].x, triProjected.p[0].z,
        triProjected.p[1].x, triProjected.p[1].z);
        SDL_RenderDrawLine(renderer, triProjected.p[1].x, triProjected.p[1].z,
        triProjected.p[2].x, triProjected.p[2].z);
        SDL_RenderDrawLine(renderer, triProjected.p[2].x, triProjected.p[2].z,
        triProjected.p[0].x, triProjected.p[0].z);
    }

    //SDL_RenderDrawLine(renderer, 50, 50, 100, 100);

    // render window
    SDL_RenderPresent(renderer);
}

bool Affichage::initialiser(){
    return estInitialiser;
}

void Affichage::setJoueur(Joueur* j){
    joueur = j;
}

void Affichage::MultiplyMatrixVector(vertex &i, vertex &o, mat4x4 &m){
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        o.x /= w;
        o.y /= w;
        o.z /= w;
    }
}
