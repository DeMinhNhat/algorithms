#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <limits>
#include <vector>
#define ii pair<int, int>
#define il pair<int, long>
#define ll long long int
#define ul unsigned long int
#define ull unsigned long long int
#define MAX 100100
#define MIN -100100
#define MAXN 101
using namespace std;

typedef bool (*comp)(ii, ii);
bool compare(ii a, ii b)
{
    if (a.first > b.first)
        return true;
    if (a.first == b.first && a.second > b.second)
        return true;
    return false;
}

int main()
{
    int n = 8, x, y;
    ii point;
    set<ii> dataset;
    vector<int> allX, allY;
    while (n--)
    {
        cin >> x >> y;
        point.first = x;
        point.second = y;
        allX.push_back(x);
        allY.push_back(y);
        dataset.insert(point);
    }

    string output = "respectable";
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
        {
            if (a == 1 && b == 1)
                continue;
            if (dataset.find(pair<long, long>(allX[a], allY[b])) == dataset.end())
                output = "ugly";
        }

    cout << output << endl;
    return 0;
}
