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
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
private:
  fstream fin;
  vector<pair<unsigned long long, unsigned long long>> ranges;
  vector<unsigned long long> numbers;

  void parse() {
    string line;
    bool isEmptyLine = false;

    while (getline(this->fin, line)) {
      if (line.empty()) {
        isEmptyLine = true;
        continue;
      }

      if (!isEmptyLine) {
        vector<string> parts = split(line, "-");
        this->ranges.push_back(make_pair(stoull(parts[0]), stoull(parts[1])));
      } else {
        this->numbers.push_back(stoull(line));
      }
    }
  }

  auto isInRange(unsigned long long number,
                 vector<pair<unsigned long long, unsigned long long>> ranges)
      -> bool {
    for (auto range : ranges) {
      if (number >= range.first && number <= range.second) {
        return true;
      }
    }
    return false;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int sol = 0;
    for (auto number : this->numbers) {
      if (this->isInRange(number, this->ranges)) {
        sol++;
      }
    }
    return sol;
  }

  auto part2() -> unsigned long long {
    set<unsigned long long> numbers;
    map<unsigned long long, int> inRange;
    for (auto range : this->ranges) {
      inRange[range.first]++;
      inRange[range.second + 1]--;
      numbers.insert(range.first);
      numbers.insert(range.second + 1);
    }

    unsigned long long sol = 0;
    unsigned long long cnt = 0;
    unsigned long long lastNumber = *numbers.begin();
    for (auto number : numbers) {
      unsigned long long prevCnt = cnt;
      cnt += inRange[number];

      if (prevCnt <= 0 && cnt > 0) {
        lastNumber = number;
      } else if (prevCnt > 0 && cnt <= 0) {
        sol += number - lastNumber;
      }
    }
    return sol;
  }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  auto start = chrono::high_resolution_clock::now();
  int part1TestResult = test1.part1();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1 test: " << part1TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  int part1Result = aoc.part1();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1: " << part1Result << " (Time: " << duration.count() << " μs)"
       << endl;

  cout << "--------------------------" << endl;

  start = chrono::high_resolution_clock::now();
  unsigned long long part2TestResult = test2.part2();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2 test: " << part2TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  unsigned long long part2Result = aoc.part2();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration.count() << " μs)"
       << endl;

  return 0;
}