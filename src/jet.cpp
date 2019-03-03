#include "jet.h"
 #define M_PI 3.14159265358979323846
#define RAD2DEG 180.0/M_PI
#define DEG2RAD M_PI/180.0
Jet::Jet(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
//    this->rotation = 0;
    speed = 0;
    acceleration = 0.001;
    retardation = 0.0001;
    rspeed =1;
    xspeed = 0.0;
    zspeed = 0;
    phi =0;
    tilt_back = 0.5;
    theta = 0;
    score = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    radius = 0.8;

        const int n = 360;
        const int reqd = n * 9*n;
        GLfloat vertex_buffer_data1[reqd] = {};
        GLfloat vertex_buffer_data2[300*n] = {};

        double angle = 0;
        const double pi = 4 * atan(1);
        double diff = (2 * pi) / (double)n;
        int cur = 0;
        //GLfloat vertex_buffer_data[12345];

    for(int j=0;j<n;j++){
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data1[cur++] = 0.0;
            vertex_buffer_data1[cur++] = 0.0;
            vertex_buffer_data1[cur++] = -3.0f - j*0.03;

            //Point with lower angle
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = -3.0f -j*0.03;

            //Point with higher angle
            angle += diff;
            vertex_buffer_data1[cur++] = radius * cos(angle);
            vertex_buffer_data1[cur++] = radius * sin(angle);
            vertex_buffer_data1[cur++] = -3.0f -j*0.03;

    }
        radius -= 0.000007*j;
    }

    radius = 0.4;
    cur =0;
    for(int j=0;j<50;j++){
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data2[cur++] = 0.0;
            vertex_buffer_data2[cur++] = 0.0;
            vertex_buffer_data2[cur++] = -4.0f + j*0.03;

            //Point with lower angle
            vertex_buffer_data2[cur++] = radius * cos(angle);
            vertex_buffer_data2[cur++] = radius * sin(angle);
            vertex_buffer_data2[cur++] = -4.0f +j*0.03;

            //Point with higher angle
            angle += diff;
            vertex_buffer_data2[cur++] = radius * cos(angle);
            vertex_buffer_data2[cur++] = -0.0+radius * sin(angle);
            vertex_buffer_data2[cur++] = -4.0f +j*0.03;

    }
        radius -=  0.0002*j;
    }


    GLfloat vertex_buffer_data3[] = {
        -0.1, 0.0, -7.0,
        -0.1, 0.0, -12.0,
        -4.0, 0.0, -6.0,

        0.1, 0.0, -7.0,
        0.1, 0.0, -12.0,
        4.0, 0.0, -6.0
    };
    GLfloat vertex_buffer_data4[] ={
        -0.1, 0.0, -6.0,
        -0.1, 0.0, -4.0,
        -2.0, 0.5, -3.0,

        0.1, 0.0, -6.0,
        0.1, 0.0, -4.0,
        2.0, 0.5, -3.0
    };
    GLfloat vertex_buffer_data5[]={
        -1, 1,-20,
        0, 2, -20,
        1, 1, -20,
        -1, 1, -20,
        0, 0, -20,
        1, 1, -20
    };


    this->object1 = create3DObject(GL_TRIANGLES, 2*n*10, vertex_buffer_data1, color, GL_LINE);

    this->object6 = create3DObject(GL_TRIANGLES, 100*n, vertex_buffer_data1,{255,0,0}, GL_LINE);
        this->object1 = create3DObject(GL_TRIANGLES, 3*n*n, vertex_buffer_data1,{233,243,253}, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 40*n*3, vertex_buffer_data1, {0, 0, 256}, GL_FILL);

    this->object2 = create3DObject(GL_TRIANGLES, 3*50*n, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, {233,243,253}, GL_FILL);

    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, {233,243,253}, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, {256, 256, 256}, GL_LINE);
}

void Jet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->phi * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate3    = glm::rotate((float) (this->theta * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate* rotate2*rotate3);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
}

void Jet::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
void Jet::forward() {
    if(speed >0.1)
        return ;
    this->speed += acceleration;


//    if(this->zspeed >= 1){
//        this->position.y += speed*cos(phi);
//    }
}
void Jet::tick() {
    this->zspeed = -speed * cos(DEG2RAD*this->rotation);
    this->xspeed = -speed * sin(DEG2RAD*this->rotation);
    this->position.z += zspeed;
    this->position.x += xspeed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Jet::left(){


    this->rotation += rspeed;
        if(this->phi > 45)
        return;
    this->phi += rspeed;

//    this->position.x -= xspeed;

}
void Jet::no_key(){
    if(this->speed ==0 && this->phi==0 && this->theta==0)
        return;

    if(this->speed*8000 >101)
    this->speed -= retardation;
    else
        this->speed += retardation;

    if(this->phi >0)
        this->phi -= tilt_back;
    else
        this->phi +=tilt_back;
    if(this->theta >0.5)
        this->theta -= tilt_back;
    else if (this->theta<-0.5)
        this->theta += tilt_back;
    else
        this->theta = 0;

}
void Jet::right(){


    this->rotation -= rspeed;
    if(this->phi < -45)
        return;
    this->phi -= rspeed;

    //    this->position.x += xspeed;
}
void Jet::up(){
    if(this->position.y>50)
        return;
    this->position.y += 0.1;
    if(this->theta>20)
        return;
    this->theta += rspeed;

}
void Jet::down(){
    if(this->position.y<3)
        return;
    this->position.y -=0.1;
    if(this->theta<-20)
        return;
    this->theta -= rspeed;
}
void Jet::clockwise(){
    this->phi -= rspeed*4;
    if(this->phi <= -360)
        this->phi = 0;
}
void Jet::counter_clockwise(){
    this->phi += rspeed*4;
    if(this->phi >= 360)
        this->phi = 0;
}
