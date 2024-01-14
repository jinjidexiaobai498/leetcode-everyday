// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * @lcpr version=30113
 *
 * [54] 螺旋矩阵
 *
 * https://leetcode.cn/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (49.83%)
 * Likes:    1579
 * Dislikes: 0
 * Total Accepted:    446.6K
 * Total Submissions: 892K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序
 * ，返回矩阵中的所有元素。
 *
 *
 *
 * 示例 1：
 *
 * 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * 输出：[1,2,3,6,9,8,7,4,5]
 *
 *
 * 示例 2：
 *
 * 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * 输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 10
 * -100 <= matrix[i][j] <= 100
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
  // x+,y+,x-;
  // y-,x+,y+;
  // x-,y-,x+;
  // y+,x-,y-;
  const int fxy[4][3] = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  const int fpm[4][3] = {{1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}, {1, -1, -1}};
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    auto ylen = matrix.size();
    if (ylen == 0) return {};
    auto xlen = matrix[0].size();
    vector<int> ans(xlen * ylen);

    int x = 0, y = 0;
    int index = 0;
    int turns = 0;
    while (xlen > 0 && ylen > 0 && index < ans.size()) {
      int len = 3;
      if (fxy[turns][0] && ylen == 1) len = 1;
      if (!fxy[turns][0] && xlen == 1) len = 1;
      for (int i = 0; i < len; ++i) {
        add(ans, matrix, x, y, index, turns, xlen - 1, ylen - 1, i);
      }

      xlen -= fxy[turns][0] ? 1 : 2;
      ylen -= fxy[turns][0] ? 2 : 1;

      ++turns;
      turns &= 0b11;
      if (index < ans.size()) {
        ans[index++] = matrix[y][x];
        x += fxy[turns][0] ? fpm[turns][0] : 0;
        y += fxy[turns][0] ? 0 : fpm[turns][0];
      }
    }

    return ans;
  }

  inline void add(vector<int> &ans, vector<vector<int>> &matrix, int &x, int &y,
                  int &index, int turns, int xlen, int ylen, int i) {
    int op = fpm[turns][i];
    int len = fxy[turns][i] ? xlen : ylen;
    int xop = fxy[turns][i] ? op : 0;
    int yop = fxy[turns][i] ? 0 : op;

    for (int i = 0; i < len; ++i) {
      ans[index++] = matrix[y][x];
      x += xop;
      y += yop;
    }
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3,4],[5,6,7,8],[9,10,11,12]]\n
// @lcpr case=end

// @lcpr case=start
// [[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[6,9,7]]\n
// @lcpr case=end

 */
