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
  vector<pair<int, int>> points;
  pair<int, int> topLeft = {INT_MAX, INT_MAX}, bottomRight = {INT_MIN, INT_MIN};

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      auto parts = split(line, ", ");
      auto x = stoi(parts[0]);
      auto y = stoi(parts[1]);
      this->topLeft.first = min(this->topLeft.first, x);
      this->topLeft.second = min(this->topLeft.second, y);
      this->bottomRight.first = max(this->bottomRight.first, x);
      this->bottomRight.second = max(this->bottomRight.second, y);
      this->points.push_back({x, y});
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    map<pair<int, int>, int> shortestDistance;

    for (int i = this->topLeft.first; i <= this->bottomRight.first; i++) {
      for (int j = this->topLeft.second; j <= this->bottomRight.second; j++) {
        vector<pair<int, int>> distances;
        for (int k = 0; k < this->points.size(); k++) {
          auto [x, y] = this->points[k];
          distances.push_back({abs(x - i) + abs(y - j), k});
        }
        sort(distances.begin(), distances.end());
        if (distances[0].first == distances[1].first) {
          shortestDistance[{i, j}] = -1;
        } else {
          shortestDistance[{i, j}] = distances[0].second;
        }
      }
    }

    set<int> infinite;
    for (int i = this->topLeft.first; i <= this->bottomRight.first; i++) {
      infinite.insert(shortestDistance[{i, this->topLeft.second}]);
      infinite.insert(shortestDistance[{i, this->bottomRight.second}]);
    }
    for (int j = this->topLeft.second; j <= this->bottomRight.second; j++) {
      infinite.insert(shortestDistance[{this->topLeft.first, j}]);
      infinite.insert(shortestDistance[{this->bottomRight.first, j}]);
    }

    map<int, int> area;
    for (auto [point, distance] : shortestDistance)
      if (infinite.find(distance) == infinite.end())
        area[distance]++;

    auto maxArea = *max_element(
        area.begin(), area.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; });

    return maxArea.second;
  }

  auto part2(int maxDistance) -> int {
    int sol = 0;
    for (int i = this->topLeft.first; i <= this->bottomRight.first; i++) {
      for (int j = this->topLeft.second; j <= this->bottomRight.second; j++) {
        int distance = 0;
        for (auto [x, y] : this->points) {
          distance += abs(x - i) + abs(y - j);
        }
        if (distance < maxDistance) {
          sol++;
        }
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
  auto part2TestResult = test2.part2(32);
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2 test: " << part2TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2Result = aoc.part2(10000);
  end = chrono::high_resolution_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration.count() << " ms)"
       << endl;

  return 0;
}
