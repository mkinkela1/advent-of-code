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

struct Claim {
  int id;
  int x;
  int y;
  int width;
  int height;
  Claim(int id, int x, int y, int width, int height)
      : id(id), x(x), y(y), width(width), height(height) {}
};

class Solution {
private:
  fstream fin;
  vector<Claim> claims;
  int minX = INT_MAX;
  int minY = INT_MAX;
  int maxX = INT_MIN;
  int maxY = INT_MIN;

  void parse() {
    string line;
    int id, x, y, width, height;
    while (getline(this->fin, line)) {
      sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &width, &height);
      this->claims.push_back(Claim(id, x, y, width, height));
      this->minX = min(this->minX, x);
      this->minY = min(this->minY, y);
      this->maxX = max(this->maxX, x + width);
      this->maxY = max(this->maxY, y + height);
    }
  }

  auto areClaimsOverlapping(Claim &c1, Claim &c2) -> bool {
    return c1.x < c2.x + c2.width && c1.x + c1.width > c2.x &&
           c1.y < c2.y + c2.height && c1.y + c1.height > c2.y;
  }

  auto hasOverlappingClaim(Claim &c) -> bool {
    for (auto claim : this->claims) {
      if (claim.id != c.id && this->areClaimsOverlapping(claim, c)) {
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

  auto part1() -> int {
    map<pair<int, int>, int> freq;
    for (auto claim : this->claims) {
      for (int i = claim.x; i < claim.x + claim.width; i++) {
        for (int j = claim.y; j < claim.y + claim.height; j++) {
          freq[{i, j}]++;
        }
      }
    }

    int count = 0;
    for (auto [_, f] : freq) {
      if (f > 1) {
        count++;
      }
    }
    return count;
  }

  auto part2() -> int {
    for (auto claim : this->claims) {
      if (!this->hasOverlappingClaim(claim)) {
        return claim.id;
      }
    }
    return -1;
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
