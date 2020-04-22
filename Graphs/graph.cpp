
// if we use * everywhere after Edge then it will be on heap
// then we also have to use -> instead of . in a lot of positions

#include <iostream>
#include <vector>

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
// vecto<vector<pair<int, int>>> graph(N, vector<pair<int, int>>());

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
    gp[v].push_back(Edge(u, w));
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

    addEdge(graph, 2, 5, 2);

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

void solve()
{
    constructGraph();
    // set1();
}

int main(int args, char **argv)
{
    solve();
    return 0;
}