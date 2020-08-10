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
    int n;
    while (scanf("%d", &n) != EOF)
    {
        priority_queue<int> pQueue;
        stack<int> stack;
        queue<int> queue;
        int action, value;
        int isStack = 1, isQueue = 1, isPQueue = 1;

        while (n--)
        {
            cin >> action;
            cin >> value;
            if (action == 1)
            {
                stack.push(value);
                queue.push(value);
                pQueue.push(value);
            }
            else
            {
                if (stack.size() < 1)
                    isStack = 0;
                if (isStack)
                {
                    if (stack.top() != value)
                        isStack = 0;
                    else
                        stack.pop();
                }
                if (queue.size() < 1)
                    isQueue = 0;
                if (isQueue)
                {
                    if (queue.front() != value)
                        isQueue = 0;
                    else
                        queue.pop();
                }
                if (pQueue.size() < 1)
                    isPQueue = 0;
                if (isPQueue)
                {
                    if (pQueue.top() != value)
                        isPQueue = 0;
                    else
                        pQueue.pop();
                }
            }
            // if (isPQueue + isStack + isQueue == 0)
            //     break;
        }
        if (isPQueue + isStack + isQueue > 1)
            cout << "not sure" << endl;
        else if (isPQueue)
            cout << "priority queue" << endl;
        else if (isStack)
            cout << "stack" << endl;
        else if (isQueue)
            cout << "queue" << endl;
        else
            cout << "impossible" << endl;
    }
}