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

class Board {
  int id;
  vector<vector<int>> board;
  vector<vector<bool>> marked;

public:
  Board(int id, vector<vector<int>> board) {
    this->id = id;
    this->board = board;
    this->marked = vector<vector<bool>>(board.size(),
                                        vector<bool>(board[0].size(), false));
  }

  auto getId() -> int { return this->id; }

  auto clearMarked() -> void {
    for (int i = 0; i < this->marked.size(); i++) {
      for (int j = 0; j < this->marked[0].size(); j++) {
        this->marked[i][j] = false;
      }
    }
  }

  auto mark(int number) -> void {
    for (int i = 0; i < this->board.size(); i++) {
      for (int j = 0; j < this->board[0].size(); j++) {
        if (this->board[i][j] == number) {
          this->marked[i][j] = true;
        }
      }
    }
  }

  auto isBingo() -> bool {
    for (int i = 0; i < this->board.size(); i++) {
      bool rowBingo = true;
      for (int j = 0; j < this->board[0].size(); j++) {
        if (!this->marked[i][j]) {
          rowBingo = false;
          break;
        }
      }
      if (rowBingo) {
        return true;
      }
    }
    for (int j = 0; j < this->board[0].size(); j++) {
      bool columnBingo = true;
      for (int i = 0; i < this->board.size(); i++) {
        if (!this->marked[i][j]) {
          columnBingo = false;
          break;
        }
      }
      if (columnBingo) {
        return true;
      }
    }
    return false;
  }

  auto score() -> int {
    int score = 0;
    for (int i = 0; i < this->board.size(); i++) {
      for (int j = 0; j < this->board[0].size(); j++) {
        if (!this->marked[i][j]) {
          score += this->board[i][j];
        }
      }
    }
    return score;
  }
};

class Solution {
private:
  fstream fin;
  vector<int> numbers;
  vector<Board> boards;

  void parse() {
    string line;
    int id = 0;
    vector<vector<int>> board;

    getline(this->fin, line);
    vector<string> numbers = split(line, ",");
    for (string number : numbers) {
      this->numbers.push_back(stoi(number));
    }
    getline(this->fin, line);

    while (getline(this->fin, line)) {
      if (line.empty()) {
        if (!board.empty()) {
          this->boards.push_back(Board(id++, board));
          board.clear();
        }
        continue;
      }
      vector<string> numbers = split(line, " ");
      vector<int> row;
      for (string number : numbers) {
        if (number.empty()) {
          continue;
        }
        row.push_back(stoi(number));
      }
      board.push_back(row);
    }
    if (!board.empty()) {
      this->boards.push_back(Board(id++, board));
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> unsigned long long {
    for (int number : this->numbers) {
      for (Board &board : this->boards) {
        board.mark(number);
        if (board.isBingo()) {
          return board.score() * number;
        }
      }
    }
    return 0;
  }

  auto part2() -> unsigned long long {
    for (Board &board : this->boards) {
      board.clearMarked();
    }

    set<int> bingoBoardIds;
    Board *lastBingoBoard = nullptr;
    int lastBingoNumber = -1;

    for (int number : this->numbers) {
      for (Board &board : this->boards) {
        if (bingoBoardIds.find(board.getId()) != bingoBoardIds.end()) {
          continue;
        }
        board.mark(number);
        if (board.isBingo()) {
          bingoBoardIds.insert(board.getId());
          lastBingoBoard = &board;
          lastBingoNumber = number;
        }
      }
    }

    return lastBingoBoard->score() * lastBingoNumber;
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
