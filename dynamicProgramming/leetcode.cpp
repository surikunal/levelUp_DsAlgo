#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    // leetcode 70. Climbing Stairs ==================================
    int climbingStairs_mem(int n, vector<int> &dp)
    {
        if (n <= 1)
            return dp[n] = 1;

        if (dp[n] != 0)
            return dp[n];

        int ans = climbingStairs_mem(n - 1, dp) + climbingStairs_mem(n - 2, dp);

        return dp[n] = ans;
    }

    int climbingStairs_DP(int n, vector<int> &dp)
    {
        int N = n;
        for (n = 0; n <= N; n++)
        {
            if (n <= 1)
            {
                dp[n] = 1;
                continue;
            }

            int ans = dp[n - 1] + dp[n - 2];
            dp[n] = ans;
        }
        return dp[N];
    }

    int climbingStairs_btr(int n)
    {
        int a = 1, b = 1, sum = 1;
        for (int i = 2; i <= n; i++)
        {
            sum = a + b;
            a = b;
            b = sum;
        }
        return sum;
    }

    int climbStairs(int n)
    {
        vector<int> dp(n + 1, 0);
        // return climbingStairs_mem(n, dp);
        // return climbingStairs_DP(n, dp);
        return climbingStairs_btr(n);
    }

    // leetcode 746. Min Cost Climbing Stairs=================================================================
    int minCostClimbingStairs_mem(int n, vector<int> &dp, vector<int> &cost)
    {
        if (n <= 1)
            return dp[n] = cost[n];

        if (dp[n] != 0)
            return dp[n];

        int ans = min(minCostClimbingStairs_mem(n - 1, dp, cost), minCostClimbingStairs_mem(n - 2, dp, cost));

        return dp[n] = ans + cost[n];
    }

    int minCostClimbingStairs_dp(int n, vector<int> &dp, vector<int> &cost)
    {
        int N = n;
        for (n = 0; n <= N; n++)
        {
            if (n <= 1)
            {
                dp[n] = cost[n];
                continue;
            }

            int ans = min(dp[n - 1], dp[n - 2]);

            dp[n] = ans + cost[n];
        }
        return dp[N];
    }

    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();

        cost.push_back(0); // just to increase the size so we can reach there atleast
        vector<int> dp(n + 1, 0);

        // return minCostClimbingStairs_mem(n, dp, cost);
        return minCostClimbingStairs_dp(n, dp, cost);
    }

    // https://practice.geeksforgeeks.org/problems/friends-pairing-problem/0
    int friends_pairing_problem(int n, vector<int> &dp)
    {
        if (n <= 1)
            return dp[n] = 1;

        if (dp[n] != 0)
            return dp[n];

        int single = friends_pairing_problem(n - 1, dp);
        int pairUp = friends_pairing_problem(n - 2, dp) * (n - 1);

        return dp[n] = (single + pairUp);
    }

    int friends_pairing_problem_DP(int n, vector<int> &dp)
    {
        int N = n;
        for (int n = 0; n <= N; n++)
        {
            if (n <= 1)
            {
                dp[n] = 1;
                continue;
            }

            int single = dp[n - 1];           //friends_pairing_problem(n - 1, dp);
            int pairUp = dp[n - 2] * (n - 1); //friends_pairing_problem(n - 2, dp) * (n - 1);

            dp[n] = (single + pairUp);
        }
        return dp[N];
    }

    // leetcode 64. Minimum Path Sum =====================================================

    int minSum(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
            return dp[sr][sc] = grid[sr][sc];

        if (dp[sr][sc] != 0)
            return dp[sr][sc];

        int cost = 1e8;
        if (sr + 1 < grid.size())
            cost = min(cost, minSum(sr + 1, sc, grid, dp));
        if (sc + 1 < grid[0].size())
            cost = min(cost, minSum(sr, sc + 1, grid, dp));

        return dp[sr][sc] = cost + grid[sr][sc];
    }

    int minSum_DP(int sr, int sc, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        for (sr = grid.size() - 1; sr >= 0; sr--)
        {
            for (sc = grid[0].size() - 1; sc >= 0; sc--)
            {
                if (sr == grid.size() - 1 && sc == grid[0].size() - 1)
                {
                    dp[sr][sc] = grid[sr][sc];
                    continue;
                }

                int cost = 1e8;
                if (sr + 1 < grid.size())
                    cost = min(cost, dp[sr + 1][sc]);
                if (sc + 1 < grid[0].size())
                    cost = min(cost, dp[sr][sc + 1]);

                dp[sr][sc] = cost + grid[sr][sc];
            }
        }
        return dp[0][0];
    }
    int minPathSum(vector<vector<int>> &grid)
    {
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
        // return minSum(0, 0, grid, dp);
        return minSum_DP(0, 0, grid, dp);
    }
};