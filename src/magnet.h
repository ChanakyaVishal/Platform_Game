#include"main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet
{
public:
    Magnet(){}
    Magnet(float x,float y);
    float rotation;
    float y_s;
    float y_e;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void setRotation(float rota);
    void setLoc(glm::vec3 loc);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAGNET_H
