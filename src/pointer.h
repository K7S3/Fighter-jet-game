#include "main.h"
#ifndef POINTER_H
#define POINTER_H

class Pointer
{
public:
    Pointer() {}
    Pointer(float x, float y, float z, color_t color);
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
};




#endif // POINTER_H
