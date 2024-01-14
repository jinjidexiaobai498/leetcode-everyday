// Author: xxx
// Time: 2023 年 Dec 30日 05:42:05 PM
// Blog: xxx
// FileName: /home/lxd/WorkSpace/leetcode/cpp/lt1185.cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool is_prime(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      return true;
    }
    return false;
  }
  // const string START_DATE = "1971Y 1M 1d 4week";
  const string WEEK[7] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                          "Friday", "Saturday", "Sunday"};
  const int YEAR_TURN[4] = {1, 2, 1, 1};
  const int MONTH_TRUN[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  const int PMONTH_TRUN[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  string dayOfTheWeek(int day, int month, int year) {
    int ny = (year - 1971) % 28;
    int start_week = 4 + (ny / 4) * 5;
    ny %= 4;

    for (int i = 0; i < ny; i++) {
      start_week += YEAR_TURN[i];
    }

    auto month_turn = is_prime(year) ? PMONTH_TRUN : MONTH_TRUN;
    for (int i = 0; i < month - 1; i++) {
      start_week += month_turn[i];
    }
    start_week += day - 1;
    return WEEK[start_week % 7];
  }
};

int main() {
  Solution sol;
  cout << sol.dayOfTheWeek(1, 3, 1993) << endl;
  return 0;
}
