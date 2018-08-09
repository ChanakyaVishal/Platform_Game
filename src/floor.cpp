#include "floor.h"

Floor::Floor(float y) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
  static const GLfloat g_vertex_buffer_data[]  = {
      150.0f, -9.0f, 0.0f,
     -70.0f, -9.0f, 0.0f,
     150.0f,  -11.0f, 0.0f,

       -70.0f,-9.0f, 0.0f,
       150.0f, -11.0f, 0.0f,
       -70.0f, -11.0f, 0.0f,


  };

  static const GLfloat g_vertex_buffer_data2[]  = {

      -70.0f,-10.0f, 0.0f,
      150.0f, -40.0f, 0.0f,
     150.0f, -10.0f, 0.0f,


      -70.0f,-10.0f, 0.0f,
      150.0f, -40.0f, 0.0f,
      -70.0f, -40.0f, 0.0f,
  };

    this->object1 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, COLOR_GRASS, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data2, COLOR_BROWN, GL_FILL);

}

void Floor::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
  }
