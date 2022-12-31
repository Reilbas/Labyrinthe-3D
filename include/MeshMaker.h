#ifndef MESHMAKER
#define MESHMAKER

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct vec3d {
	float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;
};

struct triangle {
	vec3d p[3];
    unsigned char r,g,b;
};

struct mesh {
	std::vector<triangle> tris;
};

class MeshMaker {
    // Constructeur et Méthodes
    public:
        static mesh Cube(float x, float y, float z, float h, float size);
        static mesh Tile(float x, float y, float z, float size);
        static mesh fromObj(std::string nomfic,float x, float y, float z, float size);
};

#endif
