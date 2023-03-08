// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=797 lang=cpp
 * @lcpr version=21801
 *
 * [797] 所有可能的路径
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
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lc code=start
struct MAP_PATH
{
    int  map_postion;
    int  start_index;
    bool un_reached;
};
class Solution {
  private:
    std::unordered_map<int, vector<vector<int>>> reached_nodes;
    std::unordered_set<int>                      unreached_nodes;

  public:
    auto allPathsSourceTarget(std::vector<std::vector<int>>& graph)
        -> std::vector<std::vector<int>>
    {
        int target = (int)graph.size() - 1;
        vector<int> path;
        path.emplace_back(target);
        reached_nodes[target].emplace_back(path);
        df(0, graph);
        return reached_nodes[0];
    }

    auto df(int node, vector<vector<int>>& g) -> bool
    {
        if (unreached_nodes.count(node) != 0) {
            return false;
        }
        if (reached_nodes.count(node) != 0)
            return true;

        bool f = false;
        for (auto n : g[node]) {
            if (df(n, g)) {
                f = true;
                for (const auto& ps : reached_nodes[n]) {
                    vector<int> p;
                    p.emplace_back(node);
                    for (auto e : ps) {
                        p.emplace_back(e);
                    }
                    reached_nodes[node].emplace_back(p);
                }
            }
        }
        if (!f) {
            unreached_nodes.insert(node);
            return false;
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
// [[1,2],[3],[3],[]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,3,1],[3,2,4],[3],[4],[]]\n
// @lcpr case=end

 */
