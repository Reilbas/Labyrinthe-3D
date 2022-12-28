#ifndef READERWRITER
#define READERWRITER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ReaderWriter {
    public:
        static char** retrievingLevel(std::string nomFic, int* L, int* l);
        //static void saveData();
};

#endif
