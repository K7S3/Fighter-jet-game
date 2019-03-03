#include "main.h"
#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation, radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed, xspeed, yspeed, zspeed, phi, rspeed, acceleration,tilt_back, retardation, theta;
private:
    VAO *object;
    VAO *object2;
};

#endif // MISSILE_H
