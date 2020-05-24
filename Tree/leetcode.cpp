#include <iostream>
#include <vector>
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

// leetcode 112. ===========================================

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