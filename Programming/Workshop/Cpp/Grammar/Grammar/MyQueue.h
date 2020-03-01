#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyQueue
{
public:
    MyQueue(void);
    MyQueue(const MyQueue &a);
    virtual ~MyQueue(void);

public:
    void initialize(void);
    void clear(void);
    MyQueue& operator=(const MyQueue &a);
    void replicate(const MyQueue &a);

    int &front(void);
    int &back(void);

public:
    bool empty(void);
    int size(void);
    int capacity(void);
    void push(int a);
    void pop(void);
    void resize(int n);

protected:
    int *mVec;
    int mSize;
    int mCapacity;
};

