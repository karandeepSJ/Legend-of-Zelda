#include "barrel.h"
#include "main.h"
Barrel::Barrel(float x,float y,float z,float l,float r,color_t color)
{
    this->position = glm::vec3(x,y,z);
    this->rotation = 90;
    this->length = l;
    this->radius = r;
    GLfloat vertex_buffer_data[14000];
    int idx=0;
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = 0;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = l;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = 0;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);
        vertex_buffer_data[idx++] = 0;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = l;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = l;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*3*2, vertex_buffer_data, color);
    
}
void Barrel::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 orient    = glm::rotate((float) (this->orientation * M_PI / 180.0f), glm::vec3(1,0,0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,1,0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // this->new_Barrel_end=Matrices.model*this->Barrel_end;
    // printf("%f %f %f\n",this->new_Barrel_end.x,this->new_Barrel_end.y,this->new_Barrel_end.z);
    draw3DObject(this->object);
}
