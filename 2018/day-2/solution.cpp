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
  vector<string> data;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->data.push_back(line);
    }
  }

  auto hasFrequency(map<char, int> &freq, int frequency) -> bool {
    for (auto [c, f] : freq) {
      if (f == frequency)
        return true;
    }
    return false;
  }

  auto commonCharacters(string &s1, string &s2) -> string {
    string result = "";
    for (int i = 0; i < s1.size(); i++) {
      if (s1[i] == s2[i]) {
        result += s1[i];
      }
    }
    return result;
  }

  auto hasOneDifference(string &s1, string &s2) -> bool {
    int count = 0;
    for (int i = 0; i < s1.size(); i++) {
      if (s1[i] != s2[i]) {
        count++;
      }
    }
    return count == 1;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int count2 = 0;
    int count3 = 0;
    for (auto line : this->data) {
      map<char, int> freq;
      for (auto c : line) {
        freq[c]++;
      }
      if (this->hasFrequency(freq, 2))
        count2++;
      if (this->hasFrequency(freq, 3))
        count3++;
    }

    return count2 * count3;
  }

  auto part2() -> string {
    for (int i = 0; i < this->data.size(); i++) {
      for (int j = i + 1; j < this->data.size(); j++) {
        if (this->hasOneDifference(this->data[i], this->data[j])) {
          return this->commonCharacters(this->data[i], this->data[j]);
        }
      }
    }
    return "";
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
