#include "main.h"
#ifndef COMPASS_H
#define COMPASS_H

class Compass
{
public:
    Compass() {}
    Compass(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation, theta;
    float value;
    color_t color;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
    void tick1();
    void tick2();
    double speed, radius;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // COMPASS_H
