#include "fuelup.h"

Fuelup::Fuelup(float x, float y, float z,color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->value = 1;
    radius = 0.5;
//    this->color = color;
    const int n = 10;
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
            vertex_buffer_data1[cur++] = 1.0;
            vertex_buffer_data1[cur++] = 0.0f;

            //Point with lower angle
            vertex_buffer_data1[cur++] = 0+radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = 0.5f;

            //Point with higher angle
            angle += diff;
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = 0.5f;

    }
    this->object1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, color, GL_FILL);
//    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_RED, GL_FILL);

}
void Fuelup::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
                glm::mat4 translate = glm::translate (this->position);
                glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
                Matrices.model *= (translate * rotate);
                Matrices.model = glm::scale(Matrices.model, glm::vec3(this->value, 1, 1));// glTranslatef
                glm::mat4 MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//                if(disp==1)
                draw3DObject(this->object1);
//                else
//                draw3DObject(this->object2);
    }
void Fuelup::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

