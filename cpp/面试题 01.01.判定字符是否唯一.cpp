/*
 * @lc app=leetcode.cn id=面试题 01.01 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 01.01] 判定字符是否唯一
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
    auto isUnique(const std::string& astr) -> bool
    {
        std::vector<bool> map(27, false);
        for (const auto& e : astr) {
            if (map[e - 'a']) {
                return false;
            }
            map[e - 'a'] = true;
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
// "leetcode"\n
// @lcpr case=end

// @lcpr case=start
// "abc"\n
// @lcpr case=end

 */
