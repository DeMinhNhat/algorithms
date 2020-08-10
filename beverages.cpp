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
#define ii pair<int, int>
#define ll long long int
#define ul unsigned long int
#define ull unsigned long long int
#define MIN -999999999
#define MAX 999999999
#define MAXN 101
using namespace std;

bool matrix[MAXN][MAXN];
int indegree[MAXN];

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
    int caze = 1, n, m;
    vector<string> output;
    string beverage, source, destination;
    while (scanf("%d", &n) != EOF)
    {
        queue<int> sushi;
        queue<int> queue;
        priority_queue<int, vector<int>, greater<int>> pQueue;
        vector<string> name;
        map<string, int> id;
        memset(matrix, false, sizeof(matrix[0][0]) * n * n);
        memset(indegree, 0, sizeof indegree);

        for (int i = 0; i < n; i++)
        {
            cin >> beverage;
            id.insert(make_pair(beverage, name.size()));
            name.push_back(beverage);
        }

        cin >> m;
        while (m--)
        {
            cin >> source >> destination;
            if (!matrix[id[source]][id[destination]])
                ++indegree[id[destination]];
            matrix[id[source]][id[destination]] = true;
        }

        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
            {
                pQueue.push(i);
                indegree[i]--;
            }

        while (!pQueue.empty())
        {
            int current = pQueue.top();
            pQueue.pop();
            sushi.push(current);

            for (int i = 0; i < n; i++)
            {
                if (matrix[current][i])
                {
                    matrix[current][i] = false;
                    indegree[i]--;
                    if (indegree[i] == 0)
                        pQueue.push(i);
                }
            }
        }

        // stringstream ss;

        cout << "Case #" << caze << ": Dilbert should drink beverages in this order:";
        while (!sushi.empty())
        {
            cout << " " << name[sushi.front()];
            sushi.pop();
        }
        cout << "." << endl
             << endl;
        caze++;
        // output.push_back(ss.str());
    }
    // for (int i = 0; i < output.size(); i++)
    //     cout << output[i] << endl;
    return 0;
}

// cachaca 1
// rum 2
// apple-juice 3
// tequila 4
// whiskey 5
// wine 6
// vodka 7
// beer 8
// martini 9
// gin 10
// apple-juice wine beer martini vodka rum whiskey tequila cachaca gin
// apple-juice wine vodka beer rum cachaca tequila whiskey martini gin
// apple-juice wine vodka beer martini rum tequila whiskey cachaca gin
// 3 6 7 8 9 2 4 5 1 10
// 3 6 8 9 7 2 5 4 1 10
// 3 6 7 8 2 1 4 5 9 10