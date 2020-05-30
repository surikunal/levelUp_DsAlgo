import java.util.ArrayList;
import java.util.LinkedList;

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

    // ROOT TO NODE PATH . =============================================

    public static boolean rootToNodePath_01(Node node, int data, ArrayList<Node> path) {
        if (node == null)
            return false;
        if (node.data == data) {
            path.add(node);
            return true;
        }
        boolean res = rootToNodePath_01(node.left, data, path) || rootToNodePath_01(node.right, data, path);
        if (res)
            path.add(node);
        return res;
    }

    public static ArrayList<Node> rootToNodePath_02(Node node, int data) {
        if (node == null)
            return new ArrayList<>();

        if (node.data == data) {
            ArrayList<Node> base = new ArrayList<>();
            base.add(node);
            return base;
        }

        ArrayList<Node> left = rootToNodePath_02(node.left, data);
        if (left.size() != 0) {
            left.add(node);
            return left;
        }
        ArrayList<Node> right = rootToNodePath_02(node.right, data);
        if (right.size() != 0) {
            right.add(node);
            return right;
        }
        return new ArrayList<>();
    }

    // LOWEST COMMON ANCESTOR. =============================================

    public static Node lowestCommonAnscestor(Node root, int p, int q) {
        ArrayList<Node> path1 = new ArrayList<>();
        ArrayList<Node> path2 = new ArrayList<>();

        rootToNodePath_01(root, p, path1);
        rootToNodePath_01(root, q, path2);

        Node ans = null;
        int i = path1.size() - 1, j = path2.size() - 1;
        while (i >= 0 && j >= 0) {
            if (path1.get(i) != path2.get(j))
                break;
            ans = path1.get(i);
            i--;
            j--;
        }
        return ans;
    }

    public static Node LCAnode = null;

    public static boolean lowestCommonAnscestor_01(Node root, int p, int q) {
        if (root == null)
            return false;

        boolean selfDone = false;
        if (root.data == p || root.data == q)
            selfDone = true;

        boolean leftAns = lowestCommonAnscestor_01(root.left, p, q);
        if (LCAnode != null)
            return true;

        boolean rightAns = lowestCommonAnscestor_01(root.right, p, q);
        if (LCAnode != null)
            return true;

        if ((selfDone && leftAns) || (rightAns && leftAns) || (selfDone && rightAns))
            LCAnode = root;

        return selfDone || leftAns || rightAns;
    }

    // FIND ALL NODES K AWAY FROM THE TARGET NODE. ================================

    public static void kDown(Node root, int level, Node blockNode) {
        if (root == null || root == blockNode)
            return;

        if (level == 0) {
            System.out.print(root.data + " ");
            return;
        }

        kDown(root.left, level - 1, blockNode);
        kDown(root.right, level - 1, blockNode);
    }

    // method 1.
    public static void allNodeKaway(Node node, int target, int K) {
        ArrayList<Node> path = new ArrayList<>();
        rootToNodePath_01(node, target, path);

        Node blockNode = null;
        for (int i = 0; i < path.size(); i++) {
            if (K - i < 0)
                break;
            kDown(path.get(i), K - i, blockNode);
            blockNode = path.get(i);
        }
    }

    // method 2.
    public static int allNodeKaway_01(Node node, int target, int K) {
        if (node == null)
            return -1;

        if (node.data == target) {
            kDown(node, K, null);
            return 1;
        }

        int leftdistance = allNodeKaway_01(node.left, target, K);
        if (leftdistance != -1) {
            if (K - leftdistance >= 0) {
                kDown(node, K - leftdistance, node.left);
                return leftdistance + 1;
            }
        }

        int rightdistance = allNodeKaway_01(node.right, target, K);
        if (rightdistance != -1) {
            if (K - rightdistance >= 0) {
                kDown(node, K - rightdistance, node.right);
                return rightdistance + 1;
            }
        }
        return -1;
    }

    // method 3.
    public static void kDown_01(Node node, int level) {
        if (node == null)
            return;

        if (level == 0) {
            System.out.print(node.data + " ");
            return;
        }

        kDown_01(node.left, level - 1);
        kDown_01(node.right, level - 1);
    }

    public static int allNodeKaway_02(Node node, int target, int K) {
        if (node == null)
            return -1;

        if (node.data == target) {
            kDown(node, K, null);
            return 1;
        }

        int leftDis = allNodeKaway_02(node.left, target, K);
        if (leftDis != -1) {
            if (K - leftDis == 0) {
                System.out.print(node.data + " ");
            } else
                kDown_01(node.right, K - leftDis - 1); // bcz w already handled zero wala case
            return leftDis + 1;
        }
        int rightDis = allNodeKaway_02(node.right, target, K);
        if (rightDis != -1) {
            if (K - rightDis == 0) {
                System.out.print(node.data + " ");
            } else
                kDown_01(node.left, K - rightDis - 1); // bcz w already handled zero wala case
            return rightDis + 1;
        }
        return -1;
    }

    public static int diameter_01(Node node) {
        if (node == null)
            return 0;

        int lh = height(node.left);
        int rh = height(node.right);

        int ld = diameter_01(node.left);
        int rd = diameter_01(node.right);

        return Math.max(Math.max(ld, rd), lh + rh + 2);
    }

    public static class diaPair {
        int hei = 0;
        int dia = 0;

        diaPair(int dia, int hei) {
            this.dia = dia;
            this.hei = hei;
        }
    }

    public static diaPair diameter_02(Node node) {
        if (node == null)
            return new diaPair(0, -1);

        diaPair ld = diameter_02(node.left);
        diaPair rd = diameter_02(node.right);

        diaPair myRes = new diaPair(0, -1);
        myRes.dia = Math.max(Math.max(ld.dia, rd.dia), ld.hei + rd.hei + 2);
        myRes.hei = Math.max(ld.hei, rd.hei) + 1;

        return myRes;
    }

    public static int diameter = 0;

    public static int diameter_03(Node node) {
        if (node == null)
            return -1;

        int lh = diameter_03(node.left);
        int rh = diameter_03(node.right);

        diameter = Math.max(diameter, lh + rh + 2);
        return Math.max(lh, rh) + 1;
    }

    public static void set03(Node node) {
        ArrayList<Node> path = new ArrayList<>();
        rootToNodePath_01(node, 100, path);
        for (Node n : path) {
            System.out.print(n.data + "->");
        }
        System.out.println();

        ArrayList<Node> ans = rootToNodePath_02(node, 100);
        for (Node n : ans) {
            System.out.print(n.data + "->");
        }

        System.out.println(lowestCommonAnscestor(node, 120, 80).data);
        lowestCommonAnscestor_01(node, 100, 70);
        System.out.println("LCA : " + (LCAnode != null ? LCAnode.data : "-1"));

        allNodeKaway(node, 60, 3);
        System.out.println();

        allNodeKaway_01(node, 60, 3);
        System.out.println();

        allNodeKaway_02(node, 60, 3);
        System.out.println();

        System.out.println(diameter_01(node));

        System.out.println(diameter_02(node).dia);

        diameter_03(node);
        System.out.println(diameter);
    }

    // level order traversals. ==========================================
    public static void levelOrder_00(Node node) {
        LinkedList<Node> pQue = new LinkedList<>(); // addLast and removeFirst
        pQue.addLast(node);

        while (pQue.size() != 0) {
            Node rnode = pQue.removeFirst();
            System.out.print(rnode.data + " ");
            if (rnode.left != null)
                pQue.addLast(rnode.left);
            if (rnode.right != null)
                pQue.addLast(rnode.right);
        }
    }

    public static void levelOrder_01(Node node) {
        LinkedList<Node> pQue = new LinkedList<>();
        LinkedList<Node> cQue = new LinkedList<>();
        pQue.addLast(node);
        int count = 0;
        System.out.print("Level " + count + " -> ");

        while (pQue.size() != 0) {
            Node rnode = pQue.removeFirst();
            System.out.print(rnode.data + " ");
            if (rnode.left != null)
                cQue.addLast(rnode.left);
            if (rnode.right != null)
                cQue.addLast(rnode.right);

            if (pQue.size() == 0) {
                LinkedList<Node> temp = pQue;
                pQue = cQue;
                cQue = temp;
                count++;
                System.out.print("\nLevel " + count + " -> ");
            }
        }
    }

    public static void levelOrder_02(Node node) {
        LinkedList<Node> pQue = new LinkedList<>();
        pQue.addLast(node);
        pQue.addLast(null);
        int count = 0;
        System.out.print("Level " + count + " -> ");

        while (pQue.size() != 1) {
            Node rnode = pQue.removeFirst();
            System.out.print(rnode.data + " ");
            if (rnode.left != null)
                pQue.addLast(rnode.left);
            if (rnode.right != null)
                pQue.addLast(rnode.right);

            if (pQue.getFirst() == null) {
                pQue.removeFirst();
                pQue.addLast(null);
                count++;
                System.out.print("\nLevel " + count + " -> ");
            }
        }
    }

    public static void levelOrder_03(Node node) {
        LinkedList<Node> pQue = new LinkedList<>();
        pQue.addLast(node);
        int count = 0;

        while (pQue.size() != 0) {
            System.out.print("Level " + count + " -> ");
            int size = pQue.size();
            while (size-- > 0) {
                Node rnode = pQue.removeFirst();
                System.out.print(rnode.data + " ");
                if (rnode.left != null)
                    pQue.addLast(rnode.left);
                if (rnode.right != null)
                    pQue.addLast(rnode.right);
            }
            count++;
            System.out.println();
        }
    }

    public static void set04(Node node) {
        levelOrder_00(node);
        System.out.println();

        levelOrder_01(node);
        System.out.println();

        levelOrder_02(node);
        System.out.println();

        levelOrder_03(node);
    }

    // VIEWS SECTION . ===============================================

    // left view.
    public static void leftView(Node node) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(node);
        while (que.size() != 0) {
            System.out.print(que.getFirst().data + " ");
            int size = que.size();
            while (size-- > 0) {
                Node rnode = que.removeFirst();
                if (rnode.left != null)
                    que.addLast(rnode.left);
                    if (rnode.right != null)
                    que.addLast(rnode.right);
            }
        }
        System.out.println();
    }
    
    // right view.
    public static void rightView(Node node) {
        LinkedList<Node> que = new LinkedList<>();
        que.addLast(node);
        while (que.size() != 0) {
            int size = que.size();
            Node prev = null;
            while (size-- > 0) {
                Node rnode = que.removeFirst();
                if (rnode.left != null)
                que.addLast(rnode.left);
                if (rnode.right != null)
                que.addLast(rnode.right);
                prev = rnode; // when prev comes out of while loop then its value is always the last one of a
                // level
            }
            System.out.print(prev.data + " ");
        }
        System.out.println();
    }
    
    // vertical order.
    
    public static void verticalOrder(Node node) {

    }

    public static void set05(Node node) {
        leftView(node);
        rightView(node);
        verticalOrder(node);
    }

    public static void solve() {
        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,
                -1 };
        Node node = constructTree(arr);
        // display(node);

        // set01(node);
        // set02(node);
        // set03(node);
        // set04(node);
        set05(node);
    }
}