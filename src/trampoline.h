#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline
{
public:
    Trampoline(){}
    Trampoline(float x,float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);\
    float x_s;
    float x_e;
    float y_s;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // TRAMPOLINE_H
