#include "objLoader.h"

objLoader::objLoader() {
    isMaterial = false;
    isNormal = false;
    isTexture = false;
}

objLoader::~objLoader() {
    for (std::vector<unsigned int>::const_iterator it = textures.begin(); it != textures.end(); it++) {
        glDeleteTextures(1, &(*it));
    }
    for (std::vector<unsigned int>::const_iterator it = lists.begin(); it != lists.end(); it++) {
        glDeleteLists(*it, 1);
    }
}

unsigned int objLoader::loadTexture(const char* filename) {
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    //glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    SDL_FreeSurface(img);
    
    textures.push_back(id);
    return id;
}

int objLoader::loadObject(const char* filename) {
    std::vector<std::string*> coords;
    std::vector<coordinate*> vertices;
    std::vector<face*> faces;
    std::vector<coordinate*> normals;
    
    if (vao == 0)
        glGenVertexArrays(1, &vao);
    
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Could not open " << filename << std::endl;
        return -1;
    }
    
    char buf[256];
    int curmat = 0;
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
                if (coords[k]->find("//") != std::string::npos) {
                    sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
                    faces.push_back(new face(b, a, c, d, e, 0, 0, 0, 0, curmat));
                } else if (coords[k]->find("/") != std::string::npos) {
                    int t[4];
                    sscanf(coords[k]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b, &e, &t[3], &b);
                    faces.push_back(new face(b, a, c, d, e, t[0], t[1], t[2], t[3], curmat));
                } else {
                    sscanf(coords[k]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
                    faces.push_back(new face(-1, a, b, c, d, 0, 0, 0, 0, curmat));
                }
            } else { //triangle
                if (coords[k]->find("//") != std::string::npos) {
                    sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
                    faces.push_back(new face(b, a, c, d, 0, 0, 0, curmat));
                } else if (coords[k]->find("/") != std::string::npos) {
                    int t[3];
                    sscanf(coords[k]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b);
                    faces.push_back(new face(b, a, c, d, t[0], t[1], t[2], curmat));
                } else {
                    sscanf(coords[k]->c_str(), "f %d %d %d", &a, &b, &c);
                    faces.push_back(new face(-1, a, b, c, 0, 0, 0, curmat));
                }
            }
        } else if ((*coords[k])[0] == 'u' && (*coords[k])[1] == 's' && (*coords[k])[2] == 'e') {
            char tmp[200];
            sscanf(coords[k]->c_str(), "usemtl %s", tmp);
            for (int i = 0; i < materials.size(); i++) {
                if (strcmp(materials[i]->name.c_str(), tmp)) {
                    curmat = i;
                    break;
                }
            }
        } else if ((*coords[k])[0] == 'm' && (*coords[k])[1] == 't' && (*coords[k])[2] == 'l') {
            char filen[200];
            sscanf(coords[k]->c_str(), "mtllib %s", filen);
            std::ifstream mtlin(filen);
            if (!mtlin.is_open()) {
                std::cout << "Couldn't open " << filen << std::endl;
                clean();
                return -1;
            }
            isMaterial = true;
            std::vector<std::string> tmp;
            char c[200];
            while (!mtlin.eof()) {
                mtlin.getline(c, 200);
                tmp.push_back(c);
            }
            char name[200];
            char filename[200];
            float amb[3], dif[3], spec[3], alpha, ns, ni;
            int illum;
            unsigned int texture;
            bool isMaterial = false;
            strcpy(filename, "\0");
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp[i][0] == '#') {
                    continue;
                }
                if (tmp[i][0] == 'n' && tmp[i][1] == 'e' && tmp[i][2] == 'w') {
                    if (isMaterial) {
                        if (strcmp(filename, "\0|") != 0) {
                            materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
                            strcpy(filename, "\0");
                        } else {
                            materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
                        }
                    }
                    isMaterial = false;
                    sscanf(tmp[i].c_str(), "newmtl %s", name);
                } else if (tmp[i][0] == 'N' && tmp[i][1] == 's') {
                    sscanf(tmp[i].c_str(), "Ns %f", &ns);
                    isMaterial = true;
                } else if (tmp[i][0] == 'K' && tmp[i][1] == 'a') {
                    sscanf(tmp[i].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
                    isMaterial = true;
                } else if (tmp[i][0] == 'K' && tmp[i][1] == 'd') {
                    sscanf(tmp[i].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
                    isMaterial = true;
                } else if (tmp[i][0] == 'K' && tmp[i][1] == 's') {
                    sscanf(tmp[i].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
                    isMaterial = true;
                } else if (tmp[i][0] == 'N' && tmp[i][1] == 'i') {
                    sscanf(tmp[i].c_str(), "Ki %f", &ni);
                    isMaterial = true;
                } else if (tmp[i][0] == 'd' && tmp[i][1] == ' ') {
                    sscanf(tmp[i].c_str(), "d %f", &alpha);
                    isMaterial = true;
                } else if (tmp[i][0] == 'i' && tmp[i][1] == 'l') {
                    sscanf(tmp[i].c_str(), "illum %d", &illum);
                    isMaterial = true;
                } else if (tmp[i][0] == 'm' && tmp[i][1] == 'a') {
                    sscanf(tmp[i].c_str(), "map_Kd %s", filename);
                    texture = loadTexture(filename);
                    isMaterial = true;
                }
            }
            if (isMaterial) {
                if (strcmp(filename, "\0|") != 0) {
                    materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texture));
                } else {
                    materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
                }
            }
        } else if ((*coords[k])[0] == 'v' && (*coords[k])[1] == 't') {
            float u, v;
            sscanf(coords[k]->c_str(), "vt %f %f", &u, &v);
            texCoords.push_back(new texCoord(u, 1-v));
            isTexture = true;
        }
        if (materials.size() == 0) {
            isMaterial = false;
        } else {
            isMaterial = true;
        }
    }
    
    //draw
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);
    int last = -1;
    for (int j = 0; j < faces.size(); j++) {
        if (last != faces[j]->mat && isMaterial) {
            float diffuse[] = { materials[faces[j]->mat]->dif[0], materials[faces[j]->mat]->dif[1], materials[faces[j]->mat]->dif[2], 1.0 };
            float ambient[] = { materials[faces[j]->mat]->amb[0], materials[faces[j]->mat]->amb[1], materials[faces[j]->mat]->amb[2], 1.0 };
            float specular[] = { materials[faces[j]->mat]->spec[0], materials[faces[j]->mat]->spec[1], materials[faces[j]->mat]->spec[2], 1.0 };
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
            glMaterialf(GL_FRONT, GL_SHININESS, materials[faces[j]->mat]->ns);
            last = faces[j]->mat;
            if (materials[faces[j]->mat]->texture == -1) {
                glDisable(GL_TEXTURE_2D);
            } else {
                glEnable(GL_TEXTURE_2D);
                //glBindVertexArray(vao);
                glBindTexture(GL_TEXTURE_2D, materials[faces[j]->mat]->texture);
            }
        }
        
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
    clean();
    lists.push_back(num);
    return num;
}

void objLoader::clean() {
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
    for (int i=0; i<materials.size(); i++) {
        delete materials[i];
    }
    for (int i=0; i<texCoords.size(); i++) {
        delete texCoords[i];
    }
    coords.clear();
    faces.clear();
    normals.clear();
    vertices.clear();
    materials.clear();
    texCoords.clear();
}