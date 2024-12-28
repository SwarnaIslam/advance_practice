#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
bool dfs(int r, int c, vector<vector<int>> &dp, vector<vector<int>> &vis, vector<vector<int>> &g)
{
    if (r == n - 1 && c == 0)
    {
        return true;
    }
    if (dp[r][c] != -1)
    {
        return true;
    }
    int temp = INT_MAX;
    vis[r][c] = 1;
    for (int i = c - 1; i >= 0; i--)
    {
        if (g[r][i] == 0)
            break;
        if (vis[r][i] == 0 && dfs(r, i, dp, vis, g))
        {
            temp = min(temp, dp[r][i]);
        }
    }
    for (int i = c + 1; i < m; i++)
    {
        if (g[r][i] == 0)
            break;
        if (vis[r][i] == 0 && dfs(r, i, dp, vis, g))
        {
            temp = min(temp, dp[r][i]);
        }
    }
    for (int i = r - 1; i >= 0; i--)
    {
        if (g[i][c] == 0)
            continue;
        if (vis[i][c] == 0 && dfs(i, c, dp, vis, g))
        {
            temp = min(temp, max(dp[i][c], abs(r - i)));
        }
        else if (dp[i][c] != INT_MAX && dp[i][c] != -1)
        {
            temp = min(temp, max(dp[i][c], abs(r - i)));
        }
    }
    for (int i = r + 1; i < n; i++)
    {
        if (g[i][c] == 0)
            continue;
        if (vis[i][c] == 0 && dfs(i, c, dp, vis, g))
        {
            temp = min(temp, max(dp[i][c], abs(r - i)));
        }
        else if (dp[i][c] != INT_MAX && dp[i][c] != -1)
        {
            temp = min(temp, max(dp[i][c], abs(r - i)));
        }
    }
    // cout << r << " " << c << " " << temp << endl;
    dp[r][c] = temp;
    return temp != INT_MAX;
}
int main()
{
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int x, y;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            if (g[i][j] == 3)
            {
                x = i, y = j;
            }
        }
    }
    dp[n - 1][0] = 0;
    dfs(x, y, dp, vis, g);
    cout << dp[x][y] << endl;
}

/*
The problem statement is very confusing. But what we are ultimately asked is the minimum maximum distance we need to cross in a column sequentially to reach from the bottom left corner to the destination.

For example,

1001
1000
1111

From (0,0) to reach (2,0), we need to jump from (0,0) to (1,0), then from (1,0) to (2,0). So the max distance we needed to ascend or descend is 1. But in order to reach (2,0) from (0,3),
(0,3) -> (2,3)
(2,3) -> (2,2)
(2,3) -> (2,1)
(2,3) -> (2,0)

The maximum distance we needed to ascend/descend is 2. So the minimum maximum distance is 1

Notice we can go left/right in a particular row if there is 1 consecutively, otherwise impossible. No such restriction in a column as long as there is 1 up/down in that column anywhere from a paeticular spot.

So in this solution, we have first passed the destination position to know recursively what is the minimum maximum distance needed to reach source (n-1, 0). To utilize positions for which we know the source is unreachable or the distance is known, we can use dynamic programming.
*/