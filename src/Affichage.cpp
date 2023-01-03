#include "Affichage.h"

#define PI 3.14159265f
#define TEMPSMAX 600.0f

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

    // chargement de(s) texture(s)
    SDL_Surface* image1 = SDL_LoadBMP("assets/SpritePinguin.bmp");
    SDL_Surface* image2 = SDL_LoadBMP("assets/Win.bmp");

    sprite = SDL_CreateTextureFromSurface(renderer, image1);
    win = SDL_CreateTextureFromSurface(renderer, image2);

    SDL_FreeSurface(image1);
    SDL_FreeSurface(image2);
    murVisible = true;
}

Affichage::~Affichage(){
    SDL_DestroyTexture(sprite);
    SDL_DestroyTexture(win);

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

    matriceProj = AllMath::makeProjMatrix(90.0f, (float)ECRAN_HAUTEUR / (float)ECRAN_LARGEUR, 0.1f, 1000.0f);

    renderer = SDL_CreateRenderer(fenetre, -1, 0);

    return true;
}

void Affichage::afficher(){
    // nettoyage de l'ecran
    SDL_SetRenderDrawColor(renderer, 87, 205, 235, 255);
    SDL_RenderClear(renderer);

    // changement de couleurs de dessins (pour les outlines et barre de temps)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // definition des matrices de calcul
    mat4x4 matW = AllMath::identMatrix();
    mat4x4 matCam = AllMath::matPointAt(joueur->vCam, joueur->vTarget, joueur->vUp);
    mat4x4 matView = AllMath::matrixQuickInverse(matCam);

    mat4x4 itemMotion = AllMath::transMat(0.0f, (std::sin(n)/2)-1.0f, 0.0f);

    std::vector<triangle> Ltri;

    // Gestion des murs
    for(int i = 0 ; i < environement->getLongueur() ; i++){
        for(int j = 0 ; j < environement->getLargeur() ; j++){
            if(environement->getMurs()[i][j]){
                if(murVisible){
                    mesh cube = MeshMaker::Cube((float) i, -2.0f, (float) j, 1.0f, 1.0f);
                    this->display(&Ltri, cube, matW, matView, 157, 224, 126, true);
                }
            } else {
                mesh tile = MeshMaker::Tile((float) i, 0.0f, (float) j, 1.0f);
                if((i+j)%2){
                    this->display(&Ltri, tile, matW, matView, 235, 235, 235, false);
                } else{
                    this->display(&Ltri, tile, matW, matView, 150, 150, 150, false);
                }
            }
        }
    }

    // Gestion des objets
    for(auto e : environement->getObjets()){
        this->display(&Ltri, e.geometry, itemMotion, matView, 242, 180, 24, false);
    }

    // Triage des triangle par distance
    sort(Ltri.begin(), Ltri.end(), [](triangle &t1, triangle &t2){
        float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
        float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
        return z1 > z2;
    });

    // Affichage 3D
    this->displayTri(Ltri);

    // Affichage barre du temps restant
    this->drawTimeRectangle(joueur->tempsRestant, ECRAN_HAUTEUR-60, 30);

    // Affichage du SpritePinguin
    SDL_Rect rec = {ECRAN_LARGEUR/2 -40, ECRAN_HAUTEUR-150, 80, 80};
    this->drawnSpritePinguin(rec, 7);

    // render window
    SDL_RenderPresent(renderer);

    // update var n;
    n+= 0.05f;
}

void Affichage::drawTimeRectangle(int n, float y, float h){
    float ratioT = n/TEMPSMAX;
    unsigned char posC = (char)(ratioT*255);
    unsigned char minC = (char)(255-ratioT*255);
    
    SDL_Color color = { minC, posC, 0, 255 };
    /*
    std::vector<SDL_Vertex> triUi1 = {
        { SDL_FPoint{ ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y }, color },
        { SDL_FPoint{ ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y }, color },
        { SDL_FPoint{ ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y + h }, color },
    };
    std::vector<SDL_Vertex> triUi2 = {
        { SDL_FPoint{ ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2 , y }, color },
        { SDL_FPoint{ ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y + h }, color },
        { SDL_FPoint{ ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y + h }, color },
    };
    SDL_RenderGeometry(renderer, nullptr, triUi1.data(), triUi1.size(), nullptr, 0);
    SDL_RenderGeometry(renderer, nullptr, triUi2.data(), triUi2.size(), nullptr, 0);
    */
    SDL_RenderDrawLine(renderer, ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y, ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y);
    SDL_RenderDrawLine(renderer, ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y+h, ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y+h);
    SDL_RenderDrawLine(renderer, ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y, ECRAN_LARGEUR/2 + (ECRAN_LARGEUR*ratioT)/2, y+h);
    SDL_RenderDrawLine(renderer, ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y, ECRAN_LARGEUR/2 - (ECRAN_LARGEUR*ratioT)/2, y+h);
}

void Affichage::displayTri(std::vector<triangle> lTri){
    for(auto &tri: lTri){
        /*// affichage face
        SDL_Color color = { tri.r, tri.g, tri.b, 255 };
        std::vector<SDL_Vertex> verts = {
            { SDL_FPoint{ tri.p[0].x, tri.p[0].y }, color },
            { SDL_FPoint{ tri.p[1].x, tri.p[1].y }, color },
            { SDL_FPoint{ tri.p[2].x, tri.p[2].y }, color }
        };
        SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
        */
        //affichage outline
        SDL_RenderDrawLine(renderer, tri.p[0].x, tri.p[0].y,
        tri.p[1].x, tri.p[1].y);
        SDL_RenderDrawLine(renderer, tri.p[1].x, tri.p[1].y,
        tri.p[2].x, tri.p[2].y);
        SDL_RenderDrawLine(renderer, tri.p[2].x, tri.p[2].y,
        tri.p[0].x, tri.p[0].y);
    }
}

void Affichage::display(std::vector<triangle>* Ltri, mesh Mesh, mat4x4 matW, mat4x4 matView, int red, int green, int blue , bool castShadow){
    for(auto tri : Mesh.tris) {
        triangle triProjected, triTransfo, triView;
        triTransfo.p[0] = AllMath::matrixMultVector(matW, tri.p[0]);
        triTransfo.p[1] = AllMath::matrixMultVector(matW, tri.p[1]);
        triTransfo.p[2] = AllMath::matrixMultVector(matW, tri.p[2]);

        vec3d normal, l1, l2;

        l1 = AllMath::subVector(triTransfo.p[1], triTransfo.p[0]);
        l2 = AllMath::subVector(triTransfo.p[2], triTransfo.p[0]);

        normal = AllMath::crossProd(l1, l2);
        normal = AllMath::norm(normal);

        vec3d vCamRay = AllMath::subVector(triTransfo.p[0], joueur->vCam);

        if(AllMath::dotProd(normal, vCamRay) < 0.0f ) {
            if(castShadow){
                vec3d li = AllMath::norm(lumiere);
                float dp = std::max(0.1f, AllMath::dotProd(li, normal));
                triProjected.r = std::floor(red*dp);
                triProjected.g = std::floor(green*dp);
                triProjected.b = std::floor(blue*dp);
            }else{
                triProjected.r = red;
                triProjected.g = green;
                triProjected.b = blue;
            }

            triView.p[0] = AllMath::matrixMultVector(matView, triTransfo.p[0]);
            triView.p[1] = AllMath::matrixMultVector(matView, triTransfo.p[1]);
            triView.p[2] = AllMath::matrixMultVector(matView, triTransfo.p[2]);

            // cliping
            int nClippedTriangle = 0;
            triangle clipped[2];
            nClippedTriangle = AllMath::triangleClipAgainstPlane({0.0f,0.0f,0.1f}, {0.0f,0.0f,1.0f}, triView, clipped[0], clipped[1]);

            for(int i = 0 ; i < nClippedTriangle ; i++){
                // 3D -> 2D
                triProjected.p[0] = AllMath::matrixMultVector(matriceProj, clipped[i].p[0]);
                triProjected.p[1] = AllMath::matrixMultVector(matriceProj, clipped[i].p[1]);
                triProjected.p[2] = AllMath::matrixMultVector(matriceProj, clipped[i].p[2]);

                triProjected.p[0] = AllMath::divVector(triProjected.p[0], triProjected.p[0].w);
                triProjected.p[1] = AllMath::divVector(triProjected.p[1], triProjected.p[1].w);
                triProjected.p[2] = AllMath::divVector(triProjected.p[2], triProjected.p[2].w);

                vec3d offset = {1, 1, 0};
                triProjected.p[0] = AllMath::addVector(triProjected.p[0], offset);
                triProjected.p[1] = AllMath::addVector(triProjected.p[1], offset);
                triProjected.p[2] = AllMath::addVector(triProjected.p[2], offset);
                triProjected.p[0].x *= 0.5f * (float)ECRAN_LARGEUR;
                triProjected.p[0].y *= 0.5f * (float)ECRAN_HAUTEUR;
                triProjected.p[1].x *= 0.5f * (float)ECRAN_LARGEUR;
                triProjected.p[1].y *= 0.5f * (float)ECRAN_HAUTEUR;
                triProjected.p[2].x *= 0.5f * (float)ECRAN_LARGEUR;
                triProjected.p[2].y *= 0.5f * (float)ECRAN_HAUTEUR;
                
                Ltri->push_back(triProjected);
            }
        }
    }
}
void Affichage::drawnSpritePinguin(SDL_Rect rec, int speed){
    int xSprite = (int) ((n*speed)/8.0f) % 13; 
    int ySprite = (int) (n*speed) % 8;
    SDL_Rect s = {xSprite*(SPRITE_LARGEUR/13), ySprite*(SPRITE_HAUTEUR/8), SPRITE_LARGEUR/13, SPRITE_HAUTEUR/8};
    SDL_RenderCopy(renderer, sprite, &s, &rec);
}

bool Affichage::initialiser(){
    return estInitialiser;
}

void Affichage::setJoueur(Joueur* j){
    joueur = j;
}

void Affichage::setEnv(Environement* env){
    environement = env;
}

SDL_Window* Affichage::getFenetre(){
    return fenetre;
}

void Affichage::perdu(){
    n = 0;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rec = {0, 0, ECRAN_LARGEUR, ECRAN_HAUTEUR};
    this->drawnSpritePinguin(rec, 0);
    SDL_RenderPresent(renderer);
}

void Affichage::gagner(){
    SDL_SetRenderDrawColor(renderer, 33, 20, 1, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rec = {ECRAN_LARGEUR/2 - ECRAN_HAUTEUR/2, 0, ECRAN_HAUTEUR, ECRAN_HAUTEUR};
    SDL_RenderCopy(renderer, win, NULL, &rec);
    SDL_RenderPresent(renderer);
}
