#include "functions.h"

int loadObject(const char* filename) {
    std::vector<std::string*> coords;
    std::vector<coordinate*> vertices;
    std::vector<face*> faces;
    std::vector<coordinate*> normals;
    
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Could not open " << filename << std::endl;
        return -1;
    }
    
    char buf[256];
    while (!in.eof()) {
        in.getline(buf, 256);
        coords.push_back(new std::string(buf));
    }
    
    for (int k=0; k<coords.size(); k++) {
        if ((*coords[k])[0] == '#') { //ignore comments
            continue;
        } else if ((*coords[k])[0] == 'v' && (*coords[k])[1] == ' ') { //load vertices
            float tmpx, tmpy, tmpz;
            sscanf(coords[k]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
            vertices.push_back(new coordinate(tmpx, tmpy, tmpz));
        } else if ((*coords[k])[0] == 'v' && (*coords[k])[1] == 'n') { //load normals
            float tmpx, tmpy, tmpz;
            sscanf(coords[k]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
            normals.push_back(new coordinate(tmpx, tmpy, tmpz));
        } else if ((*coords[k])[0] == 'f') { //load faces
            int a, b, c, d, e;
            if (count(coords[k]->begin(), coords[k]->end(), ' ') == 4) { //quad
                sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
                faces.push_back(new face(b, a, c, d, e));
            } else { //triangle
                sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
                faces.push_back(new face(b, a, c, d));
            }
        }
        
    }
    
    //draw
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);
    for (int j = 0; j < faces.size(); j++) {
        if (faces[j]->isQuad) {
            glBegin(GL_QUADS);
            glNormal3f(normals[faces[j]->faceNum-1]->x, normals[faces[j]->faceNum-1]->y, normals[faces[j]->faceNum-1]->z);
            glVertex3f(vertices[faces[j]->faces[0]-1]->x, vertices[faces[j]->faces[0]-1]->y, vertices[faces[j]->faces[0]-1]->z);
            glVertex3f(vertices[faces[j]->faces[1]-1]->x, vertices[faces[j]->faces[1]-1]->y, vertices[faces[j]->faces[1]-1]->z);
            glVertex3f(vertices[faces[j]->faces[2]-1]->x, vertices[faces[j]->faces[2]-1]->y, vertices[faces[j]->faces[2]-1]->z);
            glVertex3f(vertices[faces[j]->faces[3]-1]->x, vertices[faces[j]->faces[3]-1]->y, vertices[faces[j]->faces[3]-1]->z);
            glEnd();
        } else {
            glBegin(GL_TRIANGLES);
            glNormal3f(normals[faces[j]->faceNum-1]->x, normals[faces[j]->faceNum-1]->y, normals[faces[j]->faceNum-1]->z);
            glVertex3f(vertices[faces[j]->faces[0]-1]->x, vertices[faces[j]->faces[0]-1]->y, vertices[faces[j]->faces[0]-1]->z);
            glVertex3f(vertices[faces[j]->faces[1]-1]->x, vertices[faces[j]->faces[1]-1]->y, vertices[faces[j]->faces[1]-1]->z);
            glVertex3f(vertices[faces[j]->faces[2]-1]->x, vertices[faces[j]->faces[2]-1]->y, vertices[faces[j]->faces[2]-1]->z);
            glEnd();
        }
    }
    glEndList();
    
    for (int i=0; i<coords.size(); i++) {
        delete coords[i];
    }
    for (int i=0; i<faces.size(); i++) {
        delete faces[i];
    }
    for (int i=0; i<normals.size(); i++) {
        delete normals[i];
    }
    for (int i=0; i<vertices.size(); i++) {
        delete vertices[i];
    }
    return num;
}

unsigned int loadTexture(const char* filename) {
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    
    return id;
}