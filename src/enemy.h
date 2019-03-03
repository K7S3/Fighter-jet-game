#include "main.h"
#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float value,y;
    color_t color;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
    void tick1();
    void tick2();
    double speed, radius, phi;
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object11;
    VAO *object2;
    VAO *object22;
};


#endif // ENEMY_H
