#include <iostream>
#include <vector>
using namespace std;
class Edge
{
public:
    int w = 0;
    int v = 0;
    Edge(int w, int v)
    {
        this->w = w;
        this->v = v;
    }
};

int n = 7;
vector<vector<Edge *>> graph(n, vector<Edge *>());

void display()
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << i << " -> ";
        for (Edge *e : graph[i])
        {
            cout << "(" << e->v << ", " << e->w << ")";
        }
        cout << endl;
    }
}

void addEdge(int u, int v, int w)
{
    if (u < 0 || v < 0 || u >= graph.size() || v >= graph.size())
        return;

    graph[u].push_back(new Edge(v, w));
    graph[v].push_back(new Edge(u, w));
}

void constructGraph()
{
    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(3, 2, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 3);
    addEdge(5, 6, 8);
    addEdge(5, 2, 2);

    display();
    cout << endl;
}

int hamiltonionPath(int vtx, int src, int vtxCount, vector<bool> &vis, string ans)
{
    if (vtxCount == graph.size() - 1)
    {
        for (Edge *e : graph[vtx])
        {
            if (e->v == src)
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
    for (Edge *e : graph[vtx])
    {
        if (!vis[e->v])
        {
            count += hamiltonionPath(e->v, src, vtxCount + 1, vis, ans + to_string(vtx) + " -> ");
        }
    }
    vis[vtx] = false;
    return count;
}

void solve()
{
    constructGraph();
    vector<bool> vis(n, false);
    cout << hamiltonionPath(0, 0, 0, vis, "") << endl;
}

int main(int args, char **argv)
{
    solve();
    return 0;
}