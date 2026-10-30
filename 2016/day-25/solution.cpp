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

enum Operation { CPY, INC, DEC, JNZ, OUT };

class Assembunny {
private:
  vector<tuple<Operation, string, string>> instructions;
  map<string, int> registers;

public:
  Assembunny() {
    this->instructions = vector<tuple<Operation, string, string>>();
    this->registers = map<string, int>();
    this->registers["a"] = 0;
    this->registers["b"] = 0;
    this->registers["c"] = 0;
    this->registers["d"] = 0;
  }

  auto clear() -> void {
    this->registers.clear();
    this->registers["a"] = 0;
    this->registers["b"] = 0;
    this->registers["c"] = 0;
    this->registers["d"] = 0;
  }

  auto setRegister(string reg, int value) -> void {
    this->registers[reg] = value;
  }

  auto execute() -> bool {
    int numberOfOuts = 0, lastOutput = 0, pos = 0;
    while (pos < this->instructions.size()) {
      auto [op, arg1, arg2] = this->instructions[pos];

      switch (op) {
      case Operation::CPY:
        if (registers.find(arg2) != registers.end()) {
          if (registers.find(arg1) != registers.end()) {
            registers[arg2] = registers[arg1];
          } else {
            registers[arg2] = stoi(arg1);
          }
        }
        ++pos;
        break;
      case Operation::INC:
        if (registers.find(arg1) != registers.end()) {
          registers[arg1]++;
        }
        ++pos;
        break;
      case Operation::DEC:
        if (registers.find(arg1) != registers.end()) {
          registers[arg1]--;
        }
        ++pos;
        break;
      case Operation::JNZ:
        if (registers.find(arg1) != registers.end()) {
          if (registers[arg1] != 0)
            pos += stoi(arg2);
          else
            ++pos;
        } else {
          if (stoi(arg1) != 0)
            pos += stoi(arg2);
          else
            ++pos;
        }
        break;
      case Operation::OUT:
        if (numberOfOuts == 0) {
          int out = registers[arg1];
          if (out != 0) {
            return false;
          }
          lastOutput = out;
          ++numberOfOuts;
          ++pos;
        } else {
          int out = registers[arg1];
          if (out < 0 || out > 1) {
            return false;
          }
          if (out == lastOutput) {
            return false;
          }
          lastOutput = out;
          ++numberOfOuts;
          ++pos;

          if (numberOfOuts >= 10) {
            return true;
          }
        }
        break;
      }
    }
    return false;
  }

  auto addInstruction(string instruction) -> void {
    char arg1[20], arg2[20];
    if (instruction.find("cpy") != string::npos) {
      sscanf(instruction.c_str(), "cpy %s %s", arg1, arg2);
      this->instructions.push_back(make_tuple(Operation::CPY, arg1, arg2));
    } else if (instruction.find("inc") != string::npos) {
      sscanf(instruction.c_str(), "inc %s", arg1);
      this->instructions.push_back(make_tuple(Operation::INC, arg1, ""));
    } else if (instruction.find("dec") != string::npos) {
      sscanf(instruction.c_str(), "dec %s", arg1);
      this->instructions.push_back(make_tuple(Operation::DEC, arg1, ""));
    } else if (instruction.find("jnz") != string::npos) {
      sscanf(instruction.c_str(), "jnz %s %s", arg1, arg2);
      this->instructions.push_back(make_tuple(Operation::JNZ, arg1, arg2));
    } else if (instruction.find("out") != string::npos) {
      sscanf(instruction.c_str(), "out %s", arg1);
      this->instructions.push_back(make_tuple(Operation::OUT, arg1, ""));
    }
  }
};

class Solution {
private:
  fstream fin;
  Assembunny assembunny;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->assembunny.addInstruction(line);
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->assembunny = Assembunny();
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    for (int a = 0; a < 100000; a++) {
      this->assembunny.clear();
      this->assembunny.setRegister("a", a);
      if (this->assembunny.execute()) {
        return a;
      }
    }
    return -1;
  }

  auto part2() -> string { return "Not implemented"; }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");

  auto start = chrono::high_resolution_clock::now();
  auto part1Result = aoc.part1();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 1: " << part1Result << " (Time: " << duration.count() << " μs)"
       << endl;

  return 0;
}
