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
#define MAX 1000000
#define N 51
using namespace std;

int dist[N][N];
int visit[N][N];

void readLine(string line, int len, int person)
{
    for (int i = 0; i < len; i++)
    {
        dist[person][i] = line[i] == 'Y' ? 1 : 0;
        // visit[person][i] = line[i] == 'Y' ? 1 : 0;
    }
}

int main()
{
    int t, len, max, index, tmp;
    string line;
    getline(cin, line);
    stringstream geek(line);
    geek >> t;

    while (t--)
    {
        memset(dist, 0, sizeof(dist));
        memset(visit, 0, sizeof(visit));

        getline(cin, line);
        len = line.length();
        readLine(line, len, 0);

        for (int i = 1; i < len; i++)
        {
            getline(cin, line);
            readLine(line, len, i);
        }

        max = 0;
        index = 0;
        for (int person = 0; person < len; person++)
        {
            tmp = 0;
            for (int i = 0; i < len; i++)
                if (dist[person][i] == 1)
                {
                    visit[person][i] = 1;
                    for (int j = 0; j < len; j++)
                        if (dist[i][j] == 1 &&
                            dist[person][j] != 1 &&
                            visit[person][j] != 1 &&
                            person != j)
                        {
                            visit[person][j] = 1;
                            tmp++;
                        }
                }

            if (tmp > max)
            {
                max = tmp;
                index = person;
            }
        }
        cout << index << " " << max << endl;
    }
}