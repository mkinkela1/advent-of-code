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
  string initialState;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->initialState = line;
    }
  }

  auto produceComplemented(string state) -> string {
    string reversed = state;
    reverse(reversed.begin(), reversed.end());

    string complemented = "";
    for (char c : reversed) {
      if (c == '0') {
        complemented += "1";
      } else {
        complemented += "0";
      }
    }

    return complemented;
  }

  auto dragonCurve(int length) -> string {
    string state = this->initialState;
    while (state.length() < length) {
      state = state + "0" + this->produceComplemented(state);
    }
    return state;
  }

  auto checksum(string state) -> string {
    while (state.length() % 2 == 0) {
      string newState = "";
      for (int i = 0; i < state.length(); i += 2) {
        if (state[i] == state[i + 1]) {
          newState += "1";
        } else {
          newState += "0";
        }
      }
      state = newState;
    }
    return state;
  }

  auto solve(int length) -> string {
    string state = this->dragonCurve(length);
    state = state.substr(0, length);
    return this->checksum(state);
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int length) -> string { return this->solve(length); }

  auto part2(int length) -> string { return this->solve(length); }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  auto start = chrono::high_resolution_clock::now();
  auto part1TestResult = test1.part1(20);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1 test: " << part1TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part1Result = aoc.part1(272);
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1: " << part1Result << " (Time: " << duration.count() << " μs)"
       << endl;

  cout << "--------------------------" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2TestResult = test2.part2(35651584);
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2 test: " << part2TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2Result = aoc.part2(35651584);
  end = chrono::high_resolution_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration.count() << " ms)"
       << endl;

  return 0;
}
