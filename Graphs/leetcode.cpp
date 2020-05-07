#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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

// 207. =================================================

class Solution
{
public:
    vector<int> kahnsAlgo(int n, vector<vector<int>> &graph, vector<vector<int>> &prerequisites)
    {
        vector<int> indegree(n, 0);
        for (vector<int> ar : prerequisites)
        {
            indegree[ar[1]]++;
        }

        queue<int> que;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                que.push(i);
            }
        }

        vector<int> ans;
        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int rvtx = que.front();
                que.pop();

                ans.push_back(rvtx);

                for (int ele : graph[rvtx])
                {
                    if (--indegree[ele] == 0)
                    {
                        que.push(ele);
                    }
                }
            }
        }
        return ans;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {

        // that is how we make graph

        vector<vector<int>> graph(numCourses, vector<int>());
        for (vector<int> ar : prerequisites)
        {
            graph[ar[0]].push_back(ar[1]);
        }

        // now call kahns algo
        vector<int> ans = kahnsAlgo(numCourses, graph, prerequisites);

        return ans.size() == numCourses;
    }
};

// 210 . =========================================================

class Solution
{
public:
    vector<int> kahnsAlgo(int n, vector<vector<int>> &graph, vector<vector<int>> &prerequisites)
    {
        vector<int> indegree(n, 0);
        for (vector<int> ar : prerequisites)
        {
            indegree[ar[1]]++;
        }

        queue<int> que;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                que.push(i);
            }
        }

        vector<int> ans;
        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int rvtx = que.front();
                que.pop();

                ans.push_back(rvtx);

                for (int ele : graph[rvtx])
                {
                    if (--indegree[ele] == 0)
                    {
                        que.push(ele);
                    }
                }
            }
        }
        return ans;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {

        //* this is how we make graph

        vector<vector<int>> graph(numCourses, vector<int>());
        for (vector<int> ar : prerequisites)
        {
            graph[ar[0]].push_back(ar[1]);
        }

        // now call kahns algo
        vector<int> ans = kahnsAlgo(numCourses, graph, prerequisites);

        reverse(ans.begin(), ans.end());
        if (ans.size() != numCourses)
            return {};
        else
            return ans;
    }
};

// 329. ========================================================

class Solution
{
public:
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        int n = matrix.size();

        if (n == 0)
            return 0;
        int m = matrix[0].size();
        if (m == 0)
            return 0;
        vector<vector<int>> dirA = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        vector<vector<int>> outdegree(n, vector<int>(m, 0));

        int length = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int d = 0; d < 4; d++) // this loop is constant so this code n^2
                {
                    int x = i + dirA[d][0];
                    int y = j + dirA[d][1];

                    if (x >= 0 and y >= 0 and x < n and y < m and matrix[x][y] > matrix[i][j])
                        outdegree[x][y]++;
                }
            }
        }

        queue<int> que;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (outdegree[i][j] == 0)
                {
                    que.push(i * m + j);
                }
            }
        }

        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int rvtx = que.front();
                que.pop();

                int i = rvtx / m;
                int j = rvtx % m;

                for (int d = 0; d < 4; d++)
                {
                    int x = i + dirA[d][0];
                    int y = j + dirA[d][1];

                    if (x >= 0 and x < n and y >= 0 and y < m and matrix[x][y] > matrix[i][j] and --outdegree[x][y] == 0)
                        que.push(x * m + y);
                }
            }
            length++;
        }
        return length;
    }
};

// leetcode 815. ======================================================

class Solution
{
public:
    int numBusesToDestination(vector<vector<int>> &routes, int S, int T)
    {
        int n = routes.size();
        if (n == 0)
            return -1;

        unordered_map<int, vector<int>> map;
        for (int i = 0; i < n; i++)
            for (int ele : routes[i])
                map[ele].emplace_back(i);

        unordered_set<int> busStandVis;
        vector<bool> busVis(n, false);

        queue<int> que;
        que.push(S);
        int level = 0;
        busStandVis.insert(S);
        while (que.size() != 0)
        {
            int size = que.size();
            while (size-- > 0)
            {
                int stand = que.front();
                que.pop();

                if (stand == T)
                    return level;

                for (int bus : map[stand])
                {
                    if (busVis[bus])
                        continue;

                    for (int busStand : routes[bus])
                    {
                        if (busStandVis.count(busStand) == 0)
                        {
                            que.push(busStand);
                            busStandVis.insert(busStand);
                        }
                    }
                    busVis[bus] = true;
                }
            }
            level++;
        }
        return -1;
    }
};

// leetcode 684. =======================================================

vector<int> par;
vector<int> setSize;

int findPar(int vtx)
{
    if (par[vtx] == vtx)
        return vtx;
    return par[vtx] = findPar(par[vtx]);
}

void mergeSet(int p1, int p2)
{
    if (setSize[p1] < setSize[p2])
    {
        par[p1] = p2;
        setSize[p2] += setSize[p1];
    }
    else
    {
        par[p2] = p1;
        setSize[p1] += setSize[p2];
    }
}

vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    for (int i = 0; i <= edges.size(); i++)
    {
        par.push_back(i);
        setSize.push_back(1);
    }

    for (vector<int> ar : edges)
    {
        int u = ar[0];
        int v = ar[1];
        int p1 = findPar(u);
        int p2 = findPar(v);

        if (p1 != p2)
        {
            mergeSet(p1, p2);
        }
        else
        {
            return ar;
        }
    }
    return {};
}

// leetcode 547. ========================================

class Solution
{
public:
    // we have to find total number of **circles** of friends
    // means union find method
    vector<int> par;
    vector<int> setSize;

    int findPar(int vtx)
    {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par[vtx]);
    }

    void mergeSet(int p1, int p2)
    {
        if (setSize[p1] < setSize[p2])
        {
            par[p1] = p2;
            setSize[p2] += setSize[p1];
        }
        else
        {
            par[p2] = p1;
            setSize[p1] += setSize[p2];
        }
    }

    int findCircleNum(vector<vector<int>> &arr)
    {
        if (arr.empty())
            return 0;

        int n = arr.size();
        // declare self as parent
        for (int i = 0; i < n; i++)
        {
            par.emplace_back(i);
            setSize.emplace_back(1);
        }

        int count = n;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++) // started from (i+1) just to avoid re-calculation but it is OK if we start from 0 as well
            {
                if (arr[i][j] != 0 && i != j) // if direct friend
                {
                    int p1 = findPar(i);
                    int p2 = findPar(j);

                    if (p1 != p2)
                    {
                        count--;
                        mergeSet(p1, p2);
                    }
                }
            }
        }
        return count;
    }
};

// 1061. ================================================
vector<int> par;
int findPar(int vtx)
{
    if (par[vtx] = vtx)
        return vtx;
    return par[vtx] = findPar(par[vtx]);
}

string smallestEquivalentString(string A, string B, string S)
{
    vector<int> par;
    for (int i = 0; i < 26; i++)
        par.emplace_back(i);

    for (int i = 0; i < A.length(); i++)
    {
        int p1 = findPar(A[i] - 'a');
        int p2 = findPar(B[i] - 'a');
        par[p1] = min(p1, p2);
        par[p2] = min(p1, p2);
    }

    string ans = "";
    for (int i = 0; i < S.length(); i++)
        ans += (char)(findPar(S[i] - 'a') + 'a');

    return ans;
}

// 200. =====================================================
//* using union find method

class Solution
{
public:
    vector<int> par;
    int findPar(int vtx)
    {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par[vtx]);
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        if (n == 0)
            return 0;
        int m = grid[0].size();
        if (m == 0)
            return 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                par.push_back(i * m + j);

        int noOfOnes = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    noOfOnes++;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    if (j + 1 < m && grid[i][j + 1] == '1')
                    {
                        int p1 = findPar(i * m + j);
                        int p2 = findPar(i * m + j + 1);

                        if (p1 != p2)
                        {
                            par[p2] = p1;
                            noOfOnes--;
                        }
                    }

                    if (i + 1 < n && grid[i + 1][j] == '1')
                    {
                        int p1 = findPar(i * m + j);
                        int p2 = findPar((i + 1) * m + j);

                        if (p1 != p2)
                        {
                            par[p2] = p1;
                            noOfOnes--;
                        }
                    }
                }
            }
        }
        return noOfOnes;
    }
};

// 839. =====================================================

class Solution
{
public:
    // using union find method
    vector<int> par;
    int findPar(int vtx)
    {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par[vtx]);
    }

    bool isSimilar(string &p, string &q)
    {
        int count = 0;
        for (int i = 0; i < p.length(); i++)
        {
            if (p[i] != q[i] && ++count > 2)
            {
                return false;
            }
        }
        return true;
    }

    int numSimilarGroups(vector<string> &A)
    {
        int n = A.size();
        for (int i = 0; i < n; i++)
            par.emplace_back(i);

        int group = n;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (isSimilar(A[i], A[j]))
                {
                    int p1 = findPar(i);
                    int p2 = findPar(j);

                    if (p1 != p2)
                    {
                        par[p1] = p2;
                        group--;
                    }
                }
            }
        }
        return group;
    }
};

// 1168. =======================================================
//* premium question
class Solution
{
public:
    vector<int> par;
    int findPar(int vtx)
    {
        if (par[vtx] == vtx)
            return vtx;
        return par[vtx] = findPar(par[vtx]);
    }

    int minCostToSupplyWater(int n, vector<int> &wells, vector<vector<int>> &pipes)
    {
        for (int i = 0; i < wells.size(); i++)
        {
            pipes.push_back({0, i + 1, wells[i]});
            par.push_back(i);
        }
        par.push_back(wells.size());

        sort(pipes.begin(), pipes.end(), [](vector<int>& a, vector<int>& b){
            return a[2] < b[2];
        });        

        int cost = 0;
        for (vector<int> &p: pipes)
        {
            int p1 = findPar(p[0]);
            int p2 = findPar(p[1]);

            if (p1 != p2)
            {
                cost += p[2];
                par[p1] = p2;
            }
        }
        return cost;
    }
};

//Hacker earth: https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/practice-problems/algorithm/mr-president/

#define lli long long int
vector<int> par;

int mrPresident()
{
	lli n, m, k;
    // cities, roads, budget
	cin >> n >> m >> k;

	vector<vector<int>> graph, kruskalGraph;
    // that's how we make a graph here
	while (m--) // for all roads
	{
		int u, v, w;
        cin >> u >> v >> w;

        vector<int> ar = {u, v, w};
        graph.push_back(ar);
        // or graph.push_back({u, v, w});
	}

    // graph is sorted now according to weights in ascending order
    sort(graph.begin(), graph.end(), [](vector<int>& a, vector<int>& b){
        return a[2] < b[2];
    });

    // declare every CITY as self parent 
    for (int i = 0; i <= n; i++)
    {
        par.push_back(i);
    }

    // now start UNION FIND method
    lli MSTweightCount = 0;
    for (vector<int> g: graph)
    {
        // asked for parents
        int p1 = findPar(g[0]);
        int p2 = findPar(g[1]);

        if (p1 != p2)
        {
            par[p1] = p2;   // random (maybe it will make it slow)
            kruskalGraph.push_back(g); // making a MST (without cycle and mini weight)
            MSTweightCount += g[2];
        }
    }

    // till here we have made a MST , if it satisfies the question the we return it otherwise we will make a super road

    int componentCount = 0; // always check for GCC
    for (int i = 1; i <= n; i++)    // bcz city count is stared from 1 in question (constraints)
        if (par[i] == i && ++componentCount > 1)
            return -1;
    
    int superRoad = 0;
    // started from end bcz road with highest weight is on last dur to sort
    for (int i = kruskalGraph.size() - 1; i >= 0; i--)
    {
        if (MSTweightCount <= k)
            break;
        
        MSTweightCount = MSTweightCount - kruskalGraph[i][2] + 1;
        superRoad++;
    }
    return MSTweightCount <= k ? superRoad : -1;
    // this check is for the condition if
    // all roads are converted to superRoad and still it's cost is not less than k
}






















