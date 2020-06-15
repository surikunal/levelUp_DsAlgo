#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 236. ==================================================
//* LOWEST COMMON ANCESTOR.
// METHOD 1. =============================================

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr || root == p || root == q)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if (left != nullptr && right != nullptr)
            return root;
        if (left != nullptr && right == nullptr)
            return left;
        if (left == nullptr && right != nullptr)
            return right;
        return nullptr;
    }
};

// leetcode 863. ==================================================
// method 1.
class Solution
{
public:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    bool rootToNodePath(TreeNode *node, TreeNode *target, vector<TreeNode *> &path)
    {
        if (node == nullptr)
            return false;
        if (node->val == target->val)
        {
            path.push_back(node);
            return true;
        }
        bool res = rootToNodePath(node->left, target, path) || rootToNodePath(node->right, target, path);
        if (res)
            path.push_back(node);
        return res;
    }
    void kDown(TreeNode *node, int level, TreeNode *blockNode, vector<int> &ans)
    {
        if (node == nullptr || node == blockNode)
            return;
        if (level == 0)
        {
            ans.push_back(node->val);
            return;
        }
        kDown(node->left, level - 1, blockNode, ans);
        kDown(node->right, level - 1, blockNode, ans);
    }
    vector<int> distanceK(TreeNode *root, TreeNode *target, int K)
    {
        vector<TreeNode *> path;
        rootToNodePath(root, target, path);

        vector<int> ans;
        TreeNode *blockNode = nullptr;
        for (int i = 0; i < path.size(); i++)
        {
            if (K - i < 0)
                break;
            kDown(path[i], K - i, blockNode, ans);
            blockNode = path[i];
        }
        return ans;
    }
};

// leetcode 112. ==================================================

auto SpeedUp = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class Solution
{
public:
    bool hasPathSum(TreeNode *node, int sum)
    {
        if (node == nullptr)
            return false;
        if (node->left == nullptr && node->right == nullptr && sum - node->val == 0)
            return true;
        bool res = false;
        res = res || hasPathSum(node->left, sum - node->val);
        res = res || hasPathSum(node->right, sum - node->val);
        return res;
    }
};

// leetcode 113. ===========================================

auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class Solution
{
public:
    void pathSum_(TreeNode *node, int sum, vector<vector<int>> &res, vector<int> &smallAns)
    {
        if (node == nullptr)
            return;
        smallAns.push_back(node->val);
        if (node->left == nullptr && node->right == nullptr && sum - node->val == 0)
        {
            res.push_back(smallAns);
        }
        pathSum_(node->left, sum - node->val, res, smallAns);
        pathSum_(node->right, sum - node->val, res, smallAns);
        smallAns.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode *root, int sum)
    {
        vector<vector<int>> res;
        vector<int> smallAns;
        pathSum_(root, sum, res, smallAns);
        return res;
    }
};

// geeksforgeeks:
// https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
// * LEAF TO LEAF SUM
class GFG
{
    struct Node
    {
        int data;
        Node *left, *right;
    };

    int sum_leafToLeaf;
    int leafToLeaf(Node *node)
    {
        if (node == NULL)
            return 0;
        int left = leafToLeaf(node->left);
        int right = leafToLeaf(node->right);

        if (node->left != NULL && node->right != NULL)
        {
            sum_leafToLeaf = max(sum_leafToLeaf, left + right + node->data);
            return max(left, right) + node->data;
        }
        return (node->left == nullptr ? right : left) + node->data;
    }
    int maxPathSum(Node *root)
    {
        sum_leafToLeaf = (int)-1e8;
        leafToLeaf(root);
        return sum_leafToLeaf;
    }
};

// leetcode 124. ===========================================

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class Solution
{
public:
    int maxNodeToNodeSum = (int)-1e8;
    int maxPathSum_(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        int leftNodeToNodeSum = maxPathSum_(node->left);
        int rightNodeToNodeSum = maxPathSum_(node->right);
        int max_ = max(rightNodeToNodeSum, leftNodeToNodeSum) + node->val;
        maxNodeToNodeSum = max(max(max_, maxNodeToNodeSum), max(node->val, rightNodeToNodeSum + node->val + leftNodeToNodeSum));

        return max(max_, node->val);
    }
    int maxPathSum(TreeNode *root)
    {
        maxPathSum_(root);
        return maxNodeToNodeSum;
    }
};

// 199. ==========================================
// right side view of a tree

class Solution
{
public:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ans;
        if (root == nullptr)
            return ans;
        queue<TreeNode *> que;
        que.push(root);
        while (que.size() != 0)
        {
            int size = que.size();
            TreeNode *prev = nullptr;
            while (size-- > 0)
            {
                TreeNode *rvtx = que.front();
                que.pop();
                if (rvtx->left != nullptr)
                    que.push(rvtx->left);
                if (rvtx->right != nullptr)
                    que.push(rvtx->right);
                prev = rvtx;
            }
            ans.push_back(prev->val);
        }
        return ans;
    }
};

// 235. ===========================================
// LCA of BST
// recursion

class Solution
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

public:
    TreeNode *lowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        if (node == nullptr)
            return nullptr;
        if (p->val < node->val && q->val < node->val)
            return lowestCommonAncestor(node->left, p, q);
        else if (p->val > node->val && q->val > node->val)
            return lowestCommonAncestor(node->right, p, q);
        else
            return node;
    }
};

// iterative
class Solution
{
public:
    bool find(TreeNode *node, int data)
    {
        TreeNode *curr = node;
        while (node != nullptr)
        {
            if (curr->val == data)
                return true;
            else if (curr->val < data)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        TreeNode *curr = root;
        while (curr != nullptr)
        {
            if (p->val < curr->val && q->val < curr->val)
                curr = curr->left;
            else if (p->val > curr->val && q->val > curr->val)
                curr = curr->right;
            else
                return find(curr, p->val) && find(curr, q->val) ? curr : nullptr;
        }
        return nullptr;
    }
};

// BST=============================================

// leetcode 98. ===================================

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class Solution
{
public:
    long long prev = -1e12;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        if (!isValidBST(root->left))
            return false;

        if (prev >= root->val)
            return false;
        prev = root->val;

        if (!isValidBST(root->right))
            return false;

        return true;
    }
};

// leetcode 99. ===================================
class Solution
{
public:
    TreeNode *a = nullptr;
    TreeNode *b = nullptr;
    TreeNode *c = nullptr; // previous
    bool recoverTree_(TreeNode *root)
    {
        if (root == nullptr)
            return false;

        if (recoverTree_(root->left))
            return true;

        if (c != nullptr && c->val > root->val)
        {
            b = root;
            if (a == nullptr)
                a = c;
            else
                return true;
        }

        c = root;

        if (recoverTree_(root->right))
            return true;

        return false;
    }
    void recoverTree(TreeNode *root)
    {
        recoverTree_(root);
        if (a != nullptr)
        {
            int temp = a->val;
            a->val = b->val;
            b->val = temp;
        }
    }
};