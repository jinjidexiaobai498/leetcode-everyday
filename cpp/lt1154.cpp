// Author: xxx
// Time: 2023 年 Dec 31日 10:59:27 AM
// Blog: xxx
// FileName: /home/lxd/WorkSpace/leetcode/cpp/lt1154.cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int dayOfYear(string date) {
    int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 +
               (date[2] - '0') * 10 + (date[3] - '0');
    int month = (date[5] - '0') * 10 + (date[6] - '0');
    int day = (date[8] - '0') * 10 + (date[9] - '0');
    bool is_prime = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    int month_days[] = {31,59,90,120,151,181,212,243,273,304,334,365};
	int days = day;
	if (month > 2 && is_prime)
		days += 1;
	if (month > 1)
		days += month_days[month-2];

	return days;
  }
};

int main() {
	Solution sol;
	cout<<sol.dayOfYear("2012-03-09")<<endl;
	return 0;
}
