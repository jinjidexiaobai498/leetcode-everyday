// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=828 lang=cpp
 * @lcpr version=30110
 *
 * [828] 统计子串中的唯一字符
 *
 * https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/description/
 *
 * algorithms
 * Hard (65.61%)
 * Likes:    363
 * Dislikes: 0
 * Total Accepted:    36.4K
 * Total Submissions: 53.9K
 * Testcase Example:  '"ABC"'
 *
 * 我们定义了一个函数 countUniqueChars(s) 来统计字符串 s
 * 中的唯一字符，并返回唯一字符的个数。
 *
 * 例如：s = "LEETCODE" ，则其中 "L", "T","C","O","D"
 * 都是唯一字符，因为它们只出现一次，所以 countUniqueChars(s) = 5 。
 *
 * 本题将会给你一个字符串 s ，我们需要返回 countUniqueChars(t) 的总和，其中 t 是
 * s 的子字符串。输入用例保证返回值为 32 位整数。
 *
 * 注意，某些子字符串可能是重复的，但你统计时也必须算上这些重复的子字符串（也就是说，你必须统计
 * s 的所有子字符串中的唯一字符）。
 *
 *
 *
 * 示例 1：
 *
 * 输入: s = "ABC"
 * 输出: 10
 * 解释: 所有可能的子串为："A","B","C","AB","BC" 和 "ABC"。
 * ⁠    其中，每一个子串都由独特字符构成。
 * ⁠    所以其长度总和为：1 + 1 + 1 + 2 + 2 + 3 = 10
 *
 *
 * 示例 2：
 *
 * 输入: s = "ABA"
 * 输出: 8
 * 解释: 除了 countUniqueChars("ABA") = 1 之外，其余与示例 1 相同。
 *
 *
 * 示例 3：
 *
 * 输入：s = "LEETCODE"
 * 输出：92
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^5
 * s 只包含大写英文字符
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
#include <map>
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
  int uniqueLetterString(string s) {
    unordered_map<char, int> last_first_map;
    unordered_map<char, int> last_second_map;
    int dpx = 1;
    last_first_map.insert({s[0], 0});
    int ans = 1;

    for (int i = 1; i < s.size(); i++) {
      dpx += i + 1;
      if (last_second_map.count(s[i])) {
        dpx += last_second_map.at(s[i]) + 1;
      }

      if (last_first_map.count(s[i])) {
        dpx -= (last_first_map.at(s[i]) + 1) * 2;
        last_second_map.insert_or_assign(s[i], last_first_map.at(s[i]));
      }

      last_first_map.insert_or_assign(s[i], i);
      ans += dpx;
    }
    return ans;
  }
};

// @lc code=end

/*
// @lcpr case=start
// "ABC"\n
// @lcpr case=end

// @lcpr case=start
// "ABA"\n
// @lcpr case=end

// @lcpr case=start
// "LEETCODE"\n
// @lcpr case=end

 */
