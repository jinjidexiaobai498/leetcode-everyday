// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=2258 lang=cpp
 * @lcpr version=30108
 *
 * [2258] 逃离火灾
 *
 * https://leetcode.cn/problems/escape-the-spreading-fire/description/
 *
 * algorithms
 * Hard (43.81%)
 * Likes:    62
 * Dislikes: 0
 * Total Accepted:    4.8K
 * Total Submissions: 11.1K
 * Testcase Example:
 * '[[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]'
 *
 * 给你一个下标从 0 开始大小为 m x
 * n 的二维整数数组 grid ，它表示一个网格图。每个格子为下面 3 个值之一：
 *
 *
 * 0 表示草地。
 * 1 表示着火的格子。
 * 2 表示一座墙，你跟火都不能通过这个格子。
 *
 *
 * 一开始你在最左上角的格子 (0, 0) ，你想要到达最右下角的安全屋格子 (m - 1, n -
 * 1) 。每一分钟，你可以移动到 相邻 的草地格子。每次你移动
 * 之后 ，着火的格子会扩散到所有不是墙的 相邻 格子。
 *
 * 请你返回你在初始位置可以停留的 最多
 * 分钟数，且停留完这段时间后你还能安全到达安全屋。如果无法实现，请你返回
 * -1 。如果不管你在初始位置停留多久，你 总是 能到达安全屋，请你返回 10^9 。
 *
 * 注意，如果你到达安全屋后，火马上到了安全屋，这视为你能够安全到达安全屋。
 *
 * 如果两个格子有共同边，那么它们为 相邻 格子。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 * 输入：grid =
 * [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
 * 输出：3
 * 解释：上图展示了你在初始位置停留 3 分钟后的情形。
 * 你仍然可以安全到达安全屋。
 * 停留超过 3 分钟会让你无法安全到达安全屋。
 *
 * 示例 2：
 *
 *
 *
 * 输入：grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]
 * 输出：-1
 * 解释：上图展示了你马上开始朝安全屋移动的情形。
 * 火会蔓延到你可以移动的所有格子，所以无法安全到达安全屋。
 * 所以返回 -1 。
 *
 *
 * 示例 3：
 *
 *
 *
 * 输入：grid = [[0,0,0],[2,2,0],[1,2,0]]
 * 输出：1000000000
 * 解释：上图展示了初始网格图。
 * 注意，由于火被墙围了起来，所以无论如何你都能安全到达安全屋。
 * 所以返回 10^9 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == grid.length
 * n == grid[i].length
 * 2 <= m, n <= 300
 * 4 <= m * n <= 2 * 10^4
 * grid[i][j] 是 0 ，1 或者 2 。
 * grid[0][0] == grid[m - 1][n - 1] == 0
 *
 *
 */

// @lcpr-template-start
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
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    constexpr static const int DIRECTIONS[4][2] = {
        { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 }
    };
    struct Hasher {
        template <class T, class U>
        size_t operator()(const pair<T, U>& p) const
        {
            return (hash<T> {}(p.first) << 16) + hash<U> {}(p.second);
        }
    };

    int maximumMinutes(vector<vector<int>>& grid)
    {
        int ans = -1;
        const int x_len = grid.size();
        const int y_len = grid[0].size();

        auto check_index = [x_len, y_len](int x, int y) -> bool {
            if (x >= 0 && x < x_len && y >= 0 && y < y_len) {
                return true;
            }
            return false;
        };

        deque<deque<pair<int, int>>> start_point_list;
        deque<unordered_set<pair<int, int>, Hasher>> path_sets;

        auto next_minute = [grid, &start_point_list, &check_index, x_len, y_len,
                               &ans, &path_sets]() -> int {
            start_point_list.push_back({ { 0, 0 } });
            path_sets.push_back({ { 0, 0 } });
            int list_len = start_point_list.size();
            int count = 0;
            while (list_len > 0) {
                list_len -= 1;
                auto list = start_point_list.front();
                start_point_list.pop_front();

                auto path = path_sets.front();
                path_sets.pop_front();

                bool arrived_flag = false;
                int len = list.size();
                while (len > 0) {
                    len -= 1;
                    auto [x, y] = list.front();
                    list.pop_front();

                    if (grid[x][y] != 0) {
                        continue;
                    }

                    for (auto [dx, dy] : DIRECTIONS) {
                        int ix = x + dx;
                        int iy = y + dy;
                        if (check_index(ix, iy) && grid[ix][iy] == 0) {
                            if (ix == x_len - 1 && iy == y_len - 1) {
                                arrived_flag = true;
                                ans += 1;
                                count += 1;
                                break;
                            }
                            auto p1 = make_pair(ix, iy);
                            if (path.count(p1) == 0) {
                                path.insert(p1);
                                list.push_back(p1);
                            }
                        }
                    }
                    if (arrived_flag) {
                        break;
                    }
                }
                if (arrived_flag || list.empty()) {
                    continue;
                }

                start_point_list.push_back(std::move(list));
                path_sets.push_back(std::move(path));
            }

            return count;
        };

        deque<pair<int, int>> fire_point_list;
        for (int i = 0; i < x_len; i++) {
            for (int j = 0; j < y_len; j++) {
                if (grid[i][j] == 1) {
                    fire_point_list.push_back({ i, j });
                }
            }
        }
        auto fire_develop = [&fire_point_list, &check_index, &grid]() {
            int len = fire_point_list.size();
            while (len > 0) {
                len -= 1;
                auto [x, y] = fire_point_list.front();
                fire_point_list.pop_front();
                for (auto [dx, dy] : DIRECTIONS) {
                    int ix = dx + x;
                    int iy = dy + y;
                    if (check_index(ix, iy) && grid[ix][iy] == 0) {
                        grid[ix][iy] = 1;
                        fire_point_list.push_back({ ix, iy });
                    }
                }
            }
        };
        while (true) {
            int addon = next_minute();

            if (addon > 0 && fire_point_list.empty()) {
                return 1000000000;
            }

            if (start_point_list.empty()) {
                return ans;
            }

            fire_develop();
        }
        return ans;
    }
};
// @lc code=end

// @lcpr-div-debug-arg-start
// funName= maximumMinutes
// paramTypes= ["number[][]"]
// @lcpr-div-debug-arg-end

/*
// @lcpr case=start
// [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0,0],[0,1,2,0],[0,2,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0],[2,2,0],[1,2,0]]\n
// @lcpr case=end

 */
