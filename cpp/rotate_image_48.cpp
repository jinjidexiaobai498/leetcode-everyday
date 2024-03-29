// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=48 lang=cpp
 * @lcpr version=30113
 *
 * [48] 旋转图像
 *
 * https://leetcode.cn/problems/rotate-image/description/
 *
 * algorithms
 * Medium (75.18%)
 * Likes:    1795
 * Dislikes: 0
 * Total Accepted:    518.8K
 * Total Submissions: 688K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
 *
 * 你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要
 * 使用另一个矩阵来旋转图像。
 *
 *
 *
 * 示例 1：
 *
 * 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * 输出：[[7,4,1],[8,5,2],[9,6,3]]
 *
 *
 * 示例 2：
 *
 * 输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 * 输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == matrix.length == matrix[i].length
 * 1 <= n <= 20
 * -1000 <= matrix[i][j] <= 1000
 *
 *
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
  void rotate(vector<vector<int>> &matrix) {
    if (matrix.size() == 0)
      return;
    pair<int, int> rot[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, rt[4] = {};
    int n = matrix.size(), len = matrix.size();

    for (int i = 0; i < (n >> 1); ++i, len -= 2) {
      rt[0] = {i, i};
      for (int j = 1; j < 4; ++j)
        rt[j] = {n - rt[j - 1].second - 1, rt[j - 1].first};

      for (int j = 0; j < len - 1; ++j) {
        int tmp = matrix[rt[3].second][rt[3].first];
        for (int k = 3; k > 0; --k)
          matrix[rt[k].second][rt[k].first] =
              matrix[rt[k - 1].second][rt[k - 1].first];
        matrix[rt[0].second][rt[0].first] = tmp;

        for (int k = 0; k < 4; ++k)
          rt[k] = {rt[k].first + rot[k].first, rt[k].second + rot[k].second};
      }
    }
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]\n
// @lcpr case=end

 */
