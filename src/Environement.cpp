#include "Environement.h"

Environement::Environement(Joueur* joueur){
    // Environnement par défaut sans enemies
    L = 5;
    l = 5;
    murs = (bool**) malloc(L * sizeof(bool*));
    for (int i = 0 ; i < L ; i++){
        murs[i] = (bool*) malloc(l * sizeof(bool));
    }

    bool m[L][l] = {
        {true,true,true,true,true},
        {false,false,false,false,true},
        {true,false,false,false,false},
        {false,false,false,false,true},
        {true,true,true,true,true}
    };

    for (int i = 0 ; i < L ; i++){
        for (int j = 0 ; j < l ; j++){
            murs[i][j] = m[i][j];
        }
    }
    joueur->setPos(2.5f, -1.0f, 2.5f);
}

Environement::Environement(Joueur* joueur, char** env, int Long, int larg){
    // TODO : rajouter un boolean qui vérifie qu'il y est bien un joueur sur la carte
    L = Long;
    l = larg;
    murs = (bool**) malloc(L * sizeof(bool*));
    for (int i = 0 ; i < L ; i++){
        murs[i] = (bool*) malloc(l * sizeof(bool));
    }
    
    for(int i = 0 ; i < L ; i++){
        for(int j = 0 ; j < l ; j++){
            switch (env[i][j])
            {
            case 'X':
            case 'x':
                // creation des murs
                murs[i][j] = true;
                break;
            case 'O':
            case 'o':
                murs[i][j] = false;
                break;
            case 'I':
            case 'i':
                // placement des objets
                objets.push_back(  {(i+0.5f), 0.0f, (j+0.5f), MeshMaker::fromObj("icosphere.obj", (i+0.5f), 0.0f, (j+0.5f), 0.3f)}  ); // TODO changer le mesh
                murs[i][j] = false;
                break;
            case 'P':
            case 'p':
                // placement du joueur
                joueur->setPos((i+0.5f), -1.5f, (j+0.5f));
                murs[i][j] = false;
                break;
            case 'E':
            case 'e':
                // placement d'ennemis
                murs[i][j] = false;
                break;
            default:
                std::cout << "Charactere non reconnus\n";
                break;
            }
        }
    }
}

Environement::~Environement(){
    for(int i = 0; i < L ; i++){
        free(murs[i]);
    }
    free(murs);
}

std::vector<Element> Environement::getObjets(){
    return objets;
}

bool** Environement::getMurs(){
    return murs;
}

int Environement::getLongueur(){
    return L;
}
int Environement::getLargeur(){
    return l;
}

void Environement::removeObj(int e){
    objets.erase(objets.begin() + e);
}

void Environement::print(){
    for(Element& e : objets){
      std::cout << e.getX() << " " << e.getY() << " " << e.getZ() << " " << std::endl;
    }
}
