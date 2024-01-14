/*
 * @lc app=leetcode.cn id=2645 lang=cpp
 * @lcpr version=30113
 *
 * [2645] 构造有效字符串的最少插入数
 *
 * https://leetcode.cn/problems/minimum-additions-to-make-valid-string/description/
 *
 * algorithms
 * Medium (56.60%)
 * Likes:    53
 * Dislikes: 0
 * Total Accepted:    16K
 * Total Submissions: 24.9K
 * Testcase Example:  '"b"'
 *
 * 给你一个字符串 word ，你可以向其中任何位置插入 "a"、"b" 或 "c" 任意次，返回使
 * word 有效 需要插入的最少字母数。
 *
 * 如果字符串可以由 "abc" 串联多次得到，则认为该字符串 有效 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：word = "b"
 * 输出：2
 * 解释：在 "b" 之前插入 "a" ，在 "b" 之后插入 "c" 可以得到有效字符串 "abc" 。
 *
 *
 * 示例 2：
 *
 * 输入：word = "aaa"
 * 输出：6
 * 解释：在每个 "a" 之后依次插入 "b" 和 "c" 可以得到有效字符串 "abcabcabc" 。
 *
 *
 * 示例 3：
 *
 * 输入：word = "abc"
 * 输出：0
 * 解释：word 已经是有效字符串，不需要进行修改。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= word.length <= 50
 * word 仅由字母 "a"、"b" 和 "c" 组成。
 *
 *
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cwchar>
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
  int addMinimum(string word) {
    int res = 1;
    for (int i = 1; i < word.size(); ++i) {
      if (word[i] <= word[i - 1]) ++res;
    }
    return res * 3 - word.size();
  }
};
// @lc code=end

/*
// @lcpr case=start
// "b"\n
// @lcpr case=end

// @lcpr case=start
// "aaa"\n
// @lcpr case=end

// @lcpr case=start
// "abc"\n
// @lcpr case=end

 */
