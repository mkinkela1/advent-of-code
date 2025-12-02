#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
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

class Solution {
private:
  fstream fin;
  vector<pair<long long, long long>> ranges;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, ",");
      for (auto part : parts) {
        vector<string> range = split(part, "-");
        this->ranges.push_back(make_pair(stol(range[0]), stol(range[1])));
      }
    }
  }

  auto hasRepeatingHalf(long long number) -> bool {
    int digits = to_string(number).size();

    if (digits % 2 == 1)
      return false;

    long long half = digits / 2;
    string firstHalf = to_string(number).substr(0, half);
    string secondHalf = to_string(number).substr(half);

    return firstHalf == secondHalf;
  }

  auto hasRepeatingDigits(long long number) -> bool {
    string s = to_string(number);

    for (int i = 1; i < s.size(); i++) {
      string substr = s.substr(0, i);

      if (s.size() % substr.size() == 0) {
        string repeated = "";
        for (int k = 0; k < s.size() / substr.size(); k++) {
          repeated += substr;
        }
        if (repeated == s)
          return true;
      }
    }
    return false;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> long long {
    set<long long> valid;
    long long sum = 0;
    for (auto range : this->ranges) {
      for (long long i = range.first; i <= range.second; i++) {
        if (valid.find(i) != valid.end())
          continue;

        if (this->hasRepeatingHalf(i))
          sum += i;
        else
          valid.insert(i);
      }
    }

    return sum;
  }

  auto part2() -> long long {
    long long sum = 0;
    set<long long> valid;
    for (auto range : this->ranges) {
      for (long long i = range.first; i <= range.second; i++) {
        if (valid.find(i) != valid.end())
          continue;

        if (this->hasRepeatingDigits(i))
          sum += i;
        else
          valid.insert(i);
      }
    }

    return sum;
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