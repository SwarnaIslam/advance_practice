#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int t, n, m, r, c, l;

    int dir[8][4] = {
        {0, 0, 0, 0},
        {1, -1, 1, -1},
        {1, -1, 0, 0},
        {0, 0, 1, -1},
        {0, -1, 1, 0},
        {1, 0, 1, 0},
        {1, 0, 0, -1},
        {0, -1, 0, -1}};
    cin >> t;
    auto isValid = [&](int tr, int tc)
    {
        return tr >= 0 && tr < n && tc >= 0 && tc < m;
    };
    while (t--)
    {
        cin >> n >> m >> r >> c >> l;
        vector<vector<int>> g(n, vector<int>(m, 0));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> g[i][j];
            }
        }
        queue<vector<int>> q;
        q.push({r, c, g[r][c], 1});
        g[r][c] = 0;
        while (!q.empty())
        {
            auto u = q.front();
            int ur = u[0];
            int uc = u[1];
            int utype = u[2];
            int ud = u[3];

            // cout << ur << " " << uc << endl;
            q.pop();
            if (ud > l)
            {
                break;
            }
            ans++;
            int down = dir[utype][0];
            int up = dir[utype][1];
            int right = dir[utype][2];
            int left = dir[utype][3];
            if (isValid(ur + down, uc) && g[ur + down][uc] != 0 && dir[g[ur + down][uc]][1] != 0)
            {
                q.push({ur + down, uc, g[ur + down][uc], ud + 1});
                g[ur + down][uc] = 0;
            }
            if (isValid(ur + up, uc) && g[ur + up][uc] != 0 && dir[g[ur + up][uc]][0] != 0)
            {
                q.push({ur + up, uc, g[ur + up][uc], ud + 1});
                g[ur + up][uc] = 0;
            }
            if (isValid(ur, uc + right) && g[ur][uc + right] != 0 && dir[g[ur][uc + right]][3] != 0)
            {
                q.push({ur, uc + right, g[ur][uc + right], ud + 1});
                g[ur][uc + right] = 0;
            }
            if (isValid(ur, uc + left) && g[ur][uc + left] != 0 && dir[g[ur][uc + left]][2] != 0)
            {
                q.push({ur, uc + left, g[ur][uc + left], ud + 1});
                g[ur][uc + left] = 0;
            }
        }
        cout << ans << endl;
    }
}
