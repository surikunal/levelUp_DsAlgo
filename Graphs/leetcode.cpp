#include <iostream>
#include <vector>
#include <queue>

#define vvc vector<vector<char>>

using namespace std;

// 130.=======================================================================

void surroundedRegion_DFS(int r, int c, int n, int m, vector<vector<char>> &board)
{
    if (board[r][c] != 'O')
        return;

    board[r][c] = '#';
    if (r + 1 < n)
        surroundedRegion_DFS(r + 1, c, n, m, board);
    if (r - 1 >= 0)
        surroundedRegion_DFS(r - 1, c, n, m, board);
    if (c + 1 < m)
        surroundedRegion_DFS(r, c + 1, n, m, board);
    if (c - 1 >= 0)
        surroundedRegion_DFS(r, c - 1, n, m, board);
}

void solve(vector<vector<char>> &board)
{
    if (board.size() == 0)
        return;

    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; i++)
    {
        if (board[i][0] == 'O')
        {
            surroundedRegion_DFS(i, 0, n, m, board);
        }
        if (board[i][m - 1] == 'O')
        {
            surroundedRegion_DFS(i, m - 1, n, m, board);
        }
    }

    for (int j = 0; j < m; j++)
    {
        if (board[0][j] == 'O')
        {
            surroundedRegion_DFS(0, j, n, m, board);
        }
        if (board[n - 1][j] == 'O')
        {
            surroundedRegion_DFS(n - 1, j, n, m, board);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == '#') // not surrounded region
                board[i][j] = 'O';
            else if (board[i][j] == 'O') //surrounded region
                board[i][j] = 'X';
        }
    }
}

// 695 .=================================================================

class Solution
{
public:
    int maxArea_dfs(int r, int c, vector<vector<int>> &arr)
    {
        if (arr[r][c] != 1)
            return 0;

        arr[r][c] = 0;
        int n = arr.size();
        int m = arr[0].size();
        int count = 0;
        if (r + 1 < n)
            count += maxArea_dfs(r + 1, c, arr);
        if (r - 1 >= 0)
            count += maxArea_dfs(r - 1, c, arr);
        if (c + 1 < m)
            count += maxArea_dfs(r, c + 1, arr);
        if (c - 1 >= 0)
            count += maxArea_dfs(r, c - 1, arr);

        return count + 1;
    }
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        if (grid.size() == 0)
            return 0;

        int max_ = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    max_ = max(max_, maxArea_dfs(i, j, grid));
                }
            }
        }
        return max_;
    }
};

// 463. =========================================================

class Solution
{
public:
    // this question can also be done using DFS
    // but this is also a same complexicity solution
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int totalEdges = 0;
        int commonEdges = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    totalEdges += 4;

                    if (i + 1 < grid.size() && grid[i + 1][j] == 1)
                        commonEdges += 2;
                    if (j + 1 < grid[0].size() && grid[i][j + 1] == 1)
                        commonEdges += 2;
                }
            }
        }
        return (totalEdges - commonEdges);
    }
};

// 200.===============================================================
class Solution
{
public:
    void DFS(vector<vector<char>> &arr, int i, int j)
    {
        if (i < 0 || j < 0 || i >= arr.size() || j >= arr[0].size() || arr[i][j] == '0')
            return;
        arr[i][j] = '0';
        DFS(arr, i + 1, j);
        DFS(arr, i - 1, j);
        DFS(arr, i, j + 1);
        DFS(arr, i, j - 1);
    }

    int numIslands(vector<vector<char>> &grid)
    {
        int count = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    DFS(grid, i, j);
                }
            }
        }
        return count;
    }
};

// 1091.======================================================

class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        int n = grid.size();
        if (n == 0)
            return -1;
        int m = grid[0].size();
        if (m == 0)
            return -1;

        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1)
            return -1;

        int dir[8][2] = {{-1, -1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}, {0, 1}, {1, 0}, {1, 1}};
        queue<int> que;
        que.push(0);
        grid[0][0] = 1;
        int level = 1;
        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int rvtx = que.front();
                que.pop();
                int r = rvtx / m;
                int c = rvtx % m;

                if (r == n - 1 && c == m - 1)
                    return level;

                for (int d = 0; d < 8; d++)
                {
                    int x = r + dir[d][0];
                    int y = c + dir[d][1];
                    if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0)
                    {
                        que.push(x * m + y);
                        grid[x][y] = 1;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};

//leetcode 286.===========================================================

void wallsAndGates(vector<vector<int>> &grid)
{
    if (grid.size() == 0 || grid[0].size() == 0)
        return;

    int n = grid.size();
    int m = grid[0].size();

    int dirA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    queue<int> que;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 0)
                que.push((i * m + j));

    int level = 1;
    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            int r = rvtx / m;
            int c = rvtx % m;

            for (int d = 0; d < 4; d++)
            {
                int x = r + dirA[d][0];
                int y = c + dirA[d][1];

                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 2147483647)
                {
                    que.push((x * m + y));
                    grid[x][y] = level;
                }
            }
        }
        level++;
    }
}

// 994. ========================================================

class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        if (grid.size() == 0 || grid[0].size() == 0)
            return -1;

        int n = grid.size();
        int m = grid[0].size();

        int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        queue<int> que;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 2)
                {
                    que.push((i * m + j));
                }
            }
        }

        int level = 0; // considering starting as 0 level
        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int rvtx = que.front();
                que.pop();

                int r = rvtx / m;
                int c = rvtx % m;

                for (int d = 0; d < 4; d++)
                {
                    int x = r + dir[d][0];
                    int y = c + dir[d][1];

                    if (x >= 0 and y >= 0 and x < n and y < m and grid[x][y] == 1)
                    {
                        que.push((x * m + y));
                        grid[x][y] = 2;
                    }
                }
            }
            level++;
        }
        // now check check if any fresh orange is remaining then retrn -1
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1)
                {
                    return -1;
                }
            }
        }
        return level == 0 ? 0 : level - 1;
    }
};