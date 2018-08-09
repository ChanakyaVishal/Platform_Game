#include "main.h"

#ifndef GAMEOVER_H
#define GAMEOVER_H


class GameOver
{
public:
    GameOver(){}
    GameOver(int score);
    int score;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // GAMEOVER_H
