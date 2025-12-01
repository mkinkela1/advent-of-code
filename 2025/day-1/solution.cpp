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
  vector<pair<char, int>> instructions;
  const int TOTAL_STEPS = 100;

  void parse() {
    string line;
    char direction;
    int steps;
    while (getline(this->fin, line)) {
      sscanf(line.c_str(), "%c%d", &direction, &steps);
      this->instructions.push_back(make_pair(direction, steps));
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int totalZeros = 0;
    int current = 50;

    for (auto [direction, steps] : this->instructions) {
      if (direction == 'L') {
        current -= steps;
        while (current < 0) {
          current += TOTAL_STEPS;
        }
        current %= TOTAL_STEPS;
      } else {
        current += steps;
        current %= TOTAL_STEPS;
      }

      if (current == 0)
        ++totalZeros;
    }

    return totalZeros;
  }

  auto part2() -> int {
    int totalZeros = 0;
    int current = 50;
    cout << endl;
    for (auto [direction, steps] : this->instructions) {
      int dir = direction == 'L' ? -1 : 1;

      for (int i = 0; i < steps; i++) {
        current += dir;
        current %= TOTAL_STEPS;
        if (current == 0)
          totalZeros++;
      }
    }

    return totalZeros;
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