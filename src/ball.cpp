#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z,float r, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[1200000];
    int idx=0,k;
    this->rotation=0;
    float a,b,c;
    this->radius=r;
    for(int i=0;i<=360;i++)
    {
        for(int j=0;j<=180;j++)
        {
            c=r*cos(M_PI*j/180);
            a=r*sin(M_PI*j/180)*cos(M_PI*i/180);
            b=r*sin(M_PI*j/180)*sin(M_PI*i/180);
            vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*cos(M_PI*(i+1)/180);
            vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*sin(M_PI*(i+1)/180);
            vertex_buffer_data[idx++]=r*cos(M_PI*j/180);
            vertex_buffer_data[idx++]=a;
            vertex_buffer_data[idx++]=b;
            vertex_buffer_data[idx++]=c;
            k=j+1;
            c=r*cos(M_PI*k/180);
            a=r*sin(M_PI*k/180)*cos(M_PI*i/180);
            b=r*sin(M_PI*k/180)*sin(M_PI*i/180);
            vertex_buffer_data[idx++]=a;
            vertex_buffer_data[idx++]=b;
            vertex_buffer_data[idx++]=c;
        }
    }
    for(int i=0;i<=360;i++)
    {
        for(int j=0;j<=180;j++)
        {
            c=r*cos(M_PI*(j+1)/180);
            a=r*sin(M_PI*(j+1)/180)*cos(M_PI*(i+1)/180);
            b=r*sin(M_PI*(j+1)/180)*sin(M_PI*(i+1)/180);
            vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*cos(M_PI*(i+1)/180);
            vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*sin(M_PI*(i+1)/180);
            vertex_buffer_data[idx++]=r*cos(M_PI*j/180);
            vertex_buffer_data[idx++]=a;
            vertex_buffer_data[idx++]=b;
            vertex_buffer_data[idx++]=c;
            k=j+1;
            c=r*cos(M_PI*k/180);
            a=r*sin(M_PI*k/180)*cos(M_PI*i/180);
            b=r*sin(M_PI*k/180)*sin(M_PI*i/180);
            vertex_buffer_data[idx++]=a;
            vertex_buffer_data[idx++]=b;
            vertex_buffer_data[idx++]=c;
        }
    }
    // for(int i=0;i<idx;i++)
    //     printf("%f ",vertex_buffer_data[i]);
    this->object = create3DObject(GL_TRIANGLES, 181*361*3*2, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (rotate*translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Ball::fire(float speed,float rotation,float angle)
{
    double theta=M_PI*angle/180;
    this->uy=2*speed*sin(theta)*cos(M_PI*rotation/180);
    this->ux=2*speed*sin(theta)*sin(-M_PI*rotation/180);
    printf("%f\n",angle);
    this->u=speed*cos(theta);
    this->v=speed*cos(theta);
    this->launchz=this->position.z;
}

void Ball::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}
