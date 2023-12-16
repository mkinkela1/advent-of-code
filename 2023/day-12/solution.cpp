#include "../../utils/split.h"
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
private:
  fstream fin;
  vector<pair<string, vector<bool>>> input1;
  vector<pair<string, vector<bool>>> input2;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> instructions = split(line, " ");
      vector<string> arrangement = split(instructions[1], ",");
      vector<bool> arrangementBool = {false};
      for (string s : arrangement) {
        if (s == "")
          continue;

        int cnt = stoi(s);

        for (int i = 0; i < cnt; i++)
          arrangementBool.push_back(true);
        arrangementBool.push_back(false);
      }

      this->input1.push_back(
          make_pair("." + instructions[0] + ".", arrangementBool));

      arrangementBool.erase(arrangementBool.begin());
      arrangementBool.pop_back();

      vector<bool> newArrangementBool = {false};
      string newInstructions = "";
      for (int i = 0; i < 5; i++) {
        newInstructions += instructions[0] + (i == 4 ? "" : "?");
        for (string s : arrangement) {
          if (s == "")
            continue;

          int cnt = stoi(s);

          for (int i = 0; i < cnt; i++)
            newArrangementBool.push_back(true);
          newArrangementBool.push_back(false);
        }
      }

      this->input2.push_back(
          make_pair("." + newInstructions + ".", newArrangementBool));
    }
  }

  auto solve(string instructions, vector<bool> arrangement) -> long long {
    int n = instructions.size();
    int m = arrangement.size();

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
    dp[n][m] = 1;

    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        switch (instructions[i]) {
        case '#':
          dp[i][j] = arrangement[j] ? dp[i + 1][j + 1] : 0;
          break;
        case '.':
          dp[i][j] = arrangement[j] ? 0 : dp[i + 1][j + 1] + dp[i + 1][j];
          break;
        case '?':
          dp[i][j] = (arrangement[j] ? dp[i + 1][j + 1] : 0) +
                     (arrangement[j] ? 0 : dp[i + 1][j + 1] + dp[i + 1][j]);
          break;
        }
      }
    }

    return dp[0][0];
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int ans = 0;
    for (auto p : this->input1) {
      ans += this->solve(p.first, p.second);
    }
    return ans;
  }

  auto part2() -> long long {
    long long ans = 0;
    for (auto p : this->input2) {
      long long tmp = this->solve(p.first, p.second);
      ans += tmp;
    }
    return ans;
  }
};

auto main() -> int {

  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  cout << "Part 1 test: " << test1.part1() << endl;
  cout << "Part 1: " << aoc.part1() << endl;
  cout << "--------------------------" << endl;
  cout << "Part 2 test: " << test2.part2() << endl;
  cout << "Part 2: " << aoc.part2() << endl;

  return 0;
}
