import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.HashSet;

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

class Solution1 {
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

class Solution2 {
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

// 200.==========================================================

class Solution3 {

    public void DFS(char[][] arr, int i, int j) {
        if (i < 0 || j < 0 || i >= arr.length || j >= arr[0].length || arr[i][j] == '0')
            return;
        arr[i][j] = '0';
        DFS(arr, i + 1, j);
        DFS(arr, i - 1, j);
        DFS(arr, i, j + 1);
        DFS(arr, i, j - 1);
    }

    public int numIslands(char[][] grid) {
        int count = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    DFS(grid, i, j);
                }
            }
        }
        return count;
    }

}

// ! cpp have some extra question so pls kindly check there

// leetcode 815.=======================================================
class Solution6 {
    public int numBusesToDestination(int[][] routes, int S, int T) {
        if (routes.length == 0)
            return -1;
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
        for (int i = 0; i < routes.length; i++) {
            for (int ele : routes[i]) {
                map.putIfAbsent(ele, new ArrayList<>());
                map.get(ele).add(i);
            }
        }

        HashSet<Integer> busStandVis = new HashSet();
        boolean[] busVis = new boolean[routes.length];

        LinkedList<Integer> que = new LinkedList<>();
        que.addLast(S);
        int level = 0;
        busStandVis.add(S);

        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int stand = que.removeFirst();

                if (stand == T)
                    return level;

                for (int bus : map.get(stand)) {
                    if (busVis[bus])
                        continue;

                    for (int busStand : routes[bus]) {
                        if (!busStandVis.contains(busStand)) {
                            que.addLast(busStand);
                            busStandVis.add(busStand);
                        }
                    }
                    busVis[bus] = true;
                }
            }
            level++;
        }

        return -1;
    }
}

// 684. =====================================================

class Solution4 {
    int[] par;
    int[] set_size;

    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        par = new int[n + 1];
        set_size = new int[n + 1];
        Arrays.fill(set_size, 1);
        int[] ans = new int[0];
        for (int i = 0; i <= n; i++) {
            par[i] = i;
        }
        for (int[] edge : edges) {
            int p1 = findpar(edge[0]);
            int p2 = findpar(edge[1]);
            if (p1 != p2) {
                mergeset(p1, p2);
            } else {
                return edge;
            }
        }
        return ans;
    }

    public int findpar(int vtx) {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findpar(par[vtx]);
    }

    public void mergeset(int p1, int p2) {
        if (set_size[p1] < set_size[p2]) {
            par[p1] = p2;
            set_size[p2] += set_size[p1];
        } else {
            par[p2] = p1;
            set_size[p1] += set_size[p2];
        }
    }

}

// leetcode 547. ========================================

class Solution5 {
    int findPar(int[] par, int vtx) {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par, par[vtx]);
    }

    void mergeSet(int p1, int p2, int[] setSize, int[] par) {
        if (setSize[p1] < setSize[p2]) {
            par[p1] = p2;
            setSize[p2] += setSize[p1];
        } else {
            par[p2] = p1;
            setSize[p1] += setSize[p2];
        }
    }

    public int findCircleNum(int[][] arr) {
        int n = arr.length;
        if (n == 0)
            return 0;

        int[] par = new int[n];
        int[] setSize = new int[n];

        for (int i = 0; i < n; i++) {
            par[i] = i;
        }
        Arrays.fill(setSize, 1);

        int count = n;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i][j] != 0 && i != j) {
                    int p1 = findPar(par, i);
                    int p2 = findPar(par, j);

                    if (p1 != p2) {
                        mergeSet(p1, p2, setSize, par);
                        count--;
                    }
                }
            }
        }
        return count;
    }
}
