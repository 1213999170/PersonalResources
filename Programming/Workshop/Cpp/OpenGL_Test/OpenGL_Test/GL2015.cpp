/*************************************************
 * Copyright (C) 2015 J.K, all rights reserved.
 *
 * Filename: GL2015.cpp
 * Author  : J.K
 * Date    : 2015-10-08 16:37
 * Last Modified: 2016-03-11 18:09
 * Describe: 
 *
 ************************************************/

#include <iostream>
#include <cassert>
#include <cmath>

#include <GL/freeglut.h>

#include "Const.h"
#include "GL2015.h"

namespace GL2015 {
  bool call_glutInit = true;

  bool init;
  int dim;

  bool bQuit;
  bool Tap;

  float **tM;
  float **tM0;

  MouseButton lBtn;
  MouseButton rBtn;

  bool dotLine;
  int ROT;

  int MenuID;
  bool dispTitle;
  bool extend_z = true;
}

void GL2015::renderBitmapString(float x, float y, void *font, const char *s) {
  if(font == GLUT_BITMAP_TIMES_ROMAN_24) glColor3f(1.0f, 0.0f, 0.0f);
  else glColor3f(0.0f, 0.0f, 0.0f);
  glRasterPos3f(x, y, 1.0f);
  for(const char *c = s; *c != '\0'; ++ c) glutBitmapCharacter(font, *c);
}

void GL2015::addFixedInfomation(float cx, float cy, 
                                const char *s, void *font, char format) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glLoadIdentity();
  if (format == 'l' || format == 'L') {
    renderBitmapString(cx, cy, font, s);
  }else {
    int len = 0;
    for (const char *p = s; *p != '\0'; ++ p) {
      len += glutBitmapWidth(font, *p);
    }

    int width = glutGet(GLUT_WINDOW_WIDTH);
    float scale = static_cast<float>(len) / width;

    if(format == 'c' || format == 'C') 
      renderBitmapString(cx - scale, cy, font, s);
    else if(format == 'r' || format == 'R')
      renderBitmapString(cx - 2 * scale, cy, font, s);
    else {
      std::cerr << "Undefined format: " << format << std::endl;
      exit(0);
    }
  }
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void GL2015::displayTitle(const char *s) {
  static bool title;
  static char buffer[100];

  if (s != nullptr) {
    int i = 0;
    for(const char *p = s; i < 99 && *p != '\0'; ++ p) buffer[i ++] = *p;
    buffer[i] = '\0';

    title = true;
  }

  if (dispTitle && title) {
    addFixedInfomation(0.0f, 0.90f, buffer, GLUT_BITMAP_TIMES_ROMAN_24, 'c');
  }
}

void GL2015::displayMessage(const char *s) {
  static int time = glutGet(GLUT_ELAPSED_TIME);
  static char buffer[100];

  if (s != nullptr) {
    time = glutGet(GLUT_ELAPSED_TIME) + 2000;

    int i = 0;
    for(const char *p = s; i < 99 && *p != '\0'; ++ p) buffer[i ++] = *p;
    buffer[i] = '\0';
  }else if (glutGet(GLUT_ELAPSED_TIME) < time) {
    addFixedInfomation(-0.95, -0.95, buffer, GLUT_BITMAP_HELVETICA_12, 'l');
  }
}

void GL2015::reshapeWindow(int width, int height) {
  // if(height == 0) height = 1;
  // float ratio = static_cast<float>(width) / height;

  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // glViewport(0, 0, width, height);
  // gluPerspective(90, ratio, 1.0, 3.0);
  // glMatrixMode(GL_MODELVIEW);
}

void GL2015::processMenuEvents(int option) {
  switch (option) {
    case 1 : recover(); break;
    case 2 : 
      if (dim == 2) {
        dim = 3;
        displayMessage("dim = 3");
      }else {
        dim = 2;
        displayMessage("dim = 2");
      }
      break;
    case 3 : dispTitle = !dispTitle; break;
    case 4 : rescale(-1.0f, 1.0f, 1.0f); break;
    case 5 : rescale(1.0f, -1.0f, 1.0f); break;
    case 6 : rescale(1.0f, 1.0f, -1.0f); break;
    case 7 : 
      if(extend_z) displayMessage("reduce z-depth");
      else displayMessage("extend z-depth");

      extend_z = !extend_z;
      break;

    default : displayMessage("Read ~/private/GraphicsLibrary/gl_note.txt");
  }
}

void GL2015::createMenu(void) {
  glutAddMenuEntry("help",                   0);
  glutAddMenuEntry("recover",                1);
  glutAddMenuEntry("toggle dimension",       2);
  glutAddMenuEntry("toggle show title",      3);
  glutAddMenuEntry("reverse left and right", 4);
  glutAddMenuEntry("upside down",            5);
  glutAddMenuEntry("reverse depth",          6);
  glutAddMenuEntry("toggle z-depth",         7);

  glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void GL2015::processNormalKeys(unsigned char key, int x, int y) {
  if (ROT != 0) {
    if(key == 27) bQuit = true;
    return;
  }

  int mod = glutGetModifiers();
  switch (key) {
    // Key ESC:
    case 27: bQuit = true; break;
    // Key BackSpace: 
    case 8: recover(); break;
    // Key Space:
    case 32: 
      if(mod == GLUT_ACTIVE_SHIFT) rescale(0.6666f);
      else rescale(1.5f);
      break;

    case 'W': case 'w':
      if(mod == GLUT_ACTIVE_SHIFT) rescale(1.0f, 1.25f, 1.0f);
      else translate(0.0f, 0.1f, 0.0f);
      break;
    case 'S': case 's':
      if(mod == GLUT_ACTIVE_SHIFT) rescale(1.0f, 0.8f, 1.0f); 
      else translate(0.0f, -0.1f, 0.0f);
      break;
    case 'A': case 'a':
      if(mod == GLUT_ACTIVE_SHIFT) rescale(0.8f, 1.0f, 1.0f); 
      else translate(-0.1f, 0.0f, 0.0f);
      break;
    case 'D': case 'd':
      if(mod == GLUT_ACTIVE_SHIFT) rescale(1.25f, 1.0f, 1.0f);
      else translate(0.1f, 0.0f, 0.0f);
      break;
    case 'R': case 'r': translate(0.0f, 0.0f, 0.1f); break;
    case 'E': case 'e': translate(0.0f, 0.0f, -0.1f); break;

    case 'J': case 'j': rotateY(-2.0); break;
    case 'K': case 'k': rotateY(2.0); break;
    case 'U': case 'u': rotateX(-2.0); break;
    case 'M': case 'm': rotateX(2.0); break;
    case 'O': case 'o': rotateZ(-2.0); break;
    case 'I': case 'i': rotateZ(2.0); break;

    default : displayMessage("Undefined Key Operator");
  }
}

void GL2015::processSpecialKeys(int key, int x, int y) {
  if (ROT != 0) {
    if(key == 27) bQuit = true;
    return;
  }

  int mod = glutGetModifiers();
  if (mod == GLUT_ACTIVE_SHIFT) {
    switch (key) {
      case GLUT_KEY_UP    : rescale(1.0f, 1.25f, 1.0f); break;
      case GLUT_KEY_DOWN  : rescale(1.0f, 0.8f, 1.0f);  break;
      case GLUT_KEY_LEFT  : rescale(0.8f, 1.0f, 1.0f);  break;
      case GLUT_KEY_RIGHT : rescale(1.25f, 1.0f, 1.0f); break;
    }
  }else {
    switch (key) {
      case GLUT_KEY_UP    : translate(0.0f, 0.1f, 0.0f);  break;
      case GLUT_KEY_DOWN  : translate(0.0f, -0.1f, 0.0f); break;
      case GLUT_KEY_LEFT  : translate(-0.1f, 0.0f, 0.0f); break;
      case GLUT_KEY_RIGHT : translate(0.1f, 0.0f, 0.0f);  break;
    }
  }
}

void GL2015::processMouse(int button, int state, int x, int y) {
  float Pt[2];
  locateMousePoint(Pt, x, y);

  switch (button) {
    case GLUT_LEFT_BUTTON  : processLeftButton(state, Pt);  break;
    case GLUT_RIGHT_BUTTON : if(ROT == 0) processRightButton(state, Pt); break;
    default : displayMessage("Undefined Mouse Operator");
  }
}

void GL2015::processMotionMouse(int x, int y) {
  if(ROT != 0) return;

  float Pt[2];
  locateMousePoint(Pt, x, y);

  if (lBtn.press) {
    float dx = Pt[0] - lBtn.curPos[0];
    float dy = Pt[1] - lBtn.curPos[1];
    translate(dx, dy, 0.0f);

    lBtn.curPos[0] = Pt[0]; lBtn.curPos[1] = Pt[1];
    lBtn.moveDist += fabs(dx) + fabs(dy);
  }else if (rBtn.press) {
    if(dim == 2) dotLine = true;
    else {
      float rPt[2];
      rPt[0] = rBtn.curPos[0]; rPt[1] = rBtn.curPos[1];

      float nx = rPt[1] - Pt[1];
      float ny = Pt[0] - rPt[0];
      float nz = rPt[0] * Pt[1] - Pt[0] * rPt[1];
      
      float a = sqrt(rPt[0] * rPt[0] + rPt[1] * rPt[1] + 1.0f);
      float b = sqrt(Pt[0] * Pt[0] + Pt[1] * Pt[1] + 1.0f);

      float theta = acos((rPt[0] * Pt[0] + rPt[1] * Pt[1] + 1.0f) / (a * b));
      rotate(180.0f / M_PI * theta, nx, ny, nz);
    }

    float dx = Pt[0] - rBtn.curPos[0];
    float dy = Pt[1] - rBtn.curPos[1];
    rBtn.moveDist += fabs(dx) + fabs(dy);
    rBtn.curPos[0] = Pt[0]; rBtn.curPos[1] = Pt[1];
  }
}

void GL2015::locateMousePoint(float Pt[2], int x, int y) {
  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);

  Pt[0] = 2.0f * x / width - 1.0f;
  Pt[1] = 1.0f - 2.0f * y / height;
}

void GL2015::processLeftButton(int state, float Pt[2]) {
  if (state == GLUT_DOWN) {
    rBtn.clear();

    lBtn.press = true;
    lBtn.prePos[0] = Pt[0]; lBtn.prePos[1] = Pt[1];
    lBtn.curPos[0] = Pt[0]; lBtn.curPos[1] = Pt[1];
    lBtn.moveDist = 0.0f;

    if(lBtn.waitDoubleClick) lBtn.doubleClick = true;
  }else if (lBtn.press) {
    if (lBtn.doubleClick) {
      leftButtonDoubleClickFunction(Pt);
      lBtn.clear();
    }else {
      float dx = Pt[0] - lBtn.curPos[0];
      float dy = Pt[1] - lBtn.curPos[1];
      lBtn.moveDist += fabs(dx) + fabs(dy);

      if (lBtn.moveDist > 0.01f) {
        if(ROT == 0) translate(dx, dy, 0.0f);
        lBtn.clear();
      }else {
        lBtn.waitDoubleClick = true;
        lBtn.waitTime = glutGet(GLUT_ELAPSED_TIME) + 250;
      }
    }
  }
}

void GL2015::leftButtonDoubleClickFunction(float Pt[2]) {
  if (dim == 3) {
    if (ROT == 0) {
      if (fabs(Pt[0]) < 0.5 && fabs(Pt[1]) < 0.5) {
        if(Pt[0] > 0) ROT = -3;
        else ROT = 3;
      }else if (Pt[0] > Pt[1]) {
        if(Pt[0] + Pt[1] > 0) ROT = 2;
        else ROT = 1;
      }else {
        if(Pt[0] + Pt[1] > 0) ROT = -1;
        else ROT = -2;
      }
    }else ROT = 0;
  }
}

void GL2015::processRightButton(int state, float Pt[2]) {
  if (state == GLUT_DOWN) {
    lBtn.clear();

    rBtn.press = true;
    rBtn.prePos[0] = Pt[0]; rBtn.prePos[1] = Pt[1];
    rBtn.curPos[0] = Pt[0]; rBtn.curPos[1] = Pt[1];
    rBtn.moveDist = 0.0f;
  }else if (rBtn.press) {
    float dx = Pt[0] - rBtn.curPos[0];
    float dy = Pt[1] - rBtn.curPos[1];
    rBtn.moveDist += fabs(dx) + fabs(dy);

    if(rBtn.moveDist < 0.01f) rescaleAroundCenter(0.666, Pt[0], Pt[1]);
    else if (dim == 2) {
      float cx = 0.5 * (rBtn.prePos[0] + Pt[0]);
      float cy = 0.5 * (rBtn.prePos[1] + Pt[1]);
      dx = fabs(Pt[0] - rBtn.prePos[0]);
      dy = fabs(Pt[1] - rBtn.prePos[1]);
      float wid = dx > dy? dx: dy;

      if (wid > 0.06) {
        translate(- cx, - cy, 0.0f);
        rescale(2.0 / wid);
      }
    }else {
      float rPt[2];
      rPt[0] = rBtn.curPos[0]; rPt[1] = rBtn.curPos[1];

      float nx = rPt[1] - Pt[1];
      float ny = Pt[0] - rPt[0];
      float nz = rPt[0] * Pt[1] - Pt[0] * rPt[1];

      float a = sqrt(rPt[0] * rPt[0] + rPt[1] * rPt[1] + 1.0f);
      float b = sqrt(Pt[0] * Pt[0] + Pt[1] * Pt[1] + 1.0f);

      float theta = acos((rPt[0] * Pt[0] + rPt[1] * Pt[1] + 1.0f) / (a * b));
      rotate(180.0f / M_PI * theta, nx, ny, nz);
    }

    dotLine = false;
    rBtn.clear();
  }
}

void GL2015::storeTransMatrix(void) {
  for(int i = 0; i < 16; ++ i) tM0[0][i] = tM[0][i];
}

void GL2015::recover(void) {
  for(int i = 0; i < 16; ++ i) tM[0][i] = tM0[0][i];
}

void GL2015::translate(float x, float y, float z) {
  storeTransMatrix();

  tM[3][0] += x;
  tM[3][1] += y;
  tM[3][2] -= z;
}

void GL2015::rotateX(float theta) {
  storeTransMatrix();

  theta *= M_PI / 180.0f;

  float cs = cos(theta);
  float sn = - sin(theta);// Axis Z is on opposite direction;

  for (int i = 0; i < 4; ++ i) {
    float t0 = tM[i][1] * cs - tM[i][2] * sn;
    float t1 = tM[i][1] * sn + tM[i][2] * cs;

    tM[i][1] = t0;
    tM[i][2] = t1;
  }
}

void GL2015::rotateY(float theta) {
  storeTransMatrix();

  theta *= M_PI / 180.0f;

  float cs = cos(theta);
  float sn = - sin(theta);// Axis Z is on opposite direction;

  for (int i = 0; i < 4; ++ i) {
    float t0 = tM[i][2] * cs - tM[i][0] * sn;
    float t1 = tM[i][2] * sn + tM[i][0] * cs;

    tM[i][2] = t0;
    tM[i][0] = t1;
  }
}

void GL2015::rotateZ(float theta) {
  storeTransMatrix();

  theta *= M_PI / 180.0f;

  float cs = cos(theta);
  float sn = sin(theta);

  for (int i = 0; i < 4; ++ i) {
    float t0 = tM[i][0] * cs - tM[i][1] * sn;
    float t1 = tM[i][0] * sn + tM[i][1] * cs;

    tM[i][0] = t0;
    tM[i][1] = t1;
  }
}

void GL2015::rotate(float theta, float nx, float ny, float nz) {
  float r = sqrt(nx * nx + ny * ny + nz * nz);
  if(r < EPSILON) return;

  storeTransMatrix();

  theta *= M_PI / 180.0f;
  float a = - nx / r, b = - ny / r, c = nz / r;

  float cs = cos(theta), cs_t = 1.0 - cs;
  float sn = sin(theta);
  float ab = a * b, bc = b * c, ca = c * a;

  float rM[3][3];
  rM[0][0] = cs + a * a * cs_t;
  rM[0][1] = c * sn + ab * cs_t;
  rM[0][2] = - b * sn + ca * cs_t;

  rM[1][0] = - c * sn + ab * cs_t;
  rM[1][1] = cs + b * b * cs_t;
  rM[1][2] = a * sn + bc * cs_t;

  rM[2][0] = b * sn + ca * cs_t;
  rM[2][1] = - a * sn + bc * cs_t;
  rM[2][2] = cs + c * c * cs_t;

  float mt[4][3];
  for (int i = 0; i < 4; ++ i) {
    for (int j = 0; j < 3; ++ j) {
      mt[i][j] = 0.0;
      for(int k = 0; k < 3; ++ k) mt[i][j] += tM[i][k] * rM[k][j];
    }
  }

  for (int i = 0; i < 4; ++ i) {
    for(int j = 0; j < 3; ++ j) tM[i][j] = mt[i][j];
  }
}

void GL2015::rotate(float theta, 
            float nx, float ny, float nz, 
            float rx, float ry, float rz)
{
  translate(- rx, - ry, - rz);
  rotate(theta, nx, ny, nz);
  translate(rx, ry, rz);
}

void GL2015::rescale(float s) {
  storeTransMatrix();

  assert(s > 0);
  if (s < EPSILON) {
    std::cout << "Warning: scale s is very small." << std::endl;
  }else if (s > 1.0E8) {
    std::cout << "Warning: scale s is very large." << std::endl;
  }

  for (int i = 0; i < 4; ++ i) {
    for(int j = 0; j < 3; ++ j) tM[i][j] *= s;
  }
}

void GL2015::rescale(float sx, float sy, float sz) {
  storeTransMatrix();

  if (fabs(sx) < EPSILON) {
    std::cout << "Warning: scale sx is very small." << std::endl;
  }else if (fabs(sx) > 1.0E8) {
    std::cout << "Warning: scale sx is very large." << std::endl;
  }
  if (fabs(sy) < EPSILON) {
    std::cout << "Warning: scale sy is very small." << std::endl;
  }else if (fabs(sy) > 1.0E8) {
    std::cout << "Warning: scale sy is very large." << std::endl;
  }
  if (fabs(sz) < EPSILON) {
    std::cout << "Warning: scale sz is very small." << std::endl;
  }else if (fabs(sz) > 1.0E8) {
    std::cout << "Warning: scale sz is very large." << std::endl;
  }

  for (int i = 0; i < 4; ++ i) {
    tM[i][0] *= sx;
    tM[i][1] *= sy;
    tM[i][2] *= sz;
  }
}

void GL2015::rescaleAroundCenter(float s, float cx, float cy) {
  storeTransMatrix();

  assert(s > EPSILON);

  tM[3][0] -= cx; tM[3][1] -= cy;
  for (int i = 0; i < 4; ++ i) {
    for(int j = 0; j < 3; ++ j) tM[i][j] *= s;
  }
  tM[3][0] += cx; tM[3][1] += cy;
}

void GL2015::rescaleAroundCenter(float s, float cx, float cy, float cz) {
  storeTransMatrix();

  assert(s > EPSILON);

  tM[3][0] -= cx; tM[3][1] -= cy; tM[3][2] += cz;
  for (int i = 0; i < 4; ++ i) {
    for(int j = 0; j < 3; ++ j) tM[i][j] *= s;
  }
  tM[3][0] += cx; tM[3][1] += cy; tM[3][2] -= cz;
}

