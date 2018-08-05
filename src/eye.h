#include "main.h"
#ifndef EYE_H
#define EYE_H

class Eye {
public:
    Eye() {}
    Eye(float x, float y, float z, float r,color_t color,float,float);
    glm::vec3 position;
    float rotation,vx,vy,float_speed;
    void draw(glm::mat4 VP,int);
    void set_position(float x, float y);
    void tick(int);
    void bob(int,float,float);
    double radius;
private:
    VAO *object;
};


#endif // EYE_H

