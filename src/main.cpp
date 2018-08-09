#include "main.h"
#include "timer.h"
#include "ball.h"
#include "floor.h"
#include "water.h"
#include "math.h"
#include "trampoline.h"
#include "porcupine.h"
#include "gameover.h"
#include "magnet.h"
#include "plank.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int nP =n/10;

int initial_ground = -7;
int gameOver = 0;
int gameWaitTime = 0;
int downFlag = 0;
int fatFlag = 0;
int score =0;
int popTicker = 0;
int magnetTick = 0;
bool noPause = 1;
bool puptaken = 0;
char scoreString[100];

Ball player1, ballTemp[400], ballPlanck[n/10],pop;
Water water;
Trampoline tramp,tramp2;
Magnet magnet;
Porcupine spike,spike2;
Plank plank[n/10];
GameOver gameEnd;
Floor floor1,floor2,floor3,floor4;

int color_selector = n-1.5;
int dir_flag = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render


    if(gameOver){
        gameEnd = GameOver(score);
        gameEnd.draw(VP);
    }
    else{
        floor1.draw(VP);
        water.draw(VP);
        player1.draw(VP);
        tramp.draw(VP);
        spike.draw(VP);
        spike2.draw(VP);
        for(int i=0;i<n ;i++){
            ballTemp[i].draw(VP);
        }
        for(int i=0;i<nP ;i++){
            ballPlanck[i].draw(VP);
            plank[i].draw(VP);
        }
        if(!puptaken ){
        pop.draw(VP);
    }
        magnet.draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
     int p = glfwGetKey(window, GLFW_KEY_P);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int zoomIn = glfwGetKey(window, GLFW_KEY_UP);
    int zoomOut = glfwGetKey(window, GLFW_KEY_DOWN);
    int pop = glfwGetKey(window, GLFW_KEY_W);
    if(noPause){
    if (left) {
       player1.speed_x -= 0.02;
    }

    if(right){
        player1.speed_x += 0.02;
    }

    if (up && player1.flag_air == 0){
        if(player1.trampFlag){
            player1.speed_y = 1;

        }
        else
            player1.speed_y = 0.3;
        if(player1.waterFlag !=0 ){
        player1.speed_y += 0.2;
        }
            player1.flag_air = 1;
    }
    if(zoomIn&& screen_zoom<=2){
        screen_zoom += 0.1;
        reset_screen();
    }
    if(zoomOut && screen_zoom>=1){
        screen_zoom -= 0.1;
        reset_screen();
}
    if(pop&&puptaken){
        player1.speed_y +=0.5;
        popTicker = 0;
        puptaken = 0;
    }
    }
    if(p){
        noPause = !noPause;
    }
}

void tick_elements() {
    player1.tick();
    spike.tick();
    spike2.tick();
    for(int i = 0;i<nP;i++){
    ballPlanck[i].tick();
    plank[i].tick();
    }
    if(popTicker >=1 )
        pop.tick();

    //GameOver handler
    if(gameOver){
        gameWaitTime++;
        if(gameWaitTime == 100){
            score = 0;
            puptaken = 0;
            gameOver =0;
            player1.position.x=-10;
            gameWaitTime = 0;
            spike.position.x = spike.center;
            spike2.position.x = spike2.center;
        }
    }

    //Checking for Water
    if(player1.position.x >= water.x-water.r && player1.position.x <= water.x+water.r){
       if(player1.position.x >= water.x-water.r) player1.waterFlag = 1;//right
           else player1.waterFlag = 2;//left

    }
    else {
        player1.waterFlag = 0;
    }


//Multiple flying balls mechanic
    for(int i=0;i<n ;i++){
        ballTemp[i].tick();
        if (detect_collision(player1.bounding_box(), ballTemp[i].bounding_box())) {
            int height_selector = i*1.2;
            if (height_selector <= color_selector/3.0){
                ballTemp[i] = Ball(-50,height_selector ,COLOR_YELLOW,rand() % 10 +5,0,(rand() % 3),1);
                score+=5;
                if(player1.flag_air == 1 )
                player1.speed_y += 0.3;
                else if(player1.flag_air == -1 ){
                    if(player1.speed_y <= 0)
                    player1.speed_y =  0.5;
                    else
                        player1.speed_y +=  0.3;
                    player1.flag_air = 1;
                }
                else if(player1.flag_air == 0 ){
                    player1.speed_y += 0.1;
                    player1.flag_air = 1;
               }
            }
            else if(height_selector > color_selector/3.0 && height_selector <=color_selector*2.0/3.0){
                ballTemp[i] = Ball(-50,height_selector ,COLOR_BLUE,rand() % 10 +5,0,(rand() % 3),1);
                score+=10;
                if(player1.flag_air == 1 )
                    player1.speed_y += 0.3;
                else if(player1.flag_air == -1){
                    if(player1.speed_y <= 0)
                    player1.speed_y =  0.5;
                    else
                        player1.speed_y +=  0.3;
                    player1.flag_air = 1;
                }
                else if(player1.flag_air == 0 ){
                    player1.speed_y += 0.1;
                    player1.flag_air = 1;
               }
            }
            else{
                ballTemp[i] = Ball(-50,height_selector ,COLOR_GREEN,rand() % 10 +5,0,(rand() % 3),1);
                 score+=20;
                 fatFlag = 1 ;
                 player1.r *=0.8;
                 player1.speed_y -= 0.2;
                if(player1.flag_air == 1)
                player1.speed_y += 0.1;
                else if(player1.flag_air == -1 ){
                    if(player1.speed_y <= 0)
                    player1.speed_y =  0.2;
                    else
                        player1.speed_y +=  0.1;
                    player1.flag_air = 1;
                }
                 else if(player1.flag_air == 0 && player1.position.x < 18){
                     player1.speed_y += 0.1;
                     player1.flag_air = 1;
                }
            }
        }
        if (ballTemp[i].position.x>=100)
        ballTemp[i].position.x = -30;
    }
//Power UP Manager
    if (detect_collision(player1.bounding_box(), pop.bounding_box())) {
    puptaken = 1;
    popTicker = 0;
    pop.speed_x = 0;
    pop.position.x = -80;
    }

//FatFlag Manager
    if(fatFlag <=1){
        fatFlag ++;
    }
    if(fatFlag == 100){
        fatFlag = 0;
    }
    //Player Left Right Boundaries
    if(player1.position.x >= 100){
        player1.position.x = 100;
    }
    else if(player1.position.x  <= -32){
        player1.position.x = -32;

    }
        screen_center_x = player1.position.x;
         screen_center_y = player1.position.y;
         reset_screen();

//Magnet Move
    magnetTick++;
    if(magnetTick == 200){
        magnetTick = 0;
        int temp =rand()%2;
        if(temp)
           magnet.rotation = 180;
        magnet.position.y = rand() % 50 ;
        magnet.position.x = rand() % 25 ;
    }
    else if(magnetTick == 0){
        magnet.rotation = 0;
    }

//Magnet Check
   if (detect_collision(player1.bounding_box(), magnet.bounding_box())) {
        float x = player1.position.x - magnet.position.x;
        float y = player1.position.y - magnet.position.y;
       if(player1.position.x - magnet.position.x > 0){
            player1.speed_x -= 0.1;
       }
       else if(player1.position.x - magnet.position.x < 0){
           player1.speed_x += 0.1;
       }

       if(player1.position.y - magnet.position.y > 0){
            player1.speed_y -= 0.1;
       }
       else if(player1.position.y - magnet.position.y < 0){
           player1.speed_y += 0.1;
       }

    }

   //Bonus
   if(score%100 == 0){
      popTicker = 1;
     pop.speed_x = 7;
   }
   if(popTicker >=1)
       popTicker++;
   if(popTicker == 1000){
       popTicker = 0;
   }

//Spike Check
if (detect_collision(player1.bounding_box(), spike.bounding_box())  || detect_collision(player1.bounding_box(), spike2.bounding_box())  ) {
gameOver = 1;
player1.speed_x =0;
player1.speed_y = 0;
}

//Plank Check
for(int i = 0;i<nP ;i++){
if(detect_collision(player1.bounding_box(), plank[i].bounding_box()) && !detect_collision(player1.bounding_box(), ballPlanck[i].bounding_box())){
    player1.speed_x += 1;
}
if(ballPlanck[i].position.x >= 110){
    int speed;
    int  height_selector = i*8;
        speed = rand() % 10 +1;
    ballPlanck[i] = Ball(-60, height_selector, COLOR_RED,speed,0,2,2);
    float ang = rand() % 60;
    ang +=100;
    //radius == 2
    plank[i] = Plank(-60+2*cos(ang*M_PI/180 - M_PI/2),height_selector+2*sin(ang*M_PI/180 - M_PI/2),ang,speed);

}
}
//Trampoline Check
    if((player1.position.x>=tramp.x_s && player1.position.x <=tramp.x_e) &&(player1.position.y >= tramp.y_s-0.2 && player1.position.y <= tramp.y_s+0.2) ){
        player1.trampFlag = 1;
          player1.ground_y = tramp.y_s ;

}
        else {
        if(player1.trampFlag == 1 && !(player1.position.y >= tramp.y_s-0.2 && player1.position.y <= tramp.y_s+0.2)){
             player1.flag_air = -1;
        }
        else if(player1.trampFlag == 1 ){
            player1.ground_y = initial_ground;
            player1.flag_air = -1;
        }
        player1.trampFlag = 0;
        if(!(player1.position.x>=tramp.x_s && player1.position.x <=tramp.x_e) && player1.waterFlag == 0)
        player1.ground_y =   initial_ground;
        }


//Jump Mechanic
    if(player1.speed_y <= 0 && player1.flag_air == 1){
      player1.flag_air = -1;
      player1.speed_y = 0;
    }
    if(player1.flag_air == 1){
      player1.speed_y -= 0.01;
    }
    if(player1.flag_air == -1){
      player1.speed_y -= 0.01;
    }
    //Porcupine Move
        if(spike.position.x > spike.center + spike.moveR) spike.speed = -0.05;
        if(spike.position.x < spike.center - spike.moveR) spike.speed = 0.05;
        if(spike2.position.x > spike2.center + spike2.moveR) spike2.speed = -0.05;
        if(spike2.position.x < spike2.center - spike2.moveR) spike2.speed = 0.05;


        sprintf (scoreString,"Score : %d",score);
        glfwSetWindowTitle(window,scoreString);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    floor1 =    Floor(-8.0);
    player1       = Ball(-10, initial_ground, COLOR_RED,0,0,2,0);
    water = Water(5,-9);
    tramp = Trampoline(25,0);
    magnet = Magnet(-25,9);
    spike = Porcupine(45,initial_ground-2,0.05);
    spike2 = Porcupine(60,initial_ground-2,0.05);
    pop = Ball(-50, initial_ground, color_t{rand()%255,rand()%255,rand()%255},6,0,1,1);
     int height_selector;
    for(int i=0;i<n ;i++){
        height_selector = i*1.2;
        if (color_selector/3.0 >= height_selector){
            ballTemp[i] = Ball(-60,height_selector ,COLOR_YELLOW,rand() % 10 +5,0,(rand() % 3),1);
        }
        else if(color_selector/3.0 < height_selector && color_selector*2.0/3.0 >= height_selector ){
            ballTemp[i] = Ball(-60,height_selector ,COLOR_BLUE,rand() % 10 +5,0,(rand() % 3),1);
        }
        else
            ballTemp[i] = Ball(-60,height_selector ,COLOR_GREEN,rand() % 10 +5,0,(rand() % 3),1);
         }
    int speed;
   for(int i = 0;i<nP ;i++){
        height_selector = i*8;
        speed = rand() % 10 +1;
   ballPlanck[i] = Ball(-60, height_selector, COLOR_RED,speed,0,2,2);
   float ang = rand() % 60;
   ang +=100;
   //radius == 2
   plank[i] = Plank(-60+2*cos(ang*M_PI/180 - M_PI/2),height_selector+2*sin(ang*M_PI/180 - M_PI/2),ang,speed);
    }
   //slope[i] = Rectangle(xy+rady*cos(ang*M_PI/180 - M_PI/2),vary+rady*sin(ang*M_PI/180 - M_PI/2),ang,-vely,
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
    int width  = 1600;
    int height = 800;

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
            if(noPause)
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
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 18 / screen_zoom;
    float bottom = screen_center_y - 18/ screen_zoom;
    float left   = screen_center_x - 32 / screen_zoom;
    float right  = screen_center_x + 32 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
