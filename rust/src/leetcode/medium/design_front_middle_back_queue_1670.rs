/*
* @lc app=leetcode.cn id=1670 lang=rust
* @lcpr version=30111
*
* [1670] 设计前中后队列
*
* https://leetcode.cn/problems/design-front-middle-back-queue/description/
*
* algorithms
* Medium (52.01%)
* Likes:    34
* Dislikes: 0
* Total Accepted:    8.5K
* Total Submissions: 16.2K
* Testcase Example:  '["FrontMiddleBackQueue","pushFront","pushBack","pushMiddle","pushMiddle","popFront","popMiddle","popMiddle","popBack","popFront"]\n' +
 '[[],[1],[2],[3],[4],[],[],[],[],[]]'
*
* 请你设计一个队列，支持在前，中，后三个位置的 push 和 pop 操作。
*
* 请你完成 FrontMiddleBack 类：
*
*
* FrontMiddleBack() 初始化队列。
* void pushFront(int val) 将 val 添加到队列的 最前面 。
* void pushMiddle(int val) 将 val 添加到队列的 正中间 。
* void pushBack(int val) 将 val 添加到队里的 最后面 。
* int popFront() 将 最前面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
* int popMiddle() 将 正中间 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
* int popBack() 将 最后面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
*
*
* 请注意当有 两个 中间位置的时候，选择靠前面的位置进行操作。比方说：
*
*
* 将 6 添加到 [1, 2, 3, 4, 5] 的中间位置，结果数组为 [1, 2, 6, 3, 4, 5] 。
* 从 [1, 2, 3, 4, 5, 6] 的中间位置弹出元素，返回 3 ，数组变为 [1, 2, 4, 5, 6] 。
*
*
*
*
* 示例 1：
*
* 输入：
* ["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle",
* "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
* [[], [1], [2], [3], [4], [], [], [], [], []]
* 输出：
* [null, null, null, null, null, 1, 3, 4, 2, -1]
*
* 解释：
* FrontMiddleBackQueue q = new FrontMiddleBackQueue();
* q.pushFront(1);   // [1]
* q.pushBack(2);    // [1, 2]
* q.pushMiddle(3);  // [1, 3, 2]
* q.pushMiddle(4);  // [1, 4, 3, 2]
* q.popFront();     // 返回 1 -> [4, 3, 2]
* q.popMiddle();    // 返回 3 -> [4, 2]
* q.popMiddle();    // 返回 4 -> [2]
* q.popBack();      // 返回 2 -> []
* q.popFront();     // 返回 -1 -> [] （队列为空）
*
*
*
*
* 提示：
*
*
* 1 <= val <= 10^9
* 最多调用 1000 次 pushFront， pushMiddle， pushBack， popFront， popMiddle 和 popBack
* 。
*
*
*/
// @lcpr-template-start
pub struct Solution;
// @lcpr-template-end
// @lc code=start

use std::collections::vec_deque::VecDeque;
type Que = VecDeque<i32>;
struct FrontMiddleBackQueue {
    front_half_que: Que,
    back_half_que: Que,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl FrontMiddleBackQueue {
    fn new() -> Self {
        Self {
            front_half_que: Que::new(),
            back_half_que: Que::new(),
        }
    }

    fn move_front(&mut self) {
        if self.back_half_que.is_empty() {
            return;
        }
        self.front_half_que
            .push_back(self.back_half_que.pop_front().unwrap());
    }
    fn move_back(&mut self) {
        if self.front_half_que.is_empty() {
            return;
        }
        self.back_half_que
            .push_front(self.front_half_que.pop_back().unwrap());
    }

    fn push_front(&mut self, val: i32) {
        self.front_half_que.push_front(val);
        if self.front_half_que.len() > self.back_half_que.len() {
            self.move_back();
        }
    }

    fn push_middle(&mut self, val: i32) {
        if self.front_half_que.len() == self.back_half_que.len() {
            self.back_half_que.push_front(val);
            return;
        }
        self.front_half_que.push_back(val);
    }

    fn push_back(&mut self, val: i32) {
        if self.front_half_que.len() < self.back_half_que.len() {
            self.move_front();
        }
        self.back_half_que.push_back(val);
    }

    fn pop_front(&mut self) -> i32 {
        if self.front_half_que.is_empty() && self.back_half_que.is_empty() {
            return -1;
        }
        if self.front_half_que.len() < self.back_half_que.len() {
            self.move_front();
        }
        return self.front_half_que.pop_front().unwrap();
    }

    fn pop_middle(&mut self) -> i32 {
        if self.front_half_que.is_empty() && self.back_half_que.is_empty() {
            return -1;
        }

        if self.front_half_que.len() < self.back_half_que.len() {
            return self.back_half_que.pop_front().unwrap();
        }

        return self.front_half_que.pop_back().unwrap();
    }

    fn pop_back(&mut self) -> i32 {
        if self.front_half_que.is_empty() && self.back_half_que.is_empty() {
            return -1;
        }
        if self.front_half_que.len() == self.back_half_que.len() {
            self.move_back();
        }
        return self.back_half_que.pop_back().unwrap();
    }
}

/*
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * let obj = FrontMiddleBackQueue::new();
 * obj.push_front(val);
 * obj.push_middle(val);
 * obj.push_back(val);
 * let ret_4: i32 = obj.pop_front();
 * let ret_5: i32 = obj.pop_middle();
 * let ret_6: i32 = obj.pop_back();
 */
// @lc code=end

/*
// @lcpr case=start
// ["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle","popBack", "popFront"][[], [1], [2], [3], [4], [], [], [], [], []]\n
// @lcpr case=end

 */
