import java.util.ArrayList;
import java.util.LinkedList;

public class graph {
    public static class Edge {
        int w = 0;
        int v = 0;

        Edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }

    public static int N = 8;
    // public static ArrayList<Edge>[] graph; // array of arraylist
    public static ArrayList<Integer>[] graph;

    public static void addEdge(ArrayList<Integer>[] graph, int u, int v) {
        graph[u].add(v); // inetger type
        // graph[v].add(new Edge(u, w));
    }

    public static void display() {
        for (int i = 0; i < graph.length; i++) {
            System.out.print(i + " -> ");
            for (Integer e : graph[i]) {
                System.out.print("(" + e + ") ");
            }
            System.out.println();
        }
    }

    @SuppressWarnings("unchecked")
    public static void constructGraph() {
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<Integer>();
        }

        // addEdge(graph, 0, 1, 10);
        // addEdge(graph, 0, 3, 10);
        // addEdge(graph, 1, 2, 10);
        // addEdge(graph, 2, 3, 40);
        // addEdge(graph, 3, 4, 2);
        // addEdge(graph, 4, 5, 2);
        // addEdge(graph, 4, 6, 3);
        // addEdge(graph, 5, 6, 8);

        graph[7].add(5);
        graph[7].add(6);
        graph[5].add(4);
        graph[5].add(2);
        graph[6].add(4);
        graph[6].add(3);
        graph[2].add(1);
        graph[3].add(1);
        graph[1].add(0);
        display();
    }

    // * topological sort using DFS

    public static void topoSort_(int src, boolean[] vis, ArrayList<Integer> ans) {
        vis[src] = true;
        for (Integer e : graph[src]) {
            if (!vis[e]) {
                topoSort_(e, vis, ans);
            }
        }

        ans.add(src);
    }

    public static void topoSort() {

        boolean[] vis = new boolean[N];
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                topoSort_(i, vis, ans);
            }
        }

        for (int i = ans.size() - 1; i >= 0; i--) {
            System.out.print(ans.get(i) + " ");
        }
        System.out.println();
    }

    // * topological sort using BFS
    // * also called as Kahns Algorithum

    public static void kahnsAlgo_topoInBFS() {
        int[] indegree = new int[N];
        for (int i = 0; i < N; i++) {
            for (Integer e : graph[i]) {
                indegree[e]++;
            }
        }

        LinkedList<Integer> que = new LinkedList<>();
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                que.addLast(i);
            }
        }

        // BFS
        ArrayList<Integer> ans = new ArrayList<>();
        while (que.size() != 0) {
            int size = que.size();
            while (size-- > 0) {
                int rvtx = que.removeFirst();
                // only that element is added whose indegree is Zero
                // bcz queue has only those elements whos indegree is Zero
                ans.add(rvtx);

                for (int e : graph[rvtx]) {
                    if (--indegree[e] == 0) {
                        que.addLast(e);
                    }
                }
            }
        }

        if (ans.size() != 0)
            System.out.println("Cycle");
        else
            System.out.println(ans);
    }

    // topological sort when cycle can be detected too
    public static void topologicalSortCycle() {
        int[] vis = new int[N];
        ArrayList<Integer> ans = new ArrayList<>();

        boolean res = false;

        for (int i = 0; i < N && !res; i++) // so that we can reach each and every node even if it not connected anyone
        {
            if (vis[i] == 0) {
                res = res || topologicalSortCycle_(vis, ans, i);
            }
        }

        if (!res)
            for (int i = ans.size() - 1; i >= 0; i--)
                System.out.println(ans.get(i) + " ");
        else
            System.out.println("cycle");
    }

    public static boolean topologicalSortCycle_(int[] vis, ArrayList<Integer> ans, int src) // faith: it will detect
                                                                                            // cycle
    {
        if (vis[src] == 1) // cycle detected
            return true;
        if (vis[src] == 2) // already visited
            return false;

        boolean res = false;
        vis[src] = 1;
        for (int e : graph[src])
            res = res || topologicalSortCycle_(vis, ans, e);

        vis[src] = 2;
        ans.add(src);
        return res;
    }

    // * Strongly Connected Components
    public static int DFS_SCC(int src, ArrayList<Integer>[] ngraph, boolean[] vis, ArrayList<Integer> ans) {
        vis[src] = true;
        int count = 0;
        for (int e : ngraph[src]) {
            if (!vis[e]) {
                count += DFS_SCC(e, ngraph, vis, ans);
            }
        }
        ans.add(src);
        return count + 1;
    }

    public static void SCC() {
        boolean[] vis = new boolean[N];
        ArrayList<Integer> ans = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            if (!vis[i])
                topoSort_(i, vis, ans);
        }

        ArrayList<Integer>[] ngraph = new ArrayList[N];
        for (int i = 0; i < N; i++)
            ngraph[i] = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            for (int ele : graph[i]) {
                ngraph[ele].add(i);
            }
        }

        vis = new boolean[N];

        for (int i = ans.size() - 1; i >= 0; i--) {
            if (!vis[ans.get(i)]) {
                ArrayList<Integer> ans_ = new ArrayList<>();
                System.out.print(DFS_SCC(ans.get(i), ngraph, vis, ans_));
                System.out.println(ans_);
            }
        }
    }

    public static void solve() {
        constructGraph();
        // topoSort();
        // kahnsAlgo_topoInBFS();
        SCC();
    }

    public static void main(String[] args) {
        solve();
    }
}
