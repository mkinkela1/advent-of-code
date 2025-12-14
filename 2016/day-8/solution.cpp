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
  vector<vector<bool>> screen{6, vector<bool>(50, false)};
  vector<string> instructions;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->instructions.push_back(line);
    }
  }

  void executeRect(string instruction) {
    int width, height;
    sscanf(instruction.c_str(), "rect %dx%d", &width, &height);
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        this->screen[i][j] = true;
      }
    }
  }

  void executeRotateRow(string instruction) {
    int row, shift;
    sscanf(instruction.c_str(), "rotate row y=%d by %d", &row, &shift);
    vector<bool> newRow(this->screen[row].size(), false);
    for (int i = 0; i < this->screen[row].size(); i++) {
      newRow[(i + shift) % this->screen[row].size()] = this->screen[row][i];
    }
    this->screen[row] = newRow;
  }

  void executeRotateColumn(string instruction) {
    int column, shift;
    sscanf(instruction.c_str(), "rotate column x=%d by %d", &column, &shift);
    vector<bool> newColumn(this->screen.size(), false);
    for (int i = 0; i < this->screen.size(); i++) {
      newColumn[(i + shift) % this->screen.size()] = this->screen[i][column];
    }
    for (int i = 0; i < this->screen.size(); i++) {
      this->screen[i][column] = newColumn[i];
    }
  }

  void executeInstruction(string instruction) {
    if (instruction.find("rect") != string::npos) {
      this->executeRect(instruction);
    } else if (instruction.find("rotate row") != string::npos) {
      this->executeRotateRow(instruction);
    } else if (instruction.find("rotate column") != string::npos) {
      this->executeRotateColumn(instruction);
    }
  }

  auto countPixels() -> int {
    int count = 0;
    for (int i = 0; i < this->screen.size(); i++)
      for (int j = 0; j < this->screen[i].size(); j++)
        count += this->screen[i][j];
    return count;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    for (auto instruction : this->instructions) {
      this->executeInstruction(instruction);
    }
    return this->countPixels();
  }

  auto part2() -> void {
    cout << endl;
    for (int i = 0; i < this->screen.size(); i++) {
      for (int j = 0; j < this->screen[i].size(); j++) {
        cout << (this->screen[i][j] ? '#' : '.');
      }
      cout << endl;
    }
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

  cout << "Part 2: " << endl;
  aoc.part2();

  return 0;
}