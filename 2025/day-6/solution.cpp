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
  vector<vector<unsigned long long>> problems;
  vector<string> operations;
  vector<string> input;

  void parse() {
    string line;
    vector<vector<unsigned long long>> grid;
    while (getline(this->fin, line)) {
      this->input.push_back(line);
      if (line.find("*") == string::npos) {
        vector<string> parts = split(line, " ");
        vector<unsigned long long> problem;
        for (auto part : parts) {
          if (isdigit(part[0])) {
            problem.push_back(stoull(part));
          }
        }
        grid.push_back(problem);
      } else {
        vector<string> parts = split(line, " ");
        for (auto part : parts) {
          if (part == "+" || part == "*") {
            this->operations.push_back(part);
          }
        }
      }
    }

    for (int i = 0; i < grid[0].size(); i++) {
      this->problems.push_back(vector<unsigned long long>(grid.size()));
    }

    for (int i = 0; i < grid[0].size(); i++) {
      for (int j = 0; j < grid.size(); j++) {
        this->problems[i][j] = grid[j][i];
      }
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> unsigned long long {
    unsigned long long sol = 0;
    for (int i = 0; i < this->problems.size(); i++) {
      if (this->operations[i] == "+") {
        unsigned long long total = 0;
        for (int j = 0; j < this->problems[i].size(); j++) {
          total += this->problems[i][j];
        }
        sol += total;
      } else {
        unsigned long long total = 1;
        for (int j = 0; j < this->problems[i].size(); j++) {
          total *= this->problems[i][j];
        }
        sol += total;
      }
    }

    return sol;
  }

  auto part2() -> unsigned long long {
    unsigned long long sol = 0;
    char operation;
    vector<unsigned long long> numbers;

    for (int i = this->input[0].size() - 1; i >= 0; i--) {
      bool isAllEmpty = true;
      unsigned long long number = 0;
      for (int j = 0; j < this->input.size(); j++) {
        if (this->input[j][i] != ' ')
          isAllEmpty = false;
        if (isdigit(this->input[j][i]))
          number = number * 10 + (this->input[j][i] - '0');
        if (j == this->input.size() - 1 && !isAllEmpty) {
          numbers.push_back(number);
          number = 0;
        }
        if (this->input[j][i] == '+' || this->input[j][i] == '*') {
          operation = this->input[j][i];
          if (operation == '+') {
            unsigned long long total = 0;
            for (int k = 0; k < numbers.size(); k++) {
              total += numbers[k];
            }
            sol += total;
          } else {
            unsigned long long total = 1;
            for (int k = 0; k < numbers.size(); k++) {
              total *= numbers[k];
            }
            sol += total;
          }
          numbers.clear();
          operation = ' ';
        }
      }
    }
    return sol;
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