/*
 * @lc app=leetcode.cn id=11 lang=cpp * @lcpr version=30112 *
 * [11] 盛最多水的容器
 *
 * https://leetcode.cn/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (60.04%)
 * Likes:    4710
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 1.9M
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i,
 * 0) 和 (i, height[i]) 。
 *
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 *
 * 返回容器可以储存的最大水量。
 *
 * 说明：你不能倾斜容器。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49
 * 解释：图中垂直线代表输入数组
 * [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 *
 * 示例 2：
 *
 * 输入：height = [1,1]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == height.length
 * 2 <= n <= 10^5
 * 0 <= height[i] <= 10^4
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

struct IndexedElem {
  int index;
  int value;
  bool operator<(const IndexedElem &b) { return this->value > b.value; }
};

class Solution {
 public:
  int maxArea(vector<int> &height) {
    vector<IndexedElem> list(height.size());
    for (int i = 0; i < height.size(); i++) {
      list[i].index = i;
      list[i].value = height[i];
    }
    sort(list.begin(), list.end());

    int max_index = list[0].index, min_index = list[0].index;
    int max_area = 0;

    for (int i = 1; i < height.size(); i++) {
      int index = list[i].index;
      int value = list[i].value;
      int max_abs = max(abs(max_index - index), abs(min_index - index));
      max_area = max(max_area, max_abs * value);
      max_index = max(max_index, index);
      min_index = min(min_index, index);
    }
    return max_area;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,8,6,2,5,4,8,3,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end

 */

int main() {
  vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  Solution sol;
  cout << sol.maxArea(height) << endl;
}
