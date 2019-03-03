#include "main.h"
#ifndef WORLD_H
#define WORLD_H

class World {
public:
    World() {}
    World(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // WORLD_H
