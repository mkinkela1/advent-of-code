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

class Node {
private:
  string name;
  vector<Node> children;

public:
  Node(string name) { this->name = name; }

  auto getName() -> string { return this->name; }

  auto getChildren() -> vector<Node> { return this->children; }

  auto addChild(Node child) -> void { this->children.push_back(child); }

  auto removeChild(Node child) -> void {
    this->children.erase(
        find(this->children.begin(), this->children.end(), child));
  }

  bool operator==(const Node &other) const { return this->name == other.name; }
};

class Solution {
private:
  fstream fin;
  map<string, vector<string>> data;
  map<string, int> weights;
  map<string, uint64_t> sumWeights;

  void parse() {
    string line;

    while (getline(this->fin, line)) {
      if (line.empty())
        continue;

      char name[101], output[1001];
      int weight;

      if (line.find(" -> ") != string::npos) {
        sscanf(line.c_str(), "%s (%d) -> %[^\n]", name, &weight, output);
        vector<string> parts = split(output, ", ");
        this->weights[name] = weight;
        this->data[name] = parts;
      } else {
        sscanf(line.c_str(), "%s (%d)", name, &weight);
        this->weights[name] = weight;
        this->data[name] = vector<string>();
      }
    }
  }

  auto getRoot() -> string {
    map<string, bool> isChild;
    for (auto &[name, children] : this->data) {
      for (auto &child : children) {
        isChild[child] = true;
      }
    }
    for (auto &[name, children] : this->data) {
    }
    for (auto &[name, children] : this->data) {
      if (!isChild[name]) {
        return name;
      }
    }

    return "Not found";
  }

  auto getSumWeights(string name) -> uint64_t {
    if (this->sumWeights.find(name) != this->sumWeights.end()) {
      return this->sumWeights[name];
    }
    uint64_t sum = this->weights[name];
    for (auto &child : this->data[name]) {
      sum += this->getSumWeights(child);
    }
    this->sumWeights[name] = sum;
    return sum;
  }

  auto getCorrectWeight(string name) -> uint64_t {
    auto children = this->data[name];

    if (children.empty()) {
      return 0;
    }

    map<uint64_t, vector<string>> weightGroups;
    for (auto &child : children) {
      uint64_t sumWeight = this->getSumWeights(child);
      weightGroups[sumWeight].push_back(child);
    }

    if (weightGroups.size() == 1) {
      return 0;
    }

    string oddChild;
    uint64_t correctWeight, wrongWeight;

    for (auto &[weight, nodes] : weightGroups) {
      if (nodes.size() == 1) {
        oddChild = nodes[0];
        wrongWeight = weight;
      } else {
        correctWeight = weight;
      }
    }

    uint64_t result = this->getCorrectWeight(oddChild);

    if (result == 0) {
      uint64_t diff = wrongWeight - correctWeight;
      return this->weights[oddChild] - diff;
    }

    return result;
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> string { return this->getRoot(); }

  auto part2() -> uint64_t { return this->getCorrectWeight(this->getRoot()); }
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