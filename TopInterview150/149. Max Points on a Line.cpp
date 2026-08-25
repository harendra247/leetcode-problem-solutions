class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();

        if (n <= 2) {
            return n;
        }

        int answer = 0;

        // Pick every point as an anchor.
        for (int i = 0; i < n; ++i) {

            // {dy, dx} -> number of points having this slope
            // with respect to points[i].
            map<pair<int, int>, int> slopeCount;

            int duplicate = 0;
            int best = 0;

            for (int j = i + 1; j < n; ++j) {

                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                // Duplicate point.
                if (dx == 0 && dy == 0) {
                    ++duplicate;
                    continue;
                }

                /*
                 * Normalize the slope.
                 *
                 * Vertical line:
                 *     dx = 0
                 *     Represent every vertical line as (1, 0).
                 *
                 * Horizontal line:
                 *     dy = 0
                 *     Represent every horizontal line as (0, 1).
                 *
                 * Otherwise reduce dy/dx using GCD and make dx positive.
                 */
                if (dx == 0) {
                    dy = 1;
                }
                else if (dy == 0) {
                    dx = 1;
                }
                else {
                    int g = gcd(abs(dx), abs(dy));

                    dx /= g;
                    dy /= g;

                    // Make sure equivalent slopes have
                    // the same sign representation.
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                }

                int count = ++slopeCount[{dy, dx}];

                best = max(best, count);
            }

            /*
             * +1     -> anchor point itself
             * +duplicate -> duplicate points
             */
            answer = max(answer, best + duplicate + 1);
        }

        return answer;
    }
};
