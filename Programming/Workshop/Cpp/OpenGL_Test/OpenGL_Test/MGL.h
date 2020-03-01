/*************************************************
 * Copyright (C) 2015 J.K, all rights reserved.
 *
 * Filename: MGL.H
 * Author  : J.K
 * Date    : 2015-10-09 03:18
 * Last Modified: 2015-10-12 04:14
 * Describe: 
 *
 ************************************************/

#ifndef __MGL_H_IS_INCLUDED__
#define __MGL_H_IS_INCLUDED__

#include "Graphics.h"

class MGL {
  public : 
    MGL(void);
    virtual ~MGL(void);

    MGL(const char title[]);
    MGL(int argc, char **argv);
    MGL(float x_min, float x_max, float y_min, float y_max);
    MGL(float x_min, float x_max, 
        float y_min, float y_max, 
        float z_min, float z_max);

    MGL(int argc, char **argv, 
        float x_min, float x_max, float y_min, float y_max);
    MGL(int argc, char **argv, 
        float x_min, float x_max, 
        float y_min, float y_max, 
        float z_min, float z_max);

  public : 
    bool quit(void);

    void setDimension(int d);
    void setTitle(const char *s = 0);

    void setRange(float x_min, float x_max, float y_min, float y_max);
    void setRange(float x_min, float x_max, 
                  float y_min, float y_max, 
                  float z_min, float z_max);

    void setScreen(void);
    void show(int ms = 1);

  public : 
    void initialize(void);
    void initialize(const char title[]);
    void initialize(int argc, char **argv, 
                    int x_pos = 100, int y_pos = 100, 
                    int width = 480, int height = 480);
    void finalize(void);
};

#endif //__MGL_H_IS_INCLUDED__

