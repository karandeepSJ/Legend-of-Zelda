#include "crosshair.h"
#include "main.h"
Crosshair::Crosshair(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data1[] = {
        -0.03f,-0.0f, -0.005f,
        -0.03f,-0.0f, 0.005f,
        -0.005f, 0.0f, -0.005f,
        -0.03f, 0.0f, 0.005f,
        -0.005f,-0.0f, -0.005f,
        -0.005f,-0.0f, 0.005f,
        0.03f,-0.0f, -0.005f,
        0.03f,-0.0f, 0.005f,
        0.005f, 0.0f, -0.005f,
        0.03f, 0.0f, 0.005f,
        0.005f,-0.0f, -0.005f,
        0.005f,-0.0f, 0.005f,
        
    };
    static const GLfloat vertex_buffer_data2[] = {
        -0.005f,-0.0f, -0.03f,
        0.005f,-0.0f, -0.03f,
        -0.005f, 0.0f, -0.005f,
        0.005f, 0.0f, -0.03f,
        -0.005f,-0.0f, -0.005f,
        0.005f,-0.0f, -0.005f,
        -0.005f,-0.0f, 0.03f,
        0.005f,-0.0f, 0.03f,
        -0.005f , 0.0f, 0.005f,
        0.005f, 0.0f, 0.03f,
        -0.005f,-0.0f, 0.005f,
        0.005f,-0.0f, 0.005f,
    };

    this->vert = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, color, GL_FILL);
    this->horiz = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data1, color, GL_FILL);
}

void Crosshair::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->horiz);
    draw3DObject(this->vert);
}

void Crosshair::set_position(glm::vec3 position)
{
	this->position=position;
}