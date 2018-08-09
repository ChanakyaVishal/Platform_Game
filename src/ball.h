#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, float speed_x, float speed_y,int r,int type);
    float speed_x;
    float speed_y;
    int flag_air;
    int type;
    float ground_y;
    float ground_x;
    int r;
    int waterFlag;
    int trampFlag;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
