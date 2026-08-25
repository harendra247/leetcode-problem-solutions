class Solution {
public:
    
    // Time: O(max(m, n)) Space: O(n)
    string addBinary(string a, string b) {
        int p = a.length() - 1, q = b.length() - 1;
        string ans ="";
        int carry = 0;
        while(p >= 0 || q >= 0 || carry == 1) {
            int m = p >= 0 ? (a[p--] - '0') : 0;
            int n = q >= 0 ? (b[q--] - '0') : 0;
            int sum  = (m + n + carry); // same as (m^n^carry);
            carry = sum / 2; // same as sum >> 2;
            ans = to_string(sum % 2) + ans;
        }
        return ans;     
    }
};
