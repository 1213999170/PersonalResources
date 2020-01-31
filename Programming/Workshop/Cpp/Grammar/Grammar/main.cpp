#include "Book.h"
#include "MyVector.h"

void display(MyVector &vec) {
    for (int i = 0; i < vec.mSize; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    MyVector vec;
    for (int i = 0; i < 10; ++i)
        vec.push_back((i + 1) * (i + 1));

    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    display(vec);

    system("PAUSE");
    return 0;
}





