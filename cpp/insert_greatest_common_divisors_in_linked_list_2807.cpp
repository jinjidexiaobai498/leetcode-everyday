/*
 * @lc app=leetcode.cn id=2807 lang=cpp
 * @lcpr version=30112
 *
 * [2807] 在链表中插入最大公约数
 *
 * https://leetcode.cn/problems/insert-greatest-common-divisors-in-linked-list/description/
 *
 * algorithms
 * Medium (87.65%)
 * Likes:    23
 * Dislikes: 0
 * Total Accepted:    9.1K
 * Total Submissions: 10.1K
 * Testcase Example:  '[18,6,10,3]'
 *
 * 给你一个链表的头 head ，每个结点包含一个整数值。
 *
 * 在相邻结点之间，请你插入一个新的结点，结点值为这两个相邻结点值的
 * 最大公约数 。
 *
 * 请你返回插入之后的链表。
 *
 * 两个数的 最大公约数 是可以被两个数字整除的最大正整数。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 * 输入：head = [18,6,10,3]
 * 输出：[18,6,6,2,10,1,3]
 * 解释：第一幅图是一开始的链表，第二幅图是插入新结点后的图（蓝色结点为新插入结点）。
 * - 18 和 6 的最大公约数为 6 ，插入第一和第二个结点之间。
 * - 6 和 10 的最大公约数为 2 ，插入第二和第三个结点之间。
 * - 10 和 3 的最大公约数为 1 ，插入第三和第四个结点之间。
 * 所有相邻结点之间都插入完毕，返回链表。
 *
 *
 * 示例 2：
 *
 *
 *
 * 输入：head = [7]
 * 输出：[7]
 * 解释：第一幅图是一开始的链表，第二幅图是插入新结点后的图（蓝色结点为新插入结点）。
 * 没有相邻结点，所以返回初始链表。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 链表中结点数目在 [1, 5000] 之间。
 * 1 <= Node.val <= 1000
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

#include "./header.cpp"
using namespace std;
// @lcpr-template-end
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
  ListNode *insertGreatestCommonDivisors(ListNode *head) {
    if (head == nullptr)
      return nullptr;

    auto curp = head;
    auto nextp = head->next;
    while (nextp != nullptr) {
      curp->next =  new ListNode(get_max_divisor(curp->val, nextp->val), nextp);
      curp = nextp;
      nextp = nextp->next;
    }

    return head;
  }
  int get_max_divisor(int a, int b) {
    int c = a % b;
    while (c) {
      a = b;
      b = c;
      c = a % b;
    }
    return b;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [18,6,10,3]\n
// @lcpr case=end

// @lcpr case=start
// [7]\n
// @lcpr case=end

 */
