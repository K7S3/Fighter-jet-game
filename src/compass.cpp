#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z,color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->value = 1;
    this->theta =0 ;
    radius = 1;
    int n = 100, cur =0;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data1[reqd] = {};
    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;

    for (int i = 0; i < n; i++)
    {

        //Origin
        vertex_buffer_data1[cur++] = 0.0;
        vertex_buffer_data1[cur++] = 0.0;
        vertex_buffer_data1[cur++] = 0.0;

        //Point with lower angle
        vertex_buffer_data1[cur++] = radius * cos(angle);
        vertex_buffer_data1[cur++] = radius * sin(angle);
        vertex_buffer_data1[cur++] = 0.0;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data1[cur++] = radius * cos(angle);
        vertex_buffer_data1[cur++] = radius * sin(angle);
        vertex_buffer_data1[cur++] = 0.0;

}
    static const GLfloat vertex_buffer_data2[] = {
        -0.2, 0.0, 0.1,
        0.2, 0.0, 0.1,
        0.0, 1.0, 0.1,
        -0.2, 0.0, -0.1,
        0.2, 0.0, -0.1,
        0.0, 1.0, -0.1
    };
    static const GLfloat vertex_buffer_data3[] = {
        -0.2, 0.0, 0.1,
        0.2, 0.0, 0.1,
        0.0, -1.0, 0.1,
        -0.2, 0.0, -0.1,
        0.2, 0.0, -0.1,
        0.0, -1.0, -0.1
    };
    this->object1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_COMPASSGREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_COMPASSBLUE, GL_FILL);

}
void Compass::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
                glm::mat4 translate = glm::translate (this->position);
                glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 360.0f), glm::vec3(0, 1 ,0 ));
                glm::mat4 rotate1    = glm::rotate((float) (this->theta * M_PI / 180.0f), glm::vec3(0, 0, 1));
                Matrices.model *= (translate * rotate*rotate1);
                Matrices.model = glm::scale(Matrices.model, glm::vec3(this->value, 1, 1));// glTranslatef
                glm::mat4 MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(this->object1);
                draw3DObject(this->object2);
                draw3DObject(this->object3);


    }
void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}


