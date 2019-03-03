#include "main.h"
#ifndef FUEL_H
#define FUEL_H




class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float value;
    color_t color;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
    void tick1();
    void tick2();
    double speed;
private:
    VAO *object1;
    VAO *object2;


};

#endif // FUEL_H
