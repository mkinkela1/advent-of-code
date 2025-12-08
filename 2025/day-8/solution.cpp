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

class UnionFind {
private:
  vector<int> parent;
  vector<int> rank;

public:
  UnionFind(int size) {
    this->parent.resize(size);
    this->rank.resize(size);
    for (int i = 0; i < size; i++) {
      this->makeSet(i);
    }
  }
  void makeSet(int x) {
    this->parent[x] = x;
    this->rank[x] = 0;
  }

  int find(int x) {
    int root = this->parent[x];
    if (root != x) {
      this->parent[x] = this->find(root);
    }
    return this->parent[x];
  }

  auto unionSet(int x, int y) -> void {
    auto rootX = this->find(x);
    auto rootY = this->find(y);
    if (rootX != rootY) {
      if (this->rank[rootX] > this->rank[rootY]) {
        this->parent[rootY] = rootX;
      } else if (this->rank[rootX] < this->rank[rootY]) {
        this->parent[rootX] = rootY;
      } else {
        this->parent[rootY] = rootX;
        this->rank[rootX]++;
      }
    }
  }

  int numberOfItemsWithSameRoot(int root) {
    int count = 0;
    for (int i = 0; i < this->parent.size(); i++) {
      if (this->find(i) == root) {
        count++;
      }
    }
    return count;
  }

  bool connected(int x, int y) { return this->find(x) == this->find(y); }
};

class Solution {
private:
  fstream fin;
  vector<tuple<int, int, int>> data;
  vector<pair<int, int>> pairs;
  void parse() {
    string line;
    while (getline(this->fin, line)) {
      vector<string> parts = split(line, ",");
      this->data.push_back(
          make_tuple(stoi(parts[0]), stoi(parts[1]), stoi(parts[2])));
    }

    for (int i = 0; i < this->data.size() - 1; i++) {
      for (int j = i + 1; j < this->data.size(); j++) {
        this->pairs.push_back(make_pair(i, j));
      }
    }

    sort(this->pairs.begin(), this->pairs.end(),
         [this](const pair<int, int> &a, const pair<int, int> &b) {
           const auto [xa1, ya1, za1] = this->data[a.first];
           const auto [xa2, ya2, za2] = this->data[a.second];
           const auto [xb1, yb1, zb1] = this->data[b.first];
           const auto [xb2, yb2, zb2] = this->data[b.second];
           const auto distanceA = this->distance(xa1, ya1, za1, xa2, ya2, za2);
           const auto distanceB = this->distance(xb1, yb1, zb1, xb2, yb2, zb2);
           return distanceA < distanceB;
         });
  }

  auto distance(int x1, int y1, int z1, int x2, int y2, int z2)
      -> unsigned long long {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +
           (z1 - z2) * (z1 - z2);
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int n = 10) -> unsigned long long {
    UnionFind uf(this->data.size());

    for (int i = 0; i < n; i++) {
      auto [first, second] = this->pairs[i];
      uf.unionSet(first, second);
    }

    set<pair<int, int>, greater<pair<int, int>>> connections;
    for (int i = 0; i < this->data.size(); i++) {
      auto root = uf.find(i);
      auto numberOfItems = uf.numberOfItemsWithSameRoot(root);
      connections.insert(make_pair(numberOfItems, root));
    }

    unsigned long long mul = 1;
    int idx = 0;
    for (auto [numberOfItems, root] : connections) {
      mul *= numberOfItems;
      idx++;
      if (idx == 3) {
        return mul;
      }
    }
    return mul;
  }

  auto part2() -> unsigned long long {
    UnionFind uf(this->data.size());

    for (int i = 0; i < this->pairs.size(); i++) {
      auto [first, second] = this->pairs[i];
      if (uf.connected(first, second)) {
        continue;
      }
      uf.unionSet(first, second);

      auto root = uf.find(first);
      auto numberOfItems = uf.numberOfItemsWithSameRoot(root);
      if (numberOfItems == this->data.size()) {
        auto [xa1, ya1, za1] = this->data[first];
        auto [xa2, ya2, za2] = this->data[second];

        return xa1 * xa2;
      }
    }
    return 0;
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
  auto part1Result = aoc.part1(1000);
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
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Part 2: " << part2Result << " (Time: " << duration.count() << " μs)"
       << endl;

  return 0;
}