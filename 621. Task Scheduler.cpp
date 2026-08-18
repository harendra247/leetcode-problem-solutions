class Solution {
public:
    // Time: O(N)
    // Space: O(1), because there are only 26 task types
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26] = {};

        int maxFreq = 0;

        // Find frequency of each task and maximum frequency.
        for (char task : tasks) {
            ++freq[task - 'A'];

            maxFreq = max(maxFreq, freq[task - 'A']);
        }

        /*
         * Count how many task types occur maxFreq times.
         *
         * Example:
         *
         * A -> 3
         * B -> 3
         * C -> 2
         *
         * maxFreqTasks = 2
         */
        int maxFreqTasks = 0;

        for (int count : freq) {
            if (count == maxFreq) {
                ++maxFreqTasks;
            }
        }

        /*
         * Imagine building blocks around the most
         * frequent tasks.
         *
         * Example:
         *
         * maxFreq = 3
         * n = 2
         *
         * A _ _ | A _ _ | A
         *
         * There are maxFreq - 1 full blocks.
         *
         * Each block has:
         *
         * 1 task + n cooldown positions
         *
         * = n + 1 positions.
         */
        int forcedScheduleLength = (maxFreq - 1) * (n + 1) + maxFreqTasks;

        /*
         * If enough other tasks exist, they fill the idle
         * positions and the schedule is simply tasks.size().
         *
         * Otherwise cooldowns force extra idle positions.
         */
        return max(static_cast<int>(tasks.size()), forcedScheduleLength);
    }
  
public:
    // Let T = number of tasks, U = number of unique task types.
    //
    // Since there are at most 26 task types:
    // Time:  O(T log U) = effectively O(T)
    // Space: O(U)       = effectively O(1)
    int leastInterval_(vector<char>& tasks, int n) {
        unordered_map<char, int> frequency;

        // Count how many times each task appears.
        for (char task : tasks) {
            ++frequency[task];
        }

        // Max-heap:
        // task type with highest remaining frequency first.
        priority_queue<int> maxHeap;

        for (auto [task, count] : frequency) {
            maxHeap.push(count);
        }

        int totalTime = 0;

        // One full cooldown block.
        int cycleLength = n + 1;

        while (!maxHeap.empty()) {

            /*
             * Store tasks used in this cycle.
             *
             * We don't push them back immediately,
             * otherwise the same task could be selected again
             * before its cooldown is finished.
             */
            vector<int> usedTasks;

            int tasksExecuted = 0;

            /*
             * Try to fill one cycle with up to n+1
             * DIFFERENT task types.
             */
            for (int slot = 0; slot < cycleLength && !maxHeap.empty(); ++slot) {

                usedTasks.push_back(maxHeap.top());
                maxHeap.pop();

                ++tasksExecuted;
            }

            /*
             * One execution was consumed from each task.
             * Put unfinished tasks back into the heap.
             */
            for (int count : usedTasks) {
                --count;

                if (count > 0) {
                    maxHeap.push(count);
                }
            }

            /*
             * If tasks still remain:
             *     the whole cycle counts, including idle slots.
             *
             * If no tasks remain:
             *     this was the last cycle, so trailing idle
             *     slots are unnecessary.
             */
            if (!maxHeap.empty()) {
                totalTime += cycleLength;
            } else {
                totalTime += tasksExecuted;
            }
        }

        return totalTime;
    }
};
