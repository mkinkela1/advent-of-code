#include "../../utils/manhattan.h"
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

struct Nanobot {
  long long x;
  long long y;
  long long z;
  long long radius;
};

class Solution {
private:
  fstream fin;
  vector<Nanobot> nanobots;

  void parse() {
    string line;
    long long x, y, z, radius;

    while (getline(this->fin, line)) {
      sscanf(line.c_str(), "pos=<%lld,%lld,%lld>, r=%lld", &x, &y, &z, &radius);
      this->nanobots.push_back({x, y, z, radius});
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    Nanobot maxNanobot = *max_element(
        this->nanobots.begin(), this->nanobots.end(),
        [](const Nanobot &a, const Nanobot &b) { return a.radius < b.radius; });
    int maxInRange = 0;
    for (auto nanobot : this->nanobots) {
      if (manhattan<long long>({nanobot.x, nanobot.y, nanobot.z},
                               {maxNanobot.x, maxNanobot.y, maxNanobot.z}) <=
          maxNanobot.radius) {
        maxInRange++;
      }
    }
    return maxInRange;
  }

  auto part2() -> unsigned long long {
    pair<long long, long long> xRange = {LLONG_MAX, LLONG_MIN};
    pair<long long, long long> yRange = {LLONG_MAX, LLONG_MIN};
    pair<long long, long long> zRange = {LLONG_MAX, LLONG_MIN};

    for (auto nanobot : this->nanobots) {
      xRange.first = min(xRange.first, nanobot.x);
      xRange.second = max(xRange.second, nanobot.x);
      yRange.first = min(yRange.first, nanobot.y);
      yRange.second = max(yRange.second, nanobot.y);
      zRange.first = min(zRange.first, nanobot.z);
      zRange.second = max(zRange.second, nanobot.z);
    }

    long long step = 1;
    while (step <
           max({(xRange.second - xRange.first), (yRange.second - yRange.first),
                (zRange.second - zRange.first)})) {
      step <<= 1;
    }

    long long bestX = 0, bestY = 0, bestZ = 0;
    while (step > 0) {

      int bestCount = 0;
      long long bestDist = LLONG_MAX;

      for (auto x = xRange.first; x <= xRange.second; x += step) {

        for (auto y = yRange.first; y <= yRange.second; y += step) {
          for (auto z = zRange.first; z <= zRange.second; z += step) {

            int count = 0;
            for (auto nanobot : this->nanobots) {
              if (manhattan<long long>({x, y, z},
                                       {nanobot.x, nanobot.y, nanobot.z}) <=
                  nanobot.radius + step - 1) {
                count++;
              }
            }

            long long dist = manhattan<long long>({x, y, z}, {0, 0, 0});
            if (count > bestCount || (count == bestCount && dist < bestDist)) {
              bestCount = count;
              bestDist = dist;
              bestX = x;
              bestY = y;
              bestZ = z;
            }
          }
        }
      }

      xRange.first = bestX - step;
      xRange.second = bestX + step;
      yRange.first = bestY - step;
      yRange.second = bestY + step;
      zRange.first = bestZ - step;
      zRange.second = bestZ + step;

      step >>= 1;
    }

    return manhattan<long long>({bestX, bestY, bestZ});
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