#include "ReaderWriter.h"

char** ReaderWriter::retrievingData(std::string nomFic, int* L, int* l){
    std::vector<std::string> lstr;
    std::string line;
    std::ifstream fic (nomFic);
    if (fic.is_open()){
        while(getline(fic,line)){
            lstr.push_back(line);
        }
        fic.close();
        *L = lstr.size();
        *l = lstr[0].length();
        char** env = (char**) malloc(lstr.size() * sizeof(char*));
        for (int i = 0 ; i < lstr.size() ; i++){
            env[i] = (char*) malloc(lstr[0].length() * sizeof(char));
            for(int j=0 ; j < lstr[0].length() ; j++){
                env[i][j] = lstr[i][j];
            }
        }
        return env;
    } else { 
        std::cout << "Unable to open file";
        return nullptr;
    }
}

/*
int main(){
    int L, l;
    char** env = ReaderWriter::retrievingData("test.txt", &L, &l);
    if(env != nullptr){
        std::cout << L << l;
    }
    return 0;
}
*/