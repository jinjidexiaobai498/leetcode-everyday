// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=689 lang=cpp
 * @lcpr version=30109
 *
 * [689] 三个无重叠子数组的最大和
 *
 * https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
 *
 * algorithms
 * Hard (56.09%)
 * Likes:    396
 * Dislikes: 0
 * Total Accepted:    30.2K
 * Total Submissions: 51.7K
 * Testcase Example:  '[1,2,1,2,6,7,5,1]\n2'
 *
 * 给你一个整数数组 nums 和一个整数 k ，找出三个长度为 k
 * 、互不重叠、且全部数字和（3 * k 项）最大的子数组，并返回这三个子数组。
 *
 * 以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置（下标从
 * 0 开始）。如果有多个结果，返回字典序最小的一个。
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums = [1,2,1,2,6,7,5,1], k = 2
 * 输出：[0,3,5]
 * 解释：子数组 [1, 2], [2, 6], [7, 5] 对应的起始下标为 [0, 3, 5]。
 * 也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
 *
 *
 * 示例 2：
 *
 * 输入：nums = [1,2,1,2,1,2,1,2,1], k = 2
 * 输出：[0,2,4]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 2 * 10^4
 * 1 <= nums[i] < 2^16
 * 1 <= k <= floor(nums.length / 3)
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
  vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
    int cur_first = get_sum_at_index_after_k(nums, k, 0);
    int cur_second = get_sum_at_index_after_k(nums, k, k);
    int cur_third = get_sum_at_index_after_k(nums, k, 2 * k);

    int max_first_one_index = 0;
    int max_first_one = cur_first;

    int max_first_two_sum = cur_first + cur_second;
    int max_first_two_index1 = 0;
    int max_first_two_index2 = k;

    int max_sum = cur_first + cur_second + cur_third;

    vector<int> ans{0, k, 2 * k};

    for (int i = 2 * k; i + k < nums.size(); i++) {

      cur_first += nums[i - k] - nums[i - 2 * k];
      cur_second += nums[i] - nums[i - k];
      cur_third += nums[i + k] - nums[i];

      if (cur_first > max_first_one) {
        max_first_one = cur_first;
        max_first_one_index = i - 2 * k + 1;
      }

      int cur_first_two_sum = max_first_one + cur_second;

      if (max_first_two_sum < cur_first_two_sum) {
        max_first_two_sum = cur_first_two_sum;
        max_first_two_index1 = max_first_one_index;
        max_first_two_index2 = i + 1 - k;
      }

      int cur_max_sum = max_first_two_sum + cur_third;
      if (cur_max_sum > max_sum) {
        max_sum = cur_max_sum;
        ans[0] = max_first_two_index1;
        ans[1] = max_first_two_index2;
        ans[2] = i + 1;
      }
    }
    return ans;
  }

  auto get_sum_at_index_after_k(vector<int> &nums, int k, int index) -> int {
    int sum = 0;
    for (int i = index; i < k + index; i++) {
      sum += nums[i];
    }
    return sum;
  }
};

// @lc code=end

/*
// @lcpr case=start
// [1,2,1,2,6,7,5,1]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,2,1,2,1,2,1]\n2\n
// @lcpr case=end

// @lcpr case=start
// [4,5,10,6,11,17,4,11,1,3]\n1\n
// @lcpr case=end
 */
