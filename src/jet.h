#include "main.h"
#ifndef JET_H
#define JET_H


class Jet {
public:
    Jet() {}
    Jet(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    double radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void forward();
    void no_key();
    void up();
    void down();
    void counter_clockwise();
    void clockwise();
    double speed, xspeed, yspeed, zspeed, phi, rspeed, acceleration,tilt_back, retardation, theta, score;
private:
    VAO *object1;
     VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // JET_H
