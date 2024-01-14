#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int uniqueLetterString(string s) {

    map<char, int> last_first_map;
    map<char, int> last_second_map;
    vector<int> dp(0, s.size());
    dp[0] = 1;
    last_first_map.insert({s[0], 0});

    for (int i = 1; i < s.size(); i++) {
      dp[i] += dp[i - 1] + i;
      if (last_second_map.count(s[i])) {
        dp[i] += last_second_map.at(s[i]) + 1;
      }

      if (last_first_map.count(s[i])) {
        dp[i] -= last_first_map.at(s[i]);
        last_second_map.insert_or_assign(s[i], last_first_map.at(s[i]));
      }

      last_first_map.insert_or_assign(s[i], i);
    }
    return dp.back();
  }
};
