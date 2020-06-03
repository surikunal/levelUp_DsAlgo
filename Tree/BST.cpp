#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int data;
    Node *left = nullptr;  // Node* left=nullptr;
    Node *right = nullptr; // Node* right=nullptr;

    Node(int data)
    {
        this->data = data;
    }

    Node()
    {
    }
};

Node *constructBST(vector<int> &arr, int si, int ei)
{
    if (si > ei)
        return nullptr;

    int mid = (si + ei) >> 1; // (si+ei)/2;
    Node *node = new Node(arr[mid]);
    node->left = constructBST(arr, si, mid - 1);
    node->right = constructBST(arr, mid + 1, ei);

    return node;
}

void display(Node *node)
{
    if (node == nullptr)
        return;

    string str = "";
    str += ((node->left != nullptr) ? to_string(node->left->data) : ".");
    str += " <- " + to_string(node->data) + " -> ";
    str += ((node->right != nullptr) ? to_string(node->right->data) : ".");
    cout << (str) << endl;

    display(node->left);
    display(node->right);
}

//Basic.==============================================================
int height(Node *node)
{
    if (node == nullptr)
        return -1;
    return max(height(node->left), height(node->right)) + 1;
}

int size(Node *node)
{
    if (node == nullptr)
        return 0;
    return size(node->left) + size(node->right) + 1;
}

// not using recursion means no internal stack is required (which is always there in recursion)
bool find(Node *node, int data) // logn
{
    Node *curr = node;
    while (curr != nullptr)
    {
        if (curr->data == data)
            return true;
        else if (curr->data < data)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return false;
}
bool findRec(Node *node, int data) // logn
{
    if (node == nullptr)
        return false;

    if (node->data == data)
        return true;
    else if (node->data < data)
        return findRec(node->right, data);
    else
        return findRec(node->left, data);
}

int maximumEle(Node *node) // logn
{
    Node *curr = node;
    while (curr->right != nullptr)
        curr = curr->right;

    return curr->data;
}

int minimumEle(Node *node) // logn
{
    Node *curr = node;
    while (curr->left != nullptr)
        curr = curr->left;

    return curr->data;
}
