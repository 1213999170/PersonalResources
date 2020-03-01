#include "MyVector.h"
#include "MyQueue.h"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

void displayVector(vector<int> &vec) {
    //for (vector<int>::iterator iter = vec.begin(); iter < vec.end(); iter++)
    //    cout << *iter << " ";
    
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    MyVector vec;
    //srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        vec.push_back(rand() % 1000);
    }

    vec.display();
    vec.sort();
    vec.display();


    system("PAUSE");
    return 0;
}





