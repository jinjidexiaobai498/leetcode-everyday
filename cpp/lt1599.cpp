// Author: xxx
// Time: 2024 年 Jan 01日 10:30:32 AM
// Blog: xxx
// FileName: /home/lxd/WorkSpace/leetcode/cpp/lt1599.cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

class Solution {
public:
  int minOperationsMaxProfit(vector<int> &customers, int boardingCost,
                             int runningCost) {
    // if (boardingCost * 4 <= runningCost) return -1;
    int profit = 0;
    int max_profit = -1;
    int wating_num = 0;
    int turns = 0;
    int res_turns = -1;
    while (wating_num > 0 || turns < customers.size()) {
      if (turns < customers.size()) {
        wating_num += customers[turns];
      }
      int board_num = min(wating_num, 4);
      wating_num -= board_num;

      profit += board_num * boardingCost - runningCost;
      if (max_profit < profit) {
        res_turns = turns + 1;
        max_profit = profit;
      }
      turns += 1;
    }

    return res_turns;
  }
};
