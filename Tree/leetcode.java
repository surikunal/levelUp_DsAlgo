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

// leetcode 112. ===============================================

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