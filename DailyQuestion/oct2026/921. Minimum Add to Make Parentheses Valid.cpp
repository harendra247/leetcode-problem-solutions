class Solution {
public:
    // Time: O(n) Space: O(n)
    int minAddToMakeValid_(string S) {
        stack<char> st;
        for(auto a:S) {
            if (a=='(') {
                st.push('(');
            } else if (a==')') {
                if (st.size() && st.top() == '(') {
                    st.pop();
                } else {
                    st.push(a);
                }
            } else {
                continue;
            }
        }
        
        return st.size();
    }
    
    // Time: O(n) Space: O(1)
    int minAddToMakeValid(string S) {
        int left = 0, right = 0;
        for (char c : S)
            if (c == '(')
                right++;
            else if (right > 0)
                right--;
            else
                left++;
        return left + right;
    }
};
