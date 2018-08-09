#include "porcupine.h"

Porcupine::Porcupine(float x,float y,float speed){
    this->position = glm::vec3(x, y, 0);
    this->speed =speed;
  static const GLfloat g_vertex_buffer_data[]  = {
      0.0f, 0.0f, 0.0f,
     3.0f, 0.0f, 0.0f,
      1.5f,  3.0f, 0.0f,

      1.5f, 0.0f, 0.0f,
     4.5f, 0.0f, 0.0f,
      3.0f,  3.0f, 0.0f,


  };
  this->range = 4.5;
  this->moveR = 4;
  this->center = x;
  this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data,COLOR_SPIKE, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
  }


bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x+2.25, y, this->range, this->range , 0};
    return bbox;
}

void Porcupine::tick() {
    this->position.x += this->speed;
}
