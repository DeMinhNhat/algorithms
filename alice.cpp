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
string NCYCLE = "NEGATIVE CYCLE", NOTREACHABLE = "NOT REACHABLE";

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    vector<Edge> edges;
};

struct Graph *createGraph(int V)
{
    struct Graph *graph = new Graph;
    graph->V = V;
    graph->E = 0;
    return graph;
}

vector<string> id;
Graph *graph;
bool negative[MAXN];
int dist[MAXN];
int maze[MAXN][MAXN], path[MAXN][MAXN], cost[MAXN][MAXN];
int n;

void dfs(int node)
{
    for (int i = 0; i < n; i++)
        if (!negative[i] && maze[node][i] != 0 && maze[node][i] != MAXN)
        {
            negative[i] = true;
            dfs(i);
        }
}

void FloydWarshall()
{
    for (int v = 0; v < n; v++)
        for (int u = 0; u < n; u++)
        {
            cost[v][u] = maze[v][u];
            if (cost[v][u] > 0 && u == v)
                cost[v][u] = 0;

            if (cost[v][u] == 0 && u != v)
                path[v][u] = -1;
            else
                path[v][u] = v;
        }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (cost[i][j] > maze[i][k] + maze[k][j] && path[i][k] != -1 && path[k][j] != -1)
                {
                    cost[i][j] = maze[i][k] + maze[k][j];
                    path[i][j] = i;
                }
        }
}

bool BellmanFord(int from)
{
    memset(dist, MAX, sizeof(dist));
    dist[from] = 0;
    bool nonnega = true;

    vector<int> negaNodes;

    for (int i = 0; i < graph->V; i++)
        for (int j = 0; j < graph->E; j++)
        {
            int v = graph->edges[j].src;
            int u = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[v] < MAX && weight != 0 && dist[v] + weight < dist[u])
                dist[u] = dist[v] + weight;
        }

    for (int i = 0; i < graph->V; i++)
        for (int j = 0; j < graph->E; j++)
        {
            int v = graph->edges[j].src;
            int u = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[v] < MAX && weight != 0 && dist[v] + weight < dist[u])
            {
                nonnega = false;
                negaNodes.push_back(u);
            }
        }

    memset(negative, false, sizeof(negative));
    for (int i = 0; i < negaNodes.size(); i++)
    {
        int node = negaNodes[i];
        negative[node] = true;
        dfs(node);
    }
    return nonnega;
}

int main()
{
    int weight, q, from, to, iTest = 0;
    string name;
    while (true)
    {
        cin >> n;
        if (n == 0)
            break;
        iTest++;

        graph = createGraph(n);
        for (int i = 0; i < n; i++)
        {
            memset(maze[i], MAX, sizeof(maze[i]));
            memset(path[i], MAX, sizeof(path[i]));
            memset(cost[i], MAX, sizeof(cost[i]));
        }

        for (int i = 0; i < n; i++)
        {
            cin >> name;
            id.push_back(name);
            for (int j = 0; j < n; j++)
            {
                cin >> weight;
                struct Edge edge;
                edge.src = i;
                edge.dest = j;
                edge.weight = weight;
                graph->edges.push_back(edge);
                graph->E++;
                maze[i][j] = weight;
            }
        }
        cin >> q;
        cout << "Case #" << iTest << ":" << endl;

        BellmanFord(0);
        FloydWarshall();
        while (q--)
        {
            cin >> from >> to;
            if (path[from][to] != -1 && !negative[to])
                cout << id[from] << "-" << id[to] << " " << cost[from][to] << endl;
            else if (negative[to])
                cout << NCYCLE << endl;
            else
                cout << id[from] << "-" << id[to] << " " << NOTREACHABLE << endl;
        }

        id.clear();
    }
    return 0;
}