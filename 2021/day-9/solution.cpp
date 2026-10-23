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

const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
private:
  fstream fin;
  vector<vector<int>> grid;
  map<pair<int, int>, bool> visited;

  void parse() {
    string line;

    while (getline(this->fin, line)) {
      vector<int> row;
      for (char c : line) {
        row.push_back(c - '0');
      }
      this->grid.push_back(row);
    }
  }

  auto isLowPoint(int i, int j) -> bool {
    for (auto [di, dj] : directions) {
      int ni = i + di;
      int nj = j + dj;
      if (ni < 0 || ni >= this->grid.size() || nj < 0 ||
          nj >= this->grid[i].size()) {
        continue;
      }
      if (this->grid[ni][nj] <= this->grid[i][j]) {
        return false;
      }
    }
    return true;
  }

  auto bfs(pair<int, int> start) -> long long unsigned {
    queue<pair<int, int>> q;
    q.push(start);
    this->visited[start] = true;
    long long unsigned size = 0;
    while (!q.empty()) {
      auto [i, j] = q.front();
      this->visited[{i, j}] = true;
      q.pop();
      size++;
      for (auto [di, dj] : directions) {
        int ni = i + di;
        int nj = j + dj;
        if (ni < 0 || ni >= this->grid.size() || nj < 0 ||
            nj >= this->grid[i].size()) {
          continue;
        }
        if (this->visited[{ni, nj}]) {
          continue;
        }
        if (this->grid[ni][nj] == 9) {
          continue;
        }
        q.push({ni, nj});
        this->visited[{ni, nj}] = true;
      }
    }
    return size;
  }

  auto findLowPoints() -> vector<pair<int, int>> {
    vector<pair<int, int>> lowPoints;
    for (int i = 0; i < this->grid.size(); i++) {
      for (int j = 0; j < this->grid[i].size(); j++) {
        if (this->isLowPoint(i, j)) {
          lowPoints.push_back({i, j});
        }
      }
    }
    return lowPoints;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    vector<pair<int, int>> lowPoints = this->findLowPoints();
    return accumulate(lowPoints.begin(), lowPoints.end(), 0LL,
                      [this](long long unsigned sum, pair<int, int> p) {
                        return sum + this->grid[p.first][p.second] + 1LL;
                      });
  }

  auto part2() -> long long unsigned {
    vector<long long unsigned> sizes;
    vector<pair<int, int>> lowPoints = this->findLowPoints();
    for (auto [i, j] : lowPoints) {
      unsigned long long size = this->bfs({i, j});
      sizes.push_back(size);
    }
    sort(sizes.begin(), sizes.end(), greater<long long unsigned>());
    return sizes[0] * sizes[1] * sizes[2];
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
