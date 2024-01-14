// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=753 lang=cpp
 * @lcpr version=30113
 *
 * [753] 破解保险箱
 *
 * https://leetcode.cn/problems/cracking-the-safe/description/
 *
 * algorithms
 * Hard (74.74%)
 * Likes:    247
 * Dislikes: 0
 * Total Accepted:    17.3K
 * Total Submissions: 23.1K
 * Testcase Example:  '1\n2'
 *
 * 有一个需要密码才能打开的保险箱。密码是 n 位数, 密码的每一位都是范围 [0, k -
 * 1] 中的一个数字。
 *
 * 保险箱有一种特殊的密码校验方法，你可以随意输入密码序列，保险箱会自动记住
 * 最后 n 位输入 ，如果匹配，则能够打开保险箱。
 *
 *
 * 例如，正确的密码是 "345" ，并且你输入的是 "012345" ：
 *
 *
 * 输入 0 之后，最后 3 位输入是 "0" ，不正确。
 * 输入 1 之后，最后 3 位输入是 "01" ，不正确。
 * 输入 2 之后，最后 3 位输入是 "012" ，不正确。
 * 输入 3 之后，最后 3 位输入是 "123" ，不正确。
 * 输入 4 之后，最后 3 位输入是 "234" ，不正确。
 * 输入 5 之后，最后 3 位输入是 "345" ，正确，打开保险箱。
 *
 *
 *
 *
 * 在只知道密码位数 n 和范围边界 k 的前提下，请你找出并返回确保在输入的 某个时刻
 * 能够打开保险箱的任一 最短 密码序列 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：n = 1, k = 2
 * 输出："10"
 * 解释：密码只有 1 位，所以输入每一位就可以。"01" 也能够确保打开保险箱。
 *
 *
 * 示例 2：
 *
 * 输入：n = 2, k = 2
 * 输出："01100"
 * 解释：对于每种可能的密码：
 * - "00" 从第 4 位开始输入。
 * - "01" 从第 1 位开始输入。
 * - "10" 从第 3 位开始输入。
 * - "11" 从第 2 位开始输入。
 * 因此 "01100" 可以确保打开保险箱。"01100"、"10011" 和 "11001"
 * 也可以确保打开保险箱。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 4
 * 1 <= k <= 10
 * 1 <= k^n <= 4096
 *
 *
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
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
 private:
  unordered_set<int> seen;
  string ans;
  int highest;
  int k;

 public:
  void dfs(int node) {
    for (int x = 0; x < k; ++x) {
      int nei = node * 10 + x;
      if (!seen.count(nei)) {
        seen.insert(nei);
        dfs(nei % highest);
        ans += (x + '0');
      }
    }
  }

  string crackSafe(int n, int k) {
    highest = pow(10, n - 1);
    this->k = k;
    dfs(0);
    ans += string(n - 1, '0');
    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// 1\n2\n
// @lcpr case=end

// @lcpr case=start
// 2\n2\n
// @lcpr case=end

// @lcpr case=start
// 3\n6\n
// @lcpr case=end
 */
