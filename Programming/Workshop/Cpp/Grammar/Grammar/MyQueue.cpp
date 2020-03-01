#include "MyQueue.h"


MyQueue::MyQueue(void) {
    initialize();
}

MyQueue::MyQueue(const MyQueue &a) {
    initialize();
    replicate(a);
}

MyQueue::~MyQueue(void) {
    clear();
}

void MyQueue::initialize(void) {
    mVec = NULL;
    mSize = 0;
    mCapacity = 0;
}

void MyQueue::clear(void) {
    if (mVec != NULL)
        delete[] mVec;

    initialize();
}

MyQueue& MyQueue::operator=(const MyQueue &a) {
    if (this != &a) {
        replicate(a);
    }
    return *this;
}

void MyQueue::replicate(const MyQueue &a) {
    clear();

    mSize = a.mSize;
    mCapacity = a.mCapacity;
    mVec = new int[mCapacity];
    for (int i = 0; i < mSize; ++i) {
        mVec[i] = a.mVec[i];
    }
}

int &MyQueue::front(void) {
    if (0 == mSize)
        exit(1);
    return mVec[0];
}

int &MyQueue::back(void) {
    if (0 == mSize)
        exit(1);
    return mVec[mSize - 1];
}

bool MyQueue::empty(void) {
    if (mSize == 0) {
        return true;
    }
    return false;
}

int MyQueue::size(void) {
    return mSize;
}

int MyQueue::capacity(void) {
    return mCapacity;
}

void MyQueue::push(int a) {
    if (0 == mCapacity) {
        resize(1);
    }
    if (mSize >= mCapacity)
        resize(2 * mCapacity);

    mVec[mSize] = a;
    mSize++;
}

void MyQueue::pop(void) {
    if (mSize <= 0) {
        exit(1);
    }

    for (int j = 0; j < mSize - 1; j++) {
        mVec[j] = mVec[j + 1];
    }
    mSize--;
    if (mCapacity > 4 * mSize) {
        resize(mCapacity / 2);
    }
}

void MyQueue::resize(int n) {
    if (n < 0) {
        cout << "the new size should be non-negative." << endl;
        system("PAUSE");
        exit(1);
    }

    if (n == mCapacity)
        return;

    int *newVec = new int[n];
    mSize = mSize < n ? mSize : n;
    for (int i = 0; i < mSize; ++i) {
        newVec[i] = mVec[i];
    }
    delete[] mVec;
    mVec = newVec;
    mCapacity = n;
}

