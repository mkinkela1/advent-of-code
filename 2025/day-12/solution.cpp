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
  map<int, vector<string>> shapes;
  vector<pair<tuple<int, int>, vector<int>>> regions;

  void parse() {
    string line;
    int shapeId = -1;

    while (getline(this->fin, line)) {
      if (line.empty()) {
        shapeId = -1;
        continue;
      }

      if (line.find("x") != string::npos) {
        vector<string> parts = split(line, ": ");
        vector<string> size = split(parts[0], "x");
        int width = stoi(size[0]);
        int height = stoi(size[1]);
        vector<string> quantitiesString = split(parts[1], " ");
        vector<int> quantities;
        for (auto q : quantitiesString) {
          quantities.push_back(stoi(q));
        }
        regions.push_back({{width, height}, quantities});
      } else {
        if (line.find(":") != string::npos) {
          vector<string> parts = split(line, ":");
          shapeId = stoi(parts[0]);
        } else {
          shapes[shapeId].push_back(line);
        }
      }
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    map<int, int> shapeAreas;
    int sol = 0;

    for (auto [shapeId, shape] : shapes) {
      int area = 0;
      for (auto line : shape) {
        for (auto c : line) {
          if (c == '#') {
            area++;
          }
        }
      }
      shapeAreas[shapeId] = area;
    }

    for (auto [regionSize, regionQuantities] : regions) {
      int area = std::get<0>(regionSize) * std::get<1>(regionSize);
      for (int i = 0; i < regionQuantities.size(); i++) {
        area -= regionQuantities[i] * shapeAreas[i];
      }

      if (area > 0) {
        sol++;
      }
    }

    return sol;
  }

  auto part2() -> string { return "Not implemented"; }
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