#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <unordered_map>
#include "../../utils/split.h"

using namespace std;

class Player
{
public:
    int hp;
    int mana;
    int armor;
    int manaSpent;
    int shieldTurns;
    int poisonTurns;
    int rechargeTurns;
};

class Boss
{
public:
    int hp;
    int damage;
};

class Solution
{
private:
    fstream fin;
    Player player;
    Boss boss;

    void parse()
    {
        string line;

        getline(this->fin, line);
        int hp = stoi(split(line, " ")[2]);

        getline(this->fin, line);
        int damage = stoi(split(line, " ")[1]);

        this->player.hp = 10;
        this->player.mana = 250;
        this->player.armor = 0;
        this->player.manaSpent = 0;
        this->player.shieldTurns = 0;
        this->player.poisonTurns = 0;
        this->player.rechargeTurns = 0;

        this->boss.hp = hp;
        this->boss.damage = damage;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        // TODO: Implement the calc method or replace with actual logic
        return 0; // Placeholder until calc method is implemented
    }
    auto part2() -> int
    {
        return 0; // Placeholder until part2 is implemented
    }
};

auto main() -> int
{

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