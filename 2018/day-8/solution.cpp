#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int nodeId = 0;

struct Node {
  int id;
  int numChildren;
  int numMetadata;
  vector<Node *> children;
  vector<int> metadata;

  Node(int numChildren, int numMetadata) {
    this->numChildren = numChildren;
    this->numMetadata = numMetadata;
    this->id = nodeId++;
  }
};

class Solution {
private:
  fstream fin;
  vector<int> numbers;
  vector<long long> metadata;
  int index = 0;
  Node *root = nullptr;

  void parse() {
    string line;

    while (getline(this->fin, line)) {
      vector<string> data = split(line, " ");
      for (string number : data) {
        this->numbers.push_back(stoi(number));
      }
    }

    this->root = generateTree();
  }

  auto generateTree() -> Node * {
    int numChildren = this->numbers[this->index++];
    int numMetadata = this->numbers[this->index++];

    Node *node = new Node(numChildren, numMetadata);
    for (int i = 0; i < numChildren; i++) {
      node->children.push_back(generateTree());
    }
    for (int i = 0; i < numMetadata; i++) {
      long long metadata = this->numbers[this->index++];
      this->metadata.push_back(metadata);
      node->metadata.push_back(metadata);
    }

    return node;
  }

  auto getValue(Node *node) -> long long {
    if (node->numChildren == 0) {
      return accumulate(node->metadata.begin(), node->metadata.end(), 0LL);
    }
    long long sum = 0;
    for (int metadata : node->metadata) {
      int index = metadata - 1;
      if (index >= node->numChildren || index < 0) {
        continue;
      }
      sum += getValue(node->children[index]);
    }
    return sum;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> long long {
    return accumulate(this->metadata.begin(), this->metadata.end(), 0LL);
  }

  auto part2() -> long long { return getValue(this->root); }
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
