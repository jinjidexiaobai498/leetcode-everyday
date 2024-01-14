/*
 * @lc app=leetcode.cn id=2707 lang=cpp
 * @lcpr version=30113
 *
 * [2707] 字符串中的额外字符
 *
 * https://leetcode.cn/problems/extra-characters-in-a-string/description/
 *
 * algorithms
 * Medium (45.03%)
 * Likes:    55
 * Dislikes: 0
 * Total Accepted:    7.5K
 * Total Submissions: 13.5K
 * Testcase Example:  '"leetscode"\n["leet","code","leetcode"]'
 *
 * 给你一个下标从
 * 0 开始的字符串 s 和一个单词字典 dictionary 。你需要将 s 分割成若干个
 * 互不重叠 的子字符串，每个子字符串都在
 * dictionary 中出现过。s 中可能会有一些 额外的字符 不在任何子字符串中。
 *
 * 请你采取最优策略分割 s ，使剩下的字符 最少 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：s = "leetscode", dictionary = ["leet","code","leetcode"]
 * 输出：1
 * 解释：将 s 分成两个子字符串：下标从 0 到 3 的 "leet" 和下标从 5 到 8 的
 * "code" 。只有 1 个字符没有使用（下标为 4），所以我们返回 1 。
 *
 *
 * 示例 2：
 *
 * 输入：s = "sayhelloworld", dictionary = ["hello","world"]
 * 输出：3
 * 解释：将 s 分成两个子字符串：下标从 3 到 7 的 "hello" 和下标从 8 到 12 的
 * "world" 。下标为 0 ，1 和 2 的字符没有使用，所以我们返回 3 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 50
 * 1 <= dictionary.length <= 50
 * 1 <= dictionary[i].length <= 50
 * dictionary[i] 和 s 只包含小写英文字母。
 * dictionary 中的单词互不相同。
 *
 *
 */

// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
  using StrIndex = int;
  using StrLength = size_t;
  using WordIndex = int;

private:
  unordered_map<StrIndex, vector<WordIndex>> imap;

public:
  int minExtraChar(string s, vector<string> &dictionary) {
    kmp_dict(dictionary, s);

    vector<StrIndex> dp(s.size(), (StrIndex)s.size());
    dp[0] = 1;
    for (auto wi : imap[0]) {
      StrIndex si = dictionary[wi].size();
      dp[si - 1] = 0;
    }
    for (int i = 1; i < s.size(); ++i) {
      dp[i] = min(dp[i], dp[i - 1] + 1);
      for (auto wi : imap[i]) {
        StrIndex si = i + dictionary[wi].size() - 1;
        dp[si] = min(dp[si], dp[i - 1]);
      }
    }

    return dp.back();
  }

  inline void kmp_dict(vector<string> &dict, string &s) {
    for (std::size_t i = 0; i < dict.size(); ++i) {
      auto w_found_s_index_list = kmp_list(s, dict[i]);
      for (auto index : w_found_s_index_list) {
        imap[index].push_back(i);
      }
    }

    // for (auto &[index, list] : imap) {
    //   cout << index << " : ";
    //   for (auto i : list) {
    //     cout << dict[i] << ", ";
    //   }
    //   cout << endl;
    // }
  }

  std::vector<StrIndex> kmp_init(std::string &w) {
    std::vector<StrIndex> word_indexd_map(w.size(), -1);
    StrIndex cmpare_start_index = 1;
    StrIndex compare_index = cmpare_start_index;
    StrIndex windex = 0;

    while (cmpare_start_index < w.size()) {
      if (compare_index < w.size() && w[windex] == w[compare_index]) {
        if (word_indexd_map[compare_index] == -1)
          word_indexd_map[compare_index] = windex;
        ++windex;
        ++compare_index;
      } else {
        cmpare_start_index += std::max((StrIndex)1, windex);
        compare_index = cmpare_start_index;
        windex = 0;
      }
    }
    return word_indexd_map;
  }

  StrIndex kmp_proto(std::string &s, std::string &w, StrIndex sindex,
                     std::vector<StrIndex> &word_indexd_map) {
    StrIndex windex = 0;
    while (windex < w.size() && sindex < s.size()) {

      if (s[sindex] == w[windex]) {
        ++sindex;
        ++windex;
        continue;
      }

      if (windex == 0) {
        sindex += 1;
      } else {
        windex = word_indexd_map[windex - 1] + 1;
      }
    }

    if (windex != w.size()) {
      return -1;
    }

    return sindex - windex;
  }

  StrIndex kmp(std::string &s, std::string &w, StrIndex sindex = 0) {
    auto word_indexd_map = kmp_init(w);
    return kmp_proto(s, w, sindex, word_indexd_map);
  }

  std::vector<StrIndex> kmp_list(std::string &s, std::string &w) {
    auto word_indexed_map = kmp_init(w);
    const StrIndex step =
        std::max((StrIndex)1, word_indexed_map[w.size() - 1] + 1);
    std::vector<StrIndex> str_found_index_list;
    StrIndex left = 0;
    while (left < s.size()) {
      auto found_index = kmp_proto(s, w, left, word_indexed_map);
      if (found_index == -1)
        break;
      left = found_index + step;
      str_found_index_list.push_back(found_index);
    }
    return str_found_index_list;
  }
};

// @lc code=end

/*
// @lcpr case=start
// "leetscode"\n["leet","code","leetcode"]\n
// @lcpr case=end

// @lcpr case=start
// "sayhelloworld"\n["hello","world"]\n
// @lcpr case=end

*/

int main() {
  Solution sol;
  string s = "abslxdlxaaaalxdxlaaaalxdldlaaaalxdxlaaaalxdld,"
             "asaaaalxdxlaaaalxdlddfaqwerpkasodflxdlxl,"
             "asdfjasodfjasdojcxkljasldflxdlxl";
  vector<string> dict = {"aaaalxdxlaaaalxdld", "lxd", "aaaa", "qwer"};
  sol.kmp_dict(dict, s);
}
