#include "ball.h"
#include "main.h"
#include "math.h"

//Type 0-> Player
//Type 1-> Ball
//Type 2 -> Ball + Platform

Ball::Ball(float x, float y, color_t color, float speed_x, float speed_y,int r,int type) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->flag_air = 0;
    this->waterFlag = 0;
    this->type = type;
    this->r = r;
    this->ground_y = y;

    if(this->type !=5){
    int n = 360;
    int counter = 0;
    GLfloat g_vertex_buffer_data[n*9 + 18];

    int i;
    for(i=0;i<n;i++){

    g_vertex_buffer_data[counter]=(GLfloat)0;
    g_vertex_buffer_data[counter+1]=(GLfloat)0;
    g_vertex_buffer_data[counter+2]=(GLfloat)0;

    float overlap = i*2*3.1416/n;

    g_vertex_buffer_data[counter+3] = (GLfloat) cos(overlap)*r;
    g_vertex_buffer_data[counter+4] = (GLfloat) sin(overlap)*r;
    g_vertex_buffer_data[counter+5] = (GLfloat) 0;

    float next = (i+1)*2*3.1416/n;

    g_vertex_buffer_data[counter+6] = (GLfloat) cos(next)*r;
    g_vertex_buffer_data[counter+7] = (GLfloat) sin(next)*r;
    g_vertex_buffer_data[counter+8] = (GLfloat) 0;

    counter+=9;
    }
 this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);

    }


    else if (this->type == 2){
        int n = 360;
        int counter = 0;
        GLfloat g_vertex_buffer_data[n*9 +18];

        int i;
        int plank_location = (rand() % n/4);
        float angle;
        for(i=0;i<n;i++){

        g_vertex_buffer_data[counter]=(GLfloat)0;
        g_vertex_buffer_data[counter+1]=(GLfloat)0;
        g_vertex_buffer_data[counter+2]=(GLfloat)0;

        float overlap = i*2*3.1416/n;

        g_vertex_buffer_data[counter+3] = (GLfloat) cos(overlap)*r;
        g_vertex_buffer_data[counter+4] = (GLfloat) sin(overlap)*r;
        g_vertex_buffer_data[counter+5] = (GLfloat) 0;
        if(i == plank_location){
           angle = overlap;
        }
        float next = (i+1)*2*3.1416/n;

        g_vertex_buffer_data[counter+6] = (GLfloat) cos(next)*r;
        g_vertex_buffer_data[counter+7] = (GLfloat) sin(next)*r;
        g_vertex_buffer_data[counter+8] = (GLfloat) 0;

        counter+=9;
        }
        for(int i = n;i<n+2;i++){
            g_vertex_buffer_data[counter]=(GLfloat)0;
            g_vertex_buffer_data[counter+1]=(GLfloat)0;
            g_vertex_buffer_data[counter+2]=(GLfloat)0;

            g_vertex_buffer_data[counter+3] = (GLfloat) r/cos(angle);
            g_vertex_buffer_data[counter+4] = (GLfloat) r/cos(angle);
            g_vertex_buffer_data[counter+5] = (GLfloat) 0;

            g_vertex_buffer_data[counter+6] = (GLfloat) cos(angle);
            g_vertex_buffer_data[counter+7] = (GLfloat) sin(angle);
            g_vertex_buffer_data[counter+8] = (GLfloat) 0;

            counter+=9;
        }
        this->object = create3DObject(GL_TRIANGLES, n*3+6, g_vertex_buffer_data, color, GL_FILL);


    }
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (10 * M_PI / 180.0f), glm::vec3(0, 0, 1));
     rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if(this->type == 0 && this->speed_y >= 1){
       this->speed_y = 1;
    }
    if(this->type == 0 && this->speed_x >= 1){
       this->speed_x = 1;
    }

    //Movement of other balls
    if(this->type == 1){
       this->position.x += this->speed_x/60.00;
    }
    if(this->type == 2){
       this->position.x += this->speed_x/60.00;
    }

//Ground Check
if(this->position.y <= this->ground_y && ( this->waterFlag == 0 && this->flag_air == -1 )){
    this->position.y = this->ground_y;
    this->speed_y = 0;
    this->flag_air = 0;
  }
if(this->waterFlag != 0 && (this->position.y != this->ground_y && this->flag_air==0)){
    this->position.y = this->ground_y;
        this->flag_air = 0;
}
if(this->position.y <= this->ground_y){
    this->position.y = this->ground_y;
        this->flag_air = 0;

}

//Water Ground Calculation
if(waterFlag != 0){
    this->ground_y = -7- sqrt(abs(100.0-float(pow(this->position.x-5,2)))) ;
}

//Gravity
if(this->waterFlag != 0 && (this->position.y > this->ground_y && this->position.y < -7)){
    this->position.y-= 0.001;
}
else if(!this->position.y <= this->ground_y)
    this->speed_y -= 0.1;

else if(this->waterFlag != 0){
if(this->position.x - 5.0 > +0.05){
this->position.x -=0.1;
}
else if(this->position.x - 5.0 < -0.05){
    this->position.x +=0.1;
    }
else{
    this->position.x = 5;
}
}

    //General Movement of Player
    if(this->type == 0 ){
    this->position.y += this->speed_y;
    this->position.x += this->speed_x;
        if(this->speed_x > 0.01 && this->flag_air == 0)
            this->speed_x -= 0.01;
        else if(this->speed_x < -0.01 && this->flag_air == 0)
            this->speed_x += 0.01;
        if(abs(this->speed_x) == 0.01)
            this->speed_x = 0;
    }

}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->r*1.65, this->r*1.65 , this->r};
    return bbox;
}
