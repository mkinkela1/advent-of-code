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

const pair<int, int> directions[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
private:
  fstream fin;
  vector<vector<int>> grid;

  void parse() {
    string line;
    vector<int> row;
    while (getline(this->fin, line)) {
      for (auto c : line) {
        row.push_back(c - '0');
      }
      this->grid.push_back(row);
      row.clear();
    }
  }

  auto dijkstra(vector<vector<int>> grid) -> int {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>>
        pq;
    map<pair<int, int>, bool> visited;
    pq.push({0, {0, 0}});
    while (!pq.empty()) {
      auto [cost, pos] = pq.top();
      pq.pop();
      if (visited[pos]) {
        continue;
      }
      visited[pos] = true;
      if (pos == make_pair(grid.size() - 1, grid[0].size() - 1)) {
        return cost;
      }
      for (auto [dx, dy] : directions) {
        auto [nx, ny] = make_pair(pos.first + dx, pos.second + dy);
        if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) {
          continue;
        }
        if (visited[make_pair(nx, ny)]) {
          continue;
        }
        pq.push({cost + grid[nx][ny], {nx, ny}});
      }
    }

    return -1;
  }

  auto getRisk(vector<vector<int>> grid, int i, int j, int x, int y) -> int {
    if (i == 0 && j == 0) {
      return grid[x][y];
    }

    int currentRisk = grid[x][y] + i + j;
    if (currentRisk > 9) {
      return currentRisk - 9;
    }
    return currentRisk;
  }

  auto magnifyGrid(vector<vector<int>> grid) -> vector<vector<int>> {
    vector<vector<int>> newGrid(grid.size() * 5,
                                vector<int>(grid[0].size() * 5));
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        for (int x = 0; x < grid.size(); x++) {
          for (int y = 0; y < grid[0].size(); y++) {
            newGrid[i * grid.size() + x][j * grid[0].size() + y] =
                this->getRisk(grid, i, j, x, y);
          }
        }
      }
    }
    return newGrid;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int { return this->dijkstra(this->grid); }

  auto part2() -> int {
    vector<vector<int>> grid = this->magnifyGrid(this->grid);
    return this->dijkstra(grid);
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
