// OpenGL_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "MGL.h"

int main(int argc, char *argv[])
{
    MGL gl;
    while (!gl.quit()) {
        gl.setScreen();

        plotBall(1.0);

        gl.show();
    }

    //glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //glutInitWindowPosition(100, 100);
    //glutInitWindowSize(320, 320);
    //glutCreateWindow("lighthouse");
    //glutDisplayFunc(RenderFunc);
    //glutMainLoop();

    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
