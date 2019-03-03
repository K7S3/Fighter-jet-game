#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
// Include GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//#include "shader.hpp"


#include "main.h"
#include "timer.h"
#include "ball.h"
#include "jet.h"
#include "world.h"
#include "tower.h"
#include "island.h"
#include "missile.h"
#include "score.h"
#include "fuel.h"
#include "fuelup.h"
#include "smoke.h"
#include "volcano.h"
#include "pointer.h"
#include "enemy.h"
#include "parachutes.h"
#include "bomb.h"
#include "compass.h"
#include "lifeup.h"
#define RAD2DEG 180.0/M_PI
#define DEG2RAD M_PI/180.0
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Jet  jet1;
World world1;
Tower tower1[20];
Island island1[30];
Missile missile1;
Score altitude[2];
Score speed[3];
Score score[4];
Fuel fuel1;
Fuel health1;
Fuelup fuelup1[10];
Smoke smoke1[7];
Volcano volcano1[100];
Pointer pointer1;
Enemy enemy1[10000];
Missile missile2[10];
Parachutes parachute1[5];
Bomb bomb1;
Compass compass1;
Lifeup lifeup1[5];
int fuel_value =1, health_value=2, tower_checked = 0, no_of_fuelups=10, no_of_smokes=7, no_of_volcanoes=100, count[10];
int no_of_enemies=10, no_of_parachutes=5, no_of_lifeups=5;
int launch_missile = 0, launch_bomb = 0;
int no_of_islands=30, no_of_towers=20;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0, camera_x=0, camera_y=4, camera_z=3, target_x=0, target_y=0, target_z=-20;
int camera_type = 1;
float helix_angle_1=0, helix_angle_2=0;
Timer t60(1.0 / 60);

void set_camera(int camera_type);
int check_jet_position();
int collision_fuelup(Fuelup a, Jet b);
int pass_smoke(Smoke a, Jet b);
int collision_volcano(Jet a, Volcano b);
int missile2_collision(Jet a, Missile b);
int missile1_collsion(Enemy a, Missile b);
int parachute_collision(Parachutes a, Missile b);
int bomb_collision(Bomb a, Enemy b);
int collision_lifeup(Jet a, Lifeup b);
//void vertical_loop();
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
//    GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    glUseProgram (programID);

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform
    set_camera(camera_type);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(camera_x, camera_y, camera_z);
       // Target - Where is the camera looking at.  Don't change unless you are sure!!
   glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
//     Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
//    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);
    jet1.draw(VP);
    world1.draw(VP);
//    tower1.draw(VP);
    missile1.draw(VP);
    bomb1.draw(VP);
    for(int i=0;i<no_of_islands;i++)
    {
        island1[i].draw(VP);
    }
    for(int i=1;i<no_of_fuelups;i++)
    {
        fuelup1[i].draw(VP, 1);
    }
    for(int i=1;i<no_of_smokes;i++)
    {
        smoke1[i].draw(VP, 1);
    }
    for(int i=1;i<no_of_enemies;i++){
        enemy1[i].draw(VP,enemy1[i].value);
    }
    for(int i=0;i<no_of_volcanoes;i+=2)
    {
        volcano1[i].draw(VP, 1);
        volcano1[i+1].draw(VP, 1);
    }
    for(int i=0;i<no_of_towers;i+=2)
    {
        if(check_jet_position()*2>=i)
           {

            tower1[i].draw(VP,1);
            tower1[i+1].draw(VP,1);
        }

        else{
             tower1[i].draw(VP,0);
             tower1[i+1].draw(VP,0);
        }
    }
    if(camera_type==1 || camera_type==2){
    int alt = jet1.position.y;
    for(int i=0;i<2;i++){
         altitude[i].draw(VP,alt%10);
         alt/=10;
    }
    int jet_speed = jet1.speed*8000;

    for(int i=0;i<3;i++){
         speed[i].draw(VP,jet_speed%10);
         jet_speed/=10;
    }
    int sc = jet1.score;
    for(int i=0;i<4;i++){
        score[i].draw(VP, sc%10);
        sc = sc/10;
    }
    fuel1.draw(VP, fuel_value);
    health1.draw(VP, health_value);
    compass1.draw(VP,1);
    pointer1.draw(VP, 1);
    }
//    speed.draw(VP);
    for(int i =1;i<no_of_enemies;i++){

        missile2[i].draw(VP);
    }
    for(int i=0;i<no_of_parachutes;i++){
        parachute1[i].draw(VP,1);
    }
    for(int i=0;i<no_of_lifeups;i++){
        lifeup1[i].draw(VP,1);
    }
}

void tick_input(GLFWwindow *window) {
    glfwSetScrollCallback(window, scroll_callback);
    //Camera Selection
    int zero = glfwGetKey(window,GLFW_KEY_0);
    int one = glfwGetKey(window,GLFW_KEY_1);
    int two = glfwGetKey(window,GLFW_KEY_2);
    int three = glfwGetKey(window,GLFW_KEY_3);
    int four = glfwGetKey(window,GLFW_KEY_4);
    int five = glfwGetKey(window,GLFW_KEY_5);
    int six = glfwGetKey(window,GLFW_KEY_6);
    if(zero){
        camera_type = 0;
    }
    if(one){
        camera_type = 1;
    }
    if(two){
        camera_type = 2;
    }
    if(three){
        camera_type = 3;
    }
    if(four){
        camera_type = 4;
    }
    if(five){
        camera_type = 5;
    }
    if(six){
        camera_type = 6;
    }
    //Camera Movements
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {

        camera_x -= 0.05;
    }
    if(right){

      camera_x += 0.05;
    }
    if(up){
        if(camera_type==6){
            helix_angle_2 -=0.5;
            camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
            camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
            camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);
        }
        else
        jet1.up();

    }
    if(down){
        if(camera_type==6){
            helix_angle_2 +=0.5;
            camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
            camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
            camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);

        }
        else
        jet1.down();

    }
    //Jet Movements
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int space_bar = glfwGetKey(window, GLFW_KEY_SPACE);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int b = glfwGetKey(window, GLFW_KEY_B);

    if(w){
        jet1.forward();
    }
    if(space_bar){
        if(jet1.theta==0){
           launch_missile = 1;
           missile1.set_position(jet1.position.x, jet1.position.y, jet1.position.z);
           missile1.rotation = jet1.rotation;
           missile1.phi      = jet1.phi;
        }
    }
    if(a){
        jet1.left();

    }
    if(d){
        jet1.right();
    }
    if(q){
        jet1.counter_clockwise();
    }
    if(e){
        jet1.clockwise();
    }
    if(b){
        if(jet1.theta==0){
           launch_bomb = 1;
           bomb1.set_position(jet1.position.x, jet1.position.y-1.5, jet1.position.z);
           bomb1.speed =jet1.speed;

           bomb1.rotation = jet1.rotation;
           bomb1.phi      = jet1.phi;
        }
    }
    if(!a || !w || !d)
    {
        jet1.no_key();
    }


}

void tick_elements() {
    if(missile1.position.y<2 && camera_type ==4){
        set_camera(1);
        camera_type = 1;}
    if(bomb1.position.y<2 && camera_type ==5){
        set_camera(1);
        camera_type = 1;}
    set_camera(camera_type);
    jet1.tick();
    for(int i=0;i<no_of_lifeups;i++){
        if(collision_lifeup(jet1, lifeup1[i])==1)
        {
            if(health1.value>1.0)
            health1.value +=1.5-health1.value;
            else
                health1.value +=0.5;

            lifeup1[i].set_position(-100,-100,-100);
        }
            lifeup1[i].tick1();
         }

    if(launch_missile == 1)
        missile1.tick();
    if(launch_bomb == 1)
        bomb1.tick();
//    int i=0;
    for(int i=0;i<2;i++){

        altitude[i].rotation = jet1.rotation;
        altitude[i].set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation-10+2*i)), camera_y-6, camera_z - 20*cos(DEG2RAD*(jet1.rotation-10+2*i)));

    }
    for(int i=0;i<3;i++){

        speed[i].rotation = jet1.rotation;
        speed[i].set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation+5+2*i)), camera_y-6, camera_z - 20*cos(DEG2RAD*(jet1.rotation+5+2*i)));

    }
    for(int i=0;i<4;i++){

        score[i].rotation = jet1.rotation;
        score[i].set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation-20+2*i)), camera_y+1, camera_z - 20*cos(DEG2RAD*(jet1.rotation-20+2*i)));

    }
    fuel1.rotation = jet1.rotation;
    fuel1.set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation+20)), camera_y-7, camera_z - 20*cos(DEG2RAD*(jet1.rotation+20)));
    pointer1.rotation = RAD2DEG*atan((tower1[check_jet_position()*2+2].position.x-jet1.position.x)/(tower1[check_jet_position()*2+2].position.z-jet1.position.z));

    pointer1.set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation)), camera_y+2, camera_z - 20*cos(DEG2RAD*(jet1.rotation)));
    compass1.rotation = RAD2DEG*atan((compass1.position.x-jet1.position.x)/(compass1.position.z-jet1.position.z));;
    compass1.theta = -jet1.rotation;
    compass1.set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation-25)), camera_y-4, camera_z - 20*cos(DEG2RAD*(jet1.rotation-25)));
    fuel1.value -= jet1.speed*0.003;
    if (fuel1.value < 0.25)
    {
        fuel_value = 2;
    }
    else
        fuel_value = 1;
    if (health1.value < 0.25)
    {
        health_value = 2;
    }
    else
        health_value = 1;
    if(fuel1.value <= 0)
    {
        quit(window);
    }
    health1.rotation = jet1.rotation;

    health1.set_position(camera_x-20*sin(DEG2RAD*(jet1.rotation-8)), camera_y-7.4, camera_z - 20*cos(DEG2RAD*(jet1.rotation-8)));
    if(health1.value <=0)
    {
        quit(window);
    }
    for(int i=1;i<no_of_fuelups;i++){
        if(collision_fuelup(fuelup1[i], jet1)==1){
            fuelup1[i].set_position(-100, -100, 100);
            fuel1.value += 0.3;
        }
    }
    for(int i=0;i<no_of_smokes;i++){
        if(pass_smoke(smoke1[i], jet1)==1)
            jet1.score +=1;
    }
    for(int i=0;i<no_of_volcanoes;i++)
    {
        if(collision_volcano(jet1 , volcano1[i])==1)
        {     quit(window);
        }
    }
    for(int i=1;i<no_of_enemies;i++){

        if(enemy1[i].value == 0)
            continue;

        if(missile1_collsion(enemy1[i], missile1)==1){
            enemy1[i].value =0;
            jet1.score +=200;
            missile2[i].set_position(-100,-100,-100);
            continue;

        }
        if(bomb_collision(bomb1, enemy1[i])==1){
            enemy1[i].value =0;
            jet1.score +=250;
            missile2[i].set_position(-100,-100,-100);
            continue;
        }
        enemy1[i].rotation = 180+RAD2DEG*atan((jet1.position.x - enemy1[i].position.x)/(jet1.position.z-10-enemy1[i].position.z));
        if(abs(enemy1[i].position.z - jet1.position.z) < 50 && count[i] ==0)
        {
            missile2[i].set_position(enemy1[i].position.x, 3.5+enemy1[i].y, enemy1[i].position.z);
            missile2[i].rotation = enemy1[i].rotation;
//            missile2[i].phi      = -wjet1.phi;
            count[i] = 1;

        }
    }
    for(int i=1;i<no_of_enemies;i++){
    if(enemy1[i].value == 0)
        continue;
        if(count[i] == 1){
            missile2[i].tick();
            if(missile2_collision(jet1,missile2[i])==1)
            {
                health1.value -=0.05;
                count[i] = 0;

            }
            if(abs(missile2[i].position.z-enemy1[i].position.z)>50){
            count[i] = 0;
            }
        }
    }
    for(int i=0;i<no_of_parachutes;i++){
        if(abs(jet1.position.z-parachute1[i].position.z)<80)
            parachute1[i].tick();
        if(parachute_collision(parachute1[i], missile1)==1)
        {
            parachute1[i].set_position(-100,-100,-100);
            jet1.score += 100;

        }
    }
//        missile1[i].rotation = jet1.rotation
//        missile1[i].theta = jet1.theta;
//        missile1[i].phi = jet1.phi;

//    missile1.tick();
//    }
//    ball1.tick()
//    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

//    ball1       = Ball(0, 0, COLOR_RED);
    jet1        = Jet(0,5,0, COLOR_BLACK);
    world1      = World(0,0, COLOR_WATER);
    missile1    = Missile(0, -100,-150, COLOR_RED);
    fuel1       = Fuel(0,5,1, COLOR_GREEN);
    health1     = Fuel(0,5, 1, COLOR_HOTPINK);
    pointer1    = Pointer(0, 10, 0, COLOR_GREEN);
    bomb1       = Bomb(0, -100, -150, COLOR_ORANGE);
    compass1    = Compass(0, -10, -10, COLOR_ASHGREY);
    for(int i=0;i<no_of_lifeups;i++)
    lifeup1[i]     = Lifeup(rand()%60-30, rand()%5 +10, -i*175 - 60,COLOR_HOTPINK);
    for(int i=0;i<no_of_parachutes;i++){
        parachute1[i] = Parachutes(rand()%40-20, rand()%5 +10, -i*200 - 50, COLOR_PARACHUTE);
    }
//    missile2[0] = Missile(-100,-100,-100,COLOR_ASHGREY);
    int count =1;
    for(int i = 1;i<10&&count<no_of_enemies;i++){
        for(int j=1;j<=i;j++){
//          srand(time(0));
        int a = rand()%3;
        int b = rand()%5;
        missile2[count] = Missile(enemy1[count].position.x, 3.5+b*2+5, enemy1[count].position.z, COLOR_FIREENGINERED);
        enemy1[count] = Enemy(20*a - 20,b*2+5, -i*90, COLOR_ORANGE);
        count++;
}
    }
    for(int i=1;i<no_of_smokes;i++){
        smoke1[i] = Smoke(rand()%40 - 20,rand()%15+5, -i*175, COLOR_WHITE);
    }
    for(int i=1;i<no_of_fuelups;i++){
        fuelup1[i] = Fuelup(0,rand()%15+5, -i*100-20, COLOR_YELLOW);
    }
    for(int i=0, j=0;i<no_of_volcanoes;i+=2, j++){
        volcano1[i]      = Volcano(100,0,-j*20, COLOR_VOLCANO);
        volcano1[i+1]    = Volcano(-100,0,-j*20, COLOR_VOLCANO);
    }
    for(int i=0, j=0;i<no_of_towers;i+=2, j++){
    tower1[i]      = Tower(20,0,-j*100, COLOR_GREEN);
    tower1[i+1]    = Tower(-20,0,-j*100, COLOR_GREEN);
    }
    for(int i=0;i<2;i++)
        altitude[i]    = Score(camera_x-20*sin(DEG2RAD*(jet1.rotation-10+2*i)), camera_y-6, camera_z - 20*cos(DEG2RAD*(jet1.rotation-10+2*i)), COLOR_ORANGERED);
    for(int i=0;i<3;i++)
        speed[i]    = Score(camera_x-20*sin(DEG2RAD*(jet1.rotation+5+2*i)), camera_y-6, camera_z - 20*cos(DEG2RAD*(jet1.rotation+5+2*i)), COLOR_CYAN);
    for(int i=0;i<4;i++)
        score[i]    = Score(camera_x-20*sin(DEG2RAD*(jet1.rotation+2*i)), camera_y, camera_z - 20*cos(DEG2RAD*(jet1.rotation+5+2*i)), COLOR_BLACK);


//    speed    = Score(-2, -3, -20, {0,0,0});
    for(int i=0, j=0;i<no_of_islands;i+=3,j++){
        island1[i] = Island(0,0, -j*100, COLOR_WARMSAND);
        island1[i+1] = Island(20,0, -j*100 +20, COLOR_WARMSAND);
        island1[i+2] = Island(-20,0, -j*100 +20, COLOR_WARMSAND);
    }


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) && (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
   Matrices.projection = glm::perspective(45.0f, 1.0f, 10.0f, 100.0f);
//    Matrices.projection = glm::ortho(left,right,top, bottom, 0.1f, 500.0f);
}

void firstpersonview(){
    camera_x = 0;
    camera_y = 0;
    camera_z = 0;
//    target_z = 0;
}
void tower_view(){
    camera_x = 15;
    camera_y = 5;
    camera_z = 10;
}
void set_camera(int camera_type){

    if(camera_type==0){
        camera_x = 20;
        camera_y = 10;
        camera_z = tower1[check_jet_position()*2].position.z;
        target_x=jet1.position.x;
        target_y=jet1.position.y;
        target_z=-20+jet1.position.z;
    }
    if(camera_type == 1){
        camera_x = jet1.position.x+10*sin(DEG2RAD*jet1.rotation);
        camera_y = jet1.position.y+10+10*sin(DEG2RAD*jet1.theta);
        camera_z = jet1.position.z+10*cos(DEG2RAD*jet1.rotation);
        target_x=jet1.position.x;
        target_y=jet1.position.y+6;
        target_z=jet1.position.z;
    }
    if(camera_type == 2){
        camera_x = jet1.position.x-10*sin(DEG2RAD*jet1.rotation);
        camera_y = jet1.position.y+4+10*sin(DEG2RAD*jet1.theta);
        camera_z = jet1.position.z-10*cos(DEG2RAD*jet1.rotation);
        target_x=jet1.position.x-40*sin(DEG2RAD*jet1.rotation);
        target_y=jet1.position.y-1;
        target_z=jet1.position.z-40*cos(DEG2RAD*jet1.rotation);
    }
    if(camera_type == 3){
        camera_x = jet1.position.x;
        camera_y = jet1.position.y+80;
        camera_z =jet1.position.z;
        target_x=jet1.position.x;
        target_y=jet1.position.y;
        target_z=jet1.position.z-20;
    }
    if(camera_type == 4){

        camera_x = missile1.position.x-3*sin(DEG2RAD*missile1.rotation);
        camera_y = missile1.position.y+3+3*sin(DEG2RAD*missile1.theta);
        camera_z = missile1.position.z+10*cos(DEG2RAD*missile1.rotation);
        target_x=missile1.position.x;
        target_y=missile1.position.y-1;
        target_z=missile1.position.z;

    }
    if(camera_type == 5){

        camera_x = bomb1.position.x-3*sin(DEG2RAD*bomb1.rotation);
        camera_y = bomb1.position.y+5+3*sin(DEG2RAD*bomb1.phi);
        camera_z = bomb1.position.z+3*cos(DEG2RAD*bomb1.rotation);
        target_x=bomb1.position.x;
        target_y=bomb1.position.y+2;
        target_z=bomb1.position.z;

    }
    if(camera_type==7){

        camera_z = jet1.position.z+35;
        camera_y = jet1.position.y;
        camera_x = jet1.position.x +35;
        target_x =jet1.position.x;
        target_y =jet1.position.y;
        target_z = jet1.position.z + 2;
    }

}
int check_jet_position(){

    if(jet1.position.x > -20 && jet1.position.x < 20)
        return -(jet1.position.z-30)/100;
    else
        return 0;
}
int collision_fuelup(Fuelup a, Jet b){
    if(abs(a.position.x-b.position.x)<3&&abs(a.position.y-b.position.y)<3 && abs(a.position.z-b.position.z)<10)
        return 1;
    else
        return 0;
}
int pass_smoke(Smoke a, Jet b){
    if(abs(a.position.x-b.position.x)< a.radius &&abs(a.position.y - b.position.y)<a.radius && abs(a.position.z - b.position.z)<5)
        return 1;
    else
        return 0;
}
int collision_volcano(Jet a, Volcano b){
    if(abs(a.position.x-b.position.x)<b.radius +25&& abs(a.position.z - b.position.z) < b.radius+25)
        return 1;
    else
        return 0;
}
int missile2_collision(Jet a, Missile b){
    if(abs(a.position.x - b.position.x)<4 && abs(a.position.z - b.position.z)< 10 &&abs(a.position.y - b.position.y)<3)
        return 1;
    else
        return 0;
}
int missile1_collsion(Enemy a, Missile b){
    if(abs(a.position.x - b.position.x)<3 && abs(a.position.z - b.position.z)< 2&&abs(a.position.y - b.position.y)<a.y)
        return 1;
    else
        return 0;
}
int parachute_collision(Parachutes a, Missile b){
    if(abs(a.position.x-b.position.x)<5 && abs(a.position.y-b.position.y)<5&& abs(a.position.z-b.position.z)<5)
        return 1;
    else
        return 0;
}
int bomb_collision(Bomb a, Enemy b){
    return detect_collision(a.bounding_box(), b.bounding_box());
}
void helicam_func1(int arg){
    if(camera_type==6){
    if(arg==1){
        cout<<1<<endl;
        target_x +=1*sin(DEG2RAD*helix_angle_1);
        target_z +=1*cos(DEG2RAD*helix_angle_1);
        target_y +=1*sin(DEG2RAD*helix_angle_2);
        camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
        camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
        camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);
    }
    if(arg==2){
        cout<<2<<endl;
        target_x -=1*sin(DEG2RAD*helix_angle_1);
        target_z -=1*cos(DEG2RAD*helix_angle_1);
        target_y -=1*sin(DEG2RAD*helix_angle_2);
        camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
        camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
        camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);

    }
    if(arg==3){
        cout<<3<<endl;
        helix_angle_1 +=0.5;
        camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
        camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
        camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);

    }
    if(arg==4){
        cout<<4<<endl;
        helix_angle_1 -=0.5;
        camera_x = target_x+10*sin(DEG2RAD*helix_angle_1);
        camera_y = target_y+10*sin(DEG2RAD*helix_angle_2);
        camera_z = target_z+10*cos(DEG2RAD*helix_angle_1);
    }
    }
}
int collision_lifeup(Jet a, Lifeup b){
    if(abs(a.position.x-b.position.x)<4&&abs(a.position.y-b.position.y)<3&&abs(a.position.z - b.position.z)<3)
        return 1;
    else
        return 0;
}
void vertical_loop(int a){
    int b = 1;
//    camera_type =7;
    while(b != 0&&jet1.position.y >15)
    {
        camera_type = 7;
        set_camera(7);
        jet1.theta -= 10;
        jet1.yspeed +=0.01;
        jet1.tick();
        if(jet1.theta <=-360)
        {    b=0;
//            jet1.theta = 0;
            camera_type =7;
        }
    }


}
