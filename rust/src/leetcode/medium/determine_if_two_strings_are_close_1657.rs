/*
 * @lc app=leetcode.cn id=1657 lang=rust
 * @lcpr version=30111
 *
 * [1657] 确定两个字符串是否接近
 *
 * https://leetcode.cn/problems/determine-if-two-strings-are-close/description/
 *
 * algorithms
 * Medium (47.96%)
 * Likes:    97
 * Dislikes: 0
 * Total Accepted:    25.9K
 * Total Submissions: 50.7K
 * Testcase Example:  '"abc"\n"bca"'
 *
 * 如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：
 *
 *
 * 操作 1：交换任意两个 现有 字符。
 *
 *
 * 例如，abcde -> aecdb
 *
 *
 * 操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
 *
 * 例如，aacabb -> bbcbaa（所有 a 转化为 b ，而所有的 b 转换为 a ）
 *
 *
 *
 *
 * 你可以根据需要对任意一个字符串多次使用这两种操作。
 *
 * 给你两个字符串，word1 和 word2 。如果 word1 和 word2 接近 ，就返回 true ；否则，返回 false 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：word1 = "abc", word2 = "bca"
 * 输出：true
 * 解释：2 次操作从 word1 获得 word2 。
 * 执行操作 1："abc" -> "acb"
 * 执行操作 1："acb" -> "bca"
 *
 *
 * 示例 2：
 *
 * 输入：word1 = "a", word2 = "aa"
 * 输出：false
 * 解释：不管执行多少次操作，都无法从 word1 得到 word2 ，反之亦然。
 *
 * 示例 3：
 *
 * 输入：word1 = "cabbba", word2 = "abbccc"
 * 输出：true
 * 解释：3 次操作从 word1 获得 word2 。
 * 执行操作 1："cabbba" -> "caabbb"
 * 执行操作 2："caabbb" -> "baaccc"
 * 执行操作 2："baaccc" -> "abbccc"
 *
 *
 * 示例 4：
 *
 * 输入：word1 = "cabbba", word2 = "aabbss"
 * 输出：false
 * 解释：不管执行多少次操作，都无法从 word1 得到 word2 ，反之亦然。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= word1.length, word2.length <= 10^5
 * word1 和 word2 仅包含小写英文字母
 *
 *
 */

// @lcpr-template-start
pub struct Solution;
// @lcpr-template-end
// @lc code=start
use std::collections::BTreeSet;

impl Solution {
    pub fn close_strings(word1: String, word2: String) -> bool {
        if word1.len() != word2.len() {
            return false;
        }

        let mut ns1 = vec![0i32; 26usize];
        let mut ns2 = vec![0i32; 26usize];
        let mut set1 = BTreeSet::<char>::new();
        let mut set2 = BTreeSet::<char>::new();
        let mut cs1 = word1.char_indices();
        let mut cs2 = word2.char_indices();
        for _ in 0..word1.len() {
            let c1 = cs1.next().unwrap().1;
            let c2 = cs2.next().unwrap().1;
            set1.insert(c1);
            set2.insert(c2);
            ns1[((c1 as i32) - ('a' as i32)) as usize] += 1;
            ns2[((c2 as i32) - ('a' as i32)) as usize] += 1;
        }

        if set1.len() != set2.len() {
            return false;
        }

        let mut si1 = set1.iter();
        let mut si2 = set2.iter();
        for _ in 0..si1.len() {
            if si1.next().unwrap() != si2.next().unwrap() {
                return false;
            }
        }

        ns1.sort();
        ns2.sort();
        return ns1 == ns2;
    }
}
// @lc code=end

/*
// @lcpr case=start
// "abc"\n"bca"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"aa"\n
// @lcpr case=end

// @lcpr case=start
// "cabbba"\n"abbccc"\n
// @lcpr case=end

// @lcpr case=start
// "cabbba"\n"aabbss"\n
// @lcpr case=end

// @lcpr case=start
// "caaa"\n"deee"\n
// @lcpr case=end

// @lcpr case=start
// "mkmczky"\n"cckcmmy"\n
// @lcpr case=end
 */
