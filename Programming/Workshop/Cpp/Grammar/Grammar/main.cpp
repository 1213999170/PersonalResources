#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
public : 
    Book(void);
    Book(string BookName, int PageNumber, float Price);
    virtual ~Book(void);

public : 
    string GetName(void);
    float GetPrice(void);

public : 
    string mBookName;
    int mPageNumber;
    float mPrice;
    int *mCategories;
};

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

int main(int argc, char *argv[]) {
    Book book("Book1", 103, 32.3);
    cout << "Book's name is " << book.GetName() << endl;
    cout << "Book's price is " << book.GetPrice() << endl;

    system("PAUSE");
    return 0;
}





