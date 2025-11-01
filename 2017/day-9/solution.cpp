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
  string data;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->data += line;
    }
  }

  auto calculateScore(string data) -> uint64_t {
    uint64_t count = 0;
    int pos = 0;
    bool inGarbage = false;
    bool skipNext = false;
    uint64_t groupLevel = 0LL;

    while (pos < this->data.length()) {
      if (skipNext) {
        ++pos;
        skipNext = false;
        continue;
      }

      if (this->data[pos] == '!')
        skipNext = true;
      else if (this->data[pos] == '<')
        inGarbage = true;
      else if (this->data[pos] == '>')
        inGarbage = false;
      else if (inGarbage) {
        ++pos;
        continue;
      } else if (this->data[pos] == '{')
        count += ++groupLevel;
      else if (this->data[pos] == '}')
        groupLevel--;

      ++pos;
    }

    return count;
  }

  auto calculateGarbage(string data) -> uint64_t {
    uint64_t count = 0;
    int pos = 0;
    bool inGarbage = false;
    bool skipNext = false;
    uint64_t groupLevel = 0LL;

    while (pos < this->data.length()) {
      if (skipNext) {
        ++pos;
        skipNext = false;
        continue;
      }

      if (this->data[pos] == '!')
        skipNext = true;
      else if (this->data[pos] == '<' && !inGarbage)
        inGarbage = true;
      else if (this->data[pos] == '>')
        inGarbage = false;
      else if (inGarbage) {
        ++pos;
        count++;
        continue;
      }

      ++pos;
    }

    return count;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> uint64_t {
    uint64_t sol = 0;
    sol += this->calculateScore(this->data);
    return sol;
  }

  auto part2() -> uint64_t {
    uint64_t sol = 0;
    sol += this->calculateGarbage(this->data);
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