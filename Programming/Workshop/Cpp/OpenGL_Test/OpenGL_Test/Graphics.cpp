#include <GL/freeglut.h>
#include <cassert>

#include "Const.h"
#include "Graphics.h"

/***************************
 * Plot Scatter Diagram
 *
 ***************************/

void plotPoints(double *x, double *y, int N, bool coord) {
  if(N <= 0) return;

  glPointSize(5.0);
  glBegin(GL_POINTS);
  for(int i = 0; i < N; i ++) glVertex2d(x[i], y[i]);
  glEnd();

  if(coord) plotCoordinateSystem(x, N, y, N);
}

void plotPoints(double (*node)[2], int N, bool coord) {
  if(N <= 0) return;

  glPointSize(5.0);
  glBegin(GL_POINTS);
  for(int i = 0; i < N; i ++) glVertex2d(node[i][0], node[i][1]);
  glEnd();
  
  if (coord) {
    double *x = new double[N], *y = new double[N];
    for (int i = 0; i < N; i ++) {
      x[i] = node[i][0]; y[i] = node[i][1];
    }
    
    plotCoordinateSystem(x, N, y, N);
    
    delete[] x; delete[] y;
  }
}

void plotPoints(std::complex<double> *z, int N, bool coord) {
  if(N <= 0) return;

  glPointSize(5.0);
  glBegin(GL_POINTS);
  for(int i = 0; i < N; i ++) glVertex2d(z[i].real(), z[i].imag());
  glEnd();

  if (coord) {
    double *x = new double[N], *y = new double[N];
    for (int i = 0; i < N; i ++) {
      x[i] = z[i].real(); y[i] = z[i].imag();
    }

    plotCoordinateSystem(x, N, y, N);

    delete[] x; delete[] y;
  }
}

void plotPoints(double *x, double *y, double *z, int N, bool coord) {
  if(N <= 0) return;

  double z_max = z[0], z_min = z[0];
  for (int i = 1; i < N; i ++) {
    if(z[i] > z_max) z_max = z[i];
    else if(z[i] < z_min) z_min = z[i];
  }
  double wid = 0.5 * (z_max - z_min);
  
  glPointSize(5.0);
  glBegin(GL_POINTS);
  
  for (int i = 0; i < N; i ++) {
    double c = (z[i] - z_min) / wid;
    double c1, c2, c3;
    if(c < 1) {c1 = 0.0; c2 = c; c3 = 1.0 - c;}
    else {c1 = c - 1.0; c2 = 2.0 - c; c3 = 0.0;}
    
    glColor3d(c1, c2, c3);
    glVertex3d(x[i], y[i], z[i]);
  }
  
  glEnd();

  if(coord) plotCoordinateSystem(x, N, y, N, z, N);
}


/***************************
 * Plot Line
 *
 ***************************/

void plot(double *x, double *y, int N, bool coord)
{
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < N; i ++) glVertex2d(x[i], y[i]);
  glEnd();

  if(coord) plotCoordinateSystem(x, N, y, N);
}

void plot(double *x, double *y, double *z, int N, bool coord)
{
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < N; i ++) glVertex3d(x[i], y[i], z[i]);
  glEnd();

  if(coord) plotCoordinateSystem(x, N, y, N, z, N);
}

void plot(double (*node)[2], int N, bool coord)
{
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < N; i ++) glVertex2d(node[i][0], node[i][1]);
  glEnd();

  if(coord) plotCoordinateSystem(node, N);
}


/***************************
 * Plot Triangle
 *
 ***************************/

void plotTriangle(double x0, double y0,
                  double x1, double y1,
                  double x2, double y2)
{
  glBegin(GL_LINE_LOOP);
  
  glVertex2d(x0, y0);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  
  glEnd();
}

void plotTriangle(double A[2], double B[2], double C[2])
{
  glBegin(GL_LINE_LOOP);
  
  glVertex2d(A[0], A[1]);
  glVertex2d(B[0], B[1]);
  glVertex2d(C[0], C[1]);
  
  glEnd();
}

void plotTriangle(double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2)
{
  glBegin(GL_LINE_LOOP);
  
  glVertex3d(x0, y0, z0);
  glVertex3d(x1, y1, z1);
  glVertex3d(x2, y2, z2);
  
  glEnd();
}

void plotTriangle3D(double A[3], double B[3], double C[3])
{
  glBegin(GL_LINE_LOOP);

  glVertex3d(A[0], A[1], A[2]);
  glVertex3d(B[0], B[1], B[2]);
  glVertex3d(C[0], C[1], C[2]);
  
  glEnd();
}


/***************************
 * Plot Rectangle
 *
 ***************************/

void plotRectangle(double lo[2], double hi[2])
{
  glBegin(GL_LINE_LOOP);

  glVertex2d(lo[0], lo[1]);
  glVertex2d(hi[0], lo[1]);
  glVertex2d(hi[0], hi[1]);
  glVertex2d(lo[0], hi[1]);

  glEnd();
}

void plotRectangle(double xlo, double ylo,
                   double xhi, double yhi)
{
  glBegin(GL_LINE_LOOP);

  glVertex2d(xlo, ylo);
  glVertex2d(xhi, ylo);
  glVertex2d(xhi, yhi);
  glVertex2d(xlo, yhi);
  
  glEnd();
}


/***************************
 * Plot Quadrangle
 *
 ***************************/

void plotQuadrangle(double x0, double y0,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3)
{
  glBegin(GL_LINE_LOOP);

  glVertex2d(x0, y0);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  glVertex2d(x3, y3);
  
  glEnd();
}

void plotQuadrangle(double A[2], double B[2],
                    double C[2], double D[2])
{
  glBegin(GL_LINE_LOOP);

  glVertex2d(A[0], A[1]);
  glVertex2d(B[0], B[1]);
  glVertex2d(C[0], C[1]);
  glVertex2d(D[0], D[1]);
  
  glEnd();
}

void plotQuadrangle(double x0, double y0, double z0,
                    double x1, double y1, double z1,
                    double x2, double y2, double z2,
                    double x3, double y3, double z3)
{
  glBegin(GL_LINE_LOOP);

  glVertex3d(x0, y0, z0);
  glVertex3d(x1, y1, z1);
  glVertex3d(x2, y2, z2);
  glVertex3d(x3, y3, z3);
  
  glEnd();
}

void plotQuadrangle3D(double A[3], double B[3],
                      double C[3], double D[3])
{
  glBegin(GL_LINE_LOOP);

  glVertex3d(A[0], A[1], A[2]);
  glVertex3d(B[0], B[1], B[2]);
  glVertex3d(C[0], C[1], C[2]);
  glVertex3d(D[0], D[1], D[2]);

  glEnd();
}


/***************************
 * Plot Circle
 *
 ***************************/

void plotCircle(double ctr_x, double ctr_y, double r)
{
  glBegin(GL_LINE_LOOP);
  
  int N = static_cast<int>(M_2PI * r / 0.01);
  if(N < 600) N = 600;
  double dt = M_2PI / N;
  double cs = cos(dt), sn = sin(dt);
  
  double cs0 = r, sn0 = 0.0;
  for (int i = 0; i < N; i ++) {
    glVertex2d(cs0 + ctr_x, sn0 + ctr_y);
    
    double cs1 = cs0 * cs - sn0 * sn;
    double sn1 = sn0 * cs + cs0 * sn;
    cs0 = cs1; sn0 = sn1;
  }
  
  glEnd();
}

void plotCircle(double ctr_x, double ctr_y, double ctr_z,
                double nx, double ny, double nz, double r)
{
  glBegin(GL_LINE_LOOP);

  double t1x, t1y, t1z;
  if (fabs(nx) < EPSILON) {
    t1x = 1.0; t1y = 0.0; t1z = 0.0;
  }else {
    t1x = ny; t1y = - nx; t1z = 0.0;
  }
  
  double t2x, t2y, t2z;
  t2x = - nz * t1y; t2y = nz * t1x; t2z = nx * t1y - ny * t1x;
  
  double r1 = sqrt(t1x * t1x + t1y * t1y + t1z * t1z);
  double r2 = sqrt(t2x * t2x + t2y * t2y + t2z * t2z);
  
  double s1 = r / r1;
  double s2 = r / r2;
  
  t1x *= s1; t1y *= s1; t1z *= s1;
  t2x *= s2; t2y *= s2; t2z *= s2;
  
  int N = static_cast<int>(M_2PI * r / 0.01);
  if(N < 600) N = 600;
  double dt = M_2PI / N;
  
  double theta = 0.0;
  for (int i = 0; i < N; i ++) {
    double cs = cos(theta);
    double sn = sin(theta);
    
    double px = t1x * cs + t2x * sn + ctr_x;
    double py = t1y * cs + t2y * sn + ctr_y;
    double pz = t1z * cs + t2z * sn + ctr_z;
    
    glVertex3d(px, py, pz);
    
    theta += dt;
  }
  
  glEnd();
}


/***************************
 * Plot Ball (= Draw Ball)
 *
 ***************************/

void plotBall(double r) {
  plotBall(0.0, 0.0, 0.0, r);
}  

void plotBall(double ctr_x, double ctr_y, double ctr_z, double r)
{
  drawBall(ctr_x, ctr_y, ctr_z, r);
}


/***************************
 * Plot Cube (= Draw Cube)
 *
 ***************************/

void plotCube(double x0, double y0, double z0,
              double x1, double y1, double z1,
              double x2, double y2, double z2,
              double x3, double y3, double z3)
{
  drawCube(x0, y0, z0,
           x1, y1, z1,
           x2, y2, z2,
           x3, y3, z3);
}


/***************************
 * Plot Coordinate System
 *
 ***************************/

void plotCoordinateSystem(double x[2], double y[2])
{
  glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(4, 0x5555);
  glBegin(GL_LINES);

  int meshNumber = 5;
  double dx = (x[1] - x[0]) / meshNumber;
  double dy = (y[1] - y[0]) / meshNumber;
  
  double x_max = x[1], y_max = y[1];
  if (dx < 10 * dy && dy < 10 * dx) {
    if (dx < dy) {
      dy = dx;
      y_max = y[0] + dy * static_cast<int>((y[1] - y[0]) / dy + 1);
    }else {
      dx = dy;
      x_max = x[0] + dx * static_cast<int>((x[1] - x[0]) / dx + 1);
    }
  }

  double xt = x[0] - 0.01 * dx;
  while (xt <= x_max) {
    glVertex2d(xt, y[0]); glVertex2d(xt, y_max);
    xt += dx;
  }

  double yt = y[0] - 0.01 * dy;
  while (yt <= y_max) {
    glVertex2d(x[0], yt); glVertex2d(x_max, yt);
    yt += dy;
  }

  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void plotCoordinateSystem(double x0, double x1, double y0, double y1)
{
  glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(4, 0x5555);
  glBegin(GL_LINES);

  int meshNumber = 5;
  double dx = (x1 - x0) / meshNumber;
  double dy = (y1 - y0) / meshNumber;

  double x_max = x1, y_max = y1;
  if (dx < 10 * dy && dy < 10 * dx) {
    if (dx < dy) {
      dy = dx;
      y_max = y0 + dy * static_cast<int>((y1 - y0) / dy + 1);
    }else {
      dx = dy;
      x_max = x0 + dx * static_cast<int>((x1 - x0) / dx + 1);
    }
  }
  
  double xt = x0 - 0.01 * dx;
  while (xt <= x_max) {
    glVertex2d(xt, y0); glVertex2d(xt, y_max);
    xt += dx;
  }

  double yt = y0 - 0.01 * dy;
  while (yt <= y_max) {
    glVertex2d(x0, yt); glVertex2d(x_max, yt);
    yt += dy;
  }

  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void plotCoordinateSystem(double *x, int M, double y[2])
{
  double xt[2] = {x[0], x[0]};
  for (int i = 1; i < M; i ++) {
    if(x[i] < xt[0]) xt[0] = x[i];
    else if(x[i] > xt[1]) xt[1] = x[i];
  }

  double dx = 0.2 * (xt[1] - xt[0]);
  xt[0] -= dx; xt[1] += dx;

  plotCoordinateSystem(xt, y);
}

void plotCoordinateSystem(double *x, int M, double *y, int N)
{
  double xt[2] = {x[0], x[0]};
  for (int i = 1; i < M; i ++) {
    if(x[i] < xt[0]) xt[0] = x[i];
    else if(x[i] > xt[1]) xt[1] = x[i];
  }

  double dx = 0.2 * (xt[1] - xt[0]);
  xt[0] -= dx; xt[1] += dx;

  double yt[2] = {y[0], y[0]};
  for (int i = 1; i < N; i ++) {
    if(y[i] < yt[0]) yt[0] = y[i];
    else if(y[i] > yt[1]) yt[1] = y[i];
  }

  double dy = 0.2 * (yt[1] - yt[0]);
  yt[0] -= dy; yt[1] += dy;

  plotCoordinateSystem(xt, yt);
}

void plotCoordinateSystem(double (*node)[2], int N)
{
  double xt[2] = {node[0][0], node[0][0]};
  double yt[2] = {node[0][1], node[0][1]};
  
  for (int i = 1; i < N; i ++) {
    if(node[i][0] < xt[0]) xt[0] = node[i][0];
    else if(node[i][0] > xt[1]) xt[1] = node[i][0];
    
    if(node[i][1] < yt[0]) yt[0] = node[i][1];
    else if(node[i][1] > yt[1]) yt[1] = node[i][1];
  }
  
  double dx = 0.2 * (xt[1] - xt[0]);
  xt[0] -= dx; xt[1] += dx;
  double dy = 0.2 * (yt[1] - yt[0]);
  yt[0] -= dy; yt[1] += dy;
  
  plotCoordinateSystem(xt, yt);
}

void plotCoordinateSystem(double x[2], double y[2], double z[2])
{
  glColor3f(0.0f, 0.0f, 0.0f);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(4, 0x5555);
  glBegin(GL_LINES);
  
  int meshNumber = 10;
  double dx = (x[1] - x[0]) / meshNumber;
  double dy = (y[1] - y[0]) / meshNumber;
  double dz = (z[1] - z[0]) / meshNumber;
  double dh = dx < dy? (dx < dz? dx: dz): (dy < dz? dy: dz);

  double x_max = x[1], y_max = y[1], z_max = z[1];
  if (dx < 10.0 * dh && dy < 10.0 * dh && dz < 10.0 * dh) {
    dx = dh; dy = dh; dz = dh;
    x_max = x[0] + dx * static_cast<int>((x[1] - x[0]) / dx + 1);
    y_max = y[0] + dy * static_cast<int>((y[1] - y[0]) / dy + 1);
    z_max = z[0] + dz * static_cast<int>((z[1] - z[0]) / dz + 1);
  }

  double xt = x[0] - 0.01 * dx;
  while (xt < x_max) {
    glVertex3d(xt, y[0], z[0]); glVertex3d(xt, y_max, z[0]);
    glVertex3d(xt, y[0], z[0]); glVertex3d(xt, y[0], z_max);
    xt += dx;
  }
  
  double yt = y[0] - 0.01 * dy;
  while (yt < y_max) {
    glVertex3d(x[0], yt, z[0]); glVertex3d(x[0], yt, z_max);
    glVertex3d(x[0], yt, z[0]); glVertex3d(x_max, yt, z[0]);
    yt += dy;
  }
  
  double zt = z[0] - 0.01 * dz;
  while (zt < z_max) {
    glVertex3d(x[0], y[0], zt); glVertex3d(x_max, y[0], zt);
    glVertex3d(x[0], y[0], zt); glVertex3d(x[0], y_max, zt);
    zt += dz;
  }

  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void plotCoordinateSystem(double *x, int M, double *y, int N, double z[2])
{
  double xt[2] = {x[0], x[0]};
  for (int i = 1; i < M; i ++) {
    if(x[i] < xt[0]) xt[0] = x[i];
    else if(x[i] > xt[1]) xt[1] = x[i];
  }

  double dx = 0.2 * (xt[1] - xt[0]);
  xt[0] -= dx; xt[1] += dx;

  double yt[2] = {y[0], y[0]};
  for (int i = 1; i < N; i ++) {
    if(y[i] < yt[0]) yt[0] = y[i];
    else if(y[i] > yt[0]) yt[1] = y[i];
  }

  double dy = 0.2 * (yt[1] - yt[0]);
  yt[0] -= dy; yt[1] += dy;
  
  plotCoordinateSystem(xt, yt, z);
}

void plotCoordinateSystem(double *x, int M,
                          double *y, int N,
                          double *z, int L)
{
  double xt[2] = {x[0], x[0]};
  for (int i = 1; i < M; i ++) {
    if(x[i] < xt[0]) xt[0] = x[i];
    else if(x[i] > xt[1]) xt[1] = x[i];
  }

  double dx = 0.2 * (xt[1] - xt[0]);
  xt[0] -= dx; xt[1] += dx;

  double yt[2] = {y[0], y[0]};
  for (int i = 1; i < N; i ++) {
    if(y[i] < yt[0]) yt[0] = y[i];
    else if(y[i] > yt[0]) yt[1] = y[i];
  }

  double dy = 0.2 * (yt[1] - yt[0]);
  yt[0] -= dy; yt[1] += dy;

  double zt[2] = {z[0], z[0]};
  for (int i = 1; i < L; i ++) {
    if(z[i] < zt[0]) zt[0] = z[i];
    else if(z[i] > zt[0]) zt[1] = z[i];
  }

  double dz = 0.2 * (zt[1] - zt[0]);
  zt[0] -= dz; zt[1] += dz;

  plotCoordinateSystem(xt, yt, zt);
}

/***************************
 * Draw Triangle
 *
 ***************************/

void drawTriangle(double x0, double y0,
                  double x1, double y1,
                  double x2, double y2)
{
  glBegin(GL_TRIANGLES);

  glVertex2d(x0, y0);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);

  glEnd();
}

void drawTriangle(double A[2], double B[2], double C[2])
{
  glBegin(GL_TRIANGLES);

  glVertex2d(A[0], A[1]);
  glVertex2d(B[0], B[1]);
  glVertex2d(C[0], C[1]);

  glEnd();
}

void drawTriangle(double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2)
{
  glBegin(GL_TRIANGLES);

  glVertex3d(x0, y0, z0);
  glVertex3d(x1, y1, z1);
  glVertex3d(x2, y2, z2);

  glEnd();
}

void drawTriangle3D(double A[3], double B[3], double C[3])
{
  glBegin(GL_TRIANGLES);

  glVertex3d(A[0], A[1], A[2]);
  glVertex3d(B[0], B[1], B[2]);
  glVertex3d(C[0], C[1], C[2]);

  glEnd();
}


/***************************
 * Draw Rectangle
 *
 ***************************/

void drawRectangle(double lo[2], double hi[2])
{
  glBegin(GL_QUADS);

  glVertex2d(lo[0], lo[1]);
  glVertex2d(hi[0], lo[1]);
  glVertex2d(hi[0], hi[1]);
  glVertex2d(lo[0], hi[1]);

  glEnd();
}

void drawRectangle(double xlo, double ylo,
                   double xhi, double yhi)
{
  glBegin(GL_QUADS);

  glVertex2d(xlo, ylo);
  glVertex2d(xhi, ylo);
  glVertex2d(xhi, yhi);
  glVertex2d(xlo, yhi);

  glEnd();
}


/***************************
 * Draw Quadrangle
 *
 ***************************/

void drawQuadrangle(double x0, double y0,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3)
{
  glBegin(GL_QUADS);

  glVertex2d(x0, y0);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  glVertex2d(x3, y3);

  glEnd();
}

void drawQuadrangle(double A[2], double B[2],
                    double C[2], double D[2])
{
  glBegin(GL_QUADS);

  glVertex2d(A[0], A[1]);
  glVertex2d(B[0], B[1]);
  glVertex2d(C[0], C[1]);
  glVertex2d(D[0], D[1]);

  glEnd();
}

void drawQuadrangle(double x0, double y0, double z0,
                    double x1, double y1, double z1,
                    double x2, double y2, double z2,
                    double x3, double y3, double z3)
{
  glBegin(GL_QUADS);

  glVertex3d(x0, y0, z0);
  glVertex3d(x1, y1, z1);
  glVertex3d(x2, y2, z2);
  glVertex3d(x3, y3, z3);

  glEnd();
}

void drawQuadrangle3D(double A[3], double B[3],
                      double C[3], double D[3])
{
  glBegin(GL_QUADS);

  glVertex3d(A[0], A[1], A[2]);
  glVertex3d(B[0], B[1], B[2]);
  glVertex3d(C[0], C[1], C[2]);
  glVertex3d(D[0], D[1], D[2]);

  glEnd();
}


/***************************
 * Draw Circle
 *
 ***************************/

void drawCircle(double ctr_x, double ctr_y, double r)
{
  glBegin(GL_POLYGON);

  int N = static_cast<int>(M_2PI * r / 0.01);
  if(N < 600) N = 600;
  double dt = M_2PI / N;
  double cs = cos(dt), sn = sin(dt);

  double cs0 = r, sn0 = 0.0;
  for (int i = 0; i < N; i ++) {
    glVertex2d(cs0 + ctr_x, sn0 + ctr_y);

    double cs1 = cs0 * cs - sn0 * sn;
    double sn1 = sn0 * cs + cs0 * sn;
    cs0 = cs1; sn0 = sn1;
  }

  glEnd();
}

void drawCircle(double ctr_x, double ctr_y, double ctr_z,
                double nx, double ny, double nz, double r)
{
  glBegin(GL_POLYGON);

  double t1x, t1y, t1z;
  if (fabs(nx) < EPSILON) {
    t1x = 1.0; t1y = 0.0; t1z = 0.0;
  }else {
    t1x = ny; t1y = - nx; t1z = 0.0;
  }

  double t2x, t2y, t2z;
  t2x = - nz * t1y; t2y = nz * t1x; t2z = nx * t1y - ny * t1x;

  double r1 = sqrt(t1x * t1x + t1y * t1y + t1z * t1z);
  double r2 = sqrt(t2x * t2x + t2y * t2y + t2z * t2z);

  double s1 = r / r1;
  double s2 = r / r2;

  t1x *= s1; t1y *= s1; t1z *= s1;
  t2x *= s2; t2y *= s2; t2z *= s2;

  int N = static_cast<int>(M_2PI * r / 0.01);
  if(N < 600) N = 600;
  double dt = M_2PI / N;

  double theta = 0.0;
  for (int i = 0; i < N; i ++) {
    double cs = cos(theta);
    double sn = sin(theta);

    double px = t1x * cs + t2x * sn + ctr_x;
    double py = t1y * cs + t2y * sn + ctr_y;
    double pz = t1z * cs + t2z * sn + ctr_z;

    glVertex3d(px, py, pz);

    theta += dt;
  }

  glEnd();
}


/***************************
 * Draw Ball
 *
 ***************************/

void drawBall(double r) {
  drawBall(0.0, 0.0, 0.0, r);
}

void drawBall(double ctr_x, double ctr_y, double ctr_z, double r)
{
  int N = static_cast<int>(M_2PI * r / 0.1);
  if(N < 60) N = 60;
  else N = (N + 3) / 4 * 4;
  double dt = M_2PI / N, cs = cos(dt), sn = sin(dt);
  
  int N1 = N + 1;
  double *x = new double[N1], *y = new double[N1], zu, zd;
  x[0] = r; y[0] = 0.0, zu = zd = ctr_z;
  for (int i = 0; i < N; i ++) {
    x[i + 1] = x[i] * cs - y[i] * sn;
    y[i + 1] = y[i] * cs + x[i] * sn;
  }
  
  double *xt = new double[N1], *yt = new double[N1], zut, zdt;
  
  int Nt = N / 4;
  double theta = 0.0, sn0 = 0.0;
  for (int i = 1; i < Nt; i ++) {
    glBegin(GL_QUAD_STRIP);
    
    theta += dt;
    double snt = sin(theta), zt = r * snt;
    zut = zt + ctr_z; zdt = - zt + ctr_z;
    
    double s = r * cos(theta) / x[0];
    for (int j = 0; j < N1; j ++) {
      xt[j] = x[j] * s; yt[j] = y[j] * s;

      glColor4d(sn0, 1.0 - sn0, 0.0, 1.0);
      glVertex3d(x[j] + ctr_x, y[j] + ctr_y, zu);
      
      glColor4d(snt, 1.0 - snt, 0.0, 1.0);
      glVertex3d(xt[j] + ctr_x, yt[j] + ctr_y, zut);
    }
    
    glEnd();
    
    // Draw the down part of Ball;
    glBegin(GL_QUAD_STRIP);
    
    for (int j = 0; j < N1; j ++) {
      glColor4d(0.0, 1.0 - sn0, sn0, 1.0);
      glVertex3d(x[j] + ctr_x, y[j] + ctr_y, zd);
      
      glColor4d(0.0, 1.0 - snt, snt, 1.0);
      glVertex3d(xt[j] + ctr_x, yt[j] + ctr_y, zdt);
      
      x[j] = xt[j]; y[j] = yt[j];
    }
    
    zu = zut; zd = zdt; sn0 = snt;
    
    glEnd();
  }
  
  glBegin(GL_TRIANGLE_FAN);

  glColor4d(1.0, 0.0, 0.0, 0.0);
  glVertex3d(ctr_x, ctr_y, r + ctr_z);

  glColor4d(sn0, 1.0 - sn0, 0.0, 0.0);
  for(int j = 0; j < N1; j ++) glVertex3d(x[j] + ctr_x, y[j] + ctr_y, zu);

  glEnd();

  glBegin(GL_TRIANGLE_FAN);

  glColor4d(0.0, 0.0, 1.0, 0.0);
  glVertex3d(ctr_x, ctr_y, - r + ctr_z);

  glColor4d(0.0, 1.0 - sn0, sn0, 0.0);
  for(int j = 0; j < N1; j ++) glVertex3d(x[j] + ctr_x, y[j] + ctr_y, zd);

  glEnd();

  delete[] x; delete[] y;
  delete[] xt; delete[] yt;
}


/***************************
 * Draw Cube
 *
 ***************************/

void drawCube(double x0, double y0, double z0,
              double x1, double y1, double z1,
              double x2, double y2, double z2,
              double x3, double y3, double z3)
{
  double dx1 = x1 - x0, dy1 = y1 - y0, dz1 = z1 - z0;
  double dx2 = x2 - x0, dy2 = y2 - y0, dz2 = z2 - z0;
  double dx3 = x3 - x0, dy3 = y3 - y0, dz3 = z3 - z0;
  
  double r1 = dx1 * dx1 + dy1 * dy1 + dz1 * dz1;
  double r2 = dx2 * dx2 + dy2 * dy2 + dz2 * dz2;
  double r3 = dx3 * dx3 + dy3 * dy3 + dz3 * dz3;
  
  assert(r1 > EPSILON);
  assert(fabs(r2 - r1) < EPSILON12 && fabs(r3 - r1) < EPSILON12);
  
  double x4 = x0 + dx2 + dx3;
  double y4 = y0 + dy2 + dy3;
  double z4 = z0 + dz2 + dz3;

  double x5 = x0 + dx3 + dx1;
  double y5 = y0 + dy3 + dy1;
  double z5 = z0 + dz3 + dz1;

  double x6 = x0 + dx1 + dx2;
  double y6 = y0 + dy1 + dy2;
  double z6 = z0 + dz1 + dz2;
  
  double x7 = x4 + dx1;
  double y7 = y4 + dy1;
  double z7 = z4 + dz1;

  glBegin(GL_QUADS);

  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3d(x3, y3, z3); glVertex3d(x5, y5, z5);
  glVertex3d(x7, y7, z7); glVertex3d(x4, y4, z4);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3d(x0, y0, z0); glVertex3d(x1, y1, z1);
  glVertex3d(x6, y6, z6); glVertex3d(x2, y2, z2);

  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3d(x0, y0, z0); glVertex3d(x3, y3, z3);
  glVertex3d(x5, y5, z5); glVertex3d(x1, y1, z1);

  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3d(x1, y1, z1); glVertex3d(x5, y5, z5);
  glVertex3d(x7, y7, z7); glVertex3d(x6, y6, z6);

  glColor3f(0.0f, 1.0f, 1.0f);
  glVertex3d(x6, y6, z6); glVertex3d(x7, y7, z7);
  glVertex3d(x4, y4, z4); glVertex3d(x2, y2, z2);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3d(x2, y2, z2); glVertex3d(x4, y4, z4);
  glVertex3d(x3, y3, z3); glVertex3d(x0, y0, z0);
  
  glEnd();
}


/***************************
 * Mesh Surface
 *
 ***************************/

void mesh(double **U, double *x, int M, double *y, int N)
{
  double u_max = U[0][0], u_min = U[0][0];
  for (int i = 0; i < M; i ++) {
    for (int j = 0; j < N; j ++) {
      if(U[i][j] > u_max) u_max = U[i][j];
      else if(U[i][j] < u_min) u_min = U[i][j];
    }
  }
  double wid = 0.5 * (u_max - u_min);

  // Plot Grid;
  double Ut[2] = {u_min - 0.4 * wid, u_max + 0.4 * wid};
  plotCoordinateSystem(x, M, y, N, Ut);

  double (*c)[3] = new double[N][3];
  for (int j = 0; j < N; j ++) {
    double T = (U[0][j] - u_min) / wid;
    if(T < 1) {c[j][0] = 0.0; c[j][1] = T; c[j][2] = 1.0 - T;}
    else {c[j][0] = T - 1.0; c[j][1] = 2.0 - T; c[j][2] = 0.0;}
  }

  int M1 = M - 1;
  for (int i = 0; i < M1; i ++) {
    glBegin(GL_QUAD_STRIP);

    for (int j = 0; j < N; j ++) {
      glColor3d(c[j][0], c[j][1], c[j][2]);
      glVertex3d(x[i], y[j], U[i][j]);

      double T = (U[i + 1][j] - u_min) / wid;
      if(T < 1) {c[j][0] = 0.0; c[j][1] = T; c[j][2] = 1.0 - T;}
      else {c[j][0] = T - 1.0; c[j][1] = 2.0 - T; c[j][2] = 0.0;}

      glColor3d(c[j][0], c[j][1], c[j][2]);
      glVertex3d(x[i + 1], y[j], U[i + 1][j]);
    }

    glEnd();
  }

  delete[] c;
}

void mesh(double **U, double *x, double *y, int M, int N)
{
  mesh(U, x, M, y, N);
}

void mesh(double **U, double **X, int M, double **Y, int N)
{
  double u_max = U[0][0], u_min = U[0][0];
  for (int i = 0; i < M; i ++) {
    for (int j = 0; j < N; j ++) {
      if(U[i][j] > u_max) u_max = U[i][j];
      else if(U[i][j] < u_min) u_min = U[i][j];
    }
  }
  double wid = 0.5 * (u_max - u_min);

  double (*c)[3] = new double[N][3];
  for (int j = 0; j < N; j ++) {
    double T = (U[0][j] - u_min) / wid;
    if(T < 1) {c[j][0] = 0.0; c[j][1] = T; c[j][2] = 1.0 - T;}
    else {c[j][0] = T - 1.0; c[j][1] = 2.0 - T; c[j][2] = 0.0;}
  }

  int M1 = M - 1;
  for (int i = 0; i < M1; i ++) {
    glBegin(GL_QUAD_STRIP);

    for (int j = 0; j < N; j ++) {
      glColor3d(c[j][0], c[j][1], c[j][2]);
      glVertex3d(X[i][j], Y[i][j], U[i][j]);

      double T = (U[i + 1][j] - u_min) / wid;
      if(T < 1) {c[j][0] = 0.0; c[j][1] = T; c[j][2] = 1.0 - T;}
      else {c[j][0] = T - 1.0; c[j][1] = 2.0 - T; c[j][2] = 0.0;}

      glColor3d(c[j][0], c[j][1], c[j][2]);
      glVertex3d(X[i + 1][j], Y[i + 1][j], U[i + 1][j]);
    }

    glEnd();
  }

  delete[] c;
}

void mesh(double **U, double **X, double **Y, int M, int N)
{
  mesh(U, X, M, Y, N);
}


