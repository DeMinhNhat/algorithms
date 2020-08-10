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

string NCYCLE = "NEGATIVE CYCLE", NOTREACHABLE = "NOT REACHABLE";
vector<string> id;
int maze[MAXN][MAXN];
Graph *graph;
int cost[MAXN];
int dist[MAXN][MAXN];
int n;

void FloydWarshall()
{
    for (int i = 0; i < MAXN; i++)
        memset(dist[i], MAX, sizeof(dist[i]));

    for (int i = 0; i < graph->E; i++)
    {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int weight = graph->edges[i].weight;
        maze[u][v] = weight;
    }

    for (int v = 0; v < MAXN; v++)
        for (int u = 0; u < MAXN; u++)
        {
            dist[v][u] = maze[v][u];

            if (v == u)
                cost[v][u] = 0;
            else if (cost[v][u] != INT_MAX)
                cost[v][u] = v;
            else
                cost[v][u] = -1;
        }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][j] > maze[i][k] + maze[k][j])
                    dist[i][j] = maze[i][k] + maze[k][j];
}

bool BellmanFord(int from)
{
    memset(cost, MAX, sizeof(cost));
    cost[from] = 0;

    for (int i = 0; i < graph->V; i++)
        for (int j = 0; j < graph->E; j++)
        {
            int v = graph->edges[j].src;
            int u = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (cost[v] < MAX && weight != 0 && cost[v] + weight < cost[u])
                cost[u] = cost[v] + weight;
        }

    for (int i = 0; i < graph->V; i++)
        for (int j = 0; j < graph->E; j++)
        {
            int v = graph->edges[j].src;
            int u = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (cost[v] < MAX && weight != 0 && cost[v] + weight < cost[u])
                return true;
        }
    return false;
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
            }
        }
        cout << "Case #" << iTest << ":" << endl;
        cin >> q;
        if (BellmanFord(0))
            while (q--)
            {
                cin >> from >> to;
                cout << NCYCLE << endl;
            }
        else
        {
            FloydWarshall();
            while (q--)
            {
                cin >> from >> to;
                if (dist[from][to] < MAX)
                    cout << id[from] << "-" << id[to] << " " << dist[from][to] << endl;
                else
                    cout << id[from] << "-" << id[to] << " " << NOTREACHABLE << endl;
            }
        }

        id.clear();
        for (int i = 0; i < MAXN; i++)
            memset(maze[i], MAX, sizeof(maze[i]));
    }
    return 0;
}