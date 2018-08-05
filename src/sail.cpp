#include "sail.h"
#include "main.h"
Sail::Sail(float x,float y,float z,float h,float r)
{
    this->u=0;
    this->v=0;
    this->position = glm::vec3(x,y,z);
    this->rotation = 0;
    this->height = h;
    this->float_speed=0.005;
    GLfloat vertex_buffer_data_rod[14000];
    GLfloat vertex_buffer_data_flag[] = {
        0.0f,r,h, // triangle 1 : begin
        0.0f,r, h/2,
        0.0f, r+0.5f, 3*h/4, // triangle 1 : end
    };
    this->flag = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_flag, COLOR_ORANGE);
    int idx=0;
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = 0;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = h;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = 0;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*j/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*j/180);
        vertex_buffer_data_rod[idx++] = 0;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = h;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = h;
    }
    for(int i=0;i<=360;i++)
    {
        int j=i+1;
        vertex_buffer_data_rod[idx++] = 0.0f;
        vertex_buffer_data_rod[idx++] = 0.0f;
        vertex_buffer_data_rod[idx++] = 0.0f;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = 0;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = 0;
        vertex_buffer_data_rod[idx++] = 0.0f;
        vertex_buffer_data_rod[idx++] = 0.0f;
        vertex_buffer_data_rod[idx++] = h;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*i/180);
        vertex_buffer_data_rod[idx++] = h;
        vertex_buffer_data_rod[idx++] = r*cos(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = r*sin(M_PI*j/180);;
        vertex_buffer_data_rod[idx++] = h;
    }
    this->rod = create3DObject(GL_TRIANGLES, 360*3*4, vertex_buffer_data_rod, COLOR_BROWN);
    
}
void Sail::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rod);
    draw3DObject(this->flag);
}

void Sail::move_forward(float vel)
{
	this->position.y+=vel*cos(-this->rotation*M_PI/180);
	this->position.x+=vel*sin(-this->rotation*M_PI/180);
}
void Sail::set_position(float x,float y,float z)
{
	this->position=glm::vec3(x,y,z);
}
void Sail::set_v(float vel)
{
	this->v=vel;
}
void Sail::jump(float vel)
{
	if(this->u==0)
	{
		this->u=vel;
		this->v=vel;
	}	
}
void Sail::turn(float angle)
{
	this->rotation+=angle;
}
void Sail::bob()
{
    if(this->u==0)
    {
        this->position.z+=this->float_speed;
        if(this->position.z<=-0.1)
        {
            this->float_speed=0.005;            
        }
        else if(this->position.z>=0.1)
        {
            this->float_speed=-0.005;           
        }
    }
}