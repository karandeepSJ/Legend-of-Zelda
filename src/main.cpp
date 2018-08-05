#include "main.h"
#include "timer.h"
#include "sphere.h"
#include "boat.h"
#include "sail.h"
#include "ball.h"
#include "eye.h"
#include "monster.h"
#include "barrel.h"
#include "cannon.h"
#include "rectangle.h"
#include "plus.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int prev_jump = GLFW_RELEASE,camera=1,fired=0,pause=0,score=0,dead_count=0;
float lives=100;
const int num_rocks=40,num_enemies=4,num_barrels=4;
Boat boat;
Ball ball;
Sail sail;
Plus health_drop[num_enemies];
Cannon cannon;
Sphere rock[num_rocks];
bool rock_gone[num_rocks]={false};
Barrel barrel[num_barrels];
Ball bonus[num_barrels];
bool taken[num_barrels]={false},h_taken[num_enemies]={false};
struct monster{
    Monster m,hand_l,hand_r,hair[5];
    Eye eye1,eye2,retina1,retina2,eye3,eye4,retina3,retina4;
    Sphere head;
    int health;
    color_t color;
    float x,y,radius,height,vx,vy;
    bool alive;
    int hit_flag;
    void tick(int f1,int f2){
        int inv = this->m.tick(-1);
        this->head.tick(inv);
        this->hand_l.tick(inv);
        this->hand_r.tick(inv);
        this->eye1.tick(inv);
        this->eye2.tick(inv);
        this->retina1.tick(inv);
        this->retina2.tick(inv);
        this->eye3.tick(inv);
        this->eye4.tick(inv);
        this->retina3.tick(inv);
        this->retina4.tick(inv);
        for(int i=0;i<5;i++)
            this->hair[i].tick(inv);
    }
    void draw(glm::mat4 VP)
    {
        if(this->hit_flag!=-1 )
            this->hit_flag++;
        this->m.draw(VP,this->hit_flag);
        this->head.draw(VP,this->hit_flag);
        this->hand_l.draw(VP,this->hit_flag);
        this->hand_r.draw(VP,this->hit_flag);
        this->eye1.draw(VP,this->hit_flag);
        this->eye2.draw(VP,this->hit_flag);
        this->retina1.draw(VP,this->hit_flag);
        this->retina2.draw(VP,this->hit_flag);
        this->eye3.draw(VP,this->hit_flag);
        this->eye4.draw(VP,this->hit_flag);
        this->retina3.draw(VP,this->hit_flag);
        this->retina4.draw(VP,this->hit_flag);
        for(int i=0;i<5;i++)
            this->hair[i].draw(VP,this->hit_flag);
        if(this->hit_flag>=60)
            this->hit_flag=-1;
    }
    void init(float x,float y,color_t color,float r,float h,int health,float vx,float vy)
    {
        this->health=health;
        this->x=x;
        this->y=y;
        this->color=color;
        this->alive=true;
        this->radius=r;
        this->height=h;
        this->vx=vx;
        this->vy=vy;
        this->hit_flag=-1;
        m=Monster(x+0,y+0,0,h,r,0,color,vx,vy);
        head=Sphere(x+0,y+0,h,r,color,vx,vy);
        hand_r=Monster(x+r-r/7,y+0,(2*h)/3,r-r/7,r/7,60,color,vx,vy);
        hand_l=Monster(x-r+r/7,y+0,(2*h)/3,r-r/7,r/7,-60,color,vx,vy);
        eye1=Eye(x+r/3,y-r,h,r*0.2,COLOR_WHITE,vx,vy);
        eye2=Eye(x-r/3,y-r,h,r*0.2,COLOR_WHITE,vx,vy);
        retina1=Eye(x+r/3,y-r,h,r*0.2 - 0.02,COLOR_BLACK,vx,vy);
        retina2=Eye(x-r/3,y-r,h,r*0.2 - 0.02,COLOR_BLACK,vx,vy);
        eye3=Eye(x+r/3,y+r,h,r*0.2,COLOR_WHITE,vx,vy);
        eye4=Eye(x-r/3,y+r,h,r*0.2,COLOR_WHITE,vx,vy);
        retina3=Eye(x+r/3,y+r,h,r*0.2 - 0.02,COLOR_BLACK,vx,vy);
        retina4=Eye(x-r/3,y+r,h,r*0.2 - 0.02,COLOR_BLACK,vx,vy);
        hair[0]=Monster(x+r/2,y+0,h+r/2,r,0.02,45,COLOR_BLACK,vx,vy);
        hair[1]=Monster(x+r/4,y+0,h+r/2,r,0.02,20,COLOR_BLACK,vx,vy);
        hair[2]=Monster(x+0.0,y+0,h+r/2,r,0.02,0,COLOR_BLACK,vx,vy);
        hair[3]=Monster(x-r/4,y+0,h+r/2,r,0.02,-20,COLOR_BLACK,vx,vy);
        hair[4]=Monster(x-r/2,y+0,h+r/2,r,0.02,-45,COLOR_BLACK,vx,vy);
        
    }
    void bob()
    {
        int inv=this->hair[2].bob(-1,0,0,this->height+this->radius);
        float x=this->hair[2].position.x,y=this->hair[2].position.y,r=this->radius;
        this->m.bob(inv,x,y,0);
        this->head.bob(inv,x,y);
        this->hair[0].bob(inv,x+r/2,y,0);
        this->hair[1].bob(inv,x+r/4,y,0);
        this->hair[3].bob(inv,x-r/4,y,0);
        this->hair[4].bob(inv,x-r/2,y,0);
        this->hand_r.bob(inv,x+r-r/7,y,0);
        this->hand_l.bob(inv,x-r+r/7,y,0);
        this->eye1.bob(inv,x+r/3,y-r);
        this->eye2.bob(inv,x-r/3,y-r);
        this->eye3.bob(inv,x+r/3,y+r);
        this->eye4.bob(inv,x-r/3,y+r);
        this->retina1.bob(inv,x+r/3,y-r);
        this->retina2.bob(inv,x-r/3,y-r);
        this->retina3.bob(inv,x+r/3,y+r);
        this->retina4.bob(inv,x-r/3,y+r);
    }
}small[num_enemies],boss;
float boat_x=0,boat_y=-3,boat_z=0.05, forward_vel=0.08, jump_vel=0.1;
float cannon_x,cannon_y,cannon_z;
Rectangle sea;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float heli_x=0,heli_y=-4;
float heli_z=20;
bool boss_dead=false,game_over=false;
double old_x=0,old_y=0,old_x_heli=heli_x,old_y_heli=heli_y;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    glm::vec3 eye,target,up;
    switch(camera)
    {
        case 1: 
        eye  = glm::vec3( boat_x,boat_y-4 ,boat_z+1.5 );
        target = glm::vec3 (boat_x, boat_y, boat_z);
        up = glm::vec3 (0, 1, 0);
        break;
        case 2:
        eye = glm::vec3( boat_x,boat_y ,boat_z+2 );
        target = glm::vec3(boat_x-4*sin(M_PI*boat.rotation/180), boat_y+4*cos(M_PI*boat.rotation/180), boat_z);
        up = glm::vec3(0, 0, 1);
        break;
        case 3:
        eye = glm::vec3( boat_x,boat_y ,20 );
        target = glm::vec3(boat_x, boat_y, boat_z);
        up = glm::vec3(0, 1, 0);
        break;
        case 4:
        eye = glm::vec3( 0,-30 ,6 );
        // target = glm::vec3(boat_x, boat_y, boat_z);
        target = glm::vec3(0, 0, 0);
        up = glm::vec3(0, 1, 0);
        break;
        case 5:
        eye = glm::vec3( heli_x,heli_y ,heli_z );
        target = glm::vec3(boat_x, boat_y, boat_z);
        up = glm::vec3(0, 0, 1);

    }
    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sail.draw(VP);
    sea.draw(VP);
    for(int i=0;i<num_rocks;i++)
        if(rock_gone[i]==false)
            rock[i].draw(VP,1000);
    boat.draw(VP);
    cannon.position.x=boat.ntop.x;
    cannon.position.y=boat.ntop.y;
    cannon.position.z=boat.ntop.z;
    cannon.draw(VP);
    if(!fired)
    {
        ball.position.x = cannon.new_cannon_end.x;
        ball.position.y = cannon.new_cannon_end.y;
        ball.position.z = cannon.new_cannon_end.z;
    }
    ball.draw(VP);
    for(int i=0;i<num_enemies;i++)
    {
        if(small[i].alive)
            small[i].draw(VP);
        else if(!h_taken[i])
            health_drop[i].draw(VP);

    }
    if(boss.alive && !boss_dead)
    {
        boss.draw(VP);
    }
    for(int i=0;i<num_barrels;i++)
    {
        if(!taken[i])
        {
            barrel[i].draw(VP);
            bonus[i].draw(VP);
        }
    }

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int up  = glfwGetKey(window, GLFW_KEY_W);
    int fire  = glfwGetKey(window, GLFW_KEY_F);
    int down  = glfwGetKey(window, GLFW_KEY_S);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int follow = glfwGetKey(window, GLFW_KEY_1);
    int bv = glfwGetKey(window, GLFW_KEY_2);
    int top = glfwGetKey(window, GLFW_KEY_3);
    int tower = glfwGetKey(window, GLFW_KEY_4);
    int heli = glfwGetKey(window, GLFW_KEY_5);
    if(left)
    {
        boat.turn(1);
        sail.turn(1);
        cannon.turn(1);
    }
    if(right)
    {
        boat.turn(-1);
        cannon.turn(-1);
        sail.turn(-1);
    }
    if(up)
    {
        boat.move_forward(forward_vel);
        sail.move_forward(forward_vel);
    }
    if(down)
    {
        boat.move_forward(-forward_vel);
        sail.move_forward(-forward_vel);
    }
    if(fire && !fired)
    {
        ball.fire(0.08,boat.rotation-cannon.orientation_x,-cannon.orientation_y);
        fired=1;
    }
    if(bv)
        camera=2;
    if(follow)
        camera=1;
    if(top)
        camera=3;
    if(tower)
        camera=4;
    if(heli)
        camera=5;
    
    if(prev_jump == GLFW_PRESS && space==GLFW_RELEASE)
    {
        prev_jump = GLFW_RELEASE;
    }
    if(space==GLFW_PRESS)
    {
        if(prev_jump==GLFW_RELEASE)
        {
            boat.jump(jump_vel);
            sail.jump(jump_vel);
        }
        prev_jump=GLFW_PRESS;
    }
}

void tick_elements() {
    for(int i=0;i<num_enemies;i++)
        health_drop[i].tick();
    char title[200];
    sprintf(title,"Score: %d\tHealth: %f\t\n",score,lives);  
    glfwSetWindowTitle(window, title);
    if (lives<=0)
    {
        if(boat.position.z<=-1.1)
            game_over=1;
        else
            boat.position.z-=0.005;
        return ;
    }
    bool temp=true;
    if(dead_count==3)
    boss.alive=true;
    int f1=1,f2=1;
    boat_x=boat.position.x;
    boat_y=boat.position.y;
    boat_z=boat.position.z;
    boat.bob();
    sail.bob();
    float q=(((float)rand())/((float)RAND_MAX));
    if(q>=0.65)
        f1=-f1;
    q=(((float)rand())/((float)RAND_MAX));
    if(q>=0.65)
        f2=-f2;
    boss.tick(f1,f2);
    boss.bob();
    for(int i=0;i<num_enemies;i++)
    {
        if(small[i].alive)
        {
            small[i].tick(f1,f2);
            health_drop[i].set_position(small[i].m.position);
        }
    }
    float g=0.003;
    if(boat.u!=0)
    {
        boat.set_v(boat.v-g);
        sail.set_v(sail.v-g);
        boat.set_position(boat_x,boat_y,(((boat.u*boat.u)-(boat.v*boat.v))/(2*g)));
        sail.set_position(boat_x,boat_y,(((sail.u*sail.u)-(sail.v*sail.v))/(2*g)));
    }
    if(boat.position.z<=-0.01)
    {
        boat.u=0;
        boat.v=0;
        sail.u=0;
        sail.v=0;
    }
    for(int i=0;i<num_rocks;i++)
    {
        if(detect_collision_rock_boat(i) && !rock_gone[i])
        {
            rock_gone[i]=true;
            lives--;
        }
    }
    for(int i=0;i<num_barrels;i++)
    {
        if(detect_collision_barrel_boat(i) && !taken[i])
        {
            taken[i]=true;
            score+=150;
        }
    }
    for(int i=0;i<num_enemies;i++)
    {
        if(detect_collision_plus_boat(i) && !h_taken[i] && !small[i].alive)
        {
            h_taken[i]=true;
            lives=min(100.0f,lives+20);
        }
    }
    for(int i=0;i<num_enemies;i++)
    {
        if(detect_collision_boat_monster(i) && small[i].alive)
        {
            if(small[i].color.r==COLOR_PURPLE.r && small[i].color.g==COLOR_PURPLE.g && small[i].color.b==COLOR_PURPLE.b)
                lives-=0.5;
            else
                lives-=1;
        }
    }
    if(detect_collision_boat_monster(num_enemies) && boss.alive)
    {
        lives=0;
    }

    if(fired)
    {
        ball.v-=g;
        ball.set_position(ball.position.x+ball.ux,ball.position.y+ball.uy,(((ball.u*ball.u)-(ball.v*ball.v))/(2*g))+ball.launchz);
        for(int i=0;i<num_enemies;i++)
        {
            if(detect_collision_ball_monster(i))
            {
                if(small[i].color.r==COLOR_PURPLE.r && small[i].color.g==COLOR_PURPLE.g && small[i].color.b==COLOR_PURPLE.b)
                    score+=100;
                else
                    score+=200;
                fired=0;
                ball.set_position(0,-0.2,1.05);
                small[i].health--;
                small[i].hit_flag=1;
                if(small[i].health<=0)
                {
                    dead_count++;
                    small[i].alive=false;
                }
                printf("%d %d\n",i,small[i].health);
            }
        }
        if(detect_collision_ball_monster(num_enemies) && boss.alive)
        {
            score+=1000;
            fired=0;
            ball.set_position(0,-0.2,1.05);
            boss.hit_flag=1;
            boss.health--;
            if(boss.health<=0)
            {
                boss_dead=true;
                boss.alive=false;
            }
            printf("%d %d\n",num_enemies,boss.health);
        }
        
    }
    if(ball.position.z<=-ball.radius)
    {
        fired=0;
        ball.set_position(0,-0.2,1.05);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    boat=Boat(boat_x,boat_y,boat_z);
    sea = Rectangle(0,0,0,15000,15000,COLOR_BLUE);
    sail = Sail(0,boat_y,0,2,0.05);
    cannon = Cannon(boat.ntop.x,boat.ntop.y,boat.ntop.z,1.5,0.1,COLOR_BLACK);
    ball=Ball(0,cannon.position.y+0.75*cos(M_PI/3),1.05,0.1,COLOR_GREEN);
    for(int i=0;i<num_enemies;i++)
    {
        float x = -20 + (40*(((float)rand())/((float)RAND_MAX)));
        float y = -20 + (80*(((float)rand())/((float)RAND_MAX)));
        float vx = -0.02 + (0.04*(((float)rand())/((float)RAND_MAX)));
        float vy = -0.02 + (0.04*(((float)rand())/((float)RAND_MAX)));
        if(i<num_enemies/2)
            small[i].init(x,y,COLOR_DARKGREEN,0.3,0.7,2,vx,vy);
        else
            small[i].init(x,y,COLOR_PURPLE,0.3,0.7,2,vx,vy);
        health_drop[i]=Plus(x,y,0.5,COLOR_GREEN);
    }
    float x = -20 + (40*(((float)rand())/((float)RAND_MAX)));
    float y = -20 + (80*(((float)rand())/((float)RAND_MAX)));
    float vx = -0.05 + (0.1*(((float)rand())/((float)RAND_MAX)));
    float vy = -0.05 + (0.1*(((float)rand())/((float)RAND_MAX)));
    boss.init(x,y,COLOR_YELLOW,0.7,2,5,vx,vy);
    boss.alive=false;
    for(int i=0;i<num_rocks;i++)
    {
        float x = -30 + (60*(((float)rand())/((float)RAND_MAX)));
        float y = -30 + (200*(((float)rand())/((float)RAND_MAX)));
        float r = 0.2 + (0.3*(((float)rand())/((float)RAND_MAX)));
        rock[i] = Sphere(x,boat_y+y,0,r,COLOR_GREY,0,0);
    }
    for(int i=0;i<num_barrels;i++)
    {
        float x = -30 + (60*(((float)rand())/((float)RAND_MAX)));
        float y = -30 + (200*(((float)rand())/((float)RAND_MAX)));
        barrel[i]=Barrel(x+0,y+0,0,1,0.4,COLOR_BROWN);
        bonus[i]=Ball(x+0.5,y+0,0.7,0.1,COLOR_CYAN);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

static void cannon_rotate(GLFWwindow *window, double x,double y)
{
    // printf("%lf %lf\n",x,old_x);
    // if(y>old_y)
    //     cannon.orientation_y=max(-90.0,cannon.orientation_y-0.5);
    // else if(y<old_y)
    //     cannon.orientation_y=min(-60.0,cannon.orientation_y+0.5);
    // old_x=x;
    // if(x<old_x)
    //     cannon.orientation_x=max(-30.0,cannon.orientation_x-0.5);
    // else if(x>old_x)
        cannon.orientation_x=(x-300)*0.1;
        cannon.orientation_y=(-y)*0.1 - 30;

}
static void heli_view(GLFWwindow *window, double x,double y)
{
    // printf("%lf %lf\n",x,old_x);
    if(y>old_y_heli)
        heli_y-=0.5;
    else if(y<old_y_heli)
        heli_y+=0.5;

    if(x<old_x_heli)
        heli_x-=0.5;
    else if(x>old_x_heli)
        heli_x+=0.5;
    // old_y=;

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {

    // Do something
    if(camera==5)
        heli_z -= yoffset;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            if(pause)
                continue;
            // 60 fps
            // OpenGL Draw commands
            if(camera==5 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
            {
                glfwGetCursorPos(window,&old_x_heli,&old_y_heli);
                glfwSetCursorPosCallback(window,heli_view);   

            }
            else
            {
                glfwGetCursorPos(window,&old_x,&old_y);
                glfwSetCursorPosCallback(window,cannon_rotate);   
            }
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            if(boss_dead || game_over)
                break;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    char mesg[200];
    if(game_over)
    {
        sprintf(mesg,"Final Score: %d. Game Over :(. Your health dropped to zero.",score);
        glfwSetWindowTitle(window,mesg);
        for(int i=0;i<1000000000;i++);
    }
    if(boss_dead)
    {
        sprintf(mesg,"Final Score: %d. Congrats!!! You completed the game",score);
        glfwSetWindowTitle(window,mesg);
        for(int i=0;i<1000000000;i++);
    }

    quit(window);
}
bool detect_collision_boat_monster(int i) {
    monster m = (i<num_enemies)?small[i]:boss; 
    double l = (boat.ntl.y-boat.nbl.y)*(m.m.position.x-boat.ntl.x)-(boat.ntl.x-boat.nbl.x)*(m.m.position.y-boat.ntl.y);
    double r = (boat.ntr.y-boat.nbr.y)*(m.m.position.x-boat.ntr.x)-(boat.ntr.x-boat.nbr.x)*(m.m.position.y-boat.ntr.y);
    double u = (boat.ntl.y-boat.ntr.y)*(m.m.position.x-boat.ntl.x)-(boat.ntl.x-boat.ntr.x)*(m.m.position.y-boat.ntl.y);
    double d = (boat.nbl.y-boat.nbr.y)*(m.m.position.x-boat.nbr.x)-(boat.nbl.x-boat.nbr.x)*(m.m.position.y-boat.nbr.y);
    
    if( l*r<=0 && u*d<=0)
        return true;
    return false;
}
bool detect_collision_ball_monster(int i) {
    monster m = (i<num_enemies)?small[i]:boss; 
    if( ball.position.z>=0 && ball.position.z<=m.height+m.radius && ball.position.x>=m.m.position.x-m.radius && ball.position.x<=m.m.position.x+m.radius && ball.position.y>=m.m.position.y-m.radius && ball.position.y<=m.m.position.y+m.radius)
        return true;
    return false;
}
bool detect_collision_rock_boat(int i) {
    double l = (boat.ntl.y-boat.nbl.y)*(rock[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.nbl.x)*(rock[i].position.y-boat.ntl.y);
    double r = (boat.ntr.y-boat.nbr.y)*(rock[i].position.x-boat.ntr.x)-(boat.ntr.x-boat.nbr.x)*(rock[i].position.y-boat.ntr.y);
    double u = (boat.ntl.y-boat.ntr.y)*(rock[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.ntr.x)*(rock[i].position.y-boat.ntl.y);
    double d = (boat.nbl.y-boat.nbr.y)*(rock[i].position.x-boat.nbr.x)-(boat.nbl.x-boat.nbr.x)*(rock[i].position.y-boat.nbr.y);
    
    if(fabs(boat_z-rock[i].position.z) <= rock[i].radius && l*r<=0 && u*d<=0)
        return true;
    return false;
}

bool detect_collision_barrel_boat(int i) {
    double l = (boat.ntl.y-boat.nbl.y)*(bonus[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.nbl.x)*(bonus[i].position.y-boat.ntl.y);
    double r = (boat.ntr.y-boat.nbr.y)*(bonus[i].position.x-boat.ntr.x)-(boat.ntr.x-boat.nbr.x)*(bonus[i].position.y-boat.ntr.y);
    double u = (boat.ntl.y-boat.ntr.y)*(bonus[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.ntr.x)*(bonus[i].position.y-boat.ntl.y);
    double d = (boat.nbl.y-boat.nbr.y)*(bonus[i].position.x-boat.nbr.x)-(boat.nbl.x-boat.nbr.x)*(bonus[i].position.y-boat.nbr.y);
    
    if(boat_z-bonus[i].position.z >= bonus[i].radius && l*r<=0 && u*d<=0)
        return true;
    return false;
}
bool detect_collision_plus_boat(int i) {
    double l = (boat.ntl.y-boat.nbl.y)*(health_drop[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.nbl.x)*(health_drop[i].position.y-boat.ntl.y);
    double r = (boat.ntr.y-boat.nbr.y)*(health_drop[i].position.x-boat.ntr.x)-(boat.ntr.x-boat.nbr.x)*(health_drop[i].position.y-boat.ntr.y);
    double u = (boat.ntl.y-boat.ntr.y)*(health_drop[i].position.x-boat.ntl.x)-(boat.ntl.x-boat.ntr.x)*(health_drop[i].position.y-boat.ntl.y);
    double d = (boat.nbl.y-boat.nbr.y)*(health_drop[i].position.x-boat.nbr.x)-(boat.nbl.x-boat.nbr.x)*(health_drop[i].position.y-boat.nbr.y);
    
    if(l*r<=0 && u*d<=0)
        return true;
    return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(1.0f,1.0f,1.0f,300.0f);
}
