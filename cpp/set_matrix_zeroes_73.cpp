/*
 * @lc app=leetcode.cn id=73 lang=cpp
 * @lcpr version=30113
 *
 * [73] 矩阵置零
 *
 * https://leetcode.cn/problems/set-matrix-zeroes/description/
 *
 * algorithms
 * Medium (64.40%)
 * Likes:    1000
 * Dislikes: 0
 * Total Accepted:    306.5K
 * Total Submissions: 471.9K
 * Testcase Example:  '[[1,1,1],[1,0,1],[1,1,1]]'
 *
 * 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0
 * 。请使用 原地 算法。
 *
 *
 *
 *
 *
 *
 * 示例 1：
 *
 * 输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * 输出：[[1,0,1],[0,0,0],[1,0,1]]
 *
 *
 * 示例 2：
 *
 * 输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * 输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == matrix.length
 * n == matrix[0].length
 * 1 <= m, n <= 200
 * -2^31 <= matrix[i][j] <= 2^31 - 1
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
 * 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
 * 你能想出一个仅使用常量空间的解决方案吗？
 *
 *
 */

// @lcpr-template-start
#include <climits>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
 public:
  void setZeroes(vector<vector<int>> &matrix) {
    int FLAG_ZERO = INT_MIN;
    auto row_len = matrix.size();
    auto col_len = matrix[0].size();
    vector<pair<int, int>> list;
    for (auto i = 0; i < row_len; ++i) {
      for (auto j = 0; j < col_len; ++j) {
        auto e = matrix[i][j];
        if (e == FLAG_ZERO) {
          matrix[i][j] = 1;
          list.push_back({i, j});
        }
      }
    }

    for (auto &row : matrix) {
      for (auto &e : row) {
        if (e == 0) e = FLAG_ZERO;
      }
    }
    for (auto i = 0; i < row_len; ++i) {
      for (auto j = 0; j < col_len; ++j) {
        auto val = matrix[i][j];
        if (val == FLAG_ZERO) {
          for (auto &e : matrix[i]) {
            if (e != FLAG_ZERO && e != 0) e = 0;
          }
          for (auto k = 0; k < row_len; ++k) {
            if (matrix[k][j] != FLAG_ZERO && matrix[k][j] != 0)
              matrix[k][j] = 0;
          }
        }
      }
    }

    for (auto &row : matrix) {
      for (auto &e : row) {
        if (e == FLAG_ZERO) e = 0;
      }
    }
    for (auto &[x, y] : list) {
      if (matrix[x][y] != 0) {
        matrix[x][y] = FLAG_ZERO;
      }
    }
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,1,1],[1,0,1],[1,1,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,1,2,0],[3,4,5,2],[1,3,1,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[-2147483648,1,2]]\n
// @lcpr case=end

 */
