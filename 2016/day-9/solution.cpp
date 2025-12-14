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
  vector<string> data;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->data.push_back(line);
    }
  }

  auto decompress(string data) -> int {
    int sol = 0;
    int pos = 0;
    while (pos < data.size()) {
      if (data[pos] == '(') {
        int xPos = data.find('x', pos);
        int charactersToRepeat = stoi(data.substr(pos + 1, xPos));
        int repeat = stoi(data.substr(xPos + 1, data.find(')', pos)));
        sol += repeat * charactersToRepeat;
        pos = data.find(')', pos) + charactersToRepeat + 1;
      } else {
        sol++;
        pos++;
      }
    }

    return sol;
  }

  auto canDecompress(string data) -> bool {
    return data.find('(') != string::npos;
  }

  auto decompress2(string data) -> unsigned long long {
    vector<int> weights(data.size(), 1);
    int pos = 0;
    unsigned long long sol = 0LLU;
    while (pos < data.size()) {
      if (data[pos] == '(') {
        int xPos = data.find('x', pos);
        int closePos = data.find(')', pos);
        int charactersToRepeat = stoi(data.substr(pos + 1, xPos));
        int repeat = stoi(data.substr(xPos + 1, closePos));
        for (int i = 0; i < charactersToRepeat; i++) {
          weights[closePos + 1 + i] *= repeat;
        }
        pos = closePos + 1;
      } else {
        sol += weights[pos++];
      }
    }

    return sol;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int sol = 0;
    for (auto line : this->data) {
      sol += this->decompress(line);
    }
    return sol;
  }

  auto part2() -> unsigned long long {
    unsigned long long sol = 0LLU;
    for (auto line : this->data) {
      sol += this->decompress2(line);
    }
    return sol;
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