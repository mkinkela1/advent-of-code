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
  vector<int> lengths;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, ",");
      for (auto part : parts) {
        this->lengths.push_back(stoi(part));
      }
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int size) -> int {
    vector<int> list(size);
    for (int i = 0; i < size; ++i) {
      list[i] = i;
    }

    int position = 0;
    int skipSize = 0;

    for (auto length : this->lengths) {
      for (int i = 0; i < length / 2; ++i) {
        int idx1 = (position + i) % size;
        int idx2 = (position + length - 1 - i) % size;
        swap(list[idx1], list[idx2]);
      }

      position = (position + length + skipSize) % size;
      skipSize++;
    }

    return list[0] * list[1];
  }

  auto part2() -> string { return "Not implemented"; }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  cout << "Part 1 test: " << test1.part1(5) << endl;
  cout << "Part 1: " << aoc.part1(256) << endl;
  cout << "--------------------------" << endl;
  cout << "Part 2 test: " << test2.part2() << endl;
  cout << "Part 2: " << aoc.part2() << endl;

  return 0;
}