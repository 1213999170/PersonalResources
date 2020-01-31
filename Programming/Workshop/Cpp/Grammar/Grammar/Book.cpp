#include "Book.h"

Book::Book(void) {
    mBookName = "";
    mPageNumber = 0;
    mPrice = 0.0;

    mCategories = new int[10];
    for (int i = 0; i < 10; ++i) {
        mCategories[i] = 0;
    }
}

Book::Book(string BookName, int PageNumber, float Price) {
    mBookName = BookName;
    mPageNumber = PageNumber;
    mPrice = Price;

    mCategories = new int[10];
    for (int i = 0; i < 10; ++i) {
        mCategories[i] = 0;
    }
}

Book::~Book(void) {
    delete[] mCategories;
}

string Book::GetName(void) {
    return mBookName;
}

float Book::GetPrice(void) {
    return mPrice;
}
