#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x, float y){

    this->position = glm::vec3(x, y, 0);
    this->x_s = 15+x;
    this->x_e = 21+x;
    this->y_s = -3.5+y;

    int n = 360;
    int counter = 0;
    GLfloat g_vertex_buffer_data[n*9/2];

    int i;
    for(i=180;i<n;i++){

    g_vertex_buffer_data[counter]=(GLfloat)18;
    g_vertex_buffer_data[counter+1]=(GLfloat)-5;
    g_vertex_buffer_data[counter+2]=(GLfloat)0;

    float overlap = i*2*3.1416/n;

    g_vertex_buffer_data[counter+3] = (GLfloat) cos(overlap)*2+18;
    g_vertex_buffer_data[counter+4] = (GLfloat) sin(overlap)*2-5;
    g_vertex_buffer_data[counter+5] = (GLfloat) 0;

    float next = (i+1)*2*3.1416/n;

    g_vertex_buffer_data[counter+6] = (GLfloat) cos(next)*2+18;
    g_vertex_buffer_data[counter+7] = (GLfloat) sin(next)*2-5;
    g_vertex_buffer_data[counter+8] = (GLfloat) 0;

    counter+=9;
    }
    this->object1 = create3DObject(GL_TRIANGLES, n*3/2, g_vertex_buffer_data, COLOR_TRAMPOLINE, GL_FILL);


  static const GLfloat g_vertex_buffer_data2[]  = {
      15.0f, -5.0f, 0.0f,
      15.0f, -9.0f, 0.0f,
      16.0f,  -5.0f, 0.0f,

      15.0f, -9.0f, 0.0f,
      16.0f,  -5.0f, 0.0f,
       16.0f, -9.0f, 0.0f,
  };
  this->object2 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data2,COLOR_RED, GL_FILL);


  static const GLfloat g_vertex_buffer_data3[]  = {
      20.0f, -5.0f, 0.0f,
      20.0f, -9.0f, 0.0f,
      21.0f,  -5.0f, 0.0f,

      20.0f, -9.0f, 0.0f,
      21.0f,  -5.0f, 0.0f,
       21.0f, -9.0f, 0.0f,


  };
  this->object3 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0* M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
  }



