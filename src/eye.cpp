#include "eye.h"
#include "main.h"
Eye::Eye(float x,float y,float z,float r,color_t color,float vx,float vy)
{
    this->position = glm::vec3(x,y,z);
    this->rotation = 90;
    this->radius = r;
    this->vx = vx;
    this->vy = vy;
    this->float_speed=0.007;
    GLfloat vertex_buffer_data[4000];
    int idx=0;
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data[idx++] = 0.0f;
        vertex_buffer_data[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data[idx++] = 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color);
    
}
void Eye::draw(glm::mat4 VP,int flag) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 orient    = glm::rotate((float) (this->orientation * M_PI / 180.0f), glm::vec3(1,0,0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1,0,0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // this->new_Eye_end=Matrices.model*this->Eye_end;
    // printf("%f %f %f\n",this->new_Eye_end.x,this->new_Eye_end.y,this->new_Eye_end.z);
    if(!(flag%2) || flag==-1)
        draw3DObject(this->object);
}

void Eye::tick(int inv)
{
    if(inv==1)
        this->vx=-this->vx;
    else if(inv==2)
        this->vy=-this->vy;
    this->position.x+=vx;
    this->position.y+=vy;
}
void Eye::bob(int inv,float x,float y)
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