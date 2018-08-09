#include "gameover.h"

GameOver::GameOver(int score)
{
    static const GLfloat g_vertex_buffer_data[]  = {

        -32.0f,-18.0f, 0.0f,
         32.0f, -18.0f, 0.0f,
        32.0f, -18.0f, 0.0f,


        -32.0f,-18.0f, 0.0f,
         32.0f, -18.0f, 0.0f,
        -32.0f, -18.0f, 0.0f,
    };
this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);
this->score = score;
}

void GameOver::draw(glm::mat4 VP) {
    draw3DObject(this->object);
  }
