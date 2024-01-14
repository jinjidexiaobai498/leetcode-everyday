// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=1944 lang=cpp
 * @lcpr version=30112
 *
 * [1944] 队列中可以看到的人数
 *
 * https://leetcode.cn/problems/number-of-visible-people-in-a-queue/description/
 *
 * algorithms
 * Hard (63.60%)
 * Likes:    78
 * Dislikes: 0
 * Total Accepted:    8.1K
 * Total Submissions: 12.1K
 * Testcase Example:  '[10,6,8,5,11,9]'
 *
 * 有 n 个人排成一个队列，从左到右 编号为 0 到 n -
 * 1 。给你以一个整数数组 heights ，每个整数 互不相同，heights[i] 表示第
 * i 个人的高度。
 *
 * 一个人能 看到 他右边另一个人的条件是这两人之间的所有人都比他们两人
 * 矮 。更正式的，第 i 个人能看到第 j 个人的条件是 i < j 且 min(heights[i],
 * heights[j]) > max(heights[i+1], heights[i+2], ..., heights[j-1]) 。
 *
 * 请你返回一个长度为
 * n 的数组 answer ，其中 answer[i] 是第 i 个人在他右侧队列中能 看到 的 人数 。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 * 输入：heights = [10,6,8,5,11,9]
 * 输出：[3,1,2,1,1,0]
 * 解释：
 * 第 0 个人能看到编号为 1 ，2 和 4 的人。
 * 第 1 个人能看到编号为 2 的人。
 * 第 2 个人能看到编号为 3 和 4 的人。
 * 第 3 个人能看到编号为 4 的人。
 * 第 4 个人能看到编号为 5 的人。
 * 第 5 个人谁也看不到因为他右边没人。
 *
 *
 * 示例 2：
 *
 * 输入：heights = [5,1,2,3,10]
 * 输出：[4,1,1,1,0]
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == heights.length
 * 1 <= n <= 10^5
 * 1 <= heights[i] <= 10^5
 * heights 中所有数 互不相同 。
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
  vector<int> canSeePersonsCount(vector<int> &heights) {
    vector<int> ans(heights.size(), 0);
    deque<int> que;

    if (heights.size() == 1) {
      return ans;
    }
    que.push_back(1);

    for (int i = 2; i < heights.size(); i++) {
      if (heights[i] > heights[que.back()]) {
        que.push_back(i);
      }
    }
    ans[0] = que.size();

    for (int i = 1; i < heights.size(); i++) {
      if (que.empty()) {
        ans[i] = 0;
        continue;
      }

      while (que.front() < i + 1) {
        que.pop_front();
      }

      if (que.front() == i + 1) {
        que.pop_front();
        ans[i] = que.size();
        continue;
      }
      if (que.front() > i) {
        int len = 1;
        que.push_back(i);
        int j = i + 1;
        while (j < que.front()) {
          if (heights[j] > heights[que.back()]) {
            que.push_back(j);
            len += 1;
          }
          j += 1;
        }

        while (len--) {
          int x = que.back();
          que.pop_back();
          que.push_front(x);
        }

        if (que.front() == i) {
          que.pop_front();
          ans[i] = que.size();
        }
      }
    }
    return ans;
  }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=canSeePersonsCount
// paramTypes= ["number[]"]
// @lcpr-div-debug-arg-end

/*
// @lcpr case=start
// [10,6,8,5,11,9]\n
// @lcpr case=end

// @lcpr case=start
// [5,1,2,3,10]\n
// @lcpr case=end

 */
