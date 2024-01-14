#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> map;
    for (auto s : strs) {
      vector<int> vm(26, 0);
      for (auto c : s) {
        vm[c - 'a'] += 1;
      }
      auto hs = get_hasher(vm);
      map[hs].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto [_, v] : map) {
      ans.push_back(std::move(v));
    }
    return ans;
  }

  string get_hasher(vector<int> &map) {
    string ans = "";
    for (int i = 0; i < map.size(); i++) {
      if (map[i] > 0) {
        ans += ('a' + i);
        ans += ('0' + map[i]);
      }
    }
    return ans;
  }
};
