/*
* @lc app=leetcode.cn id=2336 lang=rust
* @lcpr version=30111
*
* [2336] 无限集中的最小数字
*
* https://leetcode.cn/problems/smallest-number-in-infinite-set/description/
*
* algorithms
* Medium (69.46%)
* Likes:    61
* Dislikes: 0
* Total Accepted:    27.1K
* Total Submissions: 37.3K
* Testcase Example:  '["SmallestInfiniteSet","addBack","popSmallest","popSmallest","popSmallest","addBack","popSmallest","popSmallest","popSmallest"]\n' +
 '[[],[2],[],[],[],[1],[],[],[]]'
*
* 现有一个包含所有正整数的集合 [1, 2, 3, 4, 5, ...] 。
*
* 实现 SmallestInfiniteSet 类：
*
*
* SmallestInfiniteSet() 初始化 SmallestInfiniteSet 对象以包含 所有 正整数。
* int popSmallest() 移除 并返回该无限集中的最小整数。
* void addBack(int num) 如果正整数 num 不 存在于无限集中，则将一个 num 添加 到该无限集最后。
*
*
*
*
* 示例：
*
* 输入
* ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest",
* "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"]
* [[], [2], [], [], [], [1], [], [], []]
* 输出
* [null, null, 1, 2, 3, null, 1, 4, 5]
*
* 解释
* SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
* smallestInfiniteSet.addBack(2);    // 2 已经在集合中，所以不做任何变更。
* smallestInfiniteSet.popSmallest(); // 返回 1 ，因为 1 是最小的整数，并将其从集合中移除。
* smallestInfiniteSet.popSmallest(); // 返回 2 ，并将其从集合中移除。
* smallestInfiniteSet.popSmallest(); // 返回 3 ，并将其从集合中移除。
* smallestInfiniteSet.addBack(1);    // 将 1 添加到该集合中。
* smallestInfiniteSet.popSmallest(); // 返回 1 ，因为 1 在上一步中被添加到集合中，
* ⁠                                  // 且 1 是最小的整数，并将其从集合中移除。
* smallestInfiniteSet.popSmallest(); // 返回 4 ，并将其从集合中移除。
* smallestInfiniteSet.popSmallest(); // 返回 5 ，并将其从集合中移除。
*
*
*
* 提示：
*
*
* 1 <= num <= 1000
* 最多调用 popSmallest 和 addBack 方法 共计 1000 次
*
*
*/

// @lcpr-template-start
pub struct Solution;
// @lcpr-template-end
// @lc code=start

use std::collections::BTreeSet;

type Set = BTreeSet<i32>;
struct SmallestInfiniteSet {
    set: Set,
    set_left: i32,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl SmallestInfiniteSet {
    fn new() -> Self {
        Self {
            set: Set::new(),
            set_left: 1,
        }
    }

    fn pop_smallest(&mut self) -> i32 {
        if self.set.is_empty() {
            self.set_left += 1;
            return self.set_left - 1;
        }
        let res = self.set.iter().next().unwrap().clone();
        self.set.remove(&res);
        return res;
    }

    fn add_back(&mut self, num: i32) {
        if num >= self.set_left {
            return;
        }
        if self.set.contains(&num) {
            return;
        }
        if num == self.set_left - 1 {
            self.set_left -= 1;
            let mut num = self.set_left - 1;
            loop {
                if num <= 0 || !self.set.contains(&num) {
                    break;
                }
                self.set_left -= 1;
                self.set.remove(&num);
                num -= 1;
            }
            return;
        }
        self.set.insert(num);
    }
}

/*
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * let obj = SmallestInfiniteSet::new();
 * let ret_1: i32 = obj.pop_smallest();
 * obj.add_back(num);
 */
// @lc code=end
