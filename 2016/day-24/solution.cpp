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

const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
private:
  fstream fin;
  vector<string> grid;
  map<char, pair<int, int>> positions;
  map<pair<char, char>, int> distances;
  string allPositions;

  void parse() {
    string line;
    int x = 0;
    while (getline(this->fin, line)) {
      for (int y = 0; y < line.size(); y++) {
        if (isdigit(line[y])) {
          this->positions[line[y]] = {x, y};
          this->allPositions += line[y];
        }
      }
      this->grid.push_back(line);
      x++;
    }

    this->getDistances();
  }

  auto getDistances() -> void {
    for (auto pos : this->allPositions) {
      this->calculateDistances(pos);
    }
  }

  auto calculateDistances(char pos) -> void {
    auto [x, y] = this->positions[pos];
    queue<pair<int, int>> q;
    map<pair<int, int>, bool> visited;
    map<pair<int, int>, int> distances;
    distances[{x, y}] = 0;
    q.push({x, y});
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (auto [dx, dy] : directions) {
        auto [nx, ny] = make_pair(x + dx, y + dy);
        if (nx < 0 || nx >= this->grid.size() || ny < 0 ||
            ny >= this->grid[0].size()) {
          continue;
        }
        if (this->grid[nx][ny] == '#') {
          continue;
        }
        if (visited[{nx, ny}]) {
          continue;
        }
        q.push({nx, ny});
        visited[{nx, ny}] = true;
        distances[{nx, ny}] = distances[{x, y}] + 1;
      }
    }
    for (auto newPos : this->allPositions) {
      if (newPos == pos) {
        continue;
      }
      auto [x2, y2] = this->positions[newPos];
      this->distances[make_pair(pos, newPos)] = distances[{x2, y2}];
      this->distances[make_pair(newPos, pos)] = distances[{x2, y2}];
    }
  }

  auto solve(string positions, bool endWith0 = false) -> int {
    int minDistance = INT_MAX;
    do {
      int distance = 0;
      distance += this->distances[make_pair('0', positions[0])];
      for (int i = 0; i < positions.size() - 1; i++) {
        distance += this->distances[make_pair(positions[i], positions[i + 1])];
      }
      if (endWith0) {
        distance +=
            this->distances[make_pair(positions[positions.size() - 1], '0')];
      }
      minDistance = min(minDistance, distance);
    } while (next_permutation(positions.begin(), positions.end()));
    return minDistance;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    string positions = "";
    for (auto pos : this->allPositions) {
      if (pos == '0' || !isdigit(pos)) {
        continue;
      }
      positions += pos;
    }

    return this->solve(positions);
  }

  auto part2() -> int { return this->solve(this->allPositions, true); }
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
