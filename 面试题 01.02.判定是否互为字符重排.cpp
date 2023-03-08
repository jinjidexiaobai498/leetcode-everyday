/*
 * @lc app=leetcode.cn id=面试题 01.02 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 01.02] 判定是否互为字符重排
 */

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
// @lc code=start
class Solution {
  public:
    auto CheckPermutation(const std::string& s1, const std::string& s2) -> bool
    {
        if (s1.size() != s2.size())
            return false;
        std::vector<int> map(27, 0);
        for (const auto& e : s1) {
            map[e - 'a']++;
        }
        for (const auto& e : s2) {
            if (map[e - 'a'] == 0)
                return false;
            map[e - 'a']--;
        }
        return true;
    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName=
// paramTypes= []
// returnType=
// @lcpr-div-debug-arg-end

/*
// @lcpr case=start
// "abc"\n"bca"\n
// @lcpr case=end

// @lcpr case=start
// "abca"\n"bad"\n
// @lcpr case=end

 */
