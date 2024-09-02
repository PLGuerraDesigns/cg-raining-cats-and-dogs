//
//  project5.cpp
//  HW5
//
//  Created by Pablo Guerra on 4/15/20.
//  Copyright © 2020 Pablo Guerra. All rights reserved.
//
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"
#include "cubes.cpp"
using namespace std;


// Global variables
bool applyMotion = true;            // Start/stop animation
const int CubeListSize = 15;        // Max number of cubes generated at a given time.
struct Cube cubeList[CubeListSize]; // Array of cubes



//---------------------------------------
// Returns a random value between the minimum and maximum
//---------------------------------------
float getRandomVal(float min, float max){
    float val = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    
    return val;
}



//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}



//---------------------------------------
// Returns a cube with randomly generated parameters
//---------------------------------------
Cube createCube(){
    int xdim, ydim;
    unsigned char *texture;
    char filename[100];
    
    // Generate randomly selected texture
    int type = rand() % 2;
    if(type == 0){
        sprintf(filename, "cats_dogs/cat%ld.jpg", random() % 10);
    }
    else{
        sprintf(filename, "cats_dogs/dog%ld.jpg", random() % 10);
    }
    init_texture((char *)filename, texture, xdim, ydim);
    
    // Generate random X,Y position
    float Px = getRandomVal(-1000, 1000);
    float Py = getRandomVal(1000, 2000);
    float Pz = 0;
    
    // Generate random X,Y velocity
    float Vx = getRandomVal(-10, 10);
    float Vy = getRandomVal(10, 35);
    float Vz = 0;
    
    // Generate random X,Y,Z rotation
    float Ax = getRandomVal(0, 360);
    float Ay = getRandomVal(0, 360);
    float Az = getRandomVal(0, 360);
    
    // Generate random cube radius (size)
    float radius = getRandomVal(0.3, 0.9);

    // Create cube using generated parameters
    struct Cube newCube = {Px, Py, Pz, Vx, Vy, Vz, Ax, Ay, Az, radius, texture};
    
    return newCube;
}



//---------------------------------------
// Function to draw cubes
//---------------------------------------
void block(struct Cube cube)
{
   // Define 8 vertices
   float ax = 0, ay = 0, az = cube.Radius;
   float bx = cube.Radius, by = 0, bz = cube.Radius;
   float cx = cube.Radius, cy = cube.Radius, cz = cube.Radius;
   float dx = 0, dy = cube.Radius, dz = cube.Radius;

   float ex = 0, ey = 0, ez = 0;
   float fx = cube.Radius, fy = 0, fz = 0;
   float gx = cube.Radius, gy = cube.Radius, gz = 0;
   float hx = 0, hy = cube.Radius, hz = 0;

   // Draw 6 faces
   glBegin(GL_POLYGON);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(gx, gy, gz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(cx, cy, cz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();
}



//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Init view
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
   glEnable(GL_DEPTH_TEST);

    // Create cubes and store in array
    for(int i=0; i < CubeListSize; i++){
        cubeList[i] = createCube();
    }
    
    // Init texture
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR_MIPMAP_NEAREST);
}



//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    // Fixes size issue on MacOS
    #ifdef __APPLE__
        glViewport(0, 0, 1000, 1000);
    #endif


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Update display with new cube motion values
    for(int x=0; x < CubeListSize; x++){
        glPushMatrix();
        glTranslatef(cubeList[x].Px / 500.0, cubeList[x].Py / 500.0, cubeList[x].Pz / 500.0);
        glRotatef(cubeList[x].Ax, 1.0, 0.0, 0.0);
        glRotatef(cubeList[x].Ay, 0.0, 1.0, 0.0);
        glRotatef(cubeList[x].Az, 0.0, 0.0, 1.0);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, cubeList[x].texture);
        
        block(cubeList[x]);
        glPopMatrix();
    }
    glFlush();
}



//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    // Start/stop cube motion using [spacebar]
    if(key == ' '){
        applyMotion = !applyMotion;
    }
}



//---------------------------------------
// Idle callback for OpenGL
//---------------------------------------
void myidle() {
    // Update cube motion values
    if(applyMotion){
        for(int x=0; x < CubeListSize; x++){
            cubeList[x].Py -= cubeList[x].Vy;
            cubeList[x].Px -= cubeList[x].Vx;
            cubeList[x].Ax += 0.2;
            cubeList[x].Ay += 0.7;
            glutPostRedisplay();
            
            // If cube is no longer visible then generate new cube
            if(cubeList[x].Py < - 1500){
                cubeList[x] = createCube();
            }
        }
    }
}


//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
    // Create OpenGL window
    cout << "Press Spacebar to start/stop animation. \n";
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Raining Cats and Dogs");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(myidle);
    init();
    glutMainLoop();
    return 0;
}
