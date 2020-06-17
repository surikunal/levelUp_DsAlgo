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