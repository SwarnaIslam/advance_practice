#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
int r, c;
int main()
{
    cin >> r >> c;
    vector<vector<int>> g(r, vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> g[i][j];
        }
    }
    auto isValid = [&](int tr, int tc)
    {
        return tr >= 0 && tr < r && tc >= 0 && tc < c;
    };
    priority_queue<pr, vector<pr>, greater<pr>> pq;
    vector<vector<int>> dist(r, vector<int>(c, INT_MAX));
    int tr, tc;
    pq.push({0, (r - 1) * c});
    dist[r - 1][0] = 0;
    while (!pq.empty())
    {
        pr u = pq.top();
        pq.pop();
        int ur = u.second / c, uc = u.second % c;
        if (g[ur][uc] == 3)
        {
            tr = ur, tc = uc;
            break;
        }
        if (isValid(ur, uc - 1) && g[ur][uc - 1] && dist[ur][uc] < dist[ur][uc - 1])
        {
            dist[ur][uc - 1] = dist[ur][uc];
            pq.push({dist[ur][uc - 1], ur * c + uc - 1});
        }
        if (isValid(ur, uc + 1) && g[ur][uc + 1] && dist[ur][uc] < dist[ur][uc + 1])
        {
            dist[ur][uc + 1] = dist[ur][uc];
            pq.push({dist[ur][uc + 1], ur * c + uc + 1});
        }
        for (int i = 0; i < r; i++)
        {
            if (g[i][uc] == 0 || i == ur)
            {
                continue;
            }
            int d = max(abs(ur - i), dist[ur][uc]);
            if (d < dist[i][uc])
            {
                dist[i][uc] = d;
                pq.push({dist[i][uc], i * c + uc});
            }
        }
    }
    cout << dist[tr][tc] << endl;
}