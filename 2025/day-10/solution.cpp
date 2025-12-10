#include "../../utils/split.h"
#include "z3++.h"
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

auto solveButtonProblem(const vector<vector<int>> &A, const vector<int> &B)
    -> vector<int> {
  int N = A.size();                    // number of counters (rows)
  int M = A.empty() ? 0 : A[0].size(); // number of buttons (columns)
  std::vector<int> result(M, 0);       // default return if no solution

  if (N == 0 || M == 0)
    return result;

  z3::context ctx;
  z3::optimize opt(ctx);

  // Create integer variables x0..xM-1
  std::vector<z3::expr> x;
  x.reserve(M);
  for (int i = 0; i < M; ++i)
    x.push_back(ctx.int_const(("x" + std::to_string(i)).c_str()));

  // Constraints: x[i] >= 0
  for (int i = 0; i < M; ++i)
    opt.add(x[i] >= 0);

  // Constraints: A * x = B
  for (int r = 0; r < N; ++r) {
    z3::expr sum = ctx.int_val(0);
    for (int c = 0; c < M; ++c)
      sum = sum + A[r][c] * x[c];
    opt.add(sum == B[r]);
  }

  // Objective: minimize total clicks
  z3::expr total = ctx.int_val(0);
  for (int i = 0; i < M; ++i)
    total = total + x[i];
  opt.minimize(total);

  if (opt.check() == z3::sat) {
    z3::model m = opt.get_model();
    for (int i = 0; i < M; ++i) {
      result[i] = m.eval(x[i]).get_numeral_int();
    }
  } else {
    std::cerr << "No solution found.\n";
  }

  return result;
}

class Lights {
private:
  unsigned long long lights;
  vector<vector<int>> indices;
  vector<int> joltages;

  auto equals(vector<int> a, vector<int> b) -> bool {
    for (int i = 0; i < a.size(); i++) {
      if (a[i] != b[i]) {
        return false;
      }
    }
    return true;
  }

  auto check(vector<int> newJoltages, vector<int> joltages) -> bool {
    for (int i = 0; i < newJoltages.size(); i++) {
      if (newJoltages[i] > joltages[i]) {
        return false;
      }
    }
    return true;
  }

public:
  Lights(string arrangement, vector<vector<int>> indices,
         vector<int> joltages) {
    this->indices = indices;
    this->joltages = joltages;
    this->lights = 0ULL;
    for (int i = 0; i < arrangement.size(); i++) {
      if (arrangement[i] == '#') {
        this->lights |= 1LL << i;
      }
    }
  }

  auto getLights() -> unsigned long long { return this->lights; }

  auto setLight(vector<int> indices, unsigned long long currentLights)
      -> unsigned long long {
    unsigned long long newLights = currentLights;
    for (int index : indices) {
      if (currentLights & (1ULL << index)) {
        newLights &= ~(1ULL << index);
      } else {
        newLights |= 1ULL << index;
      }
    }
    return newLights;
  }

  auto solveSwitches() -> unsigned long long {
    queue<pair<unsigned long long, unsigned long long>> q;
    map<unsigned long long, bool> visited;

    q.push(make_pair(0, 0ULL));

    while (!q.empty()) {
      auto [current, dist] = q.front();
      q.pop();

      if (current == this->lights) {
        return dist;
      }

      if (visited[current])
        continue;
      visited[current] = true;

      for (int i = 0; i < this->indices.size(); i++) {
        auto newLights = this->setLight(this->indices[i], current);
        if (visited[newLights])
          continue;
        q.push(make_pair(newLights, dist + 1ULL));
      }
    }

    return 0ULL;
  }

  auto solveJoltages() -> unsigned long long {
    vector<vector<int>> A(this->joltages.size(),
                          vector<int>(this->indices.size(), 0));
    vector<int> B = this->joltages;

    for (int col = 0; col < this->indices.size(); col++) {
      for (auto row : this->indices[col]) {
        A[row][col] = 1;
      }
    }

    auto solution = solveButtonProblem(A, B);
    unsigned long long ans = 0;
    for (int i = 0; i < solution.size(); i++) {
      ans += solution[i];
    }

    return ans;
  }
};

class Solution {
private:
  fstream fin;
  vector<Lights> lights;

  void parse() {
    string line;

    while (getline(this->fin, line)) {
      vector<string> parts = split(line, " ");
      string arrangement = parts[0].substr(1, parts[0].size() - 2);

      vector<int> joltages;
      vector<string> joltageParts = split(
          parts[parts.size() - 1].substr(1, parts[parts.size() - 1].size() - 2),
          ",");
      for (string joltage : joltageParts) {
        joltages.push_back(stoi(joltage));
      }

      vector<vector<int>> indices;
      for (int i = 1; i < parts.size() - 1; i++) {
        vector<string> indexParts =
            split(parts[i].substr(1, parts[i].size() - 2), ",");
        vector<int> index;
        for (string indexPart : indexParts) {
          index.push_back(stoi(indexPart));
        }
        indices.push_back(index);
      }

      this->lights.push_back(Lights(arrangement, indices, joltages));
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> unsigned long long {
    unsigned long long ans = 0;
    for (auto light : this->lights) {
      ans += light.solveSwitches();
    }
    return ans;
  }

  auto part2() -> unsigned long long {
    unsigned long long ans = 0;
    for (auto light : this->lights) {
      ans += light.solveJoltages();
    }
    return ans;
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