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

class Instruction {
private:
  string registerToChange;
  bool isIncrement;
  int value;
  string conditionRegister;
  string conditionOperator;
  int conditionValue;

public:
  Instruction(string registerToChange, string operation, int value,
              string conditionRegister, string conditionOperator,
              int conditionValue) {
    this->registerToChange = registerToChange;
    this->isIncrement = operation == "inc";
    this->value = value;
    this->conditionRegister = conditionRegister;
    this->conditionOperator = conditionOperator;
    this->conditionValue = conditionValue;
  }

  auto getRegisterToChange() -> string { return this->registerToChange; }

  auto getIsIncrement() -> bool { return this->isIncrement; }

  auto getValue() -> int { return this->value; }

  auto getConditionRegister() -> string { return this->conditionRegister; }

  auto getConditionOperator() -> string { return this->conditionOperator; }

  auto getConditionValue() -> int { return this->conditionValue; }
};

class Solution {
private:
  fstream fin;
  vector<Instruction> instructions;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, " ");
      this->instructions.push_back(Instruction(parts[0], parts[1],
                                               stoi(parts[2]), parts[4],
                                               parts[5], stoi(parts[6])));
    }
  }

  auto resolveCondition(int conditionRegisterValue, string conditionOperator,
                        int conditionValue) -> bool {

    if (conditionOperator == "<") {
      return conditionRegisterValue < conditionValue;
    } else if (conditionOperator == ">") {
      return conditionRegisterValue > conditionValue;
    } else if (conditionOperator == "<=") {
      return conditionRegisterValue <= conditionValue;
    } else if (conditionOperator == ">=") {
      return conditionRegisterValue >= conditionValue;
    } else if (conditionOperator == "==") {
      return conditionRegisterValue == conditionValue;
    } else if (conditionOperator == "!=") {
      return conditionRegisterValue != conditionValue;
    } else {
      throw "Invalid condition operator";
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    map<string, int> registers;

    for (auto instruction : this->instructions) {
      if (this->resolveCondition(registers[instruction.getConditionRegister()],
                                 instruction.getConditionOperator(),
                                 instruction.getConditionValue())) {
        if (instruction.getIsIncrement()) {
          registers[instruction.getRegisterToChange()] +=
              instruction.getValue();
        } else {
          registers[instruction.getRegisterToChange()] -=
              instruction.getValue();
        }
      }
    }

    return max_element(
               registers.begin(), registers.end(),
               [](const auto &a, const auto &b) { return a.second < b.second; })
        ->second;
  }

  auto part2() -> int {
    map<string, int> registers;
    int maxValue = 0;

    for (auto instruction : this->instructions) {
      if (this->resolveCondition(registers[instruction.getConditionRegister()],
                                 instruction.getConditionOperator(),
                                 instruction.getConditionValue())) {
        if (instruction.getIsIncrement()) {
          registers[instruction.getRegisterToChange()] +=
              instruction.getValue();
          maxValue =
              max(maxValue, registers[instruction.getRegisterToChange()]);
        } else {
          registers[instruction.getRegisterToChange()] -=
              instruction.getValue();
          maxValue =
              max(maxValue, registers[instruction.getRegisterToChange()]);
        }
      }
    }

    return maxValue;
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