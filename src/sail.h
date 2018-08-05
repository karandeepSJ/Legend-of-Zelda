#ifndef SAIL_H
#define SAIL_H
#include "main.h"
class Sail {
public:
    Sail() {}
    Sail(float x, float y, float z,float,float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void jump(float);
    void set_v(float);
    void move_forward(float);
    void turn(float);
    void bob();
    double u,v;
    double speed,float_speed;
    double height;
private:
    VAO *rod,*flag;
};
#endif // SAIL_H

