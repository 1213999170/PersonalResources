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
    MyVector(int n, int init_value);
    MyVector(const MyVector &a);
    MyVector &operator=(const MyVector &a);
    virtual ~MyVector(void);

public:
    void initialize(void);
    void finalize(void);
    void replicate(const MyVector &a);
    void reallocate(int n);

    int &operator[](int i);
    void resize(int size);
    void resize(int size, int initial_value);
    void push_back(int a);
    void pop_back(void);

public:
    int *mVec;
    int mSize;
    int mCapacity;
};

