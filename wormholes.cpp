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
#define MAXN 1005
using namespace std;

struct Node
{
    int to;
    int weight;
};

int main()
{
    int dataSets, n, m, x, y, t;

    cin >> dataSets;
    for (int iTest = 1; iTest <= dataSets; iTest++)
    {
        cin >> n >> m;
        vector<vector<Node>> maze(n, vector<Node>());
        int distances[n];
        memset(distances, MAX, sizeof distances);

        while (m--)
        {
            cin >> x >> y >> t;
            Node node;
            node.to = y;
            node.weight = t;
            maze[x].push_back(node);
        }

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < maze[i].size(); j++)
                {
                    Node node = maze[i][j];
                    if (distances[i] + node.weight < distances[node.to])
                        distances[node.to] = distances[i] + node.weight;
                }

        bool negativeWeightCycle = false;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < maze[i].size(); j++)
                {
                    Node node = maze[i][j];
                    negativeWeightCycle |= distances[i] + node.weight < distances[node.to];
                }

        if (negativeWeightCycle)
            cout << "possible" << endl;
        else
            cout << "not possible" << endl;
    }
    return 0;
}