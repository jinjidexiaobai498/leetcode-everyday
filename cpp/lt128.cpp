#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.size() == 0)
      return 0;
    if (nums.size() == 1)
      return 1;
    sort(begin(nums), end(nums));
    int index = 1;
    int ans = 0;
    while (index < nums.size()) {
      int count = 1;
      while (index < nums.size()) {
        if (nums[index] == nums[index - 1] + 1) {
          ++count;
          ++index;
        } else if (nums[index] == nums[index - 1]) {
          ++index;
        } else {
          break;
        }
      }
      ++index;
      ans = max(ans, count);
    }
    return ans;
  }
};
