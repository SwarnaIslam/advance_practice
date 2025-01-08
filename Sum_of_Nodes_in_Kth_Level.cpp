#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int k;
    string s;
    cin >> k >> s;
    int n = s.size(), l = -1, ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            l++;
        }
        else if (s[i] == ')')
        {
            l--;
        }
        else if (l == k)
        {
            string str = "";
            while (i < n && s[i] != '(' && s[i] != ')')
            {
                str += s[i];
                i++;
            }
            int num = stoi(str);
            ans += num;
            i--;
        }
    }
    cout << ans << endl;
}
