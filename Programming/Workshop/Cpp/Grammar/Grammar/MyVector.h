#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyVector
{
public:
    MyVector(void);
    MyVector(int n);
    MyVector(int n, int initial_value);
    virtual ~MyVector(void);

public:
    int *mVec;
    int mSize;
};

