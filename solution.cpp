#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define MAX 3000

bool compareLakes(pair<int, int> i1, pair<int, int> i2)
{
    return (i1.second < i2.second);
}

bool isValid(vector<vector<char>> canvas, int x, int y)
{
    if (canvas.size() > x && x > -1)
    {
        if (canvas[x].size() > y && y > -1 && canvas[x][y] == '.')
        {
            return true;
        }
        return false;
    }
    return false;
}

bool isBorder(int n, int m, int index)
{
    if (index < m || index >= (n - 1) * m)
        return true; // up and down border
    if (index % m == 0 || index % m == m - 1)
        return true; // right and left border
    return false;
}

vector<vector<int>> createGraph(vector<vector<char>> canvas, int n, int m)
{
    vector<vector<int>> graph(n * m);

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char node = canvas[i][j];
            if (node == '.')
            {
                graph[i * m + j].push_back(i * m + j);
                for (int k = 0; k < 4; k++)
                {
                    if (isValid(canvas, i + dx[k], j + dy[k]))
                    {
                        graph[i * m + j].push_back((i + dx[k]) * m + j + dy[k]);
                    }
                }
            }
        }
    }

    return graph;
}

pair<int, vector<pair<int, int>>> findNumOfLakes(vector<vector<int>> graph, int n, int m)
{
    vector<int> visit(n * m, 0);
    stack<int> stack;
    int num = 0;
    vector<pair<int, int>> lakes;

    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].size() > 0 && visit[i] != 1)
        {
            stack.push(i);
            bool isLake = true;
            int size = -1;

            while (!stack.empty())
            {
                int node = stack.top();
                stack.pop();
                if (isLake)
                    isLake = !isBorder(n, m, node);
                size++;

                for (int j = 0; j < graph[node].size(); j++)
                {
                    if (visit[graph[node][j]] != 1)
                    {
                        visit[graph[node][j]] = 1;
                        stack.push(graph[node][j]);
                    }
                }
            }
            if (isLake == true)
            {
                num++;
                pair<int, int> lake;
                lake.first = i;
                lake.second = size;
                lakes.push_back(lake);
            }
        }
    }

    pair<int, vector<pair<int, int>>> result;
    result.first = num;
    result.second = lakes;
    return result;
}

void printBerland(
    vector<vector<char>> canvas,
    vector<vector<int>> graph,
    vector<pair<int, int>> lakes,
    int n, int m, int number)
{
    vector<int> visit(n * m, 0);
    int nodes[MAX];
    int size = 0;
    for (int i = 0; i < number; i++)
    {
        int lake = lakes[i].first;
        stack<int> stack;
        stack.push(lake);
        visit[lake] = 1;

        while (!stack.empty())
        {
            int current = stack.top();
            stack.pop();
            nodes[current] = 1;
            size++;

            for (int j = 0; j < graph[current].size(); j++)
            {
                if (visit[graph[current][j]] != 1)
                {
                    visit[graph[current][j]] = 1;
                    stack.push(graph[current][j]);
                }
            }
        }
    }

    cout << size << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (nodes[i * m + j] == 1)
                cout << "*";
            else
                cout << canvas[i][j];
        }
        cout << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int n, m, num;
    cin >> n >> m >> num;

    vector<vector<char>> canvas(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> canvas[i][j];
        }
    }

    vector<vector<int>> graph = createGraph(canvas, n, m);
    pair<int, vector<pair<int, int>>> data = findNumOfLakes(graph, n, m);

    int number = data.first - num; // num of lakes need to be fill
    vector<pair<int, int>> lakes = data.second;

    sort(lakes.begin(), lakes.end(), compareLakes);

    // for (int i = 0; i < lakes.size(); i++)
    // {
    //     cout << "(" << lakes[i].first << ", " << lakes[i].second << "), ";
    // }

    printBerland(canvas, graph, lakes, n, m, number);
}