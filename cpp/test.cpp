// Author: xxx
// Time: 2024 年 Jan 05日 08:37:49 AM
// Blog: xxx
// FileName: /home/lxd/WorkSpace/leetcode/cpp/test.cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
  string s = "testabdcasdfa";
  sort(s.begin(), s.end(), greater<>());
  cout << s << endl;
}
