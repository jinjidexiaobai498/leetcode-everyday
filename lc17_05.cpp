/*
 * @lc app=leetcode.cn id=面试题 17.05 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 17.05]  字母与数字
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
using namespace std;
// @lc code=start
class Solution {
  public:
    auto isDigit(char c) -> bool
    {
        if (c >= '0' && c <= '9')
            return true;
        else
            return false;
    }
    auto findLongestSubarray(vector<string>& array) -> vector<string>
    {
        vector<int> dp_digit(array.size() + 1, 0);
        vector<int> dp_letter(array.size() + 1, 0);
        int         max_len     = 0;
        int         start_index = 0;
        int         end_index   = 0;

        for (int i = 1; i < array.size() + 1; i++) {
            dp_digit[i] = dp_digit[i - 1];
            for (auto c : array[i - 1]) {
                if (isDigit(c)) {
                    dp_digit[i] += 1;
                }
                else {
                    dp_letter[i] += 1;
                }
                break;
            }
        }
        int  len = (int)array.size();
        bool f   = (len & 1) == 1;
        for (int i = 1; i < dp_digit.size(); i++) {
            if (i + max_len + 1 < dp_digit.size()) {
                int min_index = max_len + i + 1;
                int max_index = ((i & 1) == 1) == f ? len - 1 : len;
                for (int j = max_index; j >= min_index; j -= 2) {
                    if (dp_digit[j] - dp_digit[i - 1] == ((j - i + 1) / 2)) {
                        start_index = i;
                        end_index   = j;
                        max_len     = j - i + 1;
                        break;
                    }
                }
            }
        }

        vector<string> ans;
        if (start_index == 0)
            return ans;
        for (int i = start_index - 1; i < end_index; i++) {
            ans.emplace_back(array[i]);
        }

        return ans;
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
//
// @lcpr case=end

// @lcpr case=start
//
// @lcpr case=end

 */

//["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]

auto main() -> int
{
    vector<string> input = {"A", "1", "B", "C", "D", "2", "3", "4", "E", "5",
                            "F", "G", "6", "7", "H", "I", "J", "K", "L", "M"};
    Solution       sol;
    vector<string> ans = sol.findLongestSubarray(input);

    for (const auto& c : ans) {
        cout << c << " ";
    }
    return 0;
}