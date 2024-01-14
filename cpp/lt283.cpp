#include <vector>
using namespace std;
class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    int start_index = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != 0) {
        if (start_index != i)
          nums[start_index] = nums[i];
        ++start_index;
      }
    }
    for (int i = start_index; i < nums.size(); i++) {
      nums[i] = 0;
    }
  }
};
