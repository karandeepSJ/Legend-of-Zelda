#include "main.h"
#ifndef MONSTER_H
#define MONSTER_H

class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, float r,float h,float rot,color_t color,float,float);
    glm::vec3 position;
    float rotation,vx,vy,float_speed;
    void draw(glm::mat4 VP,int);
    void set_position(float x, float y);
    int tick(int );
    int bob(int,float,float,float);
    double height,radius;
private:
    VAO *object;
};


#endif // MONSTER_H

