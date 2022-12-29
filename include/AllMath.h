#ifndef ALLMATH
#define ALLMATH

#include <math.h>
#include <algorithm>
#include "MeshMaker.h"

struct mat4x4{
	float m[4][4] = { 0 };
};

class AllMath {
    public:
        static vec3d addVector(vec3d &v1, vec3d &v2);
        static vec3d subVector(vec3d &v1, vec3d &v2);
        static vec3d mulVector(vec3d &v, float k);
        static vec3d divVector(vec3d &v, float k);
        static float dotProd(vec3d &v1, vec3d &v2);
        static float len(vec3d &v);
        static vec3d norm(vec3d &v);
        static vec3d crossProd(vec3d &v1, vec3d &v2);
        static vec3d matrixMultVector(mat4x4 &m, vec3d &i);
        static mat4x4 identMatrix();
        static mat4x4 rotMatX(float a);
        static mat4x4 rotMatY(float a);
        static mat4x4 rotMatZ(float a);
        static mat4x4 transMat(float x, float y, float z);
        static mat4x4 makeProjMatrix(float fFov, float fAspectRatio, float fNear, float fFar);
        static mat4x4 matXmat(mat4x4 &m1, mat4x4 &m2);
        static mat4x4 matPointAt(vec3d &pos, vec3d &target, vec3d &up);
        static mat4x4 matrixQuickInverse(mat4x4 &m);
};

#endif
