#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int n, m, k, x, ans = 0;
    unordered_map<string, int> mp;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        string tmp = "";
        int c = 0;
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            tmp += (x + '0');
            c += (1 - x);
        }
        if (c <= k && (k - c) % 2 == 0)
        {
            mp[tmp]++;
            ans = max(ans, mp[tmp]);
        }
    }
    cout << ans << endl;
}
