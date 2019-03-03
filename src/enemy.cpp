#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->y = y;
    this->phi =0;
    this->value =1;
    speed = 1;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f, 0.0f,-1.0f, // triangle 1 : begin
        -1.0f,-0.0f, 1.0f,
        -1.0f, 3.0 + this->y, 1.0f, // triangle 1 : end
        1.0f, 3.0 + this->y,-1.0f, // triangle 2 : begin
        -1.0f,-0.0f,-1.0f,
        -1.0f, 3.0 + this->y,-1.0f, // triangle 2 : end
        1.0f,-0.0f, 1.0f,
        -1.0f,-0.0f,-1.0f,
        1.0f,-0.0f,-1.0f,
        1.0f, 3.0 + this->y,-1.0f,
        1.0f,0.0f,-1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f, 3.0 + this->y, 1.0f,
        -1.0f, 3.0 + this->y,-1.0f,
        1.0f,0.0f, 1.0f,
        -1.0f,0.0f, 1.0f,
        -1.0f,0.0f,-1.0f,
        -1.0f, 3.0 + this->y, 1.0f,
        -1.0f,0.0f, 1.0f,
        1.0f,0.0f, 1.0f,
        1.0f, 3.0 + this->y, 1.0f,
        1.0f,0.0f,-1.0f,
        1.0f, 3.0 + this->y,-1.0f,
        1.0f,0.0f,-1.0f,
        1.0f, 3.0 + this->y, 1.0f,
        1.0f,0.0f, 1.0f,
        1.0f, 3.0 + this->y, 1.0f,
        1.0f, 3.0 + this->y,-1.0f,
        -1.0f, 3.0 + this->y,-1.0f,
        1.0f, 3.0 + this->y, 1.0f,
        -1.0f, 3.0 + this->y,-1.0f,
        -1.0f, 3.0 + this->y, 1.0f,
        1.0f, 3.0 + this->y, 1.0f,
        -1.0f, 3.0 + this->y, 1.0f,
        1.0f,0.0f, 1.0f
    };
    radius = 0.5;

        const int n = 360;
        const int reqd = n * 9*n;
        GLfloat vertex_buffer_data1[reqd] = {};

        this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BOXBROWN, GL_FILL);
        this->object11 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_ASHGREY, GL_FILL);
        double angle = 0;
        const double pi = 4 * atan(1);
        double diff = (2 * pi) / (double)n;
        int cur = 0;
//        this->y = vertex_buffer_data[7]-3.0;
        for(int j=0;j<n;j++){
            for (int i = 0; i < n; i++)
            {

                //Origin
                vertex_buffer_data1[cur++] = 0.0;
                vertex_buffer_data1[cur++] = 3.5+y;
                vertex_buffer_data1[cur++] = -j*0.01;

                //Point with lower angle
                vertex_buffer_data1[cur++] = radius * cos(angle);
                vertex_buffer_data1[cur++] = 3.5+y+radius * sin(angle);
                vertex_buffer_data1[cur++] = -j*0.01;

                //Point with higher angle
                angle += diff;
                vertex_buffer_data1[cur++] = radius * cos(angle);
                vertex_buffer_data1[cur++] = 3.5+y+radius * sin(angle);
                vertex_buffer_data1[cur++] =  -j*0.01;

        }
            radius -= 0.000000007*j;
        }
//    this->y = y;
    this->object2 = create3DObject(GL_TRIANGLES, 3*n*n, vertex_buffer_data1, COLOR_GUNMETALBLUE, GL_FILL);
    this->object22 = create3DObject(GL_TRIANGLES, 3*n*n, vertex_buffer_data1, COLOR_ASHGREY, GL_FILL);
}




void Enemy::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(disp ==1){
        draw3DObject(this->object2);
        draw3DObject(this->object1);
    }
    else{
        draw3DObject(this->object22);
    draw3DObject(this->object11);
    }
}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Enemy::bounding_box(){
    bounding_box_t box;
       box.x = this->position.x;
       box.y = 0;
       box.z = this->position.z;
       box.width = 2;
       box.height = this->y+ 3;
       box.length = 2;
       return box;
}

