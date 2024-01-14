// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=41 lang=cpp
 * @lcpr version=30113
 *
 * [41] 缺失的第一个正数
 *
 * https://leetcode.cn/problems/first-missing-positive/description/
 *
 * algorithms
 * Hard (43.55%)
 * Likes:    2032
 * Dislikes: 0
 * Total Accepted:    344.7K
 * Total Submissions: 787.3K
 * Testcase Example:  '[1,2,0]'
 *
 * 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
 * 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums = [1,2,0]
 * 输出：3
 *
 *
 * 示例 2：
 *
 * 输入：nums = [3,4,-1,1]
 * 输出：2
 *
 *
 * 示例 3：
 *
 * 输入：nums = [7,8,9,11,12]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 5 * 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 *
 *
 */

// @lcpr-template-start
#include <pthread.h>

#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
 public:
  int firstMissingPositive(vector<int> &nums) {
    int len = nums.size();
    int val = nums[0];
    for (int index = 0; index < len; ++index) {
      val = nums[index];
      while (val > 0 && val <= len && val - 1 != index &&
             nums[val - 1] != val) {
        nums[index] = nums[val - 1];
        nums[val - 1] = val;
        val = nums[index];
      }
    }
    for (int i = 0; i < len; ++i) {
      if (i + 1 != nums[i]) {
        return i + 1;
      }
    }

    return len + 1;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,2,0]\n
// @lcpr case=end

// @lcpr case=start
// [3,4,-1,1]\n
// @lcpr case=end

// @lcpr case=start
// [3,4,-1,1,2,5,7,0,9]\n
// @lcpr case=end

// @lcpr case=start
// [7,8,9,11,12]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end
 */
