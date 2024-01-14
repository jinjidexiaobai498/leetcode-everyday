/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * @lcpr version=30113
 *
 * [438] 找到字符串中所有字母异位词
 *
 * https://leetcode.cn/problems/find-all-anagrams-in-a-string/description/
 *
 * algorithms
 * Medium (54.21%)
 * Likes:    1357
 * Dislikes: 0
 * Total Accepted:    359.8K
 * Total Submissions: 665.7K
 * Testcase Example:  '"cbaebabacd"\n"abc"'
 *
 * 给定两个字符串 s 和
 * p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
 *
 * 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
 *
 *
 *
 * 示例 1:
 *
 * 输入: s = "cbaebabacd", p = "abc"
 * 输出: [0,6]
 * 解释:
 * 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
 * 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
 *
 *
 * 示例 2:
 *
 * 输入: s = "abab", p = "ab"
 * 输出: [0,1,2]
 * 解释:
 * 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
 * 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
 * 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1 <= s.length, p.length <= 3 * 10^4
 * s 和 p 仅包含小写字母
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
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> ans;
    if (p.size() > s.size()) {
      return ans;
    }

    vector<int> list;
    int word[26] = {};
    int sw[26] = {};

    int len = p.size();
    int index = 0;
    for (int i = 0; i < len; i++) {
      index = s[i] - 'a';
      sw[index] += 1;

      index = p[i] - 'a';
      list.push_back(index);
      word[index] += 1;
    }

    auto judge = [&word, &sw, &list]() -> bool {
      for (auto i : list) {
        if (sw[i] != word[i]) {
          return false;
        }
      }
      return true;
    };

    bool last = judge();
    if (last) ans.push_back(0);

    int l = 0, r = len;
    while (r < s.size()) {
      ++sw[s[r] - 'a'];
      --sw[s[l] - 'a'];

      last = last ? (s[r] == s[l]) : judge();
      if (last) ans.push_back(l + 1);

      r += 1;
      l += 1;
    }

    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// "cbaebabacd"\n"abc"\n
// @lcpr case=end

// @lcpr case=start
// "abab"\n"ab"\n
// @lcpr case=end

*/
