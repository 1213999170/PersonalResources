#ifndef __Graphics_h_IS_INCLUDED__
#define __Graphics_h_IS_INCLUDED__

#include <complex>
#include <GL/freeglut.h>
inline void setColor(double c) {
  // assert(0.0 <= c && c <= 1.0);
  if (c < 0.5) {
    double c2 = c + c;
    glColor3f(0.0, c2, 1.0 - c2);
  }else {
    double c2 = c + c - 1.0;
    glColor3f(c2, 1.0 - c2, 0.0);
  }
}

inline void setColor(double c, double lo, double hi) {
  // assert(lo <= c && c <= hi);
  setColor((c - lo) / (hi - lo));
}

void plotPoints(double *x, double *y, int N, bool coord = false);
void plotPoints(double (*node)[2], int N, bool coord = false);
void plotPoints(std::complex<double> *z, int N, bool coord = false);
void plotPoints(double *x, double *y, double *z, int N, bool coord = false);

void plot(double *x, double *y, int N, bool coord = false);
void plot(double *x, double *y, double *z, int N, bool coord = false);
void plot(double (*node)[2], int N, bool coord = false);

void plotTriangle(double x0, double y0,
                  double x1, double y1,
                  double x2, double y2);
void plotTriangle(double A[2], double B[2], double C[2]);
void plotTriangle(double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2);
void plotTriangle3D(double A[3], double B[3], double C[3]);

void plotRectangle(double lo[2], double hi[2]);
void plotRectangle(double xlo, double ylo,
                   double xhi, double yhi);

void plotQuadrangle(double x0, double y0,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3);
void plotQuadrangle(double A[2], double B[2],
                    double C[2], double D[2]);
void plotQuadrangle(double x0, double y0, double z0,
                    double x1, double y1, double z1,
                    double x2, double y2, double z2,
                    double x3, double y3, double z3);
void plotQuadrangle3D(double A[3], double B[3],
                      double C[3], double D[3]);

void plotCircle(double x, double y, double r);
void plotCircle(double ctr_x, double ctr_y, double ctr_z,
                double nx, double ny, double nz, double r);

void plotBall(double r);
void plotBall(double x, double y, double z, double r);

void plotCube(double x0, double y0, double z0,
              double x1, double y1, double z1,
              double x2, double y2, double z2,
              double x3, double y3, double z3);

void plotCoordinateSystem(double x[2], double y[2]);
void plotCoordinateSystem(double x0, double x1, double y0, double y1);
void plotCoordinateSystem(double *x, int M, double y[2]);
void plotCoordinateSystem(double *x, int M, double *y, int N);
void plotCoordinateSystem(double (*node)[2], int N);

void plotCoordinateSystem(double x[2], double y[2], double z[2]);
void plotCoordinateSystem(double *x, int M, double *y, int N, double z[2]);
void plotCoordinateSystem(double *x, int M,
                          double *y, int N,
                          double *z, int L);

void drawTriangle(double x0, double y0,
                  double x1, double y1,
                  double x2, double y2);
void drawTriangle(double A[2], double B[2], double C[2]);
void drawTriangle(double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2);
void drawTriangle3D(double A[3], double B[3], double C[3]);

void drawRectangle(double lo[2], double hi[2]);
void drawRectangle(double xlo, double ylo,
                   double xhi, double yhi);

void drawQuadrangle(double x0, double y0,
                    double x1, double y1,
                    double x2, double y2,
                    double x3, double y3);
void drawQuadrangle(double A[2], double B[2],
                    double C[2], double D[2]);
void drawQuadrangle(double x0, double y0, double z0,
                    double x1, double y1, double z1,
                    double x2, double y2, double z2,
                    double x3, double y3, double z3);
void drawQuadrangle3D(double A[3], double B[3],
                      double C[3], double D[3]);

void drawCircle(double x, double y, double r);
void drawCircle(double ctr_x, double ctr_y, double ctr_z,
                double nx, double ny, double nz, double r);

void drawBall(double r);
void drawBall(double x, double y, double z, double r);

void drawCube(double x0, double y0, double z0,
              double x1, double y1, double z1,
              double x2, double y2, double z2,
              double x3, double y3, double z3);

void mesh(double **U, double *x, int M, double *y, int N);
void mesh(double **U, double *x, double *y, int M, int N);
void mesh(double **U, double **X, int M, double **Y, int N);
void mesh(double **U, double **X, double **Y, int M, int N);

#endif
