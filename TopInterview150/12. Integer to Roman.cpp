class Solution {
public:
    // Greedy
    //
    // Time:  O(1)
    // Space: O(1)
    //
    // O(1) because Roman numerals have only 13 fixed
    // value-symbol combinations and num <= 3999.
    string intToRoman(int num) {

        /*
         * Roman symbols are arranged from largest
         * value to smallest value.
         *
         * Special subtractive combinations are also included:
         *
         * 900 = CM
         * 400 = CD
         * 90  = XC
         * 40  = XL
         * 9   = IX
         * 4   = IV
         */
        vector<string> numeral = {
            "M", "CM", "D", "CD",
            "C", "XC", "L", "XL",
            "X", "IX", "V", "IV", "I"
        };

        // Corresponding integer values.
        vector<int> value = {
            1000, 900, 500, 400,
            100, 90, 50, 40,
            10, 9, 5, 4, 1
        };

        string result;

        // Points to the current Roman value/symbol.
        int i = 0;

        while (num > 0) {

            /*
             * GREEDY:
             *
             * If the current Roman value can fit into num,
             * use it immediately.
             *
             * Example:
             *
             * num = 1994
             *
             * 1994 >= 1000
             * => append "M"
             * => num becomes 994
             */
            if (num >= value[i]) {

                // Add corresponding Roman symbol.
                result += numeral[i];

                // Remove its value from num.
                num -= value[i];

                /*
                 * IMPORTANT:
                 * We DON'T increment i here.
                 *
                 * The same Roman symbol might be needed again.
                 *
                 * Example:
                 * num = 3000
                 *
                 * M -> remaining 2000
                 * M -> remaining 1000
                 * M -> remaining 0
                 *
                 * Result = "MMM"
                 */
            } else {

                /*
                 * Current Roman value is too large.
                 * Move to the next smaller value.
                 */
                i++;
            }
        }

        return result;
    }
public:
    string intToRoman_(int num) {
       vector<string> numeral = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        vector<int> value = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        stringstream ss;
        ss.str("");
        int i=0;//pointer to numerals / value
        while (num>0) {
            if (num >= value[i]) {
                ss << numeral[i];
                num = num-value[i];
            } else {
                i++;
            }
        }
        return ss.str();  
    }
};
