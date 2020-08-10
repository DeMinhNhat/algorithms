#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int m, n, k;
void dfs(vector<vector<int>> &vs, vector<vector<char>> lakeMap, int x, int y, vector<pair<int, int>> &coors)
{
    vs[x][y] = 1;
    coors.push_back(make_pair(x, y));
    int new_x, new_y;
    for (int i = 0; i < 4; i++)
    {
        new_x = x + dx[i];
        new_y = y + dy[i];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && lakeMap[new_x][new_y] == '.' && !vs[new_x][new_y])
        {
            dfs(vs, lakeMap, new_x, new_y, coors);
        }
    }
}
bool cmp(vector<pair<int, int>> a, vector<pair<int, int>> b)
{
    return a.size() < b.size();
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;
    vector<vector<char>> lakeMap(n, vector<char>(m));
    vector<vector<pair<int, int>>> lakeCoors;
    vector<vector<int>> vs(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> lakeMap[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (!vs[i][0] && lakeMap[i][0] == '.')
        {
            vector<pair<int, int>> coor;
            dfs(vs, lakeMap, i, 0, coor);
        }
        if (!vs[i][m - 1] && lakeMap[i][m - 1] == '.')
        {
            vector<pair<int, int>> coor;
            dfs(vs, lakeMap, i, m - 1, coor);
        }
    }
    for (int j = 1; j < m - 1; j++)
    {
        if (!vs[0][j] && lakeMap[0][j] == '.')
        {
            vector<pair<int, int>> coor;
            dfs(vs, lakeMap, 0, j, coor);
        }
        if (!vs[n - 1][j] && lakeMap[n - 1][j] == '.')
        {
            vector<pair<int, int>> coor;
            dfs(vs, lakeMap, n - 1, j, coor);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vs[i][j] && lakeMap[i][j] == '.')
            {
                //cout << "i: " << i << "j: " << j << endl;
                vector<pair<int, int>> coor;
                dfs(vs, lakeMap, i, j, coor);
                lakeCoors.push_back(coor);
            }
        }
    }
    sort(lakeCoors.begin(), lakeCoors.end(), cmp);
    int ans = 0;
    int numOfLakes = lakeCoors.size();
    for (int i = 0; i < numOfLakes - k; i++)
    {
        for (int j = 0; j < lakeCoors[i].size(); j++)
        {
            lakeMap[lakeCoors[i][j].first][lakeCoors[i][j].second] = '*';
            ans++;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << lakeMap[i][j];
        }
        cout << endl;
    }
    return 0;
}