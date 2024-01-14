// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * @lcpr version=30113
 *
 * [56] 合并区间
 *
 * https://leetcode.cn/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (49.66%)
 * Likes:    2214
 * Dislikes: 0
 * Total Accepted:    766.6K
 * Total Submissions: 1.5M
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti,
 * endi]
 * 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
 * 输出：[[1,6],[8,10],[15,18]]
 * 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
 *
 *
 * 示例 2：
 *
 * 输入：intervals = [[1,4],[4,5]]
 * 输出：[[1,5]]
 * 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= intervals.length <= 10^4
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 10^4
 *
 *
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    vector<pair<int, int>> list{intervals.size()};
    for (int i = 0; i < intervals.size(); ++i) {
      list[i] = {intervals[i][0], intervals[i][1]};
    }
    sort(begin(list), end(list));
    vector<vector<int>> ans;
    int starti = list[0].first, endi = list[0].second;
    for (int i = 1; i < list.size(); ++i) {
      auto [s, e] = list[i];
      if (s > endi) {
        ans.push_back({starti, endi});
        starti = s;
        endi = e;
      } else {
        endi = max(endi, e);
      }
    }
    ans.push_back({starti, endi});

    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,3],[2,6],[8,10],[15,18]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[4,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[2,3],[4,6],[5,7],[3,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[0,1]]\n
// @lcpr case=end
 */
