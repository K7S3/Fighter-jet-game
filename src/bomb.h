#include "main.h"
#ifndef BOMB_H
#define BOMB_H




class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed, phi, zspeed, yspeed, xspeed;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
};




#endif // BOMB_H
