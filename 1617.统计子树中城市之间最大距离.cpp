/*
 * @lc app=leetcode.cn id=1617 lang=cpp
 * @lcpr version=21801
 *
 * [1617] 统计子树中城市之间最大距离
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
    auto countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges)
        -> vector<int>
    {
        vector<vector<int>> point_access_map(edges.size() + 1, vector<int>());

        //init point_access_map
        for (auto edge : edges) {
            point_access_map[edge[0]].emplace_back(edge[1]);
            point_access_map[edge[1]].emplace_back(edge[0]);
        }

        int start_point = 1;
        while(start_point<=n&&point_access_map[start_point].size()!=1){
            start_point++;
        }


        vector<int>         ans;
        ans.emplace_back(n - 1);
        vector<vector<int>> paths;
        unordered_map<int, vector<int>> map;
        for (int i = 1; i < n; i++) {
            
        }
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
// 4\n[[1,2],[2,3],[2,4]]\n
// @lcpr case=end

// @lcpr case=start
// 2\n[[1,2]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,2],[2,3]]\n
// @lcpr case=end

 */
