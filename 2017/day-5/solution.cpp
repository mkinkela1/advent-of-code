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
      this->data.push_back(stoi(line));
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {

    vector<int> data = this->data;
    int steps = 0;
    int index = 0;
    while (index < data.size() && index >= 0) {
      int jump = data[index];
      data[index]++;
      index += jump;
      steps++;
    }
    return steps;
  }

  auto part2() -> int {

    vector<int> data = this->data;
    int steps = 0;
    int index = 0;
    while (index < data.size() && index >= 0) {
      int jump = data[index];
      if (jump >= 3) {
        data[index]--;
      } else {
        data[index]++;
      }
      index += jump;
      steps++;
    }
    return steps;
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