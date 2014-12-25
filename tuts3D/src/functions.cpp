#include "functions.h"

enum {SKY_LEFT = 0, SKY_BACK = 1, SKY_RIGHT = 2, SKY_FRONT = 3, SKY_TOP = 4, SKY_BOTTOM = 5};

float camX = 0.0, camY = 0.0, camZ = 5.0;
float camYaw = 0.0;
float camPitch = 0.0;
unsigned int skybox[6];

#ifndef M_PI
#define M_PI = 3.1415926535
#endif

void moveCamera(float dist, float dir) {
    float rad = (camYaw+dir)*M_PI/180.0;
    camX -= sin(rad)*dist;
    camZ -= cos(rad)*dist;
}

void moveCameraUp(float dist, float dir) {
    float rad = (camPitch+dir)*M_PI/180.0;
    camY -= sin(rad)*dist;
}

void lockCamera() {
    if (camPitch > 90)
        camPitch = 90;
    if (camPitch < -90)
        camPitch = -90;
    if (camYaw < 0.0)
        camYaw += 360;
    if (camYaw > 360)
        camYaw -= 360;
}

void updateCamera() {
    glTranslatef(-camX, -camY, -camZ);
}

void control(float moveVelocity, float mouseVelocity, bool mouseIn) {
    if (mouseIn) {
        int midX = 512;
        int midY = 384;
        int tmpx, tmpy;
        SDL_GetMouseState(&tmpx, &tmpy);
        camYaw += mouseVelocity * (midX - tmpx);
        camPitch += mouseVelocity * (midY - tmpy);
        lockCamera();
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]) {
            if (camPitch != 90 && camPitch != -90)
                moveCamera(moveVelocity, 0.0);
            moveCameraUp(moveVelocity, 180.0);
        } else if (keys[SDL_SCANCODE_S]) {
            if (camPitch != 90 && camPitch != -90)
                moveCamera(moveVelocity, 180.0);
            moveCameraUp(moveVelocity, 0.0);
        }
        
        if (keys[SDL_SCANCODE_A]) {
            moveCamera(moveVelocity, 90.0);
        } else if (keys[SDL_SCANCODE_D]) {
            moveCamera(moveVelocity, 270.0);
        }
    }
    
    glRotatef(-camPitch, 1.0, 0.0, 0.0);
    glRotatef(-camYaw, 0.0, 1.0, 0.0);
    camPitch = 0;
    camYaw = 0;
}

unsigned int loadTexture(const char* filename) {
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    SDL_FreeSurface(img);
    return id;
}

void initSkybox() {
    skybox[SKY_LEFT] = loadTexture("assets/sky_left.bmp");
    skybox[SKY_BACK] = loadTexture("assets/sky_back.bmp");
    skybox[SKY_RIGHT] = loadTexture("assets/sky_right.bmp");
    skybox[SKY_FRONT] = loadTexture("assets/sky_front.bmp");
    skybox[SKY_TOP] = loadTexture("assets/sky_top.bmp");
    skybox[SKY_BOTTOM] = loadTexture("assets/sky_bottom.bmp");
}

void killSkybox() {
    glDeleteTextures(6, &skybox[0]);
}

void drawSkybox(float size) {
    bool b1 = glIsEnabled(GL_TEXTURE_2D);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    //back face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size/2,size/2,size/2);
    glTexCoord2f(1,0);
    glVertex3f(-size/2,size/2,size/2);
    glTexCoord2f(1,1);
    glVertex3f(-size/2,-size/2,size/2);
    glTexCoord2f(0,1);
    glVertex3f(size/2,-size/2,size/2);
    glEnd();
    
    //left face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-size/2,size/2,size/2);
    glTexCoord2f(1,0);
    glVertex3f(-size/2,size/2,-size/2);
    glTexCoord2f(1,1);
    glVertex3f(-size/2,-size/2,-size/2);
    glTexCoord2f(0,1);
    glVertex3f(-size/2,-size/2,size/2);
    glEnd();
    
    //front face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1,0);
    glVertex3f(size/2,size/2,-size/2);
    glTexCoord2f(0,0);
    glVertex3f(-size/2,size/2,-size/2);
    glTexCoord2f(0,1);
    glVertex3f(-size/2,-size/2,-size/2);
    glTexCoord2f(1,1);
    glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    
    //right face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(size/2,size/2,-size/2);
    glTexCoord2f(1,0);
    glVertex3f(size/2,size/2,size/2);
    glTexCoord2f(1,1);
    glVertex3f(size/2,-size/2,size/2);
    glTexCoord2f(0,1);
    glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    
    //top face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);
    glBegin(GL_QUADS);
    glTexCoord2f(1,0);
    glVertex3f(size/2,size/2,size/2);
    glTexCoord2f(0,0);
    glVertex3f(-size/2,size/2,size/2);
    glTexCoord2f(0,1);
    glVertex3f(-size/2,size/2,-size/2);
    glTexCoord2f(1,1);
    glVertex3f(size/2,size/2,-size/2);
    glEnd();
    
    //bottom face
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);
    glBegin(GL_QUADS);
    glTexCoord2f(1,1);
    glVertex3f(size/2,-size/2,size/2);
    glTexCoord2f(0,1);
    glVertex3f(-size/2,-size/2,size/2);
    glTexCoord2f(0,0);
    glVertex3f(-size/2,-size/2,-size/2);
    glTexCoord2f(1,0);
    glVertex3f(size/2,-size/2,-size/2);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    if(!b1)
        glDisable(GL_TEXTURE_2D);
}

void drawCube(float size) {
    float difamb[] = {1.0, 0.5, 0.3, 1.0};
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
    
    //front face
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    
    //left face
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-size/2,size/2,size/2);
    glVertex3f(-size/2,size/2,-size/2);
    glVertex3f(-size/2,-size/2,-size/2);
    glVertex3f(-size/2,-size/2,size/2);
    
    //back face
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(size/2,size/2,-size/2);
    glVertex3f(-size/2,size/2,-size/2);
    glVertex3f(-size/2,-size/2,-size/2);
    glVertex3f(size/2,-size/2,-size/2);
    
    //right face
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(size/2,size/2,-size/2);
    glVertex3f(size/2,size/2,size/2);
    glVertex3f(size/2,-size/2,size/2);
    glVertex3f(size/2,-size/2,-size/2);
    
    //top face
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(size/2,size/2,size/2);
    glVertex3f(-size/2,size/2,size/2);
    glVertex3f(-size/2,size/2,-size/2);
    glVertex3f(size/2,size/2,-size/2);
    
    //bottom face
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(size/2,-size/2,size/2);
    glVertex3f(-size/2,-size/2,size/2);
    glVertex3f(-size/2,-size/2,-size/2);
    glVertex3f(size/2,-size/2,-size/2);
    glEnd();
}

bool raySphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r) {
    float b = 2 * (xd*(xs-xc) + yd*(ys-yc) + zd*(zs-zc));
    float c = xs*xs - 2*xs*xc + xc*xc + ys*ys - 2*ys*yc + yc*yc + zs*zs - 2*zs*zc + zc*zc - r*r;
    float disc = b*b - 4*c;
    
    if (disc < 0) {
        return false;
    } else {
        return true;
    }
}