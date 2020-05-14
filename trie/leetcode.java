// leetcode 208. ====================================================

class leetcode {
    class Node {
        int wordEnd = 0;
        Node[] childs;

        Node() {
            this.childs = new Node[26];
            this.wordEnd = 0;
        }
    }

    /** Initialize your data structure here. */
    public Trie() {
        
    }

    Node root = new Node();

    /** Inserts a word into the trie. */
    public void insert(String word) {
        Node curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++) {
            int idx = word.charAt(i) - 'a';
            if (curr.childs[idx] == null)
                curr.childs[idx] = new Node();

            curr = curr.childs[idx];
        }
        curr.wordEnd++;
    }

    /** Returns if the word is in the trie. */
    public boolean search(String word) {
        Node curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++) {
            int idx = word.charAt(i) - 'a';
            curr = curr.childs[idx];

            if (curr == null)
                return false;
        }
        return curr.wordEnd > 0;
    }

    /**
     * Returns if there is any word in the trie that starts with the given prefix.
     */
    public boolean startsWith(String word) {
        Node curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++) {
            int idx = word.charAt(i) - 'a';
            curr = curr.childs[idx];

            if (curr == null)
                return false;
        }
        return true;
    }
}

// leetcode 211. ====================================================

class WordDictionary {
    class Node {
        int wordEnd = 0;
        Node[] childs;

        Node() {
            this.wordEnd = 0;
            this.childs = new Node[26];
        }
    }

    Node root = new Node();

    /** Initialize your data structure here. */
    public WordDictionary() {

    }

    /** Adds a word into the data structure. */
    public void addWord(String word) {
        Node curr = root;
        int n = word.length();
        for (int i = 0; i < n; i++) {
            int idx = word.charAt(i) - 'a';
            if (curr.childs[idx] == null)
                curr.childs[idx] = new Node();
            curr = curr.childs[idx];
        }
        curr.wordEnd++;
    }

    /**
     * Returns if the word is in the data structure. A word could contain the dot
     * character '.' to represent any one letter.
     */
    public boolean search(String word) {
        return search_(root, 0, word);
    }

    public boolean search_(Node node, int si, String word) {
        if (node == null)
            return false;
        if (si == word.length())
            return node.wordEnd != 0;

        boolean res = false;
        if (word.charAt(si) == '.') {
            for (int i = 0; i < 26; i++) {
                if (node.childs[i] != null) {
                    res = res || search_(node.childs[i], si + 1, word);
                }
            }
        } else {
            int idx = word.charAt(si) - 'a';
            if (node.childs[idx] != null) {
                res = res || search_(node.childs[idx], si + 1, word);
            }
        }
        return res;
    }
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary(); obj.addWord(word); boolean param_2
 * = obj.search(word);
 */