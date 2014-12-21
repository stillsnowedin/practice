#ifndef __tuts3D__objLoader__
#define __tuts3D__objLoader__

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct coordinate {
    float x, y, z;
    coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
};

struct face {
    int faceNum;
    bool isQuad;
    int faces[4];
    int texcoords[4];
    int mat;
    
    face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m) {
        faceNum = facen;
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        texcoords[0] = t1;
        texcoords[1] = t2;
        texcoords[2] = t3;
        mat = m;
        isQuad = false;
    }
    
    face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m) {
        faceNum = facen;
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        faces[3] = f4;
        texcoords[0] = t1;
        texcoords[1] = t2;
        texcoords[2] = t3;
        texcoords[3] = t4;
        mat = m;
        isQuad = true;
    }
};

struct material {
    std::string name;
    float alpha, ns, ni;
    float dif[3], amb[3], spec[3];
    int illum;
    unsigned int texture;
    
    material(const char* n, float a, float p_ns, float p_ni, float* p_d, float* p_a, float* p_s, int p_i, unsigned int p_t) {
        name = n;
        alpha = a;
        ns = p_ns;
        ni = p_ni;
        
        dif[0] = p_d[0];
        dif[1] = p_d[1];
        dif[2] = p_d[2];
        
        amb[0] = p_a[0];
        amb[1] = p_a[1];
        amb[2] = p_a[2];
        
        spec[0] = p_s[0];
        spec[1] = p_s[1];
        spec[2] = p_s[2];
        
        illum = p_i;
        texture = p_t;
    };
};

struct texCoord {
    float u, v;
    texCoord(float a, float b) : u(a), v(b) {};
};

class objLoader {
public:
    objLoader();
    ~objLoader();
    int loadObject(const char* filename);
    
private:
    std::vector<std::string*> coords;
    std::vector<coordinate*> vertices;
    std::vector<face*> faces;
    std::vector<coordinate*> normals;
    std::vector<material*> materials;
    std::vector<texCoord*> texCoords;
    std::vector<coordinate*> vertexNormals;
    std::vector<unsigned int> textures;
    std::vector<unsigned int> lists;
    unsigned int vao;
    bool isMaterial, isNormal, isTexture, isVertexNormal;
    unsigned int loadTexture(const char* filename);
    void clean();
    void smoothNormals();
    
};

#endif /* defined(__tuts3D__objLoader__) */
