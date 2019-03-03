#include "score.h"
#include "main.h"

Score::Score(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    static const GLfloat vertex_buffer_data1[] = {
        0,0,1,
        0.25,0,1,
        0.21,-0.03,1,
        0,0,1,
        0,-0.03,1,
        0.21,-0.03,1,
    };
    static const GLfloat vertex_buffer_data2[] = {
        0,-0.21,1,
        0.21,-0.21,1,
        0.21,-0.27,1,
        0,-0.21,0,
        0,-0.27,0,
        0.21,-0.27,1,

    };
    static const GLfloat vertex_buffer_data3[] = {
        0,-0.5,1,
        0.21,-0.5,1,
        0.21,-0.54,1,
        0,-0.5,1,
        0,-0.54,1,
        0.21,-0.54,1,

    };
    static const GLfloat vertex_buffer_data4[] = {
        0,0,1,
        0,-0.21,1,
        0.02,-0.21,1,
        0,0,1,
        0.02,0,1,
        0.02,-0.21,1,

    };
    static const GLfloat vertex_buffer_data5[] = {
        0.21,0,1,
        0.21,-0.21,1,
        0.27,-0.21,1,
        0.21,0,1,
        0.27,0,1,
        0.27,-0.21,1,

    };
    static const GLfloat vertex_buffer_data6[] = {
        0,-0.21,1,
        0,-0.5,1,
        0.02,-0.5,1,
        0,-0.21,1,
        0.02,-0.21,1,
        0.02,-0.5,1,

    };
    static const GLfloat vertex_buffer_data7[] = {
        0.21,-0.21,1,
        0.21,-0.5,1,
        0.27,-0.5,1,
        0.21,-0.21,1,
        0.27,-0.21,1,
        0.27,-0.5,1,

    };

    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);

}

void Score::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if( disp!=1 && disp!=4 && disp<10)
        draw3DObject(this->object1);
    if((disp>1 && disp<7) || disp == 8 || disp == 9 || disp == -1)
        draw3DObject(this->object2);
    if(disp==0 || disp == 2 || disp == 3 || disp == 5 || disp == 6 || disp == 8)
        draw3DObject(this->object3);
    if(disp == 0 || (disp>3 && disp<10 && disp!=7))
        draw3DObject(this->object4);
    if(disp == -4 || (disp>=0 && (disp != 5 && disp !=6) && disp < 10))
        draw3DObject(this->object5);
    if( disp == 2 || disp == 6 || disp == 8 || disp == 0)
        draw3DObject(this->object6);
    if(disp != 2 && disp != -4 && disp<10)
        draw3DObject(this->object7);

}

void Score::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}



