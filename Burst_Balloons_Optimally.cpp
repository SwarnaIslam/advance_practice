#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int memo(int l, int r, vector<int> &ballons, vector<vector<int>> &dp)
{
    if (l > r)
    {
        return 0;
    }
    if (dp[l][r] != -1)
    {
        return dp[l][r];
    }
    int ans = 0;
    for (int i = l; i <= r; i++)
    {
        int temp = 0;
        if (l - 1 == 0 && r + 1 == n - 1)
        {
            temp = ballons[i] + memo(l, i - 1, ballons, dp) + memo(i + 1, r, ballons, dp);
        }
        else
        {
            temp = ballons[l - 1] * ballons[r + 1] + memo(l, i - 1, ballons, dp) + memo(i + 1, r, ballons, dp);
        }
        ans = max(ans, temp);
    }
    return dp[l][r] = ans;
}
int main()
{
    cin >> n;
    vector<int> ballons;
    int x;
    ballons.push_back(1);
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        ballons.push_back(x);
    }
    ballons.push_back(1);
    n += 2;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << memo(1, n - 2, ballons, dp) << endl;
}

/*
We are asked to return the highest score achievable.

Observation 1:
When the last ballon explodes, we get the value equal to the value assigned to itself.

Observation 2:
If the 2nd to last ballon explodes, the value acquired is equal to the last ballon's value.

Observation 3:
Not having any ballons to the right/left side of a ballon is same as having a ballon of value 1, except for the last ballon(Observation 1)

In the bruteforce approach, we can calculate score for all possible combination.
But we can apply top-down approach for optimization.


We will go back from the time considering a ballon to be the last ballon to the very initial scenario where no ballons weren't exploded yet.

First we will append two ballons of value 1 to the beginning and ending according to observation 3.

We will pass left and right points in each iteration where left point means this is the leftmost position upto which all ballons are exploded. Right point means this is the rightmost position.

If we ever see leftmost point exceeds rightmost point, we simply return 0 as it is not possible to get any score.

Otherwise we will traverse the range rightmost to leftmost and go back in time one step imagining a particular indexed ballon was the last exploded ballon in that range. Doesn't it mean when we go back, this ballon wasn't exploded yet?

When we go back assuming a particular ballon was not exploded yet, two parts are created. One to the left of that particular ballon containing all exploded ballons and one part to the right. If we do this recursively, we will generate all possible scenario. But as many scenarios can be like deja vu(already happened XD), we can store and use them later.

Dry run:
I will demonstrate some steps.
testcase:
4
1 2 3 4

After appending 1:
1 1 2 3 4 1

lets say ballon at 1 index will be the last ballons, then we will get value[1]=1 score and pass the 2 exploded parts.

When we go back, ballon at index 1 isn't exploded yet. So for any ballon to the right part, this will be the leftmost unexploded ballon. And for any ballon left to this, it will be the rightmost unexploded ballon.
*/