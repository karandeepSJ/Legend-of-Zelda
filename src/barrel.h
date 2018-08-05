
#ifndef BARREL_H
#define BARREL_H
#include "main.h"
class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z,float,float,color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double length,radius;
private:
    VAO *object;
};
#endif // BARREL_H

