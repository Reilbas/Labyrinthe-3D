#ifndef MESHMAKER
#define MESHMAKER

#include <iostream>
#include <vector>

struct vertex {
	float x, y, z;
};

struct triangle {
	vertex p[3];
};

struct mesh {
	std::vector<triangle> tris;
};

class MeshMaker {
    // Constructeur et Méthodes
    public:
        static mesh Pyramide(float x, float y, float z);
        static mesh Cube(float x, float y, float z);
};

#endif
