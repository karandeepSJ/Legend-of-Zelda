#include "main.h"
#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float, float r,color_t color,float,float);
    glm::vec3 position;
    float rotation,vx,vy,float_speed;
    void draw(glm::mat4 VP,int);
    void set_position(float x, float y);
    void tick(int);
    void bob(int,float,float);
    double speed,radius;
private:
    VAO *object;
};


#endif // SPHERE_H

