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

struct Player {
  int position;
  uint64_t score;

  Player(int position) : position(position), score(0) {}
  Player(int position, int score) : position(position), score(score) {}

  bool operator<(const Player &other) const {
    return this->position < other.position || this->score < other.score;
  }
  bool operator==(const Player &other) const {
    return this->position == other.position && this->score == other.score;
  }
};

struct State {
  Player player1;
  Player player2;
  int currentPlayer;

  State(Player player1, Player player2, int currentPlayer)
      : player1(player1), player2(player2), currentPlayer(currentPlayer) {}

  bool operator<(const State &other) const {
    return this->player1 < other.player1 || this->player2 < other.player2 ||
           this->currentPlayer < other.currentPlayer;
  }
  bool operator==(const State &other) const {
    return this->player1 == other.player1 && this->player2 == other.player2 &&
           this->currentPlayer == other.currentPlayer;
  }
};

class Solution {
private:
  fstream fin;
  vector<int> positions;
  map<int, uint64_t> sumFrequencies;
  map<State, pair<uint64_t, uint64_t>> memo;

  void parse() {
    string line;
    int player, position;

    while (getline(this->fin, line)) {
      sscanf(line.c_str(), "Player %d starting position: %d", &player,
             &position);
      this->positions.push_back(position);
    }
  }

  auto play() -> uint64_t {
    Player player1(this->positions[0]);
    Player player2(this->positions[1]);
    int dice = 1, currentPlayer = 0, totalRolls = 0;

    while (true) {
      int diceSum = 0;
      for (int i = 0; i < 3; i++) {
        diceSum += dice;
        dice = (dice % 100) + 1;
        totalRolls++;
      }

      if (currentPlayer == 0) {
        player1.position = ((player1.position + diceSum) % 10) == 0
                               ? 10
                               : ((player1.position + diceSum) % 10);
        player1.score += player1.position;
      } else {
        player2.position = ((player2.position + diceSum) % 10) == 0
                               ? 10
                               : ((player2.position + diceSum) % 10);
        player2.score += player2.position;
      }
      currentPlayer = (currentPlayer + 1) % 2;

      if (player1.score >= 1000) {
        return player2.score * totalRolls;
      }

      if (player2.score >= 1000) {
        return player1.score * totalRolls;
      }
    }
  }

  auto quantumPlay(Player player1, Player player2, int currentPlayer)
      -> pair<uint64_t, uint64_t> {
    if (player1.score >= 21) {
      return {1, 0};
    }
    if (player2.score >= 21) {
      return {0, 1};
    }

    auto &memo = this->memo[State(player1, player2, currentPlayer)];

    if (memo.first != 0 && memo.second != 0) {
      return memo;
    }

    pair<uint64_t, uint64_t> result = {0, 0};
    int newPosition, newScore;
    for (auto [sum, frequency] : this->sumFrequencies) {
      if (currentPlayer == 0) {
        newPosition = (player1.position + sum - 1) % 10 + 1;
        newScore = player1.score + newPosition;

        Player newPlayer = Player(newPosition, newScore);
        pair<uint64_t, uint64_t> newResult =
            this->quantumPlay(newPlayer, player2, 1);

        result.first += newResult.first * frequency;
        result.second += newResult.second * frequency;
      } else {
        newPosition = (player2.position + sum - 1) % 10 + 1;
        newScore = player2.score + newPosition;

        Player newPlayer = Player(newPosition, newScore);
        pair<uint64_t, uint64_t> newResult =
            this->quantumPlay(player1, newPlayer, 0);

        result.first += newResult.first * frequency;
        result.second += newResult.second * frequency;
      }
    }
    return memo = result;
  }

  auto populateSumFrequencies() -> void {
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        for (int k = 1; k <= 3; k++) {
          this->sumFrequencies[i + j + k]++;
        }
      }
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1() -> uint64_t { return this->play(); }

  auto part2() -> uint64_t {
    Player player1(this->positions[0]);
    Player player2(this->positions[1]);
    int currentPlayer = 0;

    this->populateSumFrequencies();

    pair<uint64_t, uint64_t> result =
        this->quantumPlay(player1, player2, currentPlayer);
    return max(result.first, result.second);
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
