#ifndef CANNON_H
#define CANNON_H
#include "main.h"
class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z,float,float,color_t);
    glm::vec3 position;
    glm::vec4 cannon_end;
    glm::vec4 new_cannon_end;
    float rotation,orientation_x,orientation_y;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void turn(float);
    double u,v;
    double speed,float_speed;
    double height;
private:
    VAO *cannon;
};
#endif // CANNON_H

