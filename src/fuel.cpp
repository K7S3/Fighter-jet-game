#include "fuel.h"

Fuel::Fuel(float x, float y, float z,color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->value = 1;
//    this->color = color;
    GLfloat vertex_buffer_data1[] = {
        0,0,1,
        5,0,1,
        0,-0.2,1,
        5,-0.2,1,
        0,-0.2,1,
        5,0,1,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_RED, GL_FILL);

}
void Fuel::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
                glm::mat4 translate = glm::translate (this->position);
                glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
                Matrices.model *= (translate * rotate);
                Matrices.model = glm::scale(Matrices.model, glm::vec3(this->value, 1, 1));// glTranslatef
                glm::mat4 MVP = VP * Matrices.model;
                glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
                if(disp==1)
                draw3DObject(this->object1);
                else
                draw3DObject(this->object2);
    }
void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

