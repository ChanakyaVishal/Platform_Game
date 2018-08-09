#include "magnet.h"

Magnet::Magnet(float x,float y){
    this->position =glm::vec3(x,y,0);
    this->rotation =0;
    static const GLfloat g_vertex_buffer_data[]  = {
        //Bottom
        0.0f, -8.0f, 0.0f,
        0.0f, -9.0f, 0.0f,
        4.0f,  -8.0f, 0.0f,

        0.0f, -9.0f, 0.0f,
        4.0f,  -8.0f, 0.0f,
         4.0f, -9.0f, 0.0f,

        //Top
        0.0f, -4.0f, 0.0f,
        0.0f, -5.0f, 0.0f,
        4.0f,  -4.0f, 0.0f,

        0.0f, -5.0f, 0.0f,
        4.0f,  -4.0f, 0.0f,
         4.0f, -5.0f, 0.0f,

        //Vertical Line
        0.0f, -4.0f, 0.0f,
        0.0f, -9.0f, 0.0f,
        1.0f,  -4.0f, 0.0f,

        0.0f, -9.0f, 0.0f,
        1.0f,  -4.0f, 0.0f,
         1.0f, -9.0f, 0.0f,


    };
    this->object = create3DObject(GL_TRIANGLES, 18, g_vertex_buffer_data,COLOR_MAGNET, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation* M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
  }

void Magnet::setRotation(float rota){
    this->rotation =rota;
}

void Magnet::setLoc(glm::vec3 loc){
    this->position =loc;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 7, 7 ,7};
    return bbox;
}
