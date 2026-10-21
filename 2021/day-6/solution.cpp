#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
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
  vector<int> fish;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> data = split(line, ",");
      for (string item : data) {
        this->fish.push_back(stoi(item));
      }
    }
  }

  auto simulate(vector<int> fish, int days) -> long long unsigned {

    map<int, long long> count;
    for (int fish : fish) {
      count[fish]++;
    }

    for (int day = 0; day < days; day++) {
      map<int, long long> newCount;
      for (auto [fish, count] : count) {
        if (fish - 1 < 0) {
          newCount[6] += count;
          newCount[8] += count;
        } else {
          newCount[fish - 1] += count;
        }
      }
      count = newCount;
    }
    return accumulate(count.begin(), count.end(), 0LL,
                      [](long long unsigned sum, pair<int, long long> p) {
                        return sum + p.second;
                      });
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int days = 80) -> long long unsigned {
    return this->simulate(this->fish, days);
  }

  auto part2(int days = 256) -> long long unsigned {
    return this->simulate(this->fish, days);
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
