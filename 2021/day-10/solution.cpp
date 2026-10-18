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

const map<char, int> ILLEGAL_CHAR_SCORE = {
    {'\0', 0}, {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137},
};

const map<char, int> CLOSING_CHAR_SCORE = {
    {')', 1},
    {']', 2},
    {'}', 3},
    {'>', 4},
};

const map<char, char> CLOSING_CHAR_MAP = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
    {'<', '>'},
};

class Solution {
private:
  fstream fin;
  vector<string> lines;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->lines.push_back(line);
    }
    this->fin.close();
  }

  auto findMissingClosingChar(string line) -> char {
    stack<char> s;
    for (char currentChar : line) {
      if (currentChar == '(' || currentChar == '[' || currentChar == '{' ||
          currentChar == '<') {
        s.push(currentChar);
      } else {
        if (s.empty()) {
          return currentChar;
        }
        char top = s.top();
        if (CLOSING_CHAR_MAP.at(top) != currentChar) {
          return currentChar;
        } else {
          s.pop();
        }
      }
    }
    return '\0';
  }

  auto findMissingClosingCharScore(char c) -> int {
    return ILLEGAL_CHAR_SCORE.at(c);
  }

  auto generateClosingCharScore(string line) -> long long {
    stack<char> s;
    for (char currentChar : line) {
      if (currentChar == '(' || currentChar == '[' || currentChar == '{' ||
          currentChar == '<') {
        s.push(currentChar);
      } else {
        const char top = s.top();
        if (CLOSING_CHAR_MAP.at(top) != currentChar) {
          return 0;
        } else {
          s.pop();
        }
      }
    }

    long long score = 0;
    while (!s.empty()) {
      char top = s.top();
      score = score * 5 + CLOSING_CHAR_SCORE.at(CLOSING_CHAR_MAP.at(top));
      s.pop();
    }
    return score;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> long long {
    long long score = 0;
    for (string line : this->lines) {
      char illegalChar = findMissingClosingChar(line);
      if (illegalChar != '\0') {
        score += findMissingClosingCharScore(illegalChar);
      }
    }
    return score;
  }

  auto part2() -> long long {
    vector<long long> scores;
    for (string line : this->lines) {
      long long score = generateClosingCharScore(line);
      if (score != 0) {
        scores.push_back(score);
      }
    }
    sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
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
