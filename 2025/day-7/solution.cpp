#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
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
  vector<string> input;
  pair<int, int> start;

  void parse() {
    string line;
    int i = 0;
    while (getline(this->fin, line)) {
      this->input.push_back(line);
      for (int j = 0; j < line.size(); j++) {
        if (line[j] == 'S') {
          this->start = {i, j};
        }
      }
      i++;
    }
  }

  auto solve() -> pair<int, unsigned long long> {
    int sol = 0;
    queue<pair<int, int>> q;
    map<pair<int, int>, bool> visited;
    map<pair<int, int>, vector<pair<int, int>>> prev;
    map<pair<int, int>, unsigned long long> total;
    q.push(this->start);
    visited[this->start] = true;
    while (!q.empty()) {
      auto [x, y] = q.front();
      visited[make_pair(x, y)] = true;
      q.pop();

      if (x >= this->input.size() - 1) {
        continue;
      }

      pair<int, int> next = {x + 1, y};
      if (visited[next])
        continue;
      if (this->input[next.first][next.second] == '.' && !visited[next]) {
        q.push(next);
        visited[next] = true;
        prev[next].push_back(make_pair(x, y));
      } else if (this->input[next.first][next.second] == '^') {
        if (!visited[make_pair(next.first, next.second)])
          ++sol;
        if (!visited[make_pair(next.first, next.second - 1)]) {
          q.push(make_pair(next.first, next.second - 1));
        }
        if (!visited[make_pair(next.first, next.second + 1)]) {
          q.push(make_pair(next.first, next.second + 1));
        }
        prev[make_pair(next.first, next.second - 1)].push_back(make_pair(x, y));
        prev[make_pair(next.first, next.second + 1)].push_back(make_pair(x, y));
      }
    }

    unsigned long long totalSum = 0;
    total[this->start] = 1;
    for (int i = 0; i < this->input.size(); i++) {
      for (int j = 0; j < this->input[i].size(); j++) {
        for (auto [x, y] : prev[make_pair(i, j)]) {
          total[make_pair(i, j)] += total[make_pair(x, y)];
        }
      }
    }

    for (int i = 0; i < this->input[0].size(); i++) {
      totalSum += total[make_pair(this->input.size() - 1, i)];
    }

    return {sol, totalSum};
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    auto [sol, totalSum] = this->solve();
    return sol;
  }

  auto part2() -> unsigned long long {
    auto [sol, totalSum] = this->solve();
    return totalSum;
  }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  cout << "Part 1 test: " << test1.part1() << endl;
  cout << "Part 1: " << aoc.part1() << endl;
  cout << "--------------------------" << endl;
  cout << "Part 2 test: " << test2.part2() << endl;
  cout << "Part 2: " << aoc.part2() << endl;

  return 0;
}