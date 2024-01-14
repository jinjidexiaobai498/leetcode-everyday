#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); ++i) {
      map.insert_or_assign(nums[i], i);
    }
    vector<int> ans(2, 0);
    for (int i = 0; i < nums.size(); ++i) {
      int another = target - nums[i];
      if (map.count(another) && map[another] != i) {
        ans[0] = i;
        ans[1] = map[another];
      }
    }
    return ans;
  }
};
