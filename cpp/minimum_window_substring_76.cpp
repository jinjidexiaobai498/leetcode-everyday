/*
 * @lc app=leetcode.cn id=76 lang=cpp @lcpr version=30113
 * [76] 最小覆盖子串
 * https://leetcode.cn/problems/minimum-window-substring/description/ algorithms
 * * Hard (45.40%) * Likes:    2792 Dislikes: 0 Total Accepted:    500.6K Total
 * Submissions: 1.1M Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s
 * 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
 *
 *
 *
 * 注意：
 *
 *
 * 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
 * 如果 s 中存在这样的子串，我们保证它是唯一的答案。
 *
 *
 *
 *
 * 示例 1：
 *
 * 输入：s = "ADOBECODEBANC", t = "ABC"
 * 输出："BANC"
 * 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
 *
 *
 * 示例 2：
 *
 * 输入：s = "a", t = "a"
 * 输出："a"
 * 解释：整个字符串 s 是最小覆盖子串。
 *
 *
 * 示例 3:
 *
 * 输入: s = "a", t = "aa"
 * 输出: ""
 * 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
 * 因此没有符合条件的子字符串，返回空字符串。
 *
 *
 *
 * 提示：
 *
 *
 * ^m == s.length
 * ^n == t.length
 * 1 <= m, n <= 10^5
 * s 和 t 由英文字母组成
 *
 *
 *
 * 进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start

class Solution {
 public:
  string minWindow(string s, string t) {
    int tcnt[123]{};
    int scnt[123]{};
    for (auto c : t) ++tcnt[c];
    int count = 0;
    int l = 0, r = 0, min_len = s.size() + 1, ans_l = 0;
    while (r < s.size() && l < s.size()) {
      char cr = s[r];
      while (r < s.size() && count < t.size()) {
        cr = s[r++];
        if (!tcnt[cr]) continue;
        count += (scnt[cr] < tcnt[cr]);
        ++scnt[cr];
      }
      char cl = s[l];
      while (l < r && count == t.size()) {
        cl = s[l++];
        if (!tcnt[cl]) continue;
        count -= (scnt[cl] == tcnt[cl]);
        --scnt[cl];
      }
      if (r - l + 1 < min_len) min_len = r - l + 1, ans_l = l - 1;
    }
    if (min_len == s.size() + 1) return "";
    return s.substr(ans_l, min_len);
  }
};
// @lc code=end

/*
// @lcpr case=start
// "ADOBECODEBANC"\n"ABC"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"a"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"aa"\n
// @lcpr case=end

 */
int main() {
  Solution sol;
  cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
  cout << sol.minWindow("a", "a") << endl;
  cout << sol.minWindow("a", "aa") << endl;
  cout << sol.minWindow("a", "b") << endl;
  cout << sol.minWindow("aa", "aa") << endl;
  cout << sol.minWindow("ab", "a") << endl;
}
