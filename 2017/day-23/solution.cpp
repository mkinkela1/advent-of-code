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

enum OperationType { SET, SUB, MUL, JNZ };

struct Operation {
  OperationType op;
  int x, y;

  Operation(string op, int x, int y) {
    if (op == "set") {
      this->op = SET;
    } else if (op == "sub") {
      this->op = SUB;
    } else if (op == "mul") {
      this->op = MUL;
    } else if (op == "jnz") {
      this->op = JNZ;
    }
    this->x = x;
    this->y = y;
  }
};

class Solution {
private:
  fstream fin;
  vector<Operation> ops;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      auto parts = split(line, " ");
      this->ops.push_back(Operation(parts[0], stoi(parts[1]), stoi(parts[2])));
    }
  }

  auto debug() -> int {
    int mulTimes = 0, idx = 0;
    map<string, int> registers;
    registers["a"] = 0;
    registers["b"] = 0;
    registers["c"] = 0;
    registers["d"] = 0;
    registers["e"] = 0;
    registers["f"] = 0;
    registers["g"] = 0;
    registers["h"] = 0;

    while (idx < this->ops.size()) {
      auto op = this->ops[idx];

      switch (op.op) {
      case SET:
        registers[op.x] = op.y;
        ++idx;
        break;
      case SUB:
        registers[op.x] -= op.y;
        ++idx;
        break;
      case MUL:
        registers[op.x] *= op.y;
        mulTimes++;
        ++idx;
        break;
      case JNZ:
        if (registers[op.x] != 0) {
          idx += op.y;
        } else {
          ++idx;
        }
        break;
      default:
        throw runtime_error("Invalid operation: " + op.op);
      }
    }

    return mulTimes;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int { return this->debug(); }

  auto part2() -> string { return "Not implemented"; }
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
