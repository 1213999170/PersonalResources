/*************************************************
 * Copyright (C) 2015 J.K, all rights reserved.
 *
 * Filename: GL2015.H
 * Author  : J.K
 * Date    : 2015-10-08 16:36
 * Last Modified: 2016-03-11 18:08
 * Describe: 
 *
 ************************************************/

#ifndef __GL2015_H_IS_INCLUDED__
#define __GL2015_H_IS_INCLUDED__

namespace GL2015 {
  struct MouseButton {
    bool press;

    float prePos[2];

    float curPos[2];
    float moveDist;
    
    bool waitDoubleClick;
    int waitTime;
    bool doubleClick;

    void clear(void) {
      press = false;

      prePos[0] = prePos[1] = 0.0f;

      curPos[0] = curPos[1] = 0.0f;
      moveDist = 0.0f;

      waitDoubleClick = false;
      doubleClick = false;
    }
  };

  extern bool call_glutInit;

  extern int dim;
  extern bool bQuit;

  extern bool Tap;
  extern bool init;

  extern float **tM;
  extern float **tM0;

  extern MouseButton lBtn;
  extern MouseButton rBtn;

  extern bool dotLine;
  extern int ROT;

  extern int MenuID;
  extern bool dispTitle;
  extern bool extend_z;

  void renderBitmapString(float x, float y, void *font, const char *s);
  void addFixedInfomation(float cx, float cy, 
                          const char *s, void *font, char format = 'c');

  void displayTitle(const char *s = nullptr);
  void displayMessage(const char *s = nullptr);

  void reshapeWindow(int weight, int height);

  void processMenuEvents(int option);
  void createMenu(void);

  void processNormalKeys(unsigned char key, int x, int y);
  void processSpecialKeys(int key, int x, int y);
  void processMouse(int button, int state, int x, int y);
  void processMotionMouse(int x, int y);

  void locateMousePoint(float Pt[2], int x, int y);

  void processLeftButton(int state, float Pt[2]);
  void leftButtonDoubleClickFunction(float Pt[2]);

  void processRightButton(int state, float Pt[2]);

  void storeTransMatrix(void);
  void recover(void);

  void translate(float x, float y, float z);
  void rotateX(float theta);
  void rotateY(float theta);
  void rotateZ(float theta);
  void rotate(float theta, float nx, float ny, float nz);
  void rotate(float theta, 
              float nx, float ny, float nz, 
              float rx, float ry, float rz);
  void rescale(float s);
  void rescale(float sx, float sy, float sz);

  void rescaleAroundCenter(float s, float cx, float cy);
  void rescaleAroundCenter(float s, float cx, float cy, float cz);
}

#endif //__GL2015_H_IS_INCLUDED__

