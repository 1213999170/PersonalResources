#include "MyVector.h"


MyVector::MyVector(void) {
    initialize();
}

MyVector::MyVector(int n) : MyVector(n, 0) {
}

MyVector::MyVector(int n, int init_value) {
    initialize();

    mVec = new int[n];
    for (int i = 0; i < n; ++i) {
        mVec[i] = 0;
    }
    mSize = n;
    mCapacity = n;
}

MyVector::MyVector(const MyVector &a) {
    initialize();
    replicate(a);
}

MyVector &MyVector::operator=(const MyVector &a) {
    if (this != &a) {
        replicate(a);
    }
    return *this;
}

MyVector::~MyVector(void) {
    finalize();
}

void MyVector::initialize(void) {
    mVec = NULL;
    mSize = 0;
    mCapacity = 0;
}

void MyVector::finalize(void) {
    if (mVec != NULL) {
        delete[] mVec;
    }
    initialize();
}

void MyVector::replicate(const MyVector &a) {
    finalize();

    mSize = a.mSize;
    mCapacity = a.mCapacity;

    mVec = new int[mCapacity];
    for (int i = 0; i < mSize; ++i) {
        mVec[i] = a.mVec[i];
    }
}

void MyVector::reallocate(int n) {
    if (n < mSize) {
        //throw exception("Size should be non-negative.");
        exit(1);
    }

    if (n == mCapacity)
        return;

    int *newVec = new int[n];
    for (int i = 0; i < mSize; ++i)
        newVec[i] = mVec[i];

    delete[] mVec;
    mVec = newVec;
    mCapacity = n;
}

int &MyVector::operator[](int i) {
    return mVec[i];
}


void MyVector::resize(int size) {
    resize(size, 0);
}

void MyVector::resize(int size, int initial_value) {
    if (size < 0) {
        //throw exception("Size should be non-negative.");
        exit(1);
    }

    if (size == mSize)
        return;
    
    if (size > mCapacity) 
        reallocate(size);

    for (int i = mSize; i < size; ++i) {
        mVec[i] = initial_value;
    }
    mSize = size;
}

void MyVector::push_back(int a) {
    if (mSize >= mCapacity) {
        if (mCapacity == 0)
            reallocate(1);
        else
            reallocate(2 * mCapacity);
    }

    mVec[mSize++] = a;
}

void MyVector::pop_back(void) {
    if (mSize <= 0) {
        //throw exception("pop_back empty vector!");
        exit(1);
    }
    --mSize;

    //if (mSize < mCapacity / 4)
    //    reallocate(mCapacity / 2);
}
