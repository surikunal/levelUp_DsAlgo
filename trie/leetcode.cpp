#include <iostream>
#include <vector>
using namespace std;

auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();

// leetcode 208. =================================================

class Trie
{
public:
    class Node
    {
    public:
        int wordEnd = 0;
        vector<Node *> childs;

        Node()
        {
            this->childs.assign(26, nullptr);
            this->wordEnd = 0;
        }
    };
    /** Initialize your data structure here. */
    Trie()
    {
    }
    Node *root = new Node();

    void insert(string word)
    {
        Node *curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++)
        {
            int idx = word[i] - 'a';
            if (curr->childs[idx] == nullptr)
            {
                curr->childs[idx] = new Node();
            }
            curr = curr->childs[idx];
        }
        curr->wordEnd++;
    }

    bool search(string word)
    {
        Node *curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++)
        {
            int idx = word[i] - 'a';
            curr = curr->childs[idx];

            if (curr == nullptr)
                return false;
        }
        return curr->wordEnd > 0;
    }

    bool startsWith(string prefix)
    {
        Node *curr = root;
        int n = prefix.length();
        for (int i = 0; i < n; i++)
        {
            int idx = prefix[i] - 'a';
            curr = curr->childs[idx];

            if (curr == nullptr)
                return false;
        }
        return true;
    }
};

// leetcode 211.============================================

auto SpeedUp = []() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return NULL;
}();
class WordDictionary
{
public:
    class Node
    {
    public:
        int wordEnd = 0;
        vector<Node *> childs;
        Node()
        {
            this->wordEnd = 0;
            this->childs.assign(26, nullptr);
        }
    };
    Node *root = new Node();
    /** Initialize your data structure here. */
    WordDictionary()
    {
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        Node *curr = root;
        int n = word.size();
        for (int i = 0; i < n; i++)
        {
            int idx = word[i] - 'a';
            if (curr->childs[idx] == nullptr)
            {
                curr->childs[idx] = new Node();
            }
            curr = curr->childs[idx];
        }
        curr->wordEnd++;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */

    bool search_(Node *node, int si, string word)
    {
        if (node == nullptr)
            return false;

        if (si == word.size())
            return node->wordEnd != 0;

        bool res = false;
        if (word[si] == '.')
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->childs[i] != nullptr)
                {
                    res = res || search_(node->childs[i], si + 1, word);
                }
            }
        }
        else
        {
            int idx = word[si] - 'a';
            if (node->childs[idx] != nullptr)
            {
                res = res || search_(node->childs[idx], si + 1, word);
            }
        }
        return res;
    }

    bool search(string word)
    {
        return search_(root, 0, word);
    }
};

// 212.==================================================

