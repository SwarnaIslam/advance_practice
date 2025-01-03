#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int memo(int curr, string &mask, string &target, unordered_map<int, unordered_map<string, int>> &dp, vector<vector<int>> &m)
{
    if (mask == target)
    {
        return m[curr][0];
    }
    if (dp[curr][mask])
    {
        return dp[curr][mask];
    }
    int ans = INT_MAX;
    for (int i = 1; i < n; i++)
    {
        if (mask[i] == '0')
        {
            mask[i] = '1';
            ans = min(ans, m[curr][i] + memo(i, mask, target, dp, m));
            mask[i] = '0';
        }
    }
    return dp[curr][mask] = ans;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<vector<int>> m(n, vector<int>(n));
        unordered_map<int, unordered_map<string, int>> dp;
        string initalMask = "1", target = "1";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> m[i][j];
            }
        }
        for (int i = 1; i < n; i++)
        {
            initalMask += '0';
            target += '1';
        }
        // cerr << "ans: ";
        cout << memo(0, initalMask, target, dp, m) << endl;
    }
}