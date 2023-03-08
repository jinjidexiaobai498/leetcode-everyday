/*
 * @lc app=leetcode.cn id=剑指 Offer 47 lang=cpp
 * @lcpr version=21801
 *
 * [剑指 Offer 47] 礼物的最大价值
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
    auto maxValue(vector<vector<int>>& grid) -> int
    {
        vector<int> dp_array(grid[0].size(), 0);
        dp_array[0] = grid[0][0];
        for (int i = 1; i < dp_array.size(); i++) {
            dp_array[i] = grid[0][i] + dp_array[i - 1];
        }
        for (int i = 1; i < grid.size(); i++) {
            dp_array[0] += grid[i][0];
            for (int j = 1; j < dp_array.size(); j++) {
                dp_array[j] = max(dp_array[j - 1], dp_array[j]) + grid[i][j];
            }
        }
        return dp_array.back();
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

 */
