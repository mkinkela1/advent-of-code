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
  vector<pair<unsigned long long, unsigned long long>> points;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, ",");
      this->points.push_back(make_pair(stoull(parts[0]), stoull(parts[1])));
    }

    sort(this->points.begin(), this->points.end());
  }

  auto gridRectangleIntersectsLineParimeter(
      pair<unsigned long long, unsigned long long> upperLeft,
      pair<unsigned long long, unsigned long long> lowerRight,
      pair<unsigned long long, unsigned long long> edge1,
      pair<unsigned long long, unsigned long long> edge2) -> bool {
    return edge1.first < lowerRight.first && edge2.first > upperLeft.first &&
           edge1.second < lowerRight.second && edge2.second > upperLeft.second;
  }

  auto isInsidePolygon(vector<tuple<unsigned long long, unsigned long long,
                                    unsigned long long, unsigned long long>>
                           edges,
                       pair<unsigned long long, unsigned long long> corner1,
                       pair<unsigned long long, unsigned long long> corner2)
      -> bool {

    pair<unsigned long long, unsigned long long> upperLeft = make_pair(
        min(corner1.first, corner2.first), min(corner1.second, corner2.second));
    pair<unsigned long long, unsigned long long> lowerRight = make_pair(
        max(corner1.first, corner2.first), max(corner1.second, corner2.second));

    for (auto edge : edges) {
      if (get<0>(edge) < lowerRight.first && get<2>(edge) > upperLeft.first &&
          get<1>(edge) < lowerRight.second && get<3>(edge) > upperLeft.second)
        return false;
    }
    return true;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> unsigned long long {
    unsigned long long sol = 0;
    for (int i = 0; i < this->points.size(); i++) {
      for (int j = i + 1; j < this->points.size(); j++) {
        unsigned long long dx =
            this->points[i].first > this->points[j].first
                ? this->points[i].first - this->points[j].first
                : this->points[j].first - this->points[i].first;
        unsigned long long dy =
            this->points[i].second > this->points[j].second
                ? this->points[i].second - this->points[j].second
                : this->points[j].second - this->points[i].second;
        unsigned long long distance = (dx + 1) * (dy + 1);
        sol = max(sol, distance);
      }
    }
    return sol;
  }

  auto part2() -> unsigned long long {
    vector<tuple<unsigned long long, unsigned long long, unsigned long long,
                 unsigned long long>>
        edges;

    for (int i = 0; i < this->points.size(); i++)
      for (int j = i + 1; j < this->points.size(); j++)
        if (this->points[i].first == this->points[j].first ||
            this->points[i].second == this->points[j].second)
          edges.push_back(
              make_tuple(this->points[i].first, this->points[i].second,
                         this->points[j].first, this->points[j].second));

    unsigned long long sol = 0;
    for (int i = 0; i < this->points.size(); i++) {
      for (int j = i + 1; j < this->points.size(); j++) {
        if (!isInsidePolygon(edges, this->points[i], this->points[j]))
          continue;

        unsigned long long dx =
            this->points[i].first > this->points[j].first
                ? this->points[i].first - this->points[j].first
                : this->points[j].first - this->points[i].first;
        unsigned long long dy =
            this->points[i].second > this->points[j].second
                ? this->points[i].second - this->points[j].second
                : this->points[j].second - this->points[i].second;
        unsigned long long distance = (dx + 1) * (dy + 1);
        sol = max(sol, distance);
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
  auto part2TestResult = test2.part2();
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2 test: " << part2TestResult << " (Time: " << duration.count()
       << " μs)" << endl;

  start = chrono::high_resolution_clock::now();
  auto part2Result = aoc.part2();
  end = chrono::high_resolution_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration_ms.count()
       << " ms)" << endl;

  return 0;
}