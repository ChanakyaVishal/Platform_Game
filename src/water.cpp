#include "water.h"

Water::Water(int x,int y){
this->x = x;
this->y = y;
this->position = glm::vec3(x,y,0);
this->r = 10;
int n = 360;
int counter = 0;
GLfloat g_vertex_buffer_data[n*9 + 9];

int i;
for(i=180;i<n;i++){

g_vertex_buffer_data[counter]=(GLfloat)0;
g_vertex_buffer_data[counter+1]=(GLfloat)0;
g_vertex_buffer_data[counter+2]=(GLfloat)0;

float overlap = i*2*3.1416/n;

g_vertex_buffer_data[counter+3] = (GLfloat) cos(overlap)*this->r;
g_vertex_buffer_data[counter+4] = (GLfloat) sin(overlap)*this->r;
g_vertex_buffer_data[counter+5] = (GLfloat) 0;

float next = (i+1)*2*3.1416/n;

g_vertex_buffer_data[counter+6] = (GLfloat) cos(next)*this->r;
g_vertex_buffer_data[counter+7] = (GLfloat) sin(next)*this->r;
g_vertex_buffer_data[counter+8] = (GLfloat) 0;

counter+=9;
}


this->object = create3DObject(GL_TRIANGLES, n*3/2, g_vertex_buffer_data, COLOR_BLUE, GL_FILL);

}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(this->x, this->y, 0));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Water::bounding_box() {
    float x = this->x, y = this->y;
    bounding_box_t bbox = { x, y, this->r, this->r };
    return bbox;
}

float Water::getAngleDeg(float x){
    int r = this->r ;
    float value = (x*18)+180;
    return 10;
}
