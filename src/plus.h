#include "main.h"
#ifndef PLUS_H
#define PLUS_H

class Plus {
public:
    Plus() {}
    Plus(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(glm::vec3);
private:
    VAO *horiz,*vert;
};


#endif // PLUS_H

