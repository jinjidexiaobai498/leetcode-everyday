/*
 * @lc app=leetcode.cn id=11 lang=rust
 * @lcpr version=30111
 *
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
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
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
 * 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
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
pub struct Solution;
// @lcpr-template-end
// @lc code=start
impl Solution {
    pub fn max_area(height: Vec<i32>) -> i32 {
        let mut ans = 0;
        let mut max_list = vec![0i32; height.len()];
        max_list[0] = height[0];
        for i in 1..max_list.len() {
            max_list[i] = std::cmp::max(max_list[i - 1], height[i]);
        }
        for i in 1..height.len() {
            let j = Self::find(height[i], &max_list, &height);
            ans = std::cmp::max(ans, ((j - i) as i32) * height[i]);
        }

        return 0;
    }
    fn rfind(x: i32, max_list: &Vec<i32>, height: &Vec<i32>) -> usize {
        let mut l = 0usize;
        let mut r = max_list.len();
        while l < r {
            let mid = (l + r) >> 1;
            if height[mid] > x {
                if mid == 0 || height[mid - 1] < x {
                    return mid;
                }
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
    fn find(x: i32, max_list: &Vec<i32>, height: &Vec<i32>) -> usize {
        let mut l = 0usize;
        let mut r = max_list.len();
        while l < r {
            let mid = (l + r) >> 1;
            if height[mid] >= x {
                if mid == 0 || height[mid - 1] < x {
                    return mid;
                }
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
}
// @lc code=end

/*
// @lcpr case=start
// [1,8,6,2,5,4,8,3,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end

 */
