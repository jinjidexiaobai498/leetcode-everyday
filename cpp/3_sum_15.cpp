/*
 * @lc app=leetcode.cn id=15 lang=cpp
 * @lcpr version=30112
 *
 * [15] 三数之和 *
 * https://leetcode.cn/problems/3sum/description/
 *
 * algorithms
 * Medium (37.46%)
 * Likes:    6629
 * Dislikes: 0
 * Total Accepted:    1.6M
 * Total Submissions: 4.3M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i
 * != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请
 *
 * 你返回所有和为 0 且不重复的三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums = [-1,0,1,2,-1,-4]
 * 输出：[[-1,-1,2],[-1,0,1]]
 * 解释：
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
 * 不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
 * 注意，输出的顺序和三元组的顺序并不重要。
 *
 *
 * 示例 2：
 *
 * 输入：nums = [0,1,1]
 * 输出：[]
 * 解释：唯一可能的三元组和不为 0 。
 *
 *
 * 示例 3：
 *
 * 输入：nums = [0,0,0]
 * 输出：[[0,0,0]]
 * 解释：唯一可能的三元组和为 0 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 3 <= nums.length <= 3000
 * -10^5 <= nums[i] <= 10^5
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
#include <stack>
#include <string>
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
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>>     ans;
        unordered_map<int, int> nmap;

        int size = 0;
        for (int i = 0; i < nums.size(); ++i) {
            nmap[nums[i]] += 1;
            if (nmap[nums[i]] <= 2) {
                size += 1;
            }
        }

        vector<int> new_nums(size, 0);
        int         ti = 0;
        for (auto [num, count] : nmap) {
            new_nums[ti] = num;
            ti += 1;
            if (count > 1) {
                new_nums[ti] = num;
                ti += 1;
            }
        }

        sort(new_nums.begin(), new_nums.end());
        for (int i = 0; i < size; ++i) {
            if (i > 0 && new_nums[i] == new_nums[i - 1]) {
                continue;
            }

            int first = new_nums[i];
            if (first > 0)
                break;
            nmap[first] -= 1;

            for (int j = i + 1; j < size; ++j) {
                if (j > i + 1 && new_nums[j] == new_nums[j - 1]) {
                    continue;
                }

                int second = new_nums[j];
                int third  = 0 - first - second;
                if (third < second)
                    break;

                nmap[second] -= 1;
                if (nmap.count(third) != 0 && nmap[third] > 0) {
                    ans.push_back({first, second, third});
                }
                nmap[second] += 1;
            }

            nmap[first] += 1;
        }

        return ans;
    }
};
// @lc code=end

/*
// @lcpr case=start
// [-1,0,1,2,-1,-4]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,0]\n
// @lcpr case=end

*/
