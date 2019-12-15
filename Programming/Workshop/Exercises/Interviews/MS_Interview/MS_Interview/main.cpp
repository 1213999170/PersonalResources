#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <windows.h>
using namespace std;


// Complete the function "judgeValidHands" to check whether the cards is the 
// mixture of straight-flush and 3/4-pairs.
extern bool judgeValidHands(vector<int> cards);


#define POINT_NUMBER 13
#define COLOR_NUMBER 4
#define CARDS_NUMBER ((COLOR_NUMBER) * (POINT_NUMBER))

#define COMPARE(a, b)	do {\
							if ((a) != (b)) {\
								cout << "COMPARE FAILED: " << (a) << " != " << (b) << endl;\
							}else {\
								cout << "COMPARE SUCCEED" << endl;\
							}\
						}while (0)

bool checkValidInput(vector<int> &cards) {
    set<int> cards_set;
    for (int i = 0; i < cards.size(); ++i) {
		int c = cards[i];
        if (c < 0 || CARDS_NUMBER <= c) {
			// cout << "Invalid input: the card " << c << " is out of range[0, 52)." << endl;
            return false;
		}
        if (cards_set.find(c) != cards_set.end()) {
			// cout << "Invalid input: the card " << c << " was repeatedly input." << endl;
            return false;
		}
        cards_set.insert(c);
    }
    return true;
}

bool searchIsolatePoint(vector<vector<int>> &cards_mat, vector<int> &point_num) {
	for (int i = 0; i < POINT_NUMBER; ++i) {
		if (point_num[i] <= 0 || point_num[i] >= 3)
			continue;
		for (int j = 0; j < COLOR_NUMBER; ++j) {
			if (0 == cards_mat[j][i])
				continue;
			if (i >= 2 && cards_mat[j][i - 2] && cards_mat[j][i - 1])
				continue;
			if (i >= 1 && i < POINT_NUMBER - 1 && cards_mat[j][i - 1] && cards_mat[j][i + 1])
				continue;
			if (i < POINT_NUMBER - 2 && cards_mat[j][i + 1] && cards_mat[j][i + 2])
				continue;
			return true;
		}
	}
	return false;
}

bool checkStraight(vector<int> &cards_vec) {
	int last_count = 0;
	for (int i = 0; i < POINT_NUMBER; ++i) {
		if (1 == cards_vec[i])
			++last_count;
		else {
			if (last_count > 0 && last_count < 3)
				return false;
			last_count = 0;
		}
	}
	if (last_count > 0 && last_count < 3)
		return false;
	return true;
}

bool judgeValidHands(vector<vector<int>> &cards_mat, vector<int> &point_num, int sum, int beg_point = 0) {
	if (0 == sum)
		return true;

	if (searchIsolatePoint(cards_mat, point_num))
		return false;

	for (int i = beg_point; i < POINT_NUMBER; ++i) {
		if (point_num[i] < 3)
			continue;

		if (3 == point_num[i]) {
			vector<int> store(COLOR_NUMBER, 0);
			for (int j = 0; j < COLOR_NUMBER; ++j) {
				store[j] = cards_mat[j][i];
				cards_mat[j][i] = 0;
			}
			point_num[i] = 0;
			if (judgeValidHands(cards_mat, point_num, sum - 3, beg_point + 1)) 
				return true;
			point_num[i] = 3;
			for (int j = 0; j < COLOR_NUMBER; ++j) 
				cards_mat[j][i] = store[j];
		}else {
			for (int j = 0; j < COLOR_NUMBER; ++j)
				cards_mat[j][i] = 0;
			point_num[i] = 0;
			if (judgeValidHands(cards_mat, point_num, sum - 4, beg_point + 1))
				return true;
			point_num[i] = 1;
			for (int j = 0; j < COLOR_NUMBER; ++j) {
				cards_mat[j][i] = 1;
				if (judgeValidHands(cards_mat, point_num, sum - 3, beg_point + 1))
					return true;
				cards_mat[j][i] = 0;
			}
			
			for (int j = 0; j < COLOR_NUMBER; ++j) {
				cards_mat[j][i] = 1;
			}
			point_num[i] = 4;
		}
	}

	for (int j = 0; j < COLOR_NUMBER; ++j) {
		if (!checkStraight(cards_mat[j]))
			return false;
	}
	return true;
}

// return true if the cards is the mixture of straight-flush and 3/4-pairs.
bool judgeValidHands(vector<int> cards) {
    if (!checkValidInput(cards))
        return false;

    int num = cards.size();
    if (num < 3)
        return false;

    vector<vector<int>> cards_mat(COLOR_NUMBER, vector<int>(POINT_NUMBER, 0));
	vector<int> point_num(POINT_NUMBER, 0);
	int sum = 0;
	for (int i = 0; i < num; ++i) {
        int color = cards[i] / POINT_NUMBER;
        int point = cards[i] % POINT_NUMBER;
        cards_mat[color][point] = 1;
		++point_num[point];
		++sum;
    }
    
	return judgeValidHands(cards_mat, point_num, sum);
}

void RunTest(const char *filename) {
	ifstream fin(filename);
	int test_number;
	fin >> test_number;
	for (int i = 0; i < test_number; ++i) {
		int num;
		fin >> num;

		vector<int> cards;
		for (int j = 0; j < num; ++j) {
			int card_index;
			fin >> card_index;
			cards.push_back(card_index);
		}

		string answer;
		fin >> answer;
		bool result = (answer == "true"? 1: 0);

		clock_t beg = clock();
		COMPARE(result, judgeValidHands(cards));
		clock_t end = clock();
		cout << "    cputime is " << 0.001 * (end - beg) <<" second." << endl;
	}
	fin.close();
}

int main(int argc, char *argv[]) {
    RunTest("test_cases.txt");
    
    system("pause");
    return 0;
}