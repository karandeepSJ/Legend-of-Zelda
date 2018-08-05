#include "cannon.h"
#include "main.h"
Cannon::Cannon(float x,float y,float z,float h,float r,color_t color)
{
    this->u=0;
    this->v=0;
    this->position = glm::vec3(x,y,z);
    this->orientation_y = -60;
    this->orientation_x = 0;
    this->rotation = 0;
    this->height = h;
    this->float_speed=0.005;
    this->cannon_end=glm::vec4(0,0,h/2,1);
    this->new_cannon_end=glm::vec4(0,0,h/2,1);
    GLfloat vertex_buffer_data[14000];
    int idx=0;
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = h/2;
    }
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = -h/2;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = h/2;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = h/2;
    }
    this->cannon = create3DObject(GL_TRIANGLES, 360*3*4, vertex_buffer_data, color);
    
}
void Cannon::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 orient_x    = glm::rotate((float) (this->orientation_x * M_PI / 180.0f), glm::vec3(0,1,0));
    glm::mat4 orient_y    = glm::rotate((float) (this->orientation_y * M_PI / 180.0f), glm::vec3(1,0,0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * orient_y * orient_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->new_cannon_end=Matrices.model*this->cannon_end;
    draw3DObject(this->cannon);
}

void Cannon::turn(float angle)
{
	this->rotation+=angle;
}
