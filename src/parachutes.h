#include "main.h"
#ifndef PARACHUTES_H
#define PARACHUTES_H

class Parachutes
{
public:
    Parachutes() {}
    Parachutes(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float value;
    color_t color;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
    void tick();
    void tick2();
    double speed, radius;
private:
    VAO *object1;
    VAO *object2;
};

#endif // PARACHUTES_H
