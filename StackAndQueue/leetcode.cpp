#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//20. ====================================================
class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        for (int i = 0; i < s.length(); i++)
        {
            if (st.size() == 0 || s[i] == '{' || s[i] == '[' || s[i] == '(')
            {
                st.push(s[i]);
                continue;
            }

            if (s[i] == '}' && st.top() != '{')
            {
                return false;
            }
            else if (s[i] == ']' && st.top() != '[')
            {
                return false;
            }
            else if (s[i] == ')' && st.top() != '(')
            {
                return false;
            }
            st.pop();
        }
        return st.size() == 0; // to handle case when there left some braces in stack
    }
};

//1021. =======================================================
class Solution
{
public:
    string removeOuterParentheses(string S)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        string ans = "";
        int count = 0;
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == '(' && count++ > 0)
                ans += S[i];
            if (S[i] == ')' && count-- > 1)
                ans += S[i];
        }
        return ans;
    }
};

//503. =======================================================

// 921. ======================================================
class Solution
{
public:
    int minAddToMakeValid(string str)
    {
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < str.length(); i++)
        {
            if (st.top() != -1 && str[i] == ')' && str[st.top()] == '(')
                st.pop();
            else
                st.push(i);
        }
        return st.size() - 1;
    }
};

// 1249. =====================================================
class Solution
{
public:
    string minRemoveToMakeValid(string str)
    {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n = str.length();
        vector<bool> marked(n, false);
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < n; i++)
        {
            if (st.top() != -1 && str[i] == ')' && str[st.top()] == '(')
            {
                int val = st.top();
                st.pop();
                marked[i] = marked[val] = true; // both opening and closing braces are marked true
            }
            else if (str[i] == '(')
                st.push(i);
            else if (str[i] != ')')
                marked[i] = true;
            // havent done anything for extra closing braces so it is false by default
        }

        string ans = "";
        for (int i = 0; i < n; i++)
        {
            if (marked[i])
                ans += str[i];
        }
        return ans;
    }
};

// 32. ============================================================

class Solution
{
public:
    int longestValidParentheses(string str)
    {
        int n = str.length();
        stack<int> st;
        st.push(-1);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (st.top() != -1 && str[i] == ')' && str[st.top()] == '(')
            {
                int val = st.top();
                st.pop();
                ans = max(ans, i - st.top());
            }
            else
            {
                st.push(i);
            }
        }
        return ans;
    }
};