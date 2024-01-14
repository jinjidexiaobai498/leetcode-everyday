/*
 * @lc app=leetcode.cn id=2258 lang=rust
 * @lcpr version=30106
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
 * Testcase Example:  '[[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]'
 *
 * 给你一个下标从 0 开始大小为 m x n 的二维整数数组 grid ，它表示一个网格图。每个格子为下面 3 个值之一：
 *
 *
 * 0 表示草地。
 * 1 表示着火的格子。
 * 2 表示一座墙，你跟火都不能通过这个格子。
 *
 *
 * 一开始你在最左上角的格子 (0, 0) ，你想要到达最右下角的安全屋格子 (m - 1, n - 1) 。每一分钟，你可以移动到 相邻
 * 的草地格子。每次你移动 之后 ，着火的格子会扩散到所有不是墙的 相邻 格子。
 *
 * 请你返回你在初始位置可以停留的 最多 分钟数，且停留完这段时间后你还能安全到达安全屋。如果无法实现，请你返回 -1 。如果不管你在初始位置停留多久，你
 * 总是 能到达安全屋，请你返回 10^9 。
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

// use crate::print::aprint;
// use log::debug;
//use log4rs;

// @lcpr-template-start
pub struct Solution();
// @lcpr-template-end
// @lc code=start
use std::collections::{HashSet, VecDeque};

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash, Debug)]
struct Point(i32, i32);

//TODO
impl Solution {
    pub fn maximum_minutes(grid: Vec<Vec<i32>>) -> i32 {
        //log4rs::init_file("log4rs.yaml", Default::default()).unwrap();
        //debug!("new debug session");

        let directions = [[0, 1], [1, 0], [-1, 0], [0, -1]];
        let mut grid = grid;
        let mut ans = -1i32;
        let x_len = grid.len() as i32;
        let y_len = grid[0].len() as i32;
        let check_bound = |x: i32, y: i32| -> bool {
            if x >= 0 && x < x_len && y >= 0 && y < y_len {
                return true;
            }
            return false;
        };

        let mut start_points_list =
            VecDeque::<VecDeque<Point>>::with_capacity((x_len + y_len) as usize);
        let mut paths_list = VecDeque::<HashSet<Point>>::with_capacity((x_len + y_len) as usize);

        // //DEBUG

        // debug!("{}\n", aprint(&grid));
        //let mut time = 100;

        let mut next_minute =
            |start_points_list: &mut VecDeque<VecDeque<Point>>, grid: &mut Vec<Vec<i32>>| -> i32 {
                let mut count = 0;
                start_points_list.push_back(VecDeque::<Point>::from([Point(0, 0)]));
                paths_list.push_back(HashSet::<Point>::from([Point(0, 0)]));

                let mut list_len = start_points_list.len();

                while list_len > 0 {
                    list_len -= 1;
                    let mut list = start_points_list.pop_front().unwrap();
                    let mut path = paths_list.pop_front().unwrap();

                    let mut len = list.len();
                    let mut arrived_flag = false;
                    while len > 0 {
                        len -= 1;
                        let point = list.pop_front().unwrap();
                        if grid[point.0 as usize][point.1 as usize] != 0 {
                            continue;
                        }

                        for direct in directions.iter() {
                            let x = direct[0] + point.0;
                            let y = direct[1] + point.1;
                            if check_bound(x, y) && grid[x as usize][y as usize] == 0 {
                                if x == (x_len - 1) && y == (y_len - 1) {
                                    ans += 1;
                                    count += 1;
                                    arrived_flag = true;
                                    // debug!("arrived");
                                    break;
                                }
                                let np = Point(x, y);
                                if !path.contains(&np) {
                                    list.push_back(Point(x, y));
                                    path.insert(Point(x, y));
                                }
                            }
                        }
                        if arrived_flag {
                            break;
                        }
                    }

                    if arrived_flag || list.is_empty() {
                        continue;
                    }

                    // DEBUG_START
                    // time += 1;
                    // let mut _g = grid.clone();
                    // for Point(x, y) in path.iter() {
                    //     _g[*x as usize][*y as usize] = time;
                    // }
                    // for Point(x, y) in list.iter() {
                    //     _g[*x as usize][*y as usize] = -1;
                    // }
                    // debug!("{}", aprint(&_g));
                    //DEBUG_END

                    start_points_list.push_back(list);
                    paths_list.push_back(path);
                }

                return count;
            };

        let mut fire_place = VecDeque::<Point>::with_capacity((x_len * y_len) as usize);
        for (i, r) in grid.iter().enumerate() {
            for (j, c) in r.iter().enumerate() {
                if *c == 1 {
                    fire_place.push_back(Point {
                        0: i as i32,
                        1: j as i32,
                    });
                }
            }
        }

        let fire_develop = |grid: &mut Vec<Vec<i32>>, fire_place: &mut VecDeque<Point>| {
            let mut size = fire_place.len();
            let mut list = VecDeque::<Point>::new();
            while size > 0 {
                size -= 1;
                let point = fire_place.pop_front().unwrap();
                for direct in directions.iter() {
                    let x = direct[0] + point.0;
                    let y = direct[1] + point.1;
                    if check_bound(x, y) && grid[x as usize][y as usize] == 0 {
                        grid[x as usize][y as usize] = 1;
                        fire_place.push_back(Point(x, y));
                        list.push_back(Point(x, y));
                    }
                }
            }
            // //DEBUG
            // let mut _g = grid.clone();
            // for Point(x, y) in list {
            //     let x = x as usize;
            //     let y = y as usize;
            //     _g[x][y] = 111;
            // }
            // debug!("{}", aprint(&_g));
        };

        let mut limit = x_len * y_len;
        loop {
            let add_count = next_minute(&mut start_points_list, &mut grid);

            if fire_place.is_empty() {
                if add_count > 0 {
                    ans = 1_000_000_000;
                    break;
                } else if limit <= 0 {
                    ans = -1;
                    break;
                } else {
                    limit -= 1;
                }
            }

            if start_points_list.is_empty() {
                break;
            }

            fire_develop(&mut grid, &mut fire_place);
        }

        return ans;
    }
}
// @lc code=end

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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        let grid = Vec::<Vec<i32>>::from(vec![
            vec![0, 2, 0, 0, 0, 0, 0],
            vec![0, 0, 0, 2, 2, 1, 0],
            vec![0, 2, 0, 0, 1, 2, 0],
            vec![0, 0, 2, 2, 2, 0, 2],
            vec![0, 0, 0, 0, 0, 0, 0],
        ]);
        let ans = Solution::maximum_minutes(grid);
        assert_eq!(ans, 3);
    }

    #[test]
    fn test2() {
        let grid = vec![vec![0, 0, 0, 0], vec![0, 1, 2, 0], vec![0, 2, 0, 0]];
        let ans = Solution::maximum_minutes(grid);
        assert_eq!(ans, -1);
    }

    #[test]
    fn test3() {
        let grid = vec![vec![0, 0, 0], vec![2, 2, 0], vec![1, 2, 0]];
        let ans = Solution::maximum_minutes(grid);
        assert_eq!(ans, 1_000_000_000);
    }
    #[test]
    fn test_time_limit() {
        let grid = vec![
            vec![
                0, 0, 2, 2, 1, 1, 0, 2, 1, 1, 2, 2, 0, 2, 2, 1, 2, 0, 1, 2, 2, 0, 1, 2, 2, 1, 2, 2,
            ],
            vec![
                2, 2, 2, 1, 1, 2, 2, 1, 2, 0, 1, 1, 1, 2, 2, 1, 1, 0, 2, 2, 2, 0, 1, 0, 1, 2, 2, 2,
            ],
            vec![
                0, 0, 1, 1, 0, 1, 2, 0, 1, 1, 1, 1, 0, 2, 0, 2, 0, 2, 1, 1, 0, 2, 1, 2, 2, 2, 1, 2,
            ],
            vec![
                2, 2, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0, 1, 2, 1, 0, 1, 1, 1, 2, 0, 2, 0,
            ],
            vec![
                2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 1, 1, 1, 1, 2, 0, 2, 1, 1, 2, 0, 2, 0, 2, 0,
            ],
            vec![
                0, 1, 0, 1, 2, 2, 2, 0, 2, 0, 2, 2, 1, 2, 0, 0, 1, 0, 2, 0, 2, 0, 1, 2, 2, 0, 2, 0,
            ],
            vec![
                1, 0, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 1, 0, 2, 2, 0, 2, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0,
            ],
            vec![
                0, 1, 2, 0, 1, 0, 1, 0, 2, 1, 2, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 2, 0, 1, 0, 1, 0, 2,
            ],
            vec![
                2, 1, 1, 0, 1, 1, 2, 2, 1, 2, 2, 1, 0, 1, 0, 0, 0, 2, 1, 0, 2, 2, 1, 2, 1, 2, 0, 1,
            ],
            vec![
                1, 1, 2, 0, 2, 2, 1, 2, 0, 2, 1, 1, 0, 0, 0, 2, 2, 2, 2, 1, 2, 2, 0, 2, 1, 1, 2, 0,
            ],
            vec![
                2, 1, 2, 2, 0, 0, 1, 0, 1, 2, 1, 0, 1, 0, 2, 0, 0, 1, 1, 0, 2, 0, 2, 0, 1, 2, 2, 0,
            ],
            vec![
                1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 2, 1, 2, 1, 1, 0, 1, 0, 0, 2, 1, 2, 1, 0, 2,
            ],
            vec![
                2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 2, 1, 2, 0, 2, 2, 2, 1, 0, 2, 1, 0, 1, 2, 1, 0, 1, 1,
            ],
            vec![
                0, 2, 2, 1, 0, 2, 1, 0, 1, 2, 2, 1, 2, 2, 1, 2, 0, 1, 2, 2, 0, 2, 1, 0, 2, 1, 0, 0,
            ],
            vec![
                0, 2, 2, 2, 1, 2, 1, 0, 0, 2, 2, 0, 1, 0, 2, 1, 0, 0, 2, 1, 1, 1, 2, 1, 2, 1, 0, 1,
            ],
            vec![
                2, 2, 2, 1, 1, 1, 1, 0, 2, 2, 2, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 2, 1, 2, 1, 2, 2,
            ],
            vec![
                2, 1, 2, 1, 1, 1, 0, 2, 1, 0, 1, 1, 2, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 0, 2, 0, 0,
            ],
        ];
        let ans = Solution::maximum_minutes(grid);
        assert_eq!(ans, -1);
    }
    #[test]
    fn test6_wrong_52() {
        let grid = vec![
            vec![
                0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0,
            ],
            vec![
                0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2,
            ],
            vec![
                0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0,
            ],
            vec![
                2, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
            ],
            vec![
                0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 0,
            ],
            vec![
                2, 2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 2,
            ],
            vec![
                0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 0,
            ],
        ];
        let ans = Solution::maximum_minutes(grid);
        assert_eq!(ans, 1_000_000_000);
    }
}
