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
  vector<vector<string>> phrases;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> words = split(line, " ");
      this->phrases.push_back(words);
    }
  }

  auto hasDuplicateWords(vector<string> phrase) -> bool {
    map<string, int> wordCount;
    for (auto word : phrase) {
      wordCount[word]++;
      if (wordCount[word] > 1)
        return true;
    }
    return false;
  }

  auto hasDuplicatedAnagrams(vector<string> phrase) -> bool {
    map<string, int> wordCount;
    for (auto word : phrase) {
      sort(word.begin(), word.end());
      wordCount[word]++;
      if (wordCount[word] > 1)
        return true;
    }
    return false;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> int {
    int count = 0;
    for (auto phrase : this->phrases) {

      if (!this->hasDuplicateWords(phrase))
        count++;
    }
    return count;
  }

  auto part2() -> int {
    int count = 0;
    for (auto phrase : this->phrases) {
      if (!this->hasDuplicatedAnagrams(phrase))
        count++;
    }
    return count;
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