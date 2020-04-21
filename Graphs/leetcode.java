
// 130. ===========================================================

class Solution {
    public void surroundedRegion_DFS(int r, int c, int n, int m, char[][] board) {
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

    public void solve(char[][] board) {
        if (board.length == 0)
            return;

        int n = board.length;
        int m = board[0].length;
        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                surroundedRegion_DFS(i, 0, n, m, board);
            }
            if (board[i][m - 1] == 'O') {
                surroundedRegion_DFS(i, m - 1, n, m, board);
            }
        }

        for (int j = 0; j < m; j++) {
            if (board[0][j] == 'O') {
                surroundedRegion_DFS(0, j, n, m, board);
            }
            if (board[n - 1][j] == 'O') {
                surroundedRegion_DFS(n - 1, j, n, m, board);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == '#') // not surrounded region
                    board[i][j] = 'O';
                else if (board[i][j] == 'O') // surrounded region
                    board[i][j] = 'X';
            }
        }
    }
}

// 695 .=================================================================

class Solution {
    public int maxAreaOfIsland(int[][] grid) {
        if (grid.length == 0)
            return 0;

        int n = grid.length;
        int m = grid[0].length;
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    maxArea = Math.max(maxArea, dfs(i, j, grid));
                }
            }
        }
        return maxArea;
    }

    public int dfs(int r, int c, int[][] arr) {
        if (r < 0 || c < 0 || r >= arr.length || c >= arr[0].length || arr[r][c] != 1) {
            return 0;
        }

        arr[r][c] = '0';
        int count = 0;
        count += dfs(r + 1, c, arr);
        count += dfs(r - 1, c, arr);
        count += dfs(r, c + 1, arr);
        count += dfs(r, c - 1, arr);

        return count + 1; // +1 is for mySelf (source)
    }
}

// 463. ==================================================

class Solution {
    // this question can also be done using DFS
    // but this is also a same complexicity solution
    int islandPerimeter(int[][] grid) {
        int totalEdges = 0;
        int commonEdges = 0;

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    totalEdges += 4;

                    if (i + 1 < grid.length && grid[i + 1][j] == 1)
                        commonEdges += 2;
                    if (j + 1 < grid[0].length && grid[i][j + 1] == 1)
                        commonEdges += 2;
                }
            }
        }
        return (totalEdges - commonEdges);
    }
}