/*************************************************
 * Copyright (C) 2015 J.K, all rights reserved.
 *
 * Filename: MGL.cpp
 * Author  : J.K
 * Date    : 2015-10-09 03:19
 * Last Modified: 2016-03-11 18:10
 * Describe: 
 *
 ************************************************/

#include <iostream>
#include <cassert>

#include <windows.h>
#include <GL/freeglut.h>

#include "Const.h"

#include "MGL.h"
#include "GL2015.h"

MGL::MGL(void) {
  initialize();
}

MGL::~MGL(void) {
  finalize();
}

MGL::MGL(const char *title) {
  initialize(title);
}

MGL::MGL(int argc, char **argv) {
  initialize(argc, argv);
}

MGL::MGL(float x_min, float x_max, float y_min, float y_max) {
  initialize();

  setRange(x_min, x_max, y_min, y_max);
}

MGL::MGL(float x_min, float x_max, 
         float y_min, float y_max, 
         float z_min, float z_max)
{
  initialize();

  setRange(x_min, x_max, y_min, y_max, z_min, z_max);
}

MGL::MGL(int argc, char **argv, 
         float x_min, float x_max, float y_min, float y_max)
{
  initialize(argc, argv);

  setRange(x_min, x_max, y_min, y_max);
}

MGL::MGL(int argc, char **argv, 
         float x_min, float x_max, 
         float y_min, float y_max, 
         float z_min, float z_max)
{
  initialize(argc, argv);

  setRange(x_min, x_max, y_min, y_max, z_min, z_max);
}

bool MGL::quit(void) {
  return GL2015::bQuit;
}

void MGL::setDimension(int d) {
  assert(2 == d || d == 3);
  GL2015::dim = d;
}

void MGL::setTitle(const char *s) {
  GL2015::displayTitle(s);
}

void MGL::setRange(float x_min, float x_max, float y_min, float y_max) {
  assert(x_min < x_max);
  assert(y_min < y_max);

  float cx = 0.5 * (x_min + x_max);
  float cy = 0.5 * (y_min + y_max);
  GL2015::translate(- cx, - cy, 0.0f);

  float dx = x_max - x_min;
  float dy = y_max - y_min;

  assert(dx > EPSILON15 && dy > EPSILON15);
  GL2015::rescale(2.0 / dx, 2.0 / dy, 1.0f);
}

void MGL::setRange(float x_min, float x_max, 
                   float y_min, float y_max, 
                   float z_min, float z_max)
{
  assert(x_min < x_max);
  assert(y_min < y_max);
  assert(z_min < z_max);

  float cx = 0.5 * (x_min + x_max);
  float cy = 0.5 * (y_min + y_max);
  float cz = 0.5 * (z_min + z_max);
  GL2015::translate(- cx, - cy, - cz);

  float dx = x_max - x_min;
  float dy = y_max - y_min;
  float dz = z_max - z_min;

  assert(dx > EPSILON15 && dy > EPSILON15 && dz > EPSILON15);
  GL2015::rescale(2.0 / dx, 2.0 / dy, 2.0 / dz);// 0.57735;
}

void MGL::setScreen(void) {
  if (GL2015::ROT == 0 && GL2015::lBtn.waitDoubleClick 
      && glutGet(GLUT_ELAPSED_TIME) > GL2015::lBtn.waitTime) {
    GL2015::rescaleAroundCenter(1.5, 
                 GL2015::lBtn.prePos[0], GL2015::lBtn.prePos[1]);
    GL2015::lBtn.clear();
  }

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  assert(!GL2015::Tap);
  glPushMatrix(); GL2015::Tap = true;

  if (GL2015::dotLine) {
    glColor3f(0.1f, 0.1f, 0.1f);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x5555);

    glBegin(GL_LINE_LOOP);
    glVertex2f(GL2015::rBtn.prePos[0], GL2015::rBtn.prePos[1]);
    glVertex2f(GL2015::rBtn.curPos[0], GL2015::rBtn.prePos[1]);
    glVertex2f(GL2015::rBtn.curPos[0], GL2015::rBtn.curPos[1]);
    glVertex2f(GL2015::rBtn.prePos[0], GL2015::rBtn.curPos[1]);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
  }

  if (GL2015::ROT != 0) {
    switch (GL2015::ROT) {
      case 1:  GL2015::rotateX( 1.0f); break;
      case 2:  GL2015::rotateY( 1.0f); break;
      case 3:  GL2015::rotateZ( 1.0f); break;
      case -1: GL2015::rotateX(-1.0f); break;
      case -2: GL2015::rotateY(-1.0f); break;
      case -3: GL2015::rotateZ(-1.0f); break;
    }
  }

  if (GL2015::extend_z) {
    GL2015::tM[3][2] -= 49.5f;
    for(int i = 0; i < 4; ++ i) GL2015::tM[i][2] /= 50.5f;
  }
  glLoadMatrixf(GL2015::tM[0]);
  if (GL2015::extend_z) {
    for(int i = 0; i < 4; ++ i) GL2015::tM[i][2] *= 50.5f;
    GL2015::tM[3][2] += 49.5f;
  }

  // glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
  // gluLookAt(0.0, 0.0, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glColor3f(0.0f, 0.0f, 0.0f);
}

void MGL::show(int ms) {
  assert(GL2015::Tap);
  glPopMatrix(); GL2015::Tap = false;

  GL2015::displayTitle();
  GL2015::displayMessage();

  glFlush();
  glutSwapBuffers();

  glutMainLoopEvent();

  Sleep(ms);
}

void MGL::initialize(void) {
  int argc = 1;
  char **argv = new char *[argc];
  for (int i = 0; i < argc; ++ i) {
    argv[i] = new char[100];

    char buffer[100] = "OpenGL Test";
    for(int j = 0; j < 100; ++ j) argv[i][j] = buffer[j];
  }

  initialize(argc, argv);

  for(int i = 0; i < argc; ++ i) delete[] argv[i];
  delete[] argv;
}

void MGL::initialize(const char *title) {
  char **argv = new char *[1];

  int max_size = 500;
  argv[0] = new char[max_size];

  int i = 0;
  while (true) {
    argv[0][i] = title[i];
    if(title[i] == '\0') break;

    if (++ i >= max_size) { 
      argv[0][-- i] = '\0';
      std::cerr << "Length of title is too long." << std::endl;
      break;
    }
  }

  initialize(1, argv);
  GL2015::displayTitle(title);

  delete[] argv[0];
  delete[] argv;
}

void MGL::initialize(int argc, char **argv, 
                     int x_pos, int y_pos, int width, int height)
{
  if (GL2015::init) {
    std::cout << "Warning: " 
              << "Can't draw two graphics in the same time." << std::endl;
    finalize();// exit(1);
  }

  if (GL2015::call_glutInit) {
    glutInit(&argc, argv);
    GL2015::call_glutInit = false;
  }

  glutInitWindowPosition(x_pos, y_pos);
  glutInitWindowSize(width, height);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  glutCreateWindow(argv[0]);

  // glutReshapeFunc(GL2015::reshapeWindow);
  GL2015::MenuID = glutCreateMenu(GL2015::processMenuEvents);
  GL2015::createMenu();

  glutKeyboardFunc(GL2015::processNormalKeys);
  glutSpecialFunc(GL2015::processSpecialKeys);

  glutMouseFunc(GL2015::processMouse);
  glutMotionFunc(GL2015::processMotionMouse);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // GL2015::init data members;
  GL2015::tM = new float *[4]; GL2015::tM0 = new float *[4];
  GL2015::tM[0] = new float[16]; GL2015::tM0[0] = new float[16];
  for(int i = 1; i < 4; ++ i) GL2015::tM[i] = GL2015::tM[i - 1] + 4;
  for(int i = 1; i < 4; ++ i) GL2015::tM0[i] = GL2015::tM0[i - 1] + 4;

  for (int i = 0; i < 4; ++ i) {
    for(int j = 0; j < 4; ++ j) GL2015::tM[i][j] = GL2015::tM0[i][j] = 0.0f;
    GL2015::tM[i][i] = GL2015::tM0[i][i] = 1.0f;
  }
  GL2015::rescale(1.0f, 1.0f, -1.0f);

  GL2015::init = true;
  GL2015::dim = 3;

  GL2015::bQuit = false;
  GL2015::Tap = false;

  GL2015::lBtn.clear();
  GL2015::rBtn.clear();

  GL2015::dotLine = false;
  GL2015::ROT = 0;

  GL2015::dispTitle = true;
  glutDisplayFunc([]() {});
}

void MGL::finalize(void) {
  if (GL2015::init) {
    if (GL2015::tM != 0) {
      delete[] GL2015::tM[0];
      delete[] GL2015::tM;
      GL2015::tM = 0;
    }
    if (GL2015::tM0 != 0) {
      delete[] GL2015::tM0[0];
      delete[] GL2015::tM0;
      GL2015::tM0 = 0;
    }

    // clear data members;
    GL2015::init = false;
    GL2015::dim = 3;

    GL2015::bQuit = false;
    GL2015::Tap = false;

    GL2015::lBtn.clear();
    GL2015::rBtn.clear();

    GL2015::dotLine = false;
    GL2015::ROT = 0;

    GL2015::dispTitle = true;
  }
}

