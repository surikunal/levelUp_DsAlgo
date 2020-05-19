
// if we use * everywhere after Edge then it will be on heap
// then we also have to use -> instead of . in a lot of positions

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define vi vector<int>
#define vb vector<bool>
#define vii vector<vector<int>>
#define vbb vector<vector<bool>>

using namespace std;
class Edge
{
public:
    int w = 0;
    int v = 0;
    Edge(int v, int w)
    {
        this->w = w;
        this->v = v;
    }
};

int N = 7;
vector<vector<Edge>> graph(N, vector<Edge>());
// vector<vector<pair<int, int>>> NumGraph(N, vector<pair<int, int>>());

void display(vector<vector<Edge>> &gp)
{
    for (int i = 0; i < gp.size(); i++)
    {
        cout << i << " -> ";
        for (Edge e : gp[i])
        {
            cout << "(" << e.v << ", " << e.w << ")"; //here we will use -> instead of . if we use * everywhere after Edge bcz then it will be on heap
        }
        cout << endl;
    }
    cout << endl;
}

int findEdge(int v1, int v2)
{
    int vtx = -1;
    for (int i = 0; i < graph[v1].size(); i++)
    {
        Edge e = graph[v1][i];
        if (e.v == v2)
        {
            vtx = i;
            break;
        }
    }
    return vtx;
}

void removeEdge(int u, int v)
{

    int idx1 = findEdge(u, v);
    int idx2 = findEdge(v, u);

    graph[u].erase(graph[u].begin() + idx1);
    graph[v].erase(graph[v].begin() + idx2);
}

void removeVtx(int vtx)
{
    while (graph[vtx].size() != 0)
    {
        // int vtx2 = graph[vtx][graph[vtx].size() - 1];

        Edge e = graph[vtx].back();
        removeEdge(vtx, e.v);
    }
}

void addEdge(vector<vector<Edge>> &gp, int u, int v, int w)
{
    // if (u < 0 || v < 0 || u >= graph.size() || v >= graph.size())
    //     return;

    gp[u].push_back(Edge(v, w)); // but if we make it on heap then we have to write = new Edge(v, w)
    gp[v].push_back(Edge(u, w)); // comment for toposort
}

void constructGraph()
{
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 3);
    addEdge(graph, 5, 6, 8);

    // addEdge(graph, 2, 5, 2);

    display(graph);
    cout << endl;
}

// has path ================================================================

bool hasPath(int src, int dest, vector<bool> &vis)
{
    if (src == dest)
        return true;

    vis[src] = true;
    bool res = false;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            res = res || hasPath(e.v, dest, vis);
        }
    }
    return res;
}

//all path======================================================================

int allPath(int src, int dest, vector<bool> &vis, int w, string ans)
{
    if (src == dest)
    {
        cout << ans << " @ " << w << endl;
        return 1;
    }

    vis[src] = true;
    int count = 0;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            count += allPath(e.v, dest, vis, w + e.w, ans + to_string(src) + " ");
        }
    }
    vis[src] = false;
    return count;
}

// all Solutions. ==============================================================

int swsf = 1e8;
string spsf = "";

int lwsf = -1;
string lpsf = "";

void allSol(int src, int dest, vector<bool> &vis, int wsf, string psf)
{
    if (src == dest)
    {
        if (wsf < swsf)
        {
            swsf = wsf;
            spsf = psf + to_string(dest);
        }

        if (wsf > lwsf)
        {
            lwsf = wsf;
            lpsf = psf + to_string(dest);
        }

        // cout << spsf << " @ " << swsf << endl;
        // cout << lpsf << " @ " << lwsf << endl;
    }

    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            allSol(e.v, dest, vis, wsf + e.w, psf + to_string(src) + " -> ");
        }
    }
    vis[src] = false;
}

// hamiltonion path. ===========================================================
int hamiltonionPath(int vtx, int src, int vtxCount, vector<bool> &vis, string ans)
{
    if (vtxCount == graph.size() - 1)
    {
        for (Edge e : graph[vtx])
        {
            if (e.v == src)
            {
                cout << "cycle : " + ans + to_string(vtx) << endl;
                return 1;
            }
        }

        cout << "path : " + ans + to_string(vtx) << endl;
        return 1;
    }

    vis[vtx] = true;
    int count = 0;
    for (Edge e : graph[vtx])
    {
        if (!vis[e.v])
        {
            count += hamiltonionPath(e.v, src, vtxCount + 1, vis, ans + to_string(vtx) + " -> ");
        }
    }
    vis[vtx] = false;
    return count;
}

// hamiltonion again .==============================================================
void hamiltonionPath_01(int src, int osrc, vb &vis, int count, string ans)
{
    if (count == vis.size() - 1)
    {
        int idx = findEdge(src, osrc);
        // means if there is any branch from osrc(destination) to src(starting) then there is a cycle
        if (idx != -1)
            cout << "Cycle : " + ans + to_string(src) << endl;
        // means if idx == -1 that means there is no edge from osrc to src that means it is a path and not a cycle
        else
            cout << "Path : " + ans + to_string(src) << endl;
        return;
    }

    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            hamiltonionPath_01(e.v, osrc, vis, count + 1, ans + to_string(src) + " ");
        }
    }
    vis[src] = false;
}

void preOrder(int src, vb &vis, int w, string ans)
{
    vis[src] = true;
    cout << ans << "@" << w << endl;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            preOrder(e.v, vis, w + e.w, ans + to_string(e.v) + " ");
        }
    }
    vis[src] = false;
}

int gcc_dfs(int idx, vb &vis)
{
    vis[idx] = true;
    int count = 0;

    for (Edge e : graph[idx])
        if (!vis[idx])
            count += gcc_dfs(e.v, vis);

    return count + 1;
}

int getConnectedComponents()
{
    vb vis(N, false);
    int count = 0;
    int maxSize = 0;
    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            count++;
            maxSize = max(maxSize, gcc_dfs(i, vis));
        }
    }
    cout << maxSize << endl;
    return count;
}

void set1()
{
    // removeEdge(3, 4);
    // addEdge(graph, 2, 0, 2);
    // display(graph);

    vector<bool> vis(N, false);

    allSol(0, 6, vis, 0, "");
    cout << spsf << " @ " << swsf << endl;
    cout << lpsf << " @ " << lwsf << endl;

    cout << (boolalpha) << hasPath(0, 6, vis) << endl;

    cout << allPath(0, 6, vis, 0, "") << endl;

    cout << hamiltonionPath(0, 0, 0, vis, "") << endl;

    preOrder(0, vis, 0, "");

    hamiltonionPath_01(0, 6, vis, 0, "");

    cout << getConnectedComponents() << endl;
}

void bfs(int src, vector<bool> &vis)
{
    queue<pair<int, string>> que;
    que.push({src, to_string(src) + ""}); // as it is pair so we have to push it like this
    // and to type cast it to string we have added an enpty string to src
    int desti = 6;

    while (que.size() != 0)
    {
        pair<int, string> rvtx = que.front();
        que.pop();

        if (vis[rvtx.first])
        {
            cout << "Cycle path: " << rvtx.second << endl;
            continue;
        }

        if (rvtx.first == desti)
        {
            cout << "destination path: " << rvtx.second << endl;
        }

        vis[rvtx.first] = true; // as it is pair
        for (Edge e : graph[rvtx.first])
        {
            if (!vis[e.v])
            {
                que.push({e.v, rvtx.second + to_string(e.v)});
            }
        }
    }
}

void bfs1(int src, vector<int> &vis)
{
    queue<int> que;
    int level = 0;
    int cycle = 0;
    int desti = 6;
    que.push(src);
    que.push(-1);

    while (que.size() != 0)
    {
        int rvtx = que.front();
        que.pop();

        if (rvtx == -1)
        {
            level++;
            que.push(-1);
            continue;
        }

        if (vis[rvtx])
        {
            cout << "cycle: " << ++cycle << " @ " << rvtx << endl;
            continue;
        }

        if (rvtx == desti)
        {
            cout << "goal: " << level << endl;
        }
        vis[rvtx] = true;
        for (Edge e : graph[rvtx])
        {
            if (!vis[e.v])
            {
                que.push(e.v);
            }
        }
    }
}

void bfs2(int src, vector<bool> &vis)
{
    int desti = 6;
    queue<int> que;
    int cycle = 0;
    int level = 0;
    que.push(src);

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            if (vis[rvtx])
            {
                cout << "cycle no " + to_string(cycle) + " at : " << rvtx << endl;
                cycle++;
                continue;
            }

            if (rvtx == desti)
            {
                cout << "destination : " << level << endl;
            }

            vis[rvtx] = true;
            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                }
            }
        }
        level++;
    }
}

void bfs3(int src, vector<bool> &vis)
{
    int desti = 6;
    queue<int> que;
    int cycle = 0;
    int level = 0;
    que.push(src);

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            int rvtx = que.front();
            que.pop();

            if (rvtx == desti)
            {
                cout << "destination : " << level << endl;
            }

            for (Edge e : graph[rvtx])
            {
                if (!vis[e.v])
                {
                    que.push(e.v);
                    vis[rvtx] = true;
                }
            }
        }
        level++;
    }
}

bool isBipatite_BFS_(int src, vector<int> &vis)
{
    queue<pair<int, int>> que; // first is src , second is color
    que.push({src, 0});        // src is red
    int cycle = 0;

    while (que.size() != 0)
    {
        int size = que.size();
        while (size-- > 0)
        {
            pair<int, int> rvtx = que.front();
            que.pop();

            if (vis[rvtx.first] != -1) // already visited cycle
            {
                cycle++;
                if (vis[rvtx.first] != rvtx.second) // check for conflict
                {
                    return false;
                }
            }

            vis[rvtx.first] = rvtx.second;
            for (Edge e : graph[rvtx.first])
            {
                if (vis[e.v] == -1)
                {
                    que.push({e.v, (rvtx.second + 1) % 2});
                }
            }
        }
    }
    return true;
}

void isBipatite_BFS()
{
    // loop is for when graph is divided in pieces
    // so we have to check for each peace

    vector<int> vis(N, -1); // -1 : unvisited, 0 : red, 1 : green
    for (int i = 0; i < N; i++)
    {
        if (vis[i] == -1)
        {
            cout << (boolalpha) << isBipatite_BFS_(i, vis) << endl;
        }
    }
}

void topoSort_(int src, vector<bool> &vis, vector<int> &stack)
{
    vis[src] = false;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            topoSort_(e.v, vis, stack);
        }
    }

    stack.push_back(src);
}

void topologicalSort()
{
    vector<bool> vis(N, false);
    vector<int> stack;

    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            topoSort_(i, vis, stack);
        }
    }
}

//. kruskal algorithum =================================

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
    if (setSize[p1] > setSize[p2])
    {
        par[p2] = p1;
        setSize[p1] += setSize[p2];
    }
    else
    {
        par[p1] = p2;
        setSize[p2] += setSize[p1];
    }
}

void kruskalAlgo(vector<vector<int>> &arr)
{
    vector<vector<Edge>> kruskalGraph(arr.size(), vector<Edge>());
    // making a new graph (but it is not compulsory in kruskal algo)

    sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2]; // this - other in java but replace '-' with '<' in cpp
        //*  increasing by default
    });

    for (vector<int> &ar : arr)
    {
        int u = ar[0];
        int v = ar[1];
        int p1 = findPar(u);
        int p2 = findPar(v);

        if (p1 != p2)
        {
            mergeSet(p1, p2);
            addEdge(kruskalGraph, u, v, ar[2]);
        }
    }
    display(kruskalGraph);
}

// digikstra ===========================================

class pair_
{
public:
    int src;
    int par;
    int w;
    int wsf;

    pair_(int src, int par, int w, int wsf)
    {
        this->src = src;
        this->par = par;
        this->w = w;
        this->wsf = wsf;
    }

    /*
    * bool operator<(pair_ const &p1) const
    *{
    *    return p1.age > this->age;  // max
    *}
    *
    */
};

struct dijikstraComparator
{
public:
    bool operator()(pair_ &p1, pair_ &p2)
    {
        return p1.wsf > p2.wsf; // default is min PQ
        // return p2.wsf > p1.wsf;  // max PQ
    }
};

void dijikstraAlgo(int src)
{
    vector<vector<Edge>> dijikstraGraph(N, vector<Edge>());
    priority_queue<pair_, vector<pair_>, dijikstraComparator> pq; // by default minPQ

    vector<bool> vis(N, false);
    pq.push(pair_(src, -1, 0, 0));

    while (pq.size() != 0)
    {
        int size = pq.size();
        while (size-- > 0)
        {
            pair_ rvtx = pq.top();
            pq.pop();

            if (vis[rvtx.src])
                continue; // cycle

            if (rvtx.par != -1)
            {
                addEdge(dijikstraGraph, rvtx.src, rvtx.par, rvtx.w);
            }

            vis[rvtx.src] = true;
            for (Edge e : graph[rvtx.src])
            {
                if (!vis[e.v])
                {
                    pq.push(pair_(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
                }
            }
        }
    }
    display(dijikstraGraph);
}

// prims algorithum. =========================================

struct primsComparator
{
public:
    bool operator()(pair_ &p1, pair_ &p2)
    {
        return p1.w > p2.w; // default is min PQ
        // return p2.wsf > p1.wsf;  // max PQ
    }
};

void primsAlgo(int src)
{
    vector<vector<Edge>> primsGraph(N, vector<Edge>());
    priority_queue<pair_, vector<pair_>, primsComparator> pq; // by default minPQ

    vector<bool> vis(N, false);
    pq.push(pair_(src, -1, 0, 0));

    while (pq.size() != 0)
    {
        int size = pq.size();
        while (size-- > 0)
        {
            pair_ rvtx = pq.top();
            pq.pop();

            if (vis[rvtx.src])
                continue; // cycle

            if (rvtx.par != -1)
            {
                addEdge(primsGraph, rvtx.src, rvtx.par, rvtx.w);
            }

            vis[rvtx.src] = true;
            for (Edge e : graph[rvtx.src])
            {
                if (!vis[e.v])
                {
                    pq.push(pair_(e.v, rvtx.src, e.w, rvtx.wsf + e.w));
                }
            }
        }
    }
    display(primsGraph);
}

// bellman ford algorithum. ====================================
// used to determine negetive cycle. ===========================

// using 2D dp , which is just to show to dry run
void bellmanFordAlgo(vector<vector<int>> &graph, int src)
{
    int INF = 1e8;
    vector<vector<int>> dp(graph.size(), vector<int>(graph.size() + 1, INF)); // size+1 is for the last iteration which is used to check negetive cycle
    dp[src][0] = 0;
    bool isNegetiveCycle = false;

    for (int i = 1; i <= graph.size(); i++) // traversing in coloumns, and starting from 1 bcz 0th index have default values
    {
        for (int j = 0; j < graph.size(); j++)
        {
            dp[j][i] = dp[j][i - 1]; // copying again and again (useless)
        }

        for (vector<int> &e : graph)
        {
            int u = e[0], v = e[1], w = e[2];

            if (dp[u][i - 1] == INF)
                continue;

            int temp = dp[v][i];
            dp[v][i] = min(dp[v][i], dp[v][i - 1] + w);

            if (i == graph.size() && dp[v][i] != temp)
                isNegetiveCycle = true;
        }
    }
}

//now using 1D dp
void bellmanFord_1D(vector<vector<int>> &graph, int src)
{
    int INF = 1e8;
    vector<int> dp(graph.size(), INF);
    dp[src] = 0;
    bool isNegetiveCycle = false;

    for (int i = 1; i <= graph.size(); i++)
    {
        for (vector<int> &e : graph)
        {
            int u = e[0], v = e[1], w = e[2];
            if (u == INF)
                continue;

            int temp = dp[v];

            dp[v] = min(dp[v], dp[u] + w);

            if (i == graph.size() && dp[v] != temp)
                isNegetiveCycle = true;
        }
    }
}

// basic. ======================================================

void set2()
{
    vector<int> visInt(N, false);
    vector<bool> visBool(N, false);
    // bfs(0, visBool);
    // bfs1(0, visInt);
    // bfs2(0, visBool);
    // bfs3(0, visBool); // when cycle is not a concern

    // isBipatite_BFS();

    // topologicalSort();  //* check this function in java too

    //* Strongly connected Components is in JAVA file

    // kruskalAlgo(NumGraph);  //?????????????????????

    dijikstraAlgo(6);

    primsAlgo(6);
}

void solve()
{
    constructGraph();
    // set1();
    set2();
}

int main(int args, char **argv)
{
    solve();
    return 0;
}