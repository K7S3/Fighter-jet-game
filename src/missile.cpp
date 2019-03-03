#include "missile.h"
#include "main.h"
#include "math.h"
#define M_PI 3.14159265358979323846
#define RAD2DEG 180.0/M_PI
#define DEG2RAD M_PI/180.0

Missile::Missile(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 180;
    speed = 1;
    xspeed = 0.0;
    zspeed = -20.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    radius = 0.2;
    const int n = 360;
    const int reqd = n * 9*n;
    GLfloat vertex_buffer_data1[reqd] = {};
    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;

    for(int j=0;j<100;j++){
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data1[cur++] = 0.0;
            vertex_buffer_data1[cur++] = 0.0;
            vertex_buffer_data1[cur++] = -7.0f - j*0.03;

            //Point with lower angle
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = -7.0f -j*0.03;

            //Point with higher angle
            angle += diff;
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = -7.0f -j*0.03;

    }

    }


    this->object = create3DObject(GL_TRIANGLES, 3*n*n, vertex_buffer_data1, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->phi * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate3    = glm::rotate((float) (this->theta * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    this->zspeed = -speed * cos(DEG2RAD*this->rotation);
    this->xspeed = -speed * sin(DEG2RAD*this->rotation);
    this->yspeed = -speed*0.30 * cos(DEG2RAD*(this->phi-45));
    this->position.z += zspeed;
    this->position.x += xspeed;
    // this->position.x -= speed;
     this->position.y += yspeed;
}

