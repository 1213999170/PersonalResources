#include "MyVector.h"

MyVector::MyVector(void) {
    mVec = NULL;
    mSize = 0;
}

MyVector::MyVector(int n) {
    if (n <= 0)
        exit(1);

    mVec = new int[n];
    mSize = n;
}

MyVector::MyVector(int n, int initial_value) {
    if (n <= 0)
        exit(1);

    mVec = new int[n];
    mSize = n;

    for (int i = 0; i < n; ++i) {
        mVec[i] = initial_value;
    }
}

MyVector::~MyVector(void) {
    delete[] mVec;
    mVec = NULL;
    mSize = 0;
}
