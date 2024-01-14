// @lcpr-template-start
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start

struct TrieNode {
  map<char, TrieNode *> child;
  bool is_val_node{false};
  char val;
  TrieNode() = default;
  TrieNode(char v) : val(v) {}
};

class Trie {
private:
  TrieNode *head{nullptr};

public:
  Trie() { head = new TrieNode(); }
  char string_startwith(string &s, size_t &index) {
    if (head == nullptr) {
      return '\0';
    }
    TrieNode *p = head;
    size_t i = index;
    for (; index < s.size(); index++) {
      if (!p->child.count(s[index])) {
        return '\0';
      }
      p = p->child[s[index]];
      if (p->is_val_node) {
        return p->val;
      }
    }
    return '\0';
  }
  bool insert(string &s, char val) {
    if (head == nullptr) {
      return false;
    }
    TrieNode *p = head;
    for (int i = 0; i < s.size(); i++) {
      if (!p->child.count(s[i])) {
        auto new_child = new TrieNode();
        if (new_child == nullptr) {
          return false;
        }
        p->child.insert({s[i], new_child});
      }
      p = p->child.at(s[i]);
    }
    p->is_val_node = true;
    p->val = val;
    return true;
  }
};

class Solution {
public:
  vector<string> slist{"quot", "apos", "amp", "gt", "lt", "frasl"};
  vector<char> charnote{'"', '\'', '&', '>', '<', '/'};

  //("quot", '"') , ("apos", '\''), ("amp", '&'),   ("gt", '>'), ("lt",
  //'<'),("frasl", '/')};
  string entityParser(string text) {
    const char ESCAPE = '&';
    Trie map;
    for (int i = 0; i < slist.size(); i++) {
      map.insert(slist[i], charnote[i]);
    }
    string res = "";
    int index = 0;
    for (; index < text.size(); index++) {
      if (text[index] == ESCAPE) {
        size_t i = index + 1;
        char x = map.string_startwith(text, i);
        if (x != '\0') {
          index = i;
          res += x;
          continue;
        }
      }
      res += text[index];
    }

    return res;
  }
};

int main() {
  string text = "hello &&&&&&quotlxd&quot&quto&apos&amp&gtll&lt&frasl";
  auto res = Solution().entityParser(text);
  cout << res << endl;
}
