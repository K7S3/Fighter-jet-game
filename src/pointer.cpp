#include "pointer.h"

Pointer::Pointer(float x, float y, float z,color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->value = 1;
    this->theta =0 ;
    int n = 100, cur =0;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data1[reqd] = {};
    for (int i = 0; i < n; i++)
    {

        vertex_buffer_data1[cur++] = -1.5;
        vertex_buffer_data1[cur++] = -i*0.003;
        vertex_buffer_data1[cur++] = 0.0;

        vertex_buffer_data1[cur++] = 1.5;
        vertex_buffer_data1[cur++] = -i*0.003;
        vertex_buffer_data1[cur++] = 0.0;
\
        vertex_buffer_data1[cur++] = 0.0;
        vertex_buffer_data1[cur++] = -i*0.003;
        vertex_buffer_data1[cur++] = -5.0;

}
    this->object1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_RED, GL_FILL);

}
void Pointer::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
                glm::mat4 translate = glm::translate (this->position);
                glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 360.0f), glm::vec3(0, 1 , 0));
                glm::mat4 rotate1    = glm::rotate((float) (this->theta * M_PI / 180.0f), glm::vec3(0, -1, 0));
                Matrices.model *= (translate * rotate);
                Matrices.model = glm::scale(Matrices.model, glm::vec3(this->value, 1, 1));// glTranslatef
                glm::mat4 MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                draw3DObject(this->object1);

    }
void Pointer::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

