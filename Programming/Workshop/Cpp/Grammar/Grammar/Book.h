#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
public:
    Book(void);
    Book(string BookName, int PageNumber, float Price);
    virtual ~Book(void);

public:
    string GetName(void);
    float GetPrice(void);

public:
    string mBookName;
    int mPageNumber;
    float mPrice;
    int *mCategories;
};
