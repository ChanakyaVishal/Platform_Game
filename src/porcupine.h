#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine
{
public:
    Porcupine(){}
    Porcupine(float x, float y,float speed);
    float speed;
    float range;
    float center;
    float moveR;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void tick();
private:
    VAO *object;
};

#endif // PORCUPINE_H
