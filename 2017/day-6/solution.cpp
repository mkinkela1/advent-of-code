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
  vector<int> data;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, "	");
      for (auto part : parts) {
        this->data.push_back(stoi(part));
      }
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {

    map<vector<int>, bool> checked;
    vector<int> data = this->data;

    checked[data] = true;
    int steps = 0;

    while (true) {
      auto maxBlock = *max_element(data.begin(), data.end());
      int index = find(data.begin(), data.end(), maxBlock) - data.begin();
      data[index] = 0;

      for (int i = 0; i < maxBlock; i++) {
        data[(index + i + 1) % data.size()]++;
      }

      steps++;
      if (checked[data]) {
        return steps;
      }

      checked[data] = true;
    }

    return -1;
  }

  auto part2() -> int {

    map<vector<int>, bool> checked;
    vector<int> data = this->data;
    vector<vector<int>> history;

    checked[data] = true;
    int steps = 0;

    while (true) {
      history.push_back(data);
      auto maxBlock = *max_element(data.begin(), data.end());
      int index = find(data.begin(), data.end(), maxBlock) - data.begin();
      data[index] = 0;

      for (int i = 0; i < maxBlock; i++) {
        data[(index + i + 1) % data.size()]++;
      }

      steps++;
      if (checked[data]) {
        return history.size() -
               (find(history.begin(), history.end(), data) - history.begin());
      }

      checked[data] = true;
    }

    return -1;
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