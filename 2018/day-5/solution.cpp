#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <cctype>
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
  string polymer;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->polymer = line;
    }
  }

  auto react(string &polymer) -> int {
    stack<char> s;
    for (auto c : polymer) {
      if (s.empty()) {
        s.push(c);
      } else {
        if (this->isReactive(s.top(), c)) {
          s.pop();
        } else {
          s.push(c);
        }
      }
    }
    return s.size();
  }
  auto isReactive(char a, char b) -> bool {
    return (a == b + 32 || a == b - 32);
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int { return this->react(this->polymer); }

  auto part2() -> int {
    int minLength = INT_MAX;
    map<char, bool> visited;
    for (auto c : this->polymer) {
      if (visited[toupper(c)])
        continue;
      visited[toupper(c)] = true;

      string newPolymer = "";
      char upperC = toupper(c);
      for (auto ch : this->polymer) {
        if (toupper(ch) == upperC)
          continue;
        newPolymer += ch;
      }
      minLength = min(minLength, this->react(newPolymer));
    }
    return minLength;
  }
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
