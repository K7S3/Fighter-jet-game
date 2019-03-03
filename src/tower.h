#include "main.h"
#ifndef TOWER_H
#define TOWER_H

class Tower {
public:
    Tower() {}
    Tower(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;

};


#endif // TOWER_H
