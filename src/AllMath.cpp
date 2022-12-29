#include "AllMath.h"
#define PI 3.14159265f

vec3d AllMath::addVector(vec3d &v1, vec3d &v2){
    return {(v1.x+v2.x),(v1.y+v2.y),(v1.z+v2.z)};
}

vec3d AllMath::subVector(vec3d &v1, vec3d &v2){
    return {(v1.x-v2.x),(v1.y-v2.y),(v1.z-v2.z)};
}

vec3d AllMath::mulVector(vec3d &v, float k){
    return {(v.x*k),(v.y*k),(v.z*k)};
}

vec3d AllMath::divVector(vec3d &v, float k){
    return {(v.x/k),(v.y/k),(v.z/k)};
}

float AllMath::dotProd(vec3d &v1, vec3d &v2){
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float AllMath::len(vec3d &v){
    return std::sqrt(AllMath::dotProd(v,v));
}

vec3d AllMath::norm(vec3d &v){
    float l = AllMath::len(v);
    return {(v.x/l),(v.y/l),(v.z/l)};
}

vec3d AllMath::crossProd(vec3d &v1, vec3d &v2){
    vec3d v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

vec3d AllMath::matrixMultVector(mat4x4 &m, vec3d &i){
    vec3d v;
    v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    return v;
}

mat4x4 AllMath::identMatrix(){
    mat4x4 m;
    m.m[0][0] = 1.0f;
    m.m[1][1] = 1.0f;
    m.m[2][2] = 1.0f;
    m.m[3][3] = 1.0f;
    return m;
}

mat4x4 AllMath::rotMatX(float a){
    mat4x4 m;
    m.m[0][0] = 1.0f;
    m.m[1][1] = std::cos(a);
    m.m[1][2] = std::sin(a);
    m.m[2][1] = -std::sin(a);
    m.m[2][2] = std::cos(a);
    m.m[3][3] = 1.0f;
    return m;
}

mat4x4 AllMath::rotMatY(float a){
    mat4x4 m;
    m.m[0][0] = std::cos(a);
    m.m[0][2] = std::sin(a);
    m.m[2][0] = -std::sin(a);
    m.m[1][1] = 1.0f;
    m.m[2][2] = std::cos(a);
    m.m[3][3] = 1.0f;
    return m;
}

mat4x4 AllMath::rotMatZ(float a){
    mat4x4 m;
    m.m[0][0] = std::cos(a);
    m.m[0][1] = std::sin(a);
    m.m[1][0] = -std::sin(a);
    m.m[1][1] = std::cos(a);
    m.m[2][2] = 1.0f;
    m.m[3][3] = 1.0f;
    return m;
}

mat4x4 AllMath::transMat(float x, float y, float z){
    mat4x4 m;
    m.m[0][0] = 1.0f;
    m.m[1][1] = 1.0f;
    m.m[2][2] = 1.0f;
    m.m[3][3] = 1.0f;
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

mat4x4 AllMath::makeProjMatrix(float fFov, float fAspectRatio, float fNear, float fFar){
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * PI);
    mat4x4 m;
    m.m[0][0] = fAspectRatio * fFovRad;
    m.m[1][1] = fFovRad;
    m.m[2][2] = fFar / (fFar - fNear);
    m.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    m.m[2][3] = 1.0f;
    m.m[3][3] = 0.0f;
    return m;
}

mat4x4 AllMath::matXmat(mat4x4 &m1, mat4x4 &m2){
    mat4x4 m;
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            m.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
    return m;
}

mat4x4 AllMath::matPointAt(vec3d &pos, vec3d &target, vec3d &up){
    vec3d newForward = AllMath::subVector(target, pos);
    newForward = AllMath::norm(newForward);

    vec3d a = AllMath::mulVector(newForward, AllMath::dotProd(up, newForward));
    vec3d newUp = AllMath::subVector(up, a);
    newUp = AllMath::norm(newUp);

    vec3d newRight = AllMath::crossProd(newUp, newForward);

    mat4x4 m;
    m.m[0][0] = newRight.x;	    m.m[0][1] = newRight.y;	    m.m[0][2] = newRight.z;	    m.m[0][3] = 0.0f;//a
    m.m[1][0] = newUp.x;		m.m[1][1] = newUp.y;		m.m[1][2] = newUp.z;		m.m[1][3] = 0.0f;//b
    m.m[2][0] = newForward.x;	m.m[2][1] = newForward.y;	m.m[2][2] = newForward.z;	m.m[2][3] = 0.0f;//c
    m.m[3][0] = pos.x;			m.m[3][1] = pos.y;			m.m[3][2] = pos.z;			m.m[3][3] = 1.0f;
    return m;
}

mat4x4 AllMath::matrixQuickInverse(mat4x4 &m){
    mat4x4 matrix;
    matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    matrix.m[3][3] = 1.0f;
    return matrix;
}