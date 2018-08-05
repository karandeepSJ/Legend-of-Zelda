#ifndef BOAT_H
#define BOAT_H
#include "main.h"
class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position,cannon_position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void jump(float);
    void set_v(float);
    void move_forward(float);
    void turn(float);
    void bob();
    double u,v;
    glm::vec4 bl;
    glm::vec4 br;
    glm::vec4 tl;
    glm::vec4 tr;
    glm::vec4 top;
    glm::vec4 ntop;
    glm::vec4 nbl;
    glm::vec4 nbr;
    glm::vec4 ntl;
    glm::vec4 ntr;
    double speed,float_speed;
private:
    VAO *base,*left,*right,*front,*back,*cannon;
};
#endif // BOAT_H

