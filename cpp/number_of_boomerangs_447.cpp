/*
 * @lc app=leetcode.cn id=447 lang=cpp
 * @lcpr version=30113
 *
 * [447] 回旋镖的数量
 *
 * https://leetcode.cn/problems/number-of-boomerangs/description/
 *
 * algorithms
 * Medium (66.78%)
 * Likes:    265
 * Dislikes: 0
 * Total Accepted:    59.6K
 * Total Submissions: 88.6K
 * Testcase Example:  '[[0,0],[1,0],[2,0]]'
 *
 * 给定平面上 n 对 互不相同 的点 points ，其中 points[i] = [xi, yi] 。回旋镖
 * 是由点 (i, j, k) 表示的元组
 * ，其中 i 和 j 之间的距离和 i 和 k 之间的欧式距离相等（需要考虑元组的顺序）。
 *
 * 返回平面上所有回旋镖的数量。
 *
 *
 * 示例 1：
 *
 * 输入：points = [[0,0],[1,0],[2,0]]
 * 输出：2
 * 解释：两个回旋镖为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]]
 *
 *
 * 示例 2：
 *
 * 输入：points = [[1,1],[2,2],[3,3]]
 * 输出：2
 *
 *
 * 示例 3：
 *
 * 输入：points = [[1,1]]
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == points.length
 * 1 <= n <= 500
 * points[i].length == 2
 * -10^4 <= xi, yi <= 10^4
 * 所有点都 互不相同
 *
 *
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
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
// @lcpr-template-end
// @lc code=start

class Solution {
public:
  int numberOfBoomerangs(vector<vector<int>> &points) {
    int ans = 0;
    int x = 0, y = 0, dis = 0;
    for (auto &p1 : points) {
      unordered_map<int, int> map;
      for (auto &p2 : points) {
        x = p1[0] - p2[0];
        y = p1[1] - p2[1];
        dis = x * x + y * y;
        ++map[dis];
      }
      for (auto &[_, count] : map) {
        ans += (count - 1) * count;
      }
    }
    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[0,0],[1,0],[2,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1],[2,2],[3,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1]]\n
// @lcpr case=end

 */
