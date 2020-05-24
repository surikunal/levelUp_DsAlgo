class Trees {
    public static void main(String[] args) {
        solve();
    }

    public static class Node {
        int data = 0;
        Node left = null;
        Node right = null;

        Node(int data) {
            this.data = data;
        }

        Node(int data, Node left, Node right) {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    public static int idx = 0;

    public static Node constructTree(int[] arr) {
        if (idx == arr.length || arr[idx] == -1) {
            idx++;
            return null;
        }

        Node node = new Node(arr[idx]);
        idx++;
        node.left = constructTree(arr);
        node.right = constructTree(arr);

        return node;
    }

    public static void display(Node node) {
        if (node == null)
            return;

        String str = "";
        str += node.left != null ? node.left.data : " . ";
        str += " <- " + node.data + " -> ";
        str += node.right != null ? node.right.data : " . ";
        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    // BASIC. ==================================================

    public static int size(Node node) {
        if (node == null)
            return 0;
        return size(node.left) + size(node.right) + 1;
    }

    public static int height(Node node) {
        if (node == null)
            return -1; // return -1, height w.r.t edge, return 0, height w.r.t node.
        return Math.max(height(node.left), height(node.right)) + 1;
    }

    public static int Maxi(Node node) {
        if (node == null)
            return (int) -1e8;
        return Math.max(Math.max(Maxi(node.left), Maxi(node.right)), node.data);
    }

    public static int Mini(Node node) {
        if (node == null)
            return (int) 1e8;
        return Math.min(Math.min(Mini(node.left), Mini(node.right)), node.data);
    }

    public static int Mini_02(Node node) {
        int min_ = node.data;

        if (node.left != null)
            min_ = Math.min(min_, Mini_02(node.left));
        if (node.right != null)
            min_ = Math.min(min_, Mini_02(node.right));

        return min_;
    }

    public static boolean find(Node node, int data) {
        if (node == null)
            return false;

        if (node.data == data)
            return true;

        return find(node.left, data) || find(node.right, data);

        // if(find(node.left,data)) return true;
        // if(find(node.rigth,data)) return true;
    }

    public static void set01(Node node) {
        System.out.println(size(node));
        System.out.println(height(node));
        System.out.println(Maxi(node));
        System.out.println(Mini(node));
        System.out.println(Mini_02(node));
        System.out.println(find(node, 30));
    }

    // TRAVERSAL. =========================================

    public static void inoder(Node node) {
        if (node == null)
            return;
        inoder(node.left);
        System.out.print(node.data + " ");
        inoder(node.right);
    }

    public static void postoder(Node node) {
        if (node == null)
            return;
        postoder(node.left);
        postoder(node.right);
        System.out.print(node.data + " ");
    }

    public static void preoder(Node node) {
        if (node == null)
            return;
        System.out.print(node.data + " ");
        preoder(node.left);
        preoder(node.right);
    }

    public static void set02(Node node) {
        preoder(node);
        System.out.println();
        inoder(node);
        System.out.println();
        postoder(node);
        System.out.println();
    }

    // ROOT TO NODE PATH . ==================================

    public static boolean rootToNodePath(Node node, int data, ArrayList<Node> path)
    {
        if (node == null)
            return false;
        if (node.data == data)
        {
            path.add(node);
            return true;
        }
        boolean res = rootToNodePath(node.left, data, path) || rootToNodePath(node.right, data, path);
        if (res)
            path.add(node);
        return res;
    }

    public static void set03(Node node) {
        ArrayList<Node> path = new ArrayList<>();
        if(rootToNodePath(node, 80, path)) {
            System.out.println();
        }
    }

    public static void solve() {
        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,
                -1 };
        Node node = constructTree(arr);
        display(node);

        // set01(node);
        // set02(node);
        set03(node);
    }
}