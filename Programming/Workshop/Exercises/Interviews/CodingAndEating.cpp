#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <map>
#include <string>
using namespace std;

double EPSILON = 1.0E-6;

int Sum(vector<int> &v) {
    int s = 0;
    for (auto e : v)
        s += e;
    return s;
}

void ComputeScale(vector<int> &a, vector<int> &b, vector<double> &s) {
    int n = s.size();
    for (int i = 0; i < n; ++i)
        s[i] = ((double)b[i]) / a[i];
}

void QuickSortScale(vector<int>::iterator pa, vector<int>::iterator pb, vector<double>::iterator ps, int n) {
    if (n <= 1)
        return;

    double target = *ps;
    int ta = *pa;
    int tb = *pb;
    int beg = 0, end = n - 1;
    while (true) {
        while (target >= *(ps + end)) {
            --end;
            if (beg == end)
                break;
        }

        if (beg == end)
            break;

        *(ps + beg) = *(ps + end);
        *(pa + beg) = *(pa + end);
        *(pb + beg) = *(pb + end);

        while (*(ps + beg) >= target) {
            ++beg;
            if (beg == end)
                break;
        }

        if (beg == end)
            break;

        *(ps + end) = *(ps + beg);
        *(pa + end) = *(pa + beg);
        *(pb + end) = *(pb + beg);
    }
    *(ps + beg) = target;
    *(pa + beg) = ta;
    *(pb + beg) = tb;

    QuickSortScale(pa, pb, ps, beg);
    QuickSortScale(pa + beg + 1, pb + beg + 1, ps + beg + 1, n - beg - 1);
}

double computeMaxEating(vector<int> &a, vector<int> &b, vector<double> &s, int surplus) {
    double max_eating = 0.0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (surplus > a[i]) {
            surplus -= a[i];
            max_eating += b[i];
        }
        else {
            max_eating += surplus * s[i];
            break;
        }
    }
    return max_eating;
}

string RunTest(void) {
    int D, S;
    cin >> D >> S;
    vector<int> a(S, 0), b(S, 0);
    for (int i = 0; i < S; ++i) {
        cin >> a[i] >> b[i];
    }

    int sa = Sum(a);
    int sb = Sum(b);

    vector<double> s(S, 0.0);
    ComputeScale(a, b, s);
    QuickSortScale(a.begin(), b.begin(), s.begin(), S);

    string answer;
    for (int d = 0; d < D; ++d) {
        int target_code, target_eating;
        cin >> target_code >> target_eating;

        if (target_code > sa || target_eating > sb) {
            answer += "N";
            continue;
        }

        double max_eating = computeMaxEating(a, b, s, sa - target_code);
        if (max_eating + EPSILON > target_eating)
            answer += "Y";
        else
            answer += "N";
    }
    return answer;
}

int main(int argc, char *argv[]) {
    string answer = RunTest();
    cout << answer << endl;

	system("PAUSE");
	return 0;
}
