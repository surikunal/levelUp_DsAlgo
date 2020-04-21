#include <iostream>
#include <vector>

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