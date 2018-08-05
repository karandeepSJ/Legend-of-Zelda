#include "sphere.h"
#include "main.h"

Sphere::Sphere(float x, float y, float z,float r, color_t color,float vx,float vy) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[600000];
    int idx=0,k;
    float a,b,c;
    this->radius=r;
    this->vx=vx;
    this->vy=vy;
    this->float_speed=0.007;
    for(int i=0;i<=360;i++)
    {
        for(int j=0;j<=90;j++)
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
        for(int j=0;j<=90;j++)
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
    this->object = create3DObject(GL_TRIANGLES, 91*361*3*2, vertex_buffer_data, color, GL_FILL);
}

void Sphere::draw(glm::mat4 VP,int flag) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(!(flag%2) || flag==-1 || flag==1000)
        draw3DObject(this->object);
}

void Sphere::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sphere::tick(int inv)
{
    if(inv==1)
        this->vx=-this->vx;
    else if(inv==2)
        this->vy=-this->vy;
    this->position.x+=vx;
    this->position.y+=vy;
}
void Sphere::bob(int inv,float x,float y)
{
        this->position.z+=this->float_speed;
        if(inv==1)
        {
            this->position.x=x;
            this->position.y=y;
            this->float_speed=0.007;            
        }
        else if(inv==2)
        {
            this->float_speed=-0.007;           
        }
}