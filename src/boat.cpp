#include "boat.h"
#include "main.h"
Boat::Boat(float x,float y,float z)
{
	this->u=0;
	this->v=0;
	this->position = glm::vec3(x,y,z);
	this->rotation = 0;
	this->float_speed=0.005;
	this->bl=glm::vec4(-0.7,-1.2,0,1);
	this->br=glm::vec4(0.7,-1.2,0,1);
	this->tl=glm::vec4(-0.7,1.6,0,1);
	this->tr=glm::vec4(0.7,1.6,0,1);
	this->top = glm::vec4(0.0,1.8,0.6,1);
	this->nbl=this->bl;
    this->nbr=this->br;
    this->ntl=this->tl;
    this->ntr=this->tr;
    this->ntop=this->top;
	GLfloat vertex_buffer_data_base[] = {
        -0.3f,-1.2f,0.0f, // triangle 1 : begin
        -0.3f,1.2f, 0.0f,
        0.3f, 1.2f, 0.0f, // triangle 1 : end
        0.3f, 1.2f,0.0f, // triangle 2 : begin
        -0.3f,-1.2f,0.0f,
        0.3f, -1.2f,0.0f, // triangle 2 : end
    };
    this->base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_base, COLOR_DARKERRED);
    GLfloat vertex_buffer_data_left[] = {
        -0.3f,-1.2f,0.0f, // triangle 1 : begin
        -0.3f,1.2f, 0.0f,
        -0.3f-0.4f, -1.2f, 0.6f, // triangle 1 : end
        -0.3f, 1.2f,0.0f, // triangle 2 : begin
        -0.3f-0.4f,-1.2f,0.6f,
        -0.3f-0.4f, 1.2f,0.6f, // triangle 2 : end
    };
    this->left = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_left, COLOR_MEDRED);
    GLfloat vertex_buffer_data_right[] = {
        0.3f,-1.2f,0.0f, // triangle 1 : begin
        0.3f,1.2f, 0.0f,
        0.3f+0.4f, -1.2f, 0.6f, // triangle 1 : end
        0.3f, 1.2f,0.0f, // triangle 2 : begin
        0.3f+0.4f,-1.2f,0.6f,
        0.3f+0.4f, 1.2f,0.6f, // triangle 2 : end
    };
    this->right = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_right, COLOR_MEDRED);
    GLfloat vertex_buffer_data_back[] = {
        -0.3f,-1.2f,0.0f, // triangle 1 : begin
        0.3f,-1.2f, 0.0f,
        -0.3-0.4, -1.2f, 0.6f, // triangle 1 : end
        0.3f, -1.2f,0.0f, // triangle 2 : begin
        -0.3-0.4,-1.2f,0.6f,
        0.3+0.4, -1.2f,0.6f, // triangle 2 : end
    };
    this->back = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_back, COLOR_RED);
    GLfloat vertex_buffer_data_front[] = {
        -0.3f,1.2f,0.0f, // triangle 1 : begin
        0.3f,1.2f, 0.0f,
        0.0f,1.8f,0.6f,
        0.0f,1.8f,0.6f,
        -0.3f-0.4f, 1.2f, 0.6f, // triangle 1 : end
        -0.3f, 1.2f,0.0f, // triangle 2 : begin
        0.0f,1.8f,0.6f,
        0.3f,1.2f, 0.0f,
        0.3f+0.4f, 1.2f,0.6f, // triangle 2 : end
    };
    this->front = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data_front, COLOR_RED);

}
void Boat::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->left);
    draw3DObject(this->right);
    draw3DObject(this->back);
    draw3DObject(this->front);
    this->nbl=Matrices.model*this->bl;
    this->nbr=Matrices.model*this->br;
    this->ntl=Matrices.model*this->tl;
    this->ntr=Matrices.model*this->tr;
    this->ntop=Matrices.model*this->top;
}

void Boat::move_forward(float vel)
{
	this->position.y+=vel*cos(-this->rotation*M_PI/180);
	this->position.x+=vel*sin(-this->rotation*M_PI/180);
}
void Boat::set_position(float x,float y,float z)
{
	this->position=glm::vec3(x,y,z);
}
void Boat::set_v(float vel)
{
	this->v=vel;
}
void Boat::jump(float vel)
{
	if(this->u==0)
	{
		this->u=vel;
		this->v=vel;
	}	
}
void Boat::turn(float angle)
{
	this->rotation+=angle;
}
void  Boat::bob()
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