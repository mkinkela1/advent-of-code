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
  string grid;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->grid = line;
    }
  }

  auto generateNextCell(string currentRow, int index) -> char {
    char left = index - 1 < 0 ? '.' : currentRow[index - 1];
    char center = currentRow[index];
    char right = index + 1 >= currentRow.size() ? '.' : currentRow[index + 1];

    if (left == '^' && center == '^' && right == '.') {
      return '^';
    }
    if (center == '^' && right == '^' && left == '.') {
      return '^';
    }
    if (left == '^' && center == '.' && right == '.') {
      return '^';
    }
    if (right == '^' && center == '.' && left == '.') {
      return '^';
    }

    return '.';
  }

  auto generateNextRow(string currentRow) -> string {
    string nextRow = "";
    for (int i = 0; i < currentRow.size(); i++) {
      nextRow += this->generateNextCell(currentRow, i);
    }
    return nextRow;
  }

  auto countSafeCells(string row) -> int {
    int count = 0;
    for (char cell : row) {
      if (cell == '.') {
        count++;
      }
    }
    return count;
  }

  auto solve(int rows) -> int {
    string currentRow = this->grid;
    int safeCells = this->countSafeCells(currentRow);
    for (int i = 1; i < rows; i++) {
      currentRow = this->generateNextRow(currentRow);
      safeCells += this->countSafeCells(currentRow);
    }
    return safeCells;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int rows = 40) -> int { return this->solve(rows); }

  auto part2() -> int { return this->solve(400000); }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");

  auto start = chrono::high_resolution_clock::now();
  auto part1TestResult = test1.part1(10);
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
