
//1021. =======================================================
class Solution {
    public String removeOuterParentheses(String S) {
        String ans = "";
        int count = 0;
        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == '(' && count++ > 0)
                ans += S.charAt(i);
            if (S.charAt(i) == ')' && count-- > 1)
                ans += S.charAt(i);
        }
        return ans;
    }
}