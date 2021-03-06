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
        int dx = 512, dy = 384;
        SDL_GetRelativeMouseState(&dx, &dy);
        //if (dx != 0 || dy != 0)
        //    std::cout << "mouse loc (" << dx << ", " << dy << ")" << std::endl;
        camYaw -= mouseVelocity * dx;
        camPitch -= mouseVelocity * dy;
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
}

void moveTo(coordinate c) {
    camX = c.x;
    camY = c.y;
    camZ = c.z;
}

coordinate cameraPosition() {
    return coordinate(camX, camY, camZ);
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

bool raySphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r, float* dist, coordinate* point) {
    float b = 2 * (xd*(xs-xc) + yd*(ys-yc) + zd*(zs-zc));
    float c = xs*xs - 2*xs*xc + xc*xc + ys*ys - 2*ys*yc + yc*yc + zs*zs - 2*zs*zc + zc*zc - r*r;
    float disc = b*b - 4*c;
    
    if (disc < 0)
        return false;
    
    if (dist != NULL) {
        (*dist) = (-b + disc) / 2;
        if (point != NULL) {
            point->x = xs+(*dist)*xd;
            point->y = ys+(*dist)*yd;
            point->z = zs+(*dist)*zd;
        }
    }
    return true;
}

bool rayPlane(float xn, float yn, float zn, float xd, float yd, float zd, float xs, float ys, float zs, coordinate p1, coordinate p2, coordinate p3, coordinate p4, float* dist, coordinate* point) {
    float a = xd*xn + yd*yn + zd*zn;
    if (a == 0)
        return false;
    
    float t = (p1.x*xn + p1.y*yn + p1.z*zn - xn*xs - yn*ys - zn*zs) / a;
    if (t < 0)
        return false;
    
    float x = xs + t*xd;
    float y = ys + t*yd;
    float z = zs + t*zd;
    coordinate cp(x, y, z);
    if (abs(triangleArea(p1, p3, p4)-triangleArea(p1, p4, cp)-triangleArea(p1, p3, cp)-triangleArea(p3, p4, cp)) < 0.00001 ||
        abs(triangleArea(p1, p2, p3)-triangleArea(p1, p2, cp)-triangleArea(p2, p3, cp)-triangleArea(p1, p3, cp)) < 0.00001) {
        if (dist != NULL) {
            (*dist) = t;
            if (point != NULL) {
                point->x = x;
                point->y = y;
                point->z = z;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool sphereSphere(coordinate& c1, float r1, coordinate c2, float r2) {
    float dist = pointDistance(c1, c2);
    if (dist <= ((r1+r2)*(r1*r2))) { //slightly more efficient to square a value than to take the square root
        float len = sqrt(dist);
        float a = len - (r1+r2);
        coordinate vec(c2.x-c1.x, c2.y-c1.y, c2.z-c1.z);
        vec.x /= len;
        vec.y /= len;
        vec.z /= len;
        c1.x = c1.x + vec.x*a;
        c1.y = c1.y + vec.y*a;
        c1.z = c1.z + vec.z*a;
        return true;
    }
    return false;
}

bool spherePlane(coordinate& sp, float r, coordinate vn, coordinate p1, coordinate p2, coordinate p3, coordinate p4) {
    float dist1 = 0, dist2 = 0;
    if (rayPlane(-vn.x, -vn.y, -vn.z, sp.x, sp.y, sp.z, vn.x, vn.y, vn.z, p1, p2, p3, p4, &dist1) ||
        rayPlane(vn.x, vn.y, vn.z, sp.x, sp.y, sp.z, -vn.x, -vn.y, -vn.z, p1, p2, p3, p4, &dist2)) {
        if (dist1 > r || dist2 > r)
            return false;
        if (dist1 > 0) {
            sp.x = sp.x - vn.x*(r-dist1);
            sp.y = sp.y - vn.y*(r-dist1);
            sp.z = sp.z - vn.z*(r-dist1);
        } else {
            sp.x = sp.x + vn.x*(r-dist2);
            sp.y = sp.y + vn.y*(r-dist2);
            sp.z = sp.z + vn.z*(r-dist2);
        }
        return true;
    }
    return false;
}

float triangleArea(coordinate p1, coordinate p2, coordinate p3) {
    float a = sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
    float b = sqrt((p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y)+(p3.z-p2.z)*(p3.z-p2.z));
    float c = sqrt((p3.x-p1.x)*(p3.x-p1.x)+(p3.y-p1.y)*(p3.y-p1.y)+(p3.z-p1.z)*(p3.z-p1.z));
    
    float s = (a+b+c) / 2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

float pointDistance(coordinate p1, coordinate p2) {
    coordinate vec(p2.x-p1.x, p2.y-p1.y, p2.z-p1.z);
    return (vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}