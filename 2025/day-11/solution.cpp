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
  map<string, vector<string>> graph;
  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> tokens = split(line, ": ");
      string node = tokens[0];
      vector<string> edges = split(tokens[1], " ");
      for (string edge : edges) {
        this->graph[node].push_back(edge);
      }
    }
  }

  auto findDifferentPaths(string start, map<string, vector<string>> graph)
      -> int {
    int ret = 0;
    queue<string> q;
    q.push(start);
    while (!q.empty()) {
      string current = q.front();
      q.pop();
      if (current == "out") {
        ret++;
      }
      for (string neighbor : graph[current]) {
        if (neighbor == "out") {
          ret++;
        } else {
          q.push(neighbor);
        }
      }
    }
    return ret;
  }

  auto findDifferentPathsContainingNodes(
      string current, bool passedDac, bool passedFft,
      map<string, vector<string>> graph,
      map<tuple<string, bool, bool>, long long> &memo) -> long long {
    if (memo[{current, passedDac, passedFft}] != -1)
      return memo[{current, passedDac, passedFft}];
    if (current == "out")
      return memo[{current, passedDac, passedFft}] =
                 (passedDac && passedFft) ? 1LL : 0LL;

    long long ret = 0LL;
    for (string neighbor : graph[current]) {
      int nextPassedDac = passedDac;
      int nextPassedFft = passedFft;
      if (neighbor == "dac")
        nextPassedDac = true;
      else if (neighbor == "fft")
        nextPassedFft = true;

      ret += this->findDifferentPathsContainingNodes(
          neighbor, nextPassedDac, nextPassedFft, graph, memo);
    }
    return memo[{current, passedDac, passedFft}] = ret;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int { return this->findDifferentPaths("you", this->graph); }

  auto part2() -> long long {
    map<tuple<string, bool, bool>, long long> memo;
    for (auto [node, neighbors] : this->graph) {
      memo[{node, false, false}] = -1;
      memo[{node, true, false}] = -1;
      memo[{node, false, true}] = -1;
      memo[{node, true, true}] = -1;
      for (string neighbor : neighbors) {
        memo[{neighbor, false, false}] = -1;
        memo[{neighbor, true, false}] = -1;
        memo[{neighbor, false, true}] = -1;
        memo[{neighbor, true, true}] = -1;
      }
    }
    return this->findDifferentPathsContainingNodes("svr", false, false,
                                                   this->graph, memo);
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