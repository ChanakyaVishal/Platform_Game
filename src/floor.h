#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor {
public:
    Floor(){}
    Floor(float y);
    float y;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};

#endif // floor_H
