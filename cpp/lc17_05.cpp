/*
 * @lc app=leetcode.cn id=面试题 17.05 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 17.05]  字母与数字
 */
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
  public:
    auto findLongestSubarray(vector<string>& array) -> vector<string>
    {
        vector<int>             dp_digit(array.size() + 1, 0);
        unordered_map<int, int> map;
        int                     max_len     = 0;
        int                     start_index = 0;
        int                     end_index   = 0;

        int sum = 0;
        for (int i = 1; i < array.size() + 1; i++) {
            if (isdigit(array[i - 1][0])) {
                sum++;
                dp_digit[i] = sum;
            }
            map[(2 * sum - i)] = i;
        }

        for (int i = 1; i < dp_digit.size(); i++) {
            if (i + max_len + 1 < dp_digit.size()) {
                int key = 2 * dp_digit[i - 1] - i + 1;
                if (map.count(key) != 0 && max_len < map[key] - i + 1) {
                    start_index = i;
                    end_index   = map[key];
                    max_len     = map[key] - i + 1;
                }
            }
        }

        if (start_index == 0)
            return {};
        return {array.begin() + start_index - 1, array.begin() + end_index};
    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end

/*
// @lcpr case=start
//
// @lcpr case=end

// @lcpr case=start
//
// @lcpr case=end

 */

//["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]

auto main() -> int
{
    vector<string> input = {"A", "1", "B", "C", "D", "2", "3", "4", "E", "5",
                            "F", "G", "6", "7", "H", "I", "J", "K", "L", "M"};
    Solution       sol;
    vector<string> ans = sol.findLongestSubarray(input);

    for (const auto& c : ans) {
        cout << c << " ";
    }
    return 0;
}