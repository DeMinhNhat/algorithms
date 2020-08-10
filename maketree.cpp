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
#define inf 1000000000
#define MAXN 100001
using namespace std;

queue<int> susie;
vector<int> nodes[MAXN];
bool visited[MAXN];

void topological_sort(int cur)
{
    for (vector<int>::iterator it = nodes[cur].begin(); it != nodes[cur].end(); ++it)
    {
        if (!visited[*it])
        {
            visited[*it] = true;
            topological_sort(*it);
            susie.push(*it);
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    int w;
    for (int i = 1; i <= k; ++i)
    {
        cin >> w;
        int node;
        for (int j = 0; j < w; ++j)
        {
            cin >> node;
            nodes[node].push_back(i);
        }
    }

    memset(visited, false, sizeof visited);

    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            visited[i] = true;
            topological_sort(i);
            susie.push(i);
        }
    }

    int prev = 0;
    int parent[MAXN];
    while (!susie.empty())
    {
        int node = susie.front();
        susie.pop();
        parent[node] = prev;
        prev = node;
    }

    for (int i = 1; i <= n; ++i)
        cout << parent[i] << endl;
    return 0;
}