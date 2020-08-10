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
#include <vector>
#define ll long long int
#define ul unsigned long int
#define ull unsigned long long int
#define MIN -1000000000
#define MAX 100000000
using namespace std;

int pushing(list<int> stack1, list<int> stack2, int time)
{
    bool clear = true;
    while (!stack1.empty())
    {
        int plant = stack1.back();
        stack1.pop_back();
        if (!stack1.empty() && left && stack1.back() < plant)
            clear = false;
        else
            stack2.push_front(plant);
    }

    if (clear)
        return time;
    else
        return pushing(stack2, stack1, ++time);
}

int main()
{
    int n, plant;
    cin >> n;
    list<int> stack1, stack2;
    while (n--)
    {
        cin >> plant;
        stack1.push_back(plant);
    }

    int time = pushing(stack1, stack2, 0);
    cout << time;
    return 0;
}