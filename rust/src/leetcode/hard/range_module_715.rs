/*
* @lc app=leetcode.cn id=715 lang=rust
* @lcpr version=30108
*
* [715] Range 模块
*
* https://leetcode.cn/problems/range-module/description/
*
* algorithms
* Hard (52.54%)
* Likes:    252
* Dislikes: 0
* Total Accepted:    24.7K
* Total Submissions: 45.1K
* Testcase Example:  '["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]\n' +
 '[[],[10,20],[14,16],[10,14],[13,15],[16,17]]'
*
* Range模块是跟踪数字范围的模块。设计一个数据结构来跟踪表示为 半开区间 的范围并查询它们。
*
* 半开区间 [left, right) 表示所有 left <= x < right 的实数 x 。
*
* 实现 RangeModule 类:
*
*
* RangeModule() 初始化数据结构的对象。
* void addRange(int left, int right) 添加 半开区间 [left,
* right)，跟踪该区间中的每个实数。添加与当前跟踪的数字部分重叠的区间时，应当添加在区间 [left, right)
* 中尚未跟踪的任何数字到该区间中。
* boolean queryRange(int left, int right) 只有在当前正在跟踪区间 [left, right)
* 中的每一个实数时，才返回 true ，否则返回 false 。
* void removeRange(int left, int right) 停止跟踪 半开区间 [left, right)
* 中当前正在跟踪的每个实数。
*
*
*
*
* 示例 1：
*
* 输入
* ["RangeModule", "addRange", "removeRange", "queryRange", "queryRange",
* "queryRange"]
* [[], [10, 20], [14, 16], [10, 14], [13, 15], [16, 17]]
* 输出
* [null, null, null, true, false, true]
*
* 解释
* RangeModule rangeModule = new RangeModule();
* rangeModule.addRange(10, 20);
* rangeModule.removeRange(14, 16);
* rangeModule.queryRange(10, 14); 返回 true （区间 [10, 14) 中的每个数都正在被跟踪）
* rangeModule.queryRange(13, 15); 返回 false（未跟踪区间 [13, 15) 中像 14, 14.03, 14.17
* 这样的数字）
* rangeModule.queryRange(16, 17); 返回 true （尽管执行了删除操作，区间 [16, 17) 中的数字 16
* 仍然会被跟踪）
*
*
*
*
* 提示：
*
*
* 1 <= left < right <= 10^9
* 在单个测试用例中，对 addRange 、  queryRange 和 removeRange 的调用总数不超过 10^4 次
*
*
*/

// @lcpr-template-start
pub struct Solution;

// @lcpr-template-end

// @lc code=start

use std::cmp::min;
use std::{cmp::Ordering, collections::BTreeSet};
#[derive(Clone, Copy, Debug)]
struct RangeUnit {
    left: i32,
    right: i32,
}
// impl PartialOrd for RangeUnit {
//     fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
//         match self.left.partial_cmp(&other.left) {
//             Some(core::cmp::Ordering::Equal) => {}
//             ord => return ord,
//         }
//         self.right.partial_cmp(&other.right)
//     }
// }

struct RangeModule {
    data_set: BTreeSet<RangeUnit>,
}
impl PartialEq for RangeUnit {
    fn eq(&self, other: &Self) -> bool {
        self.right == other.right
    }
}

impl Eq for RangeUnit {}

impl PartialOrd for RangeUnit {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(&other))
    }
}

impl Ord for RangeUnit {
    fn cmp(&self, other: &Self) -> Ordering {
        self.right.cmp(&other.right) //将排序委托给其成员path。
    }

    fn max(self, other: Self) -> Self
    where
        Self: Sized,
    {
        std::cmp::max_by(self, other, Ord::cmp)
    }

    fn min(self, other: Self) -> Self
    where
        Self: Sized,
    {
        std::cmp::min_by(self, other, Ord::cmp)
    }
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl RangeModule {
    pub fn new() -> Self {
        RangeModule {
            data_set: BTreeSet::<RangeUnit>::new(),
        }
    }

    pub fn add_range(&mut self, left: i32, right: i32) {
        let mut dv = Vec::new();
        let mut av = RangeUnit { left, right };
        let mut flag = false;

        for i in self.data_set.range(
            &RangeUnit {
                left: 0,
                right: left + 1,
            }..,
        ) {
            if i.left > right {
                break;
            }
            if i.left == right {
                av.right = i.right;
                dv.push(i.clone());
                break;
            }
            dv.push(i.clone());
            if i.left <= left {
                av.left = i.left;
                if i.right >= right {
                    flag = true;
                    break;
                }
            }
            if i.right > right {
                av.right = i.right;
                break;
            }
        }
        if flag {
            return;
        }

        if let Some(u) = self.data_set.get(&RangeUnit {
            left: 0,
            right: av.left,
        }) {
            av.left = u.left;
            dv.push(u.clone());
        }

        for i in dv {
            self.data_set.remove(&i);
        }
        self.data_set.insert(av);
    }

    pub fn query_range(&self, left: i32, right: i32) -> bool {
        if self.data_set.len() == 0 {
            return false;
        }

        if let Some(r) = self
            .data_set
            .range(
                &RangeUnit {
                    left: 0,
                    right: left + 1,
                }..,
            )
            .nth(0)
        {
            if r.right >= right && r.left <= left {
                return true;
            }
        }

        false
    }

    pub fn remove_range(&mut self, left: i32, right: i32) {
        let mut av = Vec::new();
        let mut dv = vec![];

        for i in self.data_set.range(
            &RangeUnit {
                left: 0,
                right: left + 1,
            }..,
        ) {
            if i.left >= right {
                break;
            }

            dv.push(i.clone());
            if i.left < left {
                av.push(RangeUnit {
                    left: i.left,
                    right: min(i.right, left),
                });
            }
            if i.right > right {
                av.push(RangeUnit {
                    left: right,
                    right: i.right,
                });
            }
        }
        for i in dv {
            self.data_set.remove(&i);
        }
        for i in av {
            self.data_set.insert(i);
        }
    }
    pub fn display(&self) {
        for i in self.data_set.iter() {
            print!("{:?} ", i);
        }
        print!("\n");
    }
}

/*
 Your RangeModule object will be instantiated and called as such:
 let obj = RangeModule::new();
 obj.add_range(left, right);
 let ret_2: bool = obj.query_range(left, right);
 obj.remove_range(left, right);
*/
// @lc code=end
#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn test1() {
        let mut obj = RangeModule::new();
        let rs = [[0, 0], [10, 20], [14, 16], [10, 14], [13, 15], [16, 17]];
        obj.add_range(rs[1][0], rs[1][1]);
        obj.display();
        obj.remove_range(rs[2][0], rs[2][1]);
        obj.display();
        assert_eq!(obj.query_range(rs[3][0], rs[3][1]), true);
        assert_eq!(obj.query_range(rs[4][0], rs[4][1]), false);
        assert_eq!(obj.query_range(rs[5][0], rs[5][1]), true);
    }

    #[test]
    fn test2() {
        let event = [
            "RangeModule",
            "addRange",
            "removeRange",
            "removeRange",
            "addRange",
            "removeRange",
            "addRange",
            "queryRange",
            "queryRange",
            "queryRange",
        ];
        let data = [
            [0, 0],
            [6, 8],
            [7, 8],
            [8, 9],
            [8, 9],
            [1, 3],
            [1, 8],
            [2, 4],
            [2, 9],
            [4, 6],
        ];

        let mut obj = RangeModule::new();
        let len = event.len();
        let mut res = vec![];
        for i in 0..len {
            if event[i].starts_with('q') {
                res.push(obj.query_range(data[i][0], data[i][1]).to_string());
            } else if event[i].starts_with('a') {
                res.push("null".to_string());
                println!("addRange, {},{}", data[i][0], data[i][1]);
                obj.add_range(data[i][0], data[i][1]);
            } else if event[i].starts_with('r') {
                println!("removeRange, {},{}", data[i][0], data[i][1]);
                obj.remove_range(data[i][0], data[i][1]);
                res.push("null".to_string());
            } else {
                res.push("null".to_string());
            }
            obj.display();
        }
        let ans = [
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "true".to_string(),
            "true".to_string(),
        ];
        for i in 0..ans.len() {
            assert_eq!(
                ans[i], res[i],
                "{}, {},{}, error",
                event[i], data[i][0], data[i][1]
            );
        }
    }
    #[test]
    fn test3() {
        let event = [
            "RangeModule",
            "removeRange",
            "addRange",
            "queryRange",
            "addRange",
            "removeRange",
            "queryRange",
            "queryRange",
            "addRange",
            "removeRange",
        ];

        let data = [
            [0, 0],
            [4, 8],
            [1, 10],
            [1, 7],
            [2, 3],
            [2, 3],
            [8, 9],
            [6, 9],
            [2, 3],
            [1, 8],
        ];

        let mut obj = RangeModule::new();
        let len = event.len();
        let mut res = vec![];
        for i in 0..len {
            if event[i].starts_with("q") {
                res.push(obj.query_range(data[i][0], data[i][1]).to_string());
                println!("queryRange, {},{}", data[i][0], data[i][1]);
            } else if event[i].starts_with('a') {
                res.push("null".to_string());
                println!("addRange, {},{}", data[i][0], data[i][1]);
                obj.add_range(data[i][0], data[i][1]);
            } else if event[i].starts_with('r') {
                println!("removeRange, {},{}", data[i][0], data[i][1]);
                obj.remove_range(data[i][0], data[i][1]);
                res.push("null".to_string());
            } else {
                res.push("null".to_string());
            }
            obj.display();
        }

        let ans = [
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "true".to_string(),
            "null".to_string(),
            "null".to_string(),
        ];
        for i in 0..ans.len() {
            assert_eq!(
                ans[i], res[i],
                "{}, {},{}, error",
                event[i], data[i][0], data[i][1]
            );
        }
    }
    //["RangeModule","removeRange","addRange","queryRange","addRange","removeRange","queryRange","queryRange","addRange","removeRange"]
    //[[],          [4,8],        [1,10],     [1,7],        [2,3],      [2,3],      [8,9]        ,[6,9],        [2,3],      [1,8]]
    #[test]
    fn test4() {
        let event = [
            "RangeModule",
            "queryRange",
            "queryRange",
            "addRange",
            "addRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "removeRange",
            "addRange",
            "removeRange",
            "addRange",
            "removeRange",
            "removeRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "removeRange",
            "addRange",
            "removeRange",
            "queryRange",
            "addRange",
            "addRange",
            "removeRange",
            "queryRange",
            "removeRange",
            "removeRange",
            "removeRange",
            "addRange",
            "removeRange",
            "addRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "queryRange",
            "addRange",
            "removeRange",
            "addRange",
            "addRange",
            "addRange",
            "queryRange",
            "removeRange",
            "addRange",
            "queryRange",
            "addRange",
            "queryRange",
            "removeRange",
            "removeRange",
            "addRange",
            "addRange",
            "queryRange",
            "queryRange",
            "addRange",
            "addRange",
            "removeRange",
            "removeRange",
            "removeRange",
            "queryRange",
            "removeRange",
            "removeRange",
            "addRange",
            "queryRange",
            "removeRange",
            "addRange",
            "addRange",
            "queryRange",
            "removeRange",
            "queryRange",
            "addRange",
            "addRange",
            "addRange",
            "addRange",
            "addRange",
            "removeRange",
            "removeRange",
            "addRange",
            "queryRange",
            "queryRange",
            "removeRange",
            "removeRange",
            "removeRange",
            "addRange",
            "queryRange",
            "removeRange",
            "queryRange",
            "addRange",
            "removeRange",
            "removeRange",
            "queryRange",
        ];
        let data = [
            [0, 0],
            [21, 34],
            [27, 87],
            [44, 53],
            [69, 89],
            [23, 26],
            [80, 84],
            [11, 12],
            [86, 91],
            [87, 94],
            [34, 52],
            [1, 59],
            [62, 96],
            [34, 83],
            [11, 59],
            [59, 79],
            [1, 13],
            [21, 23],
            [9, 61],
            [17, 21],
            [4, 8],
            [19, 25],
            [71, 98],
            [23, 94],
            [58, 95],
            [12, 78],
            [46, 47],
            [50, 70],
            [84, 91],
            [51, 63],
            [26, 64],
            [38, 87],
            [41, 84],
            [19, 21],
            [18, 56],
            [23, 39],
            [29, 95],
            [79, 100],
            [76, 82],
            [37, 55],
            [30, 97],
            [1, 36],
            [18, 96],
            [45, 86],
            [74, 92],
            [27, 78],
            [31, 35],
            [87, 91],
            [37, 84],
            [26, 57],
            [65, 87],
            [76, 91],
            [37, 77],
            [18, 66],
            [22, 97],
            [2, 91],
            [82, 98],
            [41, 46],
            [6, 78],
            [44, 80],
            [90, 94],
            [37, 88],
            [75, 90],
            [23, 37],
            [18, 80],
            [92, 93],
            [3, 80],
            [68, 86],
            [68, 92],
            [52, 91],
            [43, 53],
            [36, 37],
            [60, 74],
            [4, 9],
            [44, 80],
            [85, 93],
            [56, 83],
            [9, 26],
            [59, 64],
            [16, 66],
            [29, 36],
            [51, 96],
            [56, 80],
            [13, 87],
            [42, 72],
            [6, 56],
            [24, 53],
            [43, 71],
            [36, 83],
            [15, 45],
            [10, 48],
        ];
        let ans = [
            "null".to_string(),
            "false".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "true".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "false".to_string(),
            "true".to_string(),
            "true".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "true".to_string(),
            "false".to_string(),
            "false".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "true".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "true".to_string(),
            "null".to_string(),
            "false".to_string(),
            "null".to_string(),
            "null".to_string(),
            "null".to_string(),
            "false".to_string(),
        ];

        let mut obj = RangeModule::new();
        let len = event.len();
        let mut res = vec![];
        for i in 0..len {
            if event[i].starts_with("q") {
                res.push(obj.query_range(data[i][0], data[i][1]).to_string());
                println!("queryRange, {},{}", data[i][0], data[i][1]);
            } else if event[i].starts_with('a') {
                res.push("null".to_string());
                println!("addRange, {},{}", data[i][0], data[i][1]);
                obj.add_range(data[i][0], data[i][1]);
            } else if event[i].starts_with('r') {
                println!("removeRange, {},{}", data[i][0], data[i][1]);
                obj.remove_range(data[i][0], data[i][1]);
                res.push("null".to_string());
            } else {
                res.push("null".to_string());
            }
            obj.display();
        }

        for i in 0..ans.len() {
            assert_eq!(
                ans[i], res[i],
                "{}, {},{}, error",
                event[i], data[i][0], data[i][1]
            );
        }
    }
}
