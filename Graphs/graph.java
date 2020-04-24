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

    public static int N = 5;
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

        // graph[7].add(5);
        // graph[7].add(6);
        // graph[5].add(4);
        // graph[5].add(2);
        // graph[6].add(4);
        // graph[6].add(3);
        // graph[2].add(1);
        // graph[3].add(1);
        // graph[1].add(0);

        graph[0].add(1);
        graph[1].add(2);
        graph[2].add(3);
        graph[3].add(4);

        display();
    }

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

    public static void khansAlgo_topoInBFS() {
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

    public static void solve() {
        constructGraph();
        // topoSort();
        khansAlgo_topoInBFS();
    }

    public static void main(String[] args) {
        solve();
    }
}