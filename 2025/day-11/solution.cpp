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

  auto countPaths(string current, string end,
                  map<string, vector<string>> &graph,
                  map<string, long long unsigned> &memo) -> long long unsigned {

    if (memo.find(current) != memo.end()) {
      return memo[current];
    }
    if (current == end) {
      return memo[current] = 1LLU;
    }
    long long unsigned ret = 0LLU;
    for (string child : graph[current]) {
      ret += this->countPaths(child, end, graph, memo);
    }
    return memo[current] = ret;
  }

  auto countTotalPaths(vector<string> nodes) -> long long unsigned {
    map<string, long long unsigned> memo;
    long long unsigned middlePaths =
        this->countPaths(nodes[1], nodes[2], this->graph, memo);

    if (middlePaths == 0) {
      return 0LLU;
    }

    memo.clear();
    long long unsigned startPaths =
        this->countPaths(nodes[0], nodes[1], this->graph, memo);

    memo.clear();
    long long unsigned endPaths =
        this->countPaths(nodes[2], nodes[3], this->graph, memo);

    return startPaths * middlePaths * endPaths;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> long long unsigned {
    map<string, long long unsigned> memo;
    return this->countPaths("you", "out", this->graph, memo);
  }

  auto part2() -> long long unsigned {
    auto totalPaths =
        this->countTotalPaths(vector<string>{"svr", "fft", "dac", "out"});
    if (totalPaths > 0) {
      return totalPaths;
    }

    return this->countTotalPaths(vector<string>{"svr", "dac", "fft", "out"});
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