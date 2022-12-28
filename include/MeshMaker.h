#ifndef MESHMAKER
#define MESHMAKER

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct vec3d {
	float x, y, z;
};

struct triangle {
	vec3d p[3];
};

struct mesh {
	std::vector<triangle> tris;
};

class MeshMaker {
    // Constructeur et Méthodes
    public:
        static mesh Cube(float x, float y, float z);
        static mesh fromObj(std::string nomfic,float x, float y, float z, float size);
};

#endif
