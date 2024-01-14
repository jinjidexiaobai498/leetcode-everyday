// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=1096 lang=cpp
 * @lcpr version=21801
 *
 * [1096] 花括号展开 II
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
// @lc code=start

using namespace std;

enum OPERATE_TYPE { BEGIN, ADD_ELEM, SET, SET_IN, SET_OUT };
class Solution {
  public:
    auto string_add_set(vector<string>& set1, vector<string>& set2)
        -> vector<string>
    {
        vector<string> sum_set;
        for (auto& i : set1) {
            for (auto& j : set2) {
                auto s = i + j;
                sum_set.push_back(s);
            }
        }
        return sum_set;
    }

    void stack_add_set(vector<vector<vector<int>>>& stack)
    {
        vector<vector<int>> set1 = stack.back();
        stack.pop_back();
        vector<vector<int>> set2 = stack.back();
        vector<vector<int>> sum_set;
        for (auto e1 : set1) {
            for (auto e2 : set2) {
                vector<int> se;
                se = add_all(se, e2);
                se = add_all(se, e1);
                sum_set.emplace_back(se);
            }
        }
        stack.back() = sum_set;
    }

    void stack_add_elem(vector<vector<vector<int>>>& stack)
    {
        auto set1 = stack.back();
        stack.pop_back();
        auto set2 = stack.back();
        for (const auto& e : set1) {
            set2.emplace_back(e);
        }
        stack.back() = set2;
    }

    auto add_all(vector<int>& a, vector<int>& b) -> vector<int>
    {
        vector<int> c;

        c.reserve(a.size());
        for (auto e : a) {
            c.emplace_back(e);
        }
        for (auto e : b) {
            c.emplace_back(e);
        }
        return c;
    }

    auto is_letter(char x) -> bool
    {
        return (x >= 'a' && x <= 'z');
    }

    // input string expression [char {,}]
    // rule 1 : normal char xyz
    // rule 2 : normal + set
    // rule 3 : set + set
    // output string set
    auto braceExpansionII(string expression) -> vector<string>
    {
        const int      len = (int)expression.size();
        vector<string> elems;
        vector<int>    tokens;

        int i = 0;
        while (i < len) {
            string s;
            while (i < len && is_letter(expression[i])) {
                s += expression[i];
                i++;
            }
            if (!s.empty()) {
                elems.emplace_back(s);
                tokens.emplace_back(i - s.size());
            }
            if (i < len && !is_letter(expression[i])) {
                tokens.emplace_back(i);
                i++;
            }
        }
        vector<OPERATE_TYPE> op_stack;
        op_stack.emplace_back(BEGIN);
        vector<vector<vector<int>>> elem_stack;

        int p_token = 0;
        int p_elem  = 0;
        while (p_token < tokens.size()) {
            switch (expression[tokens[p_token]]) {
                case '{': {
                    op_stack.emplace_back(SET_IN);
                    // elem_stack.emplace_back();
                    break;
                }
                case '}': {
                    auto f = op_stack.back();
                    // 当前状态是一个SET,栈顶为SET,进行集合加,add_set,栈顶是ADD_SET和SET,就进行add_elme
                    if (f != SET_IN && f == SET) {
                        op_stack.pop_back();
                    }
                    else {
                        // TODO: invalid or empty set
                    }

                    while (op_stack.back() != SET_IN) {
                        f = op_stack.back();
                        op_stack.pop_back();

                        if (f == SET) {
                            op_stack.pop_back();
                            stack_add_set(elem_stack);
                        }
                        else if (f == ADD_ELEM) {
                            op_stack.pop_back();
                            stack_add_elem(elem_stack);
                        }
                        else if (op_stack.back() == BEGIN) {
                            break;
                        }
                    }
                    // pop_back() SET_IN
                    op_stack.pop_back();

                    while (op_stack.back() == SET) {
                        stack_add_set(elem_stack);
                        op_stack.pop_back();
                    }
                    op_stack.emplace_back(SET);

                    break;
                }
                case ',': {
                    op_stack.emplace_back(ADD_ELEM);
                    break;
                }
                default: {
                    vector<vector<int>> set;
                    set.emplace_back();
                    set.back().emplace_back(p_elem);
                    elem_stack.emplace_back(set);
                    p_elem++;

                    while (op_stack.back() == SET) {
                        stack_add_set(elem_stack);
                        op_stack.pop_back();
                    }
                    op_stack.emplace_back(SET);
                    break;
                }
            }
            p_token++;
        }
        vector<vector<string>> result_set;
        for (const auto& set : elem_stack) {
            vector<string>        sum_sets;
            unordered_set<string> elem_record_set;
            for (const auto& str_set : set) {
                string s;
                for (auto index : str_set) {
                    s += elems[index];
                }
                if (elem_record_set.count(s) == 0) {
                    elem_record_set.emplace(s);
                    sum_sets.emplace_back(s);
                }
            }
            result_set.emplace_back(sum_sets);
        }

        vector<string> result = result_set[0];
        for (int i = 1; i < result_set.size(); i++) {
            result = string_add_set(result, result_set[i]);
        }

        sort(result.begin(),result.end());
        return result;
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
// "{a,b}{c,{d,e}}"\n
// @lcpr case=end

// @lcpr case=start
// "{{a,z},a{b,c},{ab,z}}"\n
// @lcpr case=end

 */
