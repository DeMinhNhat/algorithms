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
#define MAXN 10005
using namespace std;

vector<vector<il>> maze;
long values[MAXN];

typedef bool (*comp)(il, il);
bool compare(il a, il b)
{
    return a.second > b.second;
}

typedef bool (*compa)(int, int);
bool compareInt(int a, int b)
{
    return a > b;
}

int dijkstra(int source, int destination, int n)
{
    memset(values, MAX, sizeof values[0] * MAXN);
    priority_queue<il, vector<il>, comp> pQueue(compare);

    pQueue.push(il(source, 0));
    values[source] = 0;

    while (!pQueue.empty())
    {
        il current = pQueue.top();
        pQueue.pop();
        int index = current.first;
        if (index == destination)
            return values[destination];

        if (values[index] < current.second)
            continue;

        for (int i = 0; i < maze[index].size(); i++)
        {
            il it = maze[index][i];
            int des = it.first;
            int cost = it.second;

            int len = values[index] + cost;
            if (values[des] > len)
            {
                values[des] = len;
                pQueue.push(il(des, len));
            }
        }
    }

    return values[destination];
}

int main()
{
    int dataSets, n, m, k, s, t;
    long di, ci, li;
    long uj, vj, qj;

    cin >> dataSets;
    while (dataSets--)
    {
        cin >> n >> m >> k >> s >> t;
        maze = vector<vector<il>>(n + 1, vector<il>());
        priority_queue<int, vector<int>, compa> pQueue(compareInt);

        while (m--)
        {
            cin >> di >> ci >> li;
            maze[di].push_back(il(ci, li));
        }

        while (k--)
        {
            cin >> uj >> vj >> qj;
            maze[uj].push_back(il(vj, qj));
            maze[vj].push_back(il(uj, qj));
            int data = dijkstra(s, t, n);
            maze[uj].pop_back();
            maze[vj].pop_back();
            pQueue.push(data);
        }
        int output = pQueue.top();
        if (output < MAX)
            cout << output << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}