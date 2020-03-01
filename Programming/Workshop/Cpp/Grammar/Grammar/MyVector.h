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
    MyVector(const MyVector &a);
    virtual ~MyVector(void);

public:
    void initialize(void);
    void initialize(int n);
    void clear(void);

    MyVector& operator=(const MyVector &a);
    void replicate(const MyVector &a);

    int &at(int index);
    int& operator[](int index);
    int &front(void);
    int &back(void);

public:
    bool empty(void);
    int size(void);
    int capacity(void);
    void push_back(int a);
    void pop_back(void);
    void insert(int i, int value);
    void erase(int i);
    void resize(int n);
    void swap(int i, int j);

public:
    void sort(void);
    void bubbleSort(void);
    void selectionSort(void);
    void insertionSort(void);
    void shellSort(void);
    void mergeSort(void);
    void display(void);

private:
    void mergeSortPart(int i0, int i1);
    void mergePart(int i0, int i1, int i2);

protected:
    int *mVec;
    int mSize;
    int mCapacity;
};

