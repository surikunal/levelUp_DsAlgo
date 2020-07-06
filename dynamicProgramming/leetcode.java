class Solution {

    // leetcode 70. Climbing Stairs
    // ============================
    public int climbStairs_mem(int n, int[] dp) {
        if (n <= 1)
            return dp[n] = 1;

        if (dp[n] != 0)
            return dp[n];

        int ans = climbStairs_mem(n - 1, dp) + climbStairs_mem(n - 2, dp);

        return ans;
    }

    public int climbStairs_dp(int n, int[] dp) {
        int N = n;
        for (n = 0; n <= N; n++) {
            if (n <= 1) {
                dp[n] = 1;
                continue;
            }

            int ans = dp[n - 1] + dp[n - 2];
            dp[n] = ans;
        }
        return dp[N];
    }

    public int climbStairs_btr(int n) {
        int a = 1, b = 1, sum = 1;
        for (int i = 2; i <= n; i++) {
            sum = a + b;
            a = b;
            b = sum;
        }
        return sum;
    }

    public int climbStairs(int n) {
        // int[] dp = new int[n + 1];
        // return climbStairs_mem(n, dp); // TLE
        // return climbStairs_dp(n, dp);
        return climbStairs_btr(n);
    }

    // leetcode 746. Min Cost Climbing
    // Stairs=========================
    public int minCost(int n, int[] cost) {// recursion
        if (n == 0 || n == 1)
            return 0;

        int a = minCost(n - 1, cost) + cost[n - 1];
        int b = minCost(n - 2, cost) + cost[n - 2];
        return Math.min(a, b);
    }

    public int minCost_DP(int n, int[] cost) {
        int[] dp = new int[n + 1];
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= n; i++)
            dp[i] = Math.min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        return dp[n];
    }

    public int minCost_btr(int n, int[] cost) {
        int a = 0, b = 0;
        for (int i = 2; i <= n; i++) {
            int temp = Math.min(a + cost[i - 2], b + cost[i - 1]);
            a = b;
            b = temp;
        }
        return b;
    }

    public int minCostClimbingStairs(int[] cost) {
        int n = cost.length;
        // return minCost(n, cost); // O(2^n) // TLE
        // return minCost_DP(n, cost); // O(n)
        return minCost_btr(n, cost); // O(n)
    }

    // https://practice.geeksforgeeks.org/problems/friends-pairing-problem/0

    static int[] dp = new int[1000];

    public int countFriendsPairings(int n) {
        if (dp[n] != -1)
            return dp[n];

        if (n > 2)
            return dp[n] = countFriendsPairings(n - 1) + (n - 1) * countFriendsPairings(n - 2);
        else
            return dp[n] = n;
    }

    public int countFriendsPairings_DP(int n) {
        int dp[] = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            if (i <= 2)
                dp[i] = i;
            else
                dp[i] = dp[i - 1] + (i - 1) * dp[i - 2];
        }
        return dp[n];
    }

    // leetcode 64. Minimum Path Sum
    // =============================
    public int minPathSum(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (i == n - 1 && j == m - 1)
                    continue;

                double a = i + 1 < n ? grid[i + 1][j] : 1e6;
                double b = j + 1 < m ? grid[i][j + 1] : 1e6;
                double cost = Math.min(a, b);
                grid[i][j] += cost;
            }
        }
        return grid[0][0];
    }
}