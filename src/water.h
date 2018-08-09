#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water
{
public:
    Water(){}
    Water(int x,int y);
    int x;
    int y;
    int r;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    glm::vec2 getAngle(float x);
    float getAngleDeg(float x);
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
};

#endif // WATER_H
