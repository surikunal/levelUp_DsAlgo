#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data = 0;
    Node *left = NULL;
    Node *right = NULL;

    Node(int data)
    {
        this->data = data;
    }

    Node(int data, Node *right, Node *left)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

int idx = 0;
Node *ConstructTree(vector<int> arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        idx++;
        return nullptr;
    }

    Node *node = new Node(arr[idx]);
    idx++;
    node->left = ConstructTree(arr);
    node->right = ConstructTree(arr);

    return node;
}

void display(Node *root)
{
    if (root == NULL)
        return;

    string str = "";
    str += root->left != nullptr ? to_string(root->left->data) : " . ";
    str += " <- " + to_string(root->data) + " -> ";
    str += root->right != nullptr ? to_string(root->right->data) : " . ";
    cout << str << endl;

    display(root->left);
    display(root->right);
}

void solve()
{
    vector<int> arr = {10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1, -1};
    Node *root = ConstructTree(arr);
    display(root);
}

int main(int args, char **argv)
{
    solve();
    return 0;
}