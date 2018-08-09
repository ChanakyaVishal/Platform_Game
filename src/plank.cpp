#include "plank.h"
#include <iostream>


Plank::Plank(float x, float y, float angle, float speed)
{

    this->position = glm::vec3 (x,y,0);
    this->speed= speed;
    this->rotation =angle;
    /*static const GLfloat g_vertex_buffer_data[]  = {
        this->position.x-2.0, this->position.y , 0.0f,
        this->position.x-2.0, this->position.y +1.0, 0.0f,
        this->position.x+2.0,  this->position.y , 0.0f,

        this->position.x-2.0, this->position.y +1.0, 0.0f,
        this->position.x+2.0,  this->position.y , 0.0f,
        this->position.x+2.0,this->position.y +1.0, 0.0f,
    };*/
    static const GLfloat g_vertex_buffer_data[]  = {
            -4.0, 0.0f , 0.0f,
           -4.0, -0.5, 0.0f,
           +4.0,  0.0f , 0.0f,

            -4.0,-0.5f, 0.0f,
           +4.0,  0.0f , 0.0f,
            +4.0,-0.5f, 0.0f,
        };
    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data,COLOR_BROWN, GL_FILL);

}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation* M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          =  rotate * glm::translate (glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

  }


void Plank::tick() {
    this->position.x += this->speed/60.00;
}

bounding_box_t Plank::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 4, 1 , 0};
    return bbox;
}


