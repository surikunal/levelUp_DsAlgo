#include <iostream>
#include <vector>
using namespace std;

void display(vector<int> &arr)
{
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

void display(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}

int fibo(int n, vector<int> &dp)
{
    if (n <= 1)
        return dp[n] = n;

    if (dp[n] != 0)
        return dp[n];

    int ans = fibo(n - 1, dp) + fibo(n - 2, dp);
    return dp[n] = ans;
}

int fiboDP(int N, vector<int> &dp)
{
    for (int i = 0; i <= N; i++)
    {
        if (i <= 1)
        {
            dp[i] = i;
            continue;
        }

        int ans = dp[i - 1] + dp[i - 2];
        dp[i] = ans;
    }
    return dp[N];
}

int fibo_btr(int n)
{
    int a = 0;
    int b = 1;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return a;
}

// MazePathSeries. ===============================================

int mazePathHVD(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
        return dp[sr][sc] = 1;

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    if (sr + 1 <= er)
        count += mazePathHVD(sr + 1, sc, er, ec, dp);

    if (sc + 1 <= ec)
        count += mazePathHVD(sr, sc + 1, er, ec, dp);

    if (sr + 1 <= er && sc + 1 <= ec)
        count += mazePathHVD(sr + 1, sc + 1, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazePathHVD_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            if (sr + 1 <= er)
                count += dp[sr + 1][sc];

            if (sc + 1 <= ec)
                count += dp[sr][sc + 1];

            if (sr + 1 <= er && sc + 1 <= ec)
                count += dp[sr + 1][sc + 1];

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int mazePath_multi_HVD(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    if (sr == er && sc == ec)
        return dp[sr][sc] = 1;

    if (dp[sr][sc] != 0)
        return dp[sr][sc];

    int count = 0;
    for (int jump = 1; sr + jump <= er; jump++)
        count += mazePath_multi_HVD(sr + jump, sc, er, ec, dp);

    for (int jump = 1; sc + jump <= ec; jump++)
        count += mazePath_multi_HVD(sr, sc + jump, er, ec, dp);

    for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
        count += mazePath_multi_HVD(sr + jump, sc + jump, er, ec, dp);

    return dp[sr][sc] = count;
}

int mazePath_multi_HVD_DP(int sr, int sc, int er, int ec, vector<vector<int>> &dp)
{
    for (sr = er; sr >= 0; sr--)
    {
        for (sc = ec; sc >= 0; sc--)
        {
            if (sr == er && sc == ec)
            {
                dp[sr][sc] = 1;
                continue;
            }

            int count = 0;
            for (int jump = 1; sr + jump <= er; jump++)
                count += dp[sr + jump][sc];

            for (int jump = 1; sc + jump <= ec; jump++)
                count += dp[sr][sc + jump];

            for (int jump = 1; sr + jump <= er && sc + jump <= ec; jump++)
                count += dp[sr + jump][sc + jump];

            dp[sr][sc] = count;
        }
    }
    return dp[0][0];
}

int boardPath(int sp, int ep, vector<int> &dp)
{
    if (sp == ep)
        return dp[sp] = 1;

    if (dp[sp] != 0)
        return dp[sp];

    int count = 0;
    for (int dice = 1; dice + sp <= ep && dice <= 6; dice++)
        count += boardPath(sp + dice, ep, dp);

    return dp[sp] = count;
}

int boardPathDP(int sp, int ep, vector<int> &dp)
{
    for (sp = ep; sp >= 0; sp--)
    {
        if (sp == ep)
        {
            dp[sp] = 1;
            continue;
        }

        int count = 0;
        for (int dice = 1; dice + sp <= ep && dice <= 6; dice++)
            count += dp[sp + dice];

        dp[sp] = count;
    }
    return dp[0];
}

void set2()
{
    int n = 3, m = 3;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    // cout << mazePathHVD(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePathHVD_DP(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePath_multi_HVD(0, 0, n - 1, m - 1, dp) << endl;
    // cout << mazePath_multi_HVD_DP(0, 0, n - 1, m - 1, dp) << endl;

    int sp = 0, ep = 10;
    vector<int> dp1(ep + 1, 0);
    cout << boardPath(sp, ep, dp1) << endl;

    cout << boardPathDP(sp, ep, dp1) << endl;
}

void set1()
{
    int n = 10;
    vector<int> dp(n + 1, 0);
    cout << fibo(n, dp) << endl;
    cout << fiboDP(n, dp) << endl;
    cout << fibo_btr(n) << endl;
}

void solve()
{
    // set1();  // basic
    set2(); //mazePath series
}

int main(int args, char **argv)
{
    solve();
    return 0;
}