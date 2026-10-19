#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
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
  string polymerTemplate;
  map<string, vector<string>> insertionRules;

  void parse() {
    string line;
    getline(this->fin, this->polymerTemplate);
    getline(this->fin, line);
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, " -> ");

      // AB -> X => [AX, XB]
      this->insertionRules.insert(
          {parts[0], {parts[0][0] + parts[1], parts[1] + parts[0][1]}});
    }
  }

  auto solve(int steps) -> long long unsigned {
    map<string, long long unsigned> polymerCounts;
    for (int i = 0; i < this->polymerTemplate.length() - 1; i++) {
      polymerCounts[this->polymerTemplate.substr(i, 2)]++;
    }

    for (int i = 0; i < steps; i++) {
      map<string, long long unsigned> newPolymerCounts;
      for (auto [polymer, count] : polymerCounts) {
        for (auto newPolymer : this->insertionRules[polymer]) {
          newPolymerCounts[newPolymer] += count;
        }
      }
      polymerCounts = newPolymerCounts;
    }

    map<char, long long unsigned> charCounts;
    for (auto [polymer, count] : polymerCounts) {
      charCounts[polymer[0]] += count;
      charCounts[polymer[1]] += count;
    }

    long long unsigned maxCount = 0LLU, minCount = LLONG_MAX;
    for (auto [_, count] : charCounts) {
      maxCount = max(maxCount, count);
      minCount = min(minCount, count);
    }

    return ceil(double(maxCount - minCount) / 2);
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> long long unsigned { return this->solve(10); }

  auto part2() -> long long unsigned { return this->solve(40); }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  auto start = chrono::high_resolution_clock::now();
  auto part1TestResult = test1.part1();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1 test: " << part1TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part1Result = aoc.part1();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1: " << part1Result << " (Time: " << duration.count() << " μs)"
       << endl;

  cout << "--------------------------" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2TestResult = test2.part2();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2 test: " << part2TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2Result = aoc.part2();
  end = chrono::high_resolution_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration.count() << " ms)"
       << endl;

  return 0;
}
