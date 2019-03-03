#include "island.h"
#include "main.h"

Island::Island(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    radius = 10;

    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data1[reqd] = {};
    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
//    int rand1 = rand()%200;
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data1[cur++] = 0;
            vertex_buffer_data1[cur++] = 0.5;
            vertex_buffer_data1[cur++] = 0.0f + z;

            //Point with lower angle
            vertex_buffer_data1[cur++] = 0+radius * cos(angle);
            vertex_buffer_data1[cur++] = 0.5f;
            vertex_buffer_data1[cur++] = radius * sin(angle)+ z;

            //Point with higher angle
            angle += diff;
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = 0.5f;
            vertex_buffer_data1[cur++] = radius * sin(angle)+z;

    }


    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, color, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Island::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Island::tick() {
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

