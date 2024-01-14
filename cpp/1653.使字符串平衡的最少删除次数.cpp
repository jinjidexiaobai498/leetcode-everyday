
/*
 * @lc app=leetcode.cn id=1653 lang=cpp
 * @lcpr version=21801
 *
 * [1653] 使字符串平衡的最少删除次数
 */
using namespace std;
#include <windows.h>
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
class Solution
{
public:
    int minimumDeletions(string s)
    {
        const int len = s.size();
        int times_min = len;
        int as[len], bs[len];
        if (s[0] == 'a')
        {
            as[0] = 1;
            bs[0] = 0;
        }
        else
        {
            as[0] = 0;
            bs[0] = 1;
        }

        for (int i = 1; i < len; i++)
        {
            as[i] = as[i - 1];
            bs[i] = bs[i - 1];
            switch (s[i])
            {
            case 'a':
            {
                as[i]++;
                break;
            }
            case 'b':
            {
                bs[i]++;
                break;
            }
            default:
            {
            }
            }
        }

        times_min = min(times_min,as[len-1]);
        times_min = min(times_min,bs[len-1]);

        // current_d_a = last_d_a + (currnet_char == 'b')
        for (int i = 0; i < len; i++)
        {
            times_min =  min(times_min,as[len-1]-as[i]+bs[i]);
        }
        return times_min;
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
// "aababbab"\n
// @lcpr case=end

// @lcpr case=start
// "bbaaaaabb"\n
// @lcpr case=end

// @lcpr case=start
// "aaaaaabbbbbbbaaaaaaaaaa"\n
// @lcpr case=end


 */
