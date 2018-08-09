#include "main.h"

#ifndef PLANK_H
#define PLANK_H


class Plank
{
public:
    Plank(){}
    Plank(float x, float y,float angle, float speed);
    float speed;
    float rotation;
    glm::vec3 position;
    bounding_box_t bounding_box();
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // PLANK_H
