/*
 * @lc app=leetcode.cn id=面试题 01.03 lang=cpp
 * @lcpr version=21801
 *
 * [面试题 01.03] URL化
 */

#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
  public:
    auto replaceSpaces(string S, int length) -> string
    {
        string s;
        for(int i=0;i<length;i++){
            if(S[i]==' '){
                s+="%20";
            }else{
                s+=S[i];
            }
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
