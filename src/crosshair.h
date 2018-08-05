#include "main.h"
#ifndef CROSSHAIR_H
#define CROSSHAIR_H

class Crosshair {
public:
    Crosshair() {}
    Crosshair(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(glm::vec3);
private:
    VAO *horiz,*vert;
};


#endif // CROSSHAIR_H

