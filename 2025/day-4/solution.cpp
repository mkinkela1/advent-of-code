#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <cmath>
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
  vector<string> data;
  vector<pair<int, int>> directions = {{1, 0}, {0, 1},   {-1, 0}, {0, -1},
                                       {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->data.push_back(line);
    }
  }

  auto canRemove(vector<string> data, int i, int j) -> bool {
    int cnt = 0;
    for (auto dir : this->directions) {
      int x = i + dir.first;
      int y = j + dir.second;
      if (x >= 0 && x < data.size() && y >= 0 && y < data[i].size() &&
          data[x][y] == '@') {
        ++cnt;
      }
    }

    return cnt < 4;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int sol = 0;
    for (int i = 0; i < this->data.size(); i++) {
      for (int j = 0; j < this->data[i].size(); j++) {
        if (this->data[i][j] == '@' && this->canRemove(this->data, i, j)) {
          sol++;
        }
      }
    }
    return sol;
  }

  auto part2() -> int {
    int sol = 0;
    vector<string> data = this->data;
    bool removedAtLeastOne = true;

    while (removedAtLeastOne) {
      removedAtLeastOne = false;
      for (int i = 0; i < this->data.size(); i++) {
        for (int j = 0; j < this->data[i].size(); j++) {
          if (data[i][j] == '@') {

            if (this->canRemove(data, i, j)) {
              sol++;
              removedAtLeastOne = true;
              data[i][j] = '.';
            }
          }
        }
      }
    }
    return sol;
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