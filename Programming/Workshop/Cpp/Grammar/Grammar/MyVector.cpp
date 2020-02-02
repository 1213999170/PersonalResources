#include "MyVector.h"

MyVector::MyVector(void) {
    mVec = NULL;
    mSize = 0;
    mCapacity = 0;
}

MyVector::MyVector(int n) {
    if (n <= 0)
        exit(1);

    mVec = new int[n];
    mSize = n;
    mCapacity = n;
}

MyVector::MyVector(int n, int initial_value) {
    if (n <= 0)
        exit(1);

    mVec = new int[n];
    mSize = n;
    mCapacity = n;

    for (int i = 0; i < n; ++i) {
        mVec[i] = initial_value;
    }
}

MyVector::~MyVector(void) {
    delete[] mVec;
    mVec = NULL;
    mSize = 0;
    mCapacity = 0;
}

MyVector::MyVector(const MyVector &a) {
    mSize = a.mSize;
    mCapacity = a.mCapacity;
    mVec = new int[mCapacity];
    for (int i = 0; i < mSize; ++i) {
        mVec[i] = a.mVec[i];
    }
}

MyVector& MyVector::operator=(const MyVector &a) {
    if (this != &a) {
        mSize = a.mSize;
        mCapacity = a.mCapacity;
        mVec = new int[mCapacity];
        for (int i = 0; i < mSize; ++i) {
            mVec[i] = a.mVec[i];
        }
    }
    return *this;
}

int& MyVector::operator[](int index) {
    if (index < 0 || index >= mSize) {
        cout << "Invalid index" << endl;
        system("PAUSE");
        exit(1);
    }
    return mVec[index];
}

void MyVector::push_back(int a) {
    if (0 == mSize) {
        mVec = new int[1];
        mCapacity = 1;
        mSize = 1;
        mVec[0] = a;
    }
    else if (mSize < mCapacity) {
        mVec[mSize] = a;
        mSize++;
    }
    else {
        int *newVec = new int[2 * mCapacity];
        for (int i = 0; i < mSize; ++i) {
            newVec[i] = mVec[i];
        }
        delete[] mVec;
        mVec = newVec;
        mCapacity *= 2;

        mVec[mSize] = a;
        mSize++;
    }
}

void MyVector::pop_back(void) {
    if (0 == mSize) {
        cout << "Cannot pop_back empty vector." << endl;
        system("PAUSE");
        exit(1);
    }
    mSize--;

    if (mSize < mCapacity / 4) {
        int *newVec = new int[mCapacity / 2];
        for (int i = 0; i < mSize; ++i) {
            newVec[i] = mVec[i];
        }
        delete[] mVec;
        mVec = newVec;
        mCapacity /= 2;
    }
}
