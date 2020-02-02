#include "MyVector.h"

// get all squares less equal than n
MyVector GetSquares(int n) {
    MyVector a;
    for (int i = 1; i <= n; ++i) {
        if (i * i > n)
            break;
        a.push_back(i * i);
    }
    return a;
}

int main(int argc, char *argv[]) {
    MyVector sq = GetSquares(100);

    sq.pop_back();

    for (int i = 0; i < sq.mSize; i++) {
        cout << sq[i] << " ";
    }
    cout << endl;

    system("PAUSE");
    return 0;
}





