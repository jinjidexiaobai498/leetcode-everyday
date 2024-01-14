
/*
 * @lc app=leetcode.cn id=面试题 01.09 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 01.09] 字符串轮转
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
    auto isFlipedString(const std::string& s1, const std::string& s2) -> bool
    {
        if (s1.size() != s2.size())
            return false;
        if (s1.size() == 0)
            return true;
        std::vector<int> self_index(s1.size(), -1);
        int              len     = (int)s1.size();
        int              current = -1;
        // kmp 算法, self_index , if word[i] ! = str[x], i = self_index[i-1]+1
        //  word[i] == word[x] , self_index[x] = i;
        // if word[self_index[i-1]+1] == word[i], self_index[i] =
        // self_index[i-1]+1;
        for (int i = 1; i < len; i++) {
            while (current != -1 && s1[current + 1] != s1[i]) {
                current = self_index[current];
            }
            if (s1[current + 1] == s1[i]) {
                current++;
            }
            self_index[i] = current;
        }
        std::string ls = s2 + s2;

        int index1 = -1;
        for (char l : ls) {
            while (index1 != -1 && l != s1[index1 + 1]) {
                index1 = self_index[index1];
            }
            if (l == s1[index1 + 1]) {
                index1 += 1;
                if (index1 == s1.size() - 1) {
                    return true;
                }
            }
        }
        return false;
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
// "waterbottle"\n"erbottlewat"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"aba"\n
// @lcpr case=end

 */

int main()
{
    std::string s1 = "abcabcefg";
    std::string s2 = "fgabcabce";
    Solution    sol;
    std::printf("%d", sol.isFlipedString(s1, s2));
    return 0;
}