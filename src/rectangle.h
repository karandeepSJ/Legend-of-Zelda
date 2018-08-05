#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "main.h"
class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y, float z,float,float, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float breadth;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};
#endif // RECTANGLE_H

