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

struct Worker {
  bool isFree;
  char step;
  int time;

  Worker(bool isFree, char step, int time) {
    this->isFree = isFree;
    this->step = step;
    this->time = time;
  }
};

class Solution {
private:
  fstream fin;
  map<char, set<char>> dependencies;
  set<char> steps;

  void parse() {
    string line;
    char dependency, step;
    while (getline(this->fin, line)) {
      sscanf(line.c_str(), "Step %c must be finished before step %c can begin.",
             &dependency, &step);
      this->dependencies[dependency].insert(step);
      this->steps.insert(dependency);
      this->steps.insert(step);
    }
  }

  auto topologicalSort() -> string {
    map<char, int> inDegree;

    for (auto [step, dependencies] : this->dependencies) {
      for (auto dependency : dependencies) {
        inDegree[dependency]++;
      }
    }

    priority_queue<char, vector<char>, greater<char>> q;
    for (auto [step, dependencies] : this->dependencies) {
      if (inDegree[step] == 0) {
        q.push(step);
      }
    }

    string sol = "";
    while (!q.empty()) {
      auto u = q.top();
      q.pop();
      sol += u;
      for (auto v : this->dependencies[u]) {
        inDegree[v]--;
        if (inDegree[v] == 0) {
          q.push(v);
        }
      }
    }
    return sol;
  }

  auto topologicalSortWithTime(int timeLimit, int numWorkers) -> int {
    map<char, int> inDegree;
    map<char, int> time;
    for (auto [step, dependencies] : this->dependencies) {
      for (auto dependency : dependencies) {
        inDegree[dependency]++;
      }
    }

    priority_queue<char, vector<char>, greater<char>> available;
    for (auto [step, dependencies] : this->dependencies) {
      if (inDegree[step] == 0) {
        available.push(step);
        time[step] = step - 'A' + 1;
      }
    }

    vector<pair<char, int>> workers(numWorkers);
    set<char> completed;
    int time = 0;

    while (completed.size() < this->steps.size()) {
    }

    return 0;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> string { return this->topologicalSort(); }

  auto part2(int timeLimit, int numWorkers) -> int {
    return this->topologicalSortWithTime(timeLimit, numWorkers);
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
