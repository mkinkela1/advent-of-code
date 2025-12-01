#include "../../utils/split.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Spell {
  string name;
  int cost;
  int damage;
  int heal;
  int armor;
  int mana;
  int duration;

  Spell(string n, int c, int d, int h, int a, int m, int dur)
      : name(n), cost(c), damage(d), heal(h), armor(a), mana(m), duration(dur) {
  }
};

struct Effect {
  string name;
  int duration;

  Effect(string name, int duration) {
    this->name = name;
    this->duration = duration;
  }

  bool operator==(const Effect &other) const {
    return name == other.name && duration == other.duration;
  }

  bool operator<(const Effect &other) const {
    if (name != other.name) {
      return name < other.name;
    }
    return duration < other.duration;
  }
};

class Solution {
private:
  fstream fin;
  vector<Spell> spells;
  int bossHealth;
  int bossDamage;
  map<tuple<int, int, int, vector<Effect>, bool, bool>, int> memo;

  void parse() {
    string line;
    while (getline(this->fin, line)) {
      if (line.find("Hit Points:") != string::npos) {
        sscanf(line.c_str(), "Hit Points: %d", &this->bossHealth);
      } else if (line.find("Damage:") != string::npos) {
        sscanf(line.c_str(), "Damage: %d", &this->bossDamage);
      }
    }

    this->spells.push_back(Spell("Magic Missile", 53, 4, 0, 0, 0, 1));
    this->spells.push_back(Spell("Drain", 73, 2, 2, 0, 0, 1));
    this->spells.push_back(Spell("Shield", 113, 0, 0, 7, 0, 6));
    this->spells.push_back(Spell("Poison", 173, 3, 0, 0, 0, 6));
    this->spells.push_back(Spell("Recharge", 229, 0, 0, 0, 101, 5));
  }

  auto simulate(int playerHp, int playerMana, int bossHp,
                vector<Effect> effects, int manaSpent, bool playerTurn,
                bool hard = false) -> int {

    if (hard && playerTurn) {
      playerHp--;
      if (playerHp <= 0) {
        return INT_MAX;
      }
    }

    int armor = 0;
    vector<Effect> newEffects;

    for (auto effect : effects) {
      if (effect.name == "Shield") {
        armor = 7;
      } else if (effect.name == "Poison") {
        bossHp -= 3;
      } else if (effect.name == "Recharge") {
        playerMana += 101;
      }

      if (effect.duration > 1) {
        newEffects.push_back(Effect(effect.name, effect.duration - 1));
      }
    }

    effects = newEffects;

    if (bossHp <= 0) {
      return manaSpent;
    }

    if (playerHp <= 0) {
      return INT_MAX;
    }

    tuple<int, int, int, vector<Effect>, bool, bool> state =
        make_tuple(playerHp, playerMana, bossHp, effects, playerTurn, hard);
    if (memo.find(state) != memo.end()) {
      int cached = memo[state];
      if (cached == INT_MAX)
        return INT_MAX;
      return manaSpent + cached;
    }

    if (playerTurn) {

      int best = INT_MAX;

      for (auto spell : this->spells) {
        if (spell.cost > playerMana)
          continue;

        if (spell.duration > 1) {
          bool alreadyActive = false;
          for (const auto &e : effects) {
            if (e.name == spell.name) {
              alreadyActive = true;
              break;
            }
          }
          if (alreadyActive)
            continue;
        }

        int nextHp = playerHp + spell.heal;
        int nextMana = playerMana - spell.cost;
        int nextBossHp = bossHp;
        if (spell.duration == 1) {
          nextBossHp = bossHp - spell.damage;
        }
        vector<Effect> nextEffects = effects;
        int nextManaSpent = manaSpent + spell.cost;

        if (spell.duration > 1)
          nextEffects.push_back(Effect(spell.name, spell.duration));

        if (nextBossHp <= 0) {
          best = min(best, nextManaSpent);
        } else {
          int result = simulate(nextHp, nextMana, nextBossHp, nextEffects,
                                nextManaSpent, false, hard);
          if (result != INT_MAX) {
            best = min(best, result);
          }
        }
      }

      if (best == INT_MAX) {
        memo[state] = INT_MAX;
        return INT_MAX;
      }

      int additionalMana = best - manaSpent;
      memo[state] = additionalMana;
      return best;

    } else {
      int damageTaken = max(1, this->bossDamage - armor);
      playerHp -= damageTaken;

      if (playerHp <= 0) {
        memo[state] = INT_MAX;
        return INT_MAX;
      }

      int result = simulate(playerHp, playerMana, bossHp, effects, manaSpent,
                            true, hard);
      int additionalMana = (result == INT_MAX) ? INT_MAX : result - manaSpent;
      memo[state] = additionalMana;
      return result;
    }
  }

public:
  Solution(string fileName) {
    this->fin.open(fileName, ios::in);
    this->parse();
    this->fin.close();
  }

  auto part1(int playerHp = 50, int playerMana = 500) -> int {
    this->memo.clear();
    return this->simulate(playerHp, playerMana, this->bossHealth,
                          vector<Effect>(), 0, true);
  }

  auto part2(int playerHp = 50, int playerMana = 500) -> int {
    this->memo.clear();
    return this->simulate(playerHp, playerMana, this->bossHealth,
                          vector<Effect>(), 0, true, true);
  }
};

auto main() -> int {
  Solution aoc = Solution("input.txt");
  Solution test1 = Solution("test1.txt");
  Solution test2 = Solution("test2.txt");
  Solution test14 = Solution("test14.txt");

  cout << "Part 1 test (boss HP 13): " << test1.part1(10, 250) << endl;
  cout << "Part 1 test (boss HP 14): " << test14.part1(10, 250) << endl;
  cout << "Part 1: " << aoc.part1() << endl;
  cout << "--------------------------" << endl;
  cout << "Part 2 test: " << test2.part2(10, 250) << endl;
  cout << "Part 2: " << aoc.part2() << endl;

  return 0;
}