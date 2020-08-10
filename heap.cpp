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
using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> upQueue;
    priority_queue<int> downQueue;
    int n, action, rating, size = 0;
    cin >> n;

    while (n--)
    {
        cin >> action;
        if (action == 1)
        {
            cin >> rating;
            if (upQueue.size() < 1 || upQueue.top() < rating)
                upQueue.push(rating);
            else
                downQueue.push(rating);
            size++;
            while (upQueue.size() > size / 3)
            {
                downQueue.push(upQueue.top());
                upQueue.pop();
            }
            while (upQueue.size() < size / 3)
            {
                upQueue.push(downQueue.top());
                downQueue.pop();
            }
        }
        else
        {
            if (size / 3 == 0)
            {
                cout << "No reviews yet" << endl;
                continue;
            }
            cout << upQueue.top() << endl;
        }
    }

    return 0;
}