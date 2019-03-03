#include "main.h"
#ifndef SMOKE_H
#define SMOKE_H



class Smoke
{
public:
    Smoke() {}
    Smoke(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
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
};

#endif // SMOKE_H
