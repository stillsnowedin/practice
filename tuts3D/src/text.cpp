#include "text.h"

text::text(float w, float h, std::vector<unsigned int>& ch) {
    width = w;
    height = h;
    characters = ch;
}

void text::drawText(coordinate pos, coordinate rot, const char* tex) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.x, 1.0, 0.0, 0.0);
    glRotatef(rot.y, 0.0, 1.0, 0.0);
    glRotatef(rot.z, 0.0, 0.0, 1.0);
    
    int g = 0;
    for (int i=0; i<strlen(tex); i++) {
        if (tex[i] == ' ') {
            glTranslatef(width, 0.0, 0.0);
            g++;
            continue;
        }
        if (tex[i] == '\n') {
            glTranslatef(-g*width, -height, 0.0);
            g = 0;
            continue;
        }
        g++;
        glCallList(characters.at((int)tex[i]-65));
        glTranslatef(width, 0.0, 0.0);
    }
    glPopMatrix();
}