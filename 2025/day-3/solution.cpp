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
  vector<string> data;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      this->data.push_back(line);
    }
  }

  auto generateBiggestNumber(string number, int index, int numberOfDigitsToTake,
                             unsigned long long currentNumber = 0)
      -> unsigned long long {
    if (numberOfDigitsToTake == 0)
      return currentNumber;

    if (index >= number.size() || index + numberOfDigitsToTake > number.size())
      return 0;

    int biggestDigit = number[index] - '0';
    int biggestDigitIndex = index;
    for (int i = 0; i < number.size(); i++) {
      if (index + i + numberOfDigitsToTake > number.size())
        break;
      if ((number[index + i] - '0') > biggestDigit &&
          index + i + numberOfDigitsToTake <= number.size()) {
        biggestDigit = (number[index + i] - '0');
        biggestDigitIndex = index + i;
      }
    }

    return this->generateBiggestNumber(number, biggestDigitIndex + 1,
                                       numberOfDigitsToTake - 1,
                                       currentNumber * 10ULL + biggestDigit);
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> unsigned long long {
    unsigned long long sum = 0;
    for (auto number : this->data) {
      unsigned long long biggestNumber =
          this->generateBiggestNumber(number, 0, 2);
      sum += biggestNumber;
    }
    return sum;
  }

  auto part2() -> unsigned long long {
    unsigned long long sum = 0;
    for (auto number : this->data) {
      unsigned long long biggestNumber =
          this->generateBiggestNumber(number, 0, 12);
      sum += biggestNumber;
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