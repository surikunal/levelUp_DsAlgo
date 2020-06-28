#include <iostream>
#include <vector>
#include <list>

using namespace std;

void display(vector<int> &arr)
{
    for (int ele : arr)
        cout << ele << " ";
    cout << endl;
}

void display2D(vector<vector<int>> &arr)
{
    for (vector<int> ar : arr)
        display(ar);
    cout << endl;
}

int fibo(int n, vector<int> &dp)
{
    if (n <= 1) //base case.
        return dp[n] = n;

    if (dp[n] != 0)
        return dp[n];

    int ans = fibo(n - 1, dp) + fibo(n - 2, dp);

    return dp[n] = ans;
}

int fiboDP(int N, vector<int> &dp)
{

    for (int n = 0; n <= N; n++)
    {
        if (n <= 1) //base case.
        {
            dp[n] = n;
            continue;
        }

        int ans = dp[n - 1] + dp[n - 2]; // fibo(n - 1, dp) + fibo(n - 2, dp);

        dp[n] = ans;
    }
    return dp[N];
}
