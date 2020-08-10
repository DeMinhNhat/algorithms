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
#include <iomanip>
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

struct Node
{
    int to;
    int weight;
};

vector<Node> city[MAXN];
double cost[MAXN];
int n;

void BellmanFord(int s)
{
    for (int i = 1; i <= n; i++)
        cost[i] = MIN;
    cost[s] = 100;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < city[i].size(); j++)
            {
                Node current = city[i][j];
                int index = current.to;
                int weight = current.weight;
                if (cost[i] > 0 && cost[index] < cost[i] * (double)weight / 100)
                    cost[index] = cost[i] * (double)weight / 100;
            }
}

int main()
{
    int m, u, v, weight;
    while (true)
    {
        cin >> n;
        if (n == 0)
            break;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> v >> u >> weight;
            Node node1;
            node1.to = u;
            node1.weight = weight;
            city[v].push_back(node1);
            Node node2;
            node2.to = v;
            node2.weight = weight;
            city[u].push_back(node2);
        }

        BellmanFord(1);
        cout << fixed << setprecision(6) << cost[n] << " percent" << endl;

        for (int i = 0; i <= MAXN; i++)
            city[i].clear();
        memset(cost, 0, sizeof(cost));
    }
    return 0;
}