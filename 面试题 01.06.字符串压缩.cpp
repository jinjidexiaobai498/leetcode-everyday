/*
 * @lc app=leetcode.cn id=面试题 01.06 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 01.06] 字符串压缩
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
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
  public:
    auto compressString(string S) -> string
    {
        int    i   = 0;
        int    len = (int)S.size();
        string s   = "";

        while (i < len) {
            int tl = 1;
            while (i + 1 < len && S[i] == S[i + 1]) {
                tl++;
                i++;
            }
            s+=S[i];
            s+=to_string(tl);
            i++;
        }
        if(s.size()>=len){
            return S;
        }
        return s;
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
