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
  map<int, vector<int>> graph;
  set<int> nodes;
  map<int, bool> visited;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> nodes = split(line, " <-> ");

      int startNode = stoi(nodes[0]);
      this->nodes.insert(startNode);
      vector<string> endNodes = split(nodes[1], ", ");
      for (string endNode : endNodes) {
        int endNodeInt = stoi(endNode);
        this->nodes.insert(endNodeInt);
        this->graph[startNode].push_back(endNodeInt);
        this->graph[endNodeInt].push_back(startNode);
      }
    }
  }

  void dfs(int node) {
    this->visited[node] = true;
    for (int neighbor : this->graph[node]) {
      if (!this->visited[neighbor]) {
        this->dfs(neighbor);
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
    this->visited.clear();
    this->dfs(0);
    return this->visited.size();
  }

  auto part2() -> int {
    this->visited.clear();
    int count = 0;
    for (int node : this->nodes) {
      if (!this->visited[node]) {
        this->dfs(node);
        count++;
      }
    }
    return count;
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
