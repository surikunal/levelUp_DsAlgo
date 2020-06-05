// Sir wala method
// 236. ======================================================

class Solution {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public TreeNode LCAnode = null;

    public boolean LCA(TreeNode root, int p, int q) {
        if (root == null)
            return false;

        boolean selfDone = false;
        if (root.val == p || root.val == q)
            selfDone = true;

        boolean leftDone = LCA(root.left, p, q);
        if (LCAnode != null)
            return true;
        boolean rightDone = LCA(root.right, p, q);
        if (LCAnode != null)
            return true;

        if ((selfDone && rightDone) || (selfDone && leftDone) || (leftDone && rightDone))
            LCAnode = root;

        return (selfDone || rightDone || leftDone);
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        LCA(root, p.val, q.val);
        return (LCAnode != null) ? LCAnode : null;
        // return root;
    }
}

// * LOWEST COMMON ANCESTOR
// METHOD 1. =================================================

class Solution1 {
    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public ArrayList<TreeNode> rootToNodePath(TreeNode node, TreeNode data) {
        if (node == null)
            return null;

        if (node.val == data.val) {
            ArrayList<TreeNode> base = new ArrayList<>();
            base.add(node);
            return base;
        }

        ArrayList<TreeNode> left = rootToNodePath(node.left, data);
        if (left != null) {
            left.add(node);
            return left;
        }

        ArrayList<TreeNode> right = rootToNodePath(node.right, data);
        if (right != null) {
            right.add(node);
            return right;
        }

        return null;
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        ArrayList<TreeNode> path1 = rootToNodePath(root, p);
        ArrayList<TreeNode> path2 = rootToNodePath(root, q);

        if (path1 == null || path2 == null)
            return null;
        TreeNode ans = null;
        int i = path1.size() - 1;
        int j = path2.size() - 1;
        while (i >= 0 && j >= 0) {
            if (path1.get(i).val == path2.get(j).val)
                ans = path1.get(i);
            else
                break;
            i--;
            j--;
        }
        return ans;
    }
}

// METHOD 2 . =============================================

class Solution2 {
    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q)
            return root;

        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);

        if (left != null && right != null)
            return root;
        if (left != null && right == null)
            return left;
        if (right != null && left == null)
            return right;
        return null;
    }
}

// leetcode 863. ===================================================
// method 1.
class Solution {

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public boolean rootToNodePath_(TreeNode node, TreeNode target, ArrayList<TreeNode> path) {
        if (node == null)
            return false;
        if (node.val == target.val) {
            path.add(node);
            return true;
        }
        boolean res = rootToNodePath_(node.left, target, path) || rootToNodePath_(node.right, target, path);
        if (res)
            path.add(node);
        return res;
    }

    public void kDown(TreeNode node, int level, TreeNode blockNode, List<Integer> ans) {
        if (node == null || node == blockNode)
            return;
        if (level == 0) {
            ans.add(node.val);
            return;
        }
        kDown(node.left, level - 1, blockNode, ans);
        kDown(node.right, level - 1, blockNode, ans);
    }

    public List<Integer> distanceK(TreeNode root, TreeNode target, int K) {
        ArrayList<TreeNode> path = new ArrayList<>();
        rootToNodePath_(root, target, path);

        TreeNode blockNode = null;
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < path.size(); i++) {
            if (K - i < 0)
                break;
            kDown(path.get(i), K - i, blockNode, ans);
            blockNode = path.get(i);
        }
        return ans;
    }
}

// leetcode 112. =====================================================

class Solution {

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public boolean hasPathSum(TreeNode root, int sum) {
        if (root == null)
            return false;
        if (root.left == null && root.right == null && sum - root.val == 0)
            return true;

        boolean res = false;
        res = res || hasPathSum(root.left, sum - root.val);
        res = res || hasPathSum(root.right, sum - root.val);
        return res;
    }
}

// leetcode 113. ================================================

class Solution {

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    public void pathSum(TreeNode root, int sum, List<List<Integer>> res, List<Integer> smallAns) {
        if (root == null)
            return;
        if (root.left == null && root.right == null && sum - root.val == 0) {
            List<Integer> base = new ArrayList<>(smallAns); // deep copy
            base.add(root.val);
            res.add(base);
            return;
        }

        smallAns.add(root.val);
        pathSum(root.left, sum - root.val, res, smallAns);
        pathSum(root.right, sum - root.val, res, smallAns);
        smallAns.remove(smallAns.size() - 1);
    }

    public List<List<Integer>> pathSum(TreeNode root, int sum) {
        if (root == null)
            return new ArrayList<>();

        List<List<Integer>> res = new ArrayList<>();
        List<Integer> smallAns = new ArrayList<>();
        pathSum(root, sum, res, smallAns);
        return res;
    }
}

// geeksforgeeks:
// https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
// * LEAF TO LEAF SUM

class GfG {
    public static int max_LeafToLeafSum;

    public static int maxPathSum(Node root) {
        max_LeafToLeafSum = (int) -1e8;
        leafToLeaf(root);
        return max_LeafToLeafSum;
    }

    public static int leafToLeaf(Node node) {
        if (node == null)
            return 0;
        int left = leafToLeaf(node.left);
        int right = leafToLeaf(node.right);

        if (node.left != null && node.right != null) {
            max_LeafToLeafSum = Math.max(max_LeafToLeafSum, left + right + node.data);
            return Math.max(left, right) + node.data;
        }
        return (node.left == null ? right : left) + node.data;
    }
}

// leetcode 124. ================================================

public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode() {
    }

    TreeNode(int val) {
        this.val = val;
    }

    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

class Solution {
    int max_nodeToNodeSum = (int) -1e8;

    public int maxPathSum(TreeNode node) {
        maxPathSum_(node);
        return max_nodeToNodeSum;
    }

    public int maxPathSum_(TreeNode node) {
        if (node == null)
            return 0;

        int leftNodeToNode = maxPathSum_(node.left);
        int rightNodeToNode = maxPathSum_(node.right);

        int max_ = Math.max(rightNodeToNode, leftNodeToNode) + node.val;
        max_nodeToNodeSum = Math.max(Math.max(max_nodeToNodeSum, node.val),
                Math.max(max_, rightNodeToNode + leftNodeToNode + node.val));

        return Math.max(max_, node.val);
    }
}

// 199. ==========================================
// right side view of a tree

class Solution {
    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null)
            return ans;
        LinkedList<TreeNode> que = new LinkedList<>();
        que.addLast(root);
        while (que.size() != 0) {
            int size = que.size();
            TreeNode prev = null;
            while (size-- > 0) {
                TreeNode rvtx = que.removeFirst();
                if (rvtx.left != null)
                    que.addLast(rvtx.left);
                if (rvtx.right != null)
                    que.addLast(rvtx.right);
                prev = rvtx;
            }
            ans.add(prev.val);
        }
        return ans;
    }
}

// Leetcode 987.====================================================
// vertical order
// * but it is giving wrong answer in leetcode (only in my profile)
class Solution {
    static int leftMinValue = 0;
    static int rightMaxValue = 0;

    public static void width(TreeNode node, int lev) {
        if (node == null)
            return;

        leftMinValue = Math.min(leftMinValue, lev);
        rightMaxValue = Math.max(rightMaxValue, lev);

        width(node.left, lev - 1);
        width(node.right, lev + 1);
    }

    public static class pairVO implements Comparable<pairVO> {
        TreeNode node; // actual Node
        int vl = 0; // vertical Level

        public pairVO(TreeNode node, int vl) {
            this.node = node;
            this.vl = vl;
        }

        @override
        public int compareTo(pairVO o) { // for c++: bool opeartor < ( pairvo const & o) const{
            if (this.vl == o.vl)
                return this.node.val - o.node.val; // in c++: replace '-' with '>'
            return this.vl - o.vl; // default behaviour of que // in c++: replace '-' with '>'
        }
    }

    public List<List<Integer>> verticalTraversal(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null)
            return ans;

        width(root, 0);
        int n = rightMaxValue - leftMinValue + 1;
        for (int i = 0; i < n; i++)
            ans.add(new ArrayList<>());

        PriorityQueue<pairVO> pque = new PriorityQueue<>();
        PriorityQueue<pairVO> cque = new PriorityQueue<>();

        pque.add(new pairVO(root, -leftMinValue));

        while (pque.size() != 0) {
            int size = pque.size();
            while (size-- > 0) {
                pairVO rpair = pque.poll();
                ans.get(rpair.vl).add(rpair.node.val);

                if (rpair.node.left != null)
                    cque.add(new pairVO(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    cque.add(new pairVO(rpair.node.right, rpair.vl + 1));
            }

            PriorityQueue<pairVO> temp = pque;
            pque = cque;
            cque = temp;
        }
    }
}

// 235. ===========================================
// LCA of BST
// recursion

class Solution {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    public TreeNode lowestCommonAncestor(TreeNode node, TreeNode p, TreeNode q) {
        if (node == null)
            return null;
        if (p.val < node.val && q.val < node.val)
            return lowestCommonAncestor(node.left, p, q);
        else if (p.val > node.val && q.val > node.val)
            return lowestCommonAncestor(node.right, p, q);
        else
            return node;
    }
}

// iterative
class Solution {
    public boolean find(TreeNode node, int data) {
        TreeNode curr = node;
        while (node != null) {
            if (curr.val == data)
                return true;
            else if (curr.val < data)
                curr = curr.right;
            else
                curr = curr.left;
        }
        return false;
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        TreeNode curr = root;
        while (curr != null) {
            if (p.val < curr.val && q.val < curr.val)
                curr = curr.left;
            else if (p.val > curr.val && q.val > curr.val)
                curr = curr.right;
            else
                return find(curr, p.val) && find(curr, q.val) ? curr : null;
        }
        return null;
    }
}