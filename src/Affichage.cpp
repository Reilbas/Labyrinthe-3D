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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    mesh cube = MeshMaker::fromObj("cube.obj",(3*std::sin(n))+0.0f, 3.0f, (2*std::sin(n*1.7f))+0.0f, 0.5f);
    //mesh cube = MeshMaker::Cube((3*std::sin(n))+0.0f, 3.0f, (2*std::sin(n*1.7f))+0.0f);

    std::vector<triangle> Ltri;

    for(auto tri : cube.tris) {
        triangle triProjected;

        vec3d normal, l1, l2;

        l1.x = tri.p[1].x - tri.p[0].x;
        l1.y = tri.p[1].y - tri.p[0].y;
        l1.z = tri.p[1].z - tri.p[0].z;

        l2.x = tri.p[2].x - tri.p[0].x;
        l2.y = tri.p[2].y - tri.p[0].y;
        l2.z = tri.p[2].z - tri.p[0].z;

        normal.x = l1.z * l2.y - l1.y * l2.z;
        normal.z = l1.y * l2.x - l1.x * l2.y;
        normal.y = l1.x * l2.z - l1.z * l2.x;

        float l = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= l;
        normal.y /= l;
        normal.z /= l;

        // pourrait être deplacer
        float li = std::sqrt(lumiere.x * lumiere.x + lumiere.y * lumiere.y + lumiere.z * lumiere.z);
        lumiere.x /= l;
        lumiere.y /= l;
        lumiere.z /= l;

        //float dp = normal.x * lumiere.x + normal.y * lumiere.y + normal.z * lumiere.z;

        if( normal.x * (tri.p[0].x - vCam.x) + normal.y * (tri.p[0].y - vCam.y) +normal.z * (tri.p[0].z - vCam.z) < 0.0f ) {
            MultiplyMatrixVector(tri.p[0], triProjected.p[0], matriceProj);
            MultiplyMatrixVector(tri.p[1], triProjected.p[1], matriceProj);
            MultiplyMatrixVector(tri.p[2], triProjected.p[2], matriceProj);

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
            
            Ltri.push_back(triProjected);
        }
        
    }

    sort(Ltri.begin(), Ltri.end(), [](triangle &t1, triangle &t2){
        float z1 = (t1.p[0].y + t1.p[1].y + t1.p[2].y) / 3.0f;
        float z2 = (t2.p[0].y + t2.p[1].y + t2.p[2].y) / 3.0f;
        return z1 > z2;
    });

    //Affichage
    for(auto &tri: Ltri){
        // face
        //Uint8 gradient = (Uint8) std::round(dp*230);
        SDL_Color color = { 255, 255, 0, 255 };
        
        std::vector<SDL_Vertex> verts = {
            { SDL_FPoint{ tri.p[0].x, tri.p[0].z }, color },
            { SDL_FPoint{ tri.p[1].x, tri.p[1].z }, color },
            { SDL_FPoint{ tri.p[2].x, tri.p[2].z }, color }
        };
        SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
        // outline
        SDL_RenderDrawLine(renderer, tri.p[0].x, tri.p[0].z,
        tri.p[1].x, tri.p[1].z);
        SDL_RenderDrawLine(renderer, tri.p[1].x, tri.p[1].z,
        tri.p[2].x, tri.p[2].z);
        SDL_RenderDrawLine(renderer, tri.p[2].x, tri.p[2].z,
        tri.p[0].x, tri.p[0].z);
    }
    n+= 0.05f;
    // render window
    SDL_RenderPresent(renderer);
}

bool Affichage::initialiser(){
    return estInitialiser;
}

void Affichage::setJoueur(Joueur* j){
    joueur = j;
}

void Affichage::MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m){
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f){
        o.x /= w;
        o.y /= w;
        o.z /= w;
    }
}
