class Solution {
public:
    // r = reservedSeats.size()
    // Time: O(r)
    // Space: O(r)
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        /*
         * Bits represent seats:
         *
         * bit:   7 6 5 4 3 2 1 0
         * seat:  9 8 7 6 5 4 3 2
         */

        // Seats 2,3,4,5
        const int LEFT = 0b00001111;

        // Seats 4,5,6,7
        const int MIDDLE = 0b00111100;

        // Seats 6,7,8,9
        const int RIGHT = 0b11110000;

        // row -> reserved seats bitmask
        unordered_map<int, int> occupied;

        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            /*
             * Seats 1 and 10 don't affect any
             * possible 4-person group.
             */
            if (col >= 2 && col <= 9) {
                occupied[row] |= 1 << (col - 2);
            }
        }

        /*
         * Every row not present in occupied has no
         * relevant reservations.
         *
         * Such a row can always fit TWO families:
         *
         * seats 2-5
         * seats 6-9
         */
        int answer = (n - static_cast<int>(occupied.size())) * 2;

        /*
         * Now handle only rows that actually have
         * relevant reservations.
         */
        for (auto [row, mask] : occupied) {

            bool leftFree = (mask & LEFT) == 0;

            bool rightFree = (mask & RIGHT) == 0;

            if (leftFree && rightFree) {
                // Can fit two families.
                answer += 2;
            } else {
                bool middleFree = (mask & MIDDLE) == 0;

                /*
                 * If either left, middle, or right
                 * block is available, we can fit
                 * exactly one family.
                 */
                if (leftFree || middleFree || rightFree) {
                    ++answer;
                }
            }
        }

        return answer;
    }
};
