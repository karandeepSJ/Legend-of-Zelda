#include "main.h"

#ifndef BALL_H
#define BALL_H
class Ball {
public:
    Ball() {}
    Ball(float , float , float , float, color_t color);
    glm::vec3 position;
    float rotation,radius;
    void draw(glm::mat4 VP);
    void fire(float,float,float);
    void set_position(float,float,float);
    float uy,ux;
    float launchz;
    float v;
    float u;
private:
    VAO *object;
};

#endif // BALL_H
