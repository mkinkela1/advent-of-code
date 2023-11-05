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

using namespace std;

enum ItemType
{
    WEAPON,
    ARMOR,
    RING
};

class Item
{
private:
    int cost;
    int damage;
    int armor;
    ItemType type;

public:
    Item(int cost, int damage, int armor, ItemType type)
    {
        this->cost = cost;
        this->damage = damage;
        this->armor = armor;
        this->type = type;
    }

    auto get_cost() -> int { return this->cost; }
    auto get_damage() -> int { return this->damage; }
    auto get_armor() -> int { return this->armor; }
    auto get_type() -> ItemType { return this->type; }
};

class Player
{
private:
    int hp;
    int damage;
    int armor;

public:
    Player() : hp(0), damage(0), armor(0) {}
    Player(int hp, int damage, int armor)
    {
        this->hp = hp;
        this->damage = damage;
        this->armor = armor;
    }

    auto get_hp() -> int { return this->hp; }
    auto get_damage() -> int { return this->damage; }
    auto get_armor() -> int { return this->armor; }

    auto set_hp(int hp) -> Player
    {
        this->hp = hp;
        return *this;
    }
    auto set_damage(int damage) -> Player
    {
        this->damage = damage;
        return *this;
    }
    auto set_armor(int armor) -> Player
    {
        this->armor = armor;
        return *this;
    }

    auto build() -> Player { return *this; }
};

class Solution
{
private:
    fstream fin;
    vector<Item> items;
    Player player, enemy;

    void parse()
    {
        string line;
        int hp, damage, armor;

        getline(this->fin, line);
        sscanf(line.c_str(), "Hit Points: %d", &hp);
        this->enemy.set_hp(hp);

        getline(this->fin, line);
        sscanf(line.c_str(), "Damage: %d", &damage);
        this->enemy.set_damage(damage);

        getline(this->fin, line);
        sscanf(line.c_str(), "Armor: %d", &armor);
        this->enemy.set_armor(armor);

        this->items.push_back(Item(8, 4, 0, WEAPON));
        this->items.push_back(Item(10, 5, 0, WEAPON));
        this->items.push_back(Item(25, 6, 0, WEAPON));
        this->items.push_back(Item(40, 7, 0, WEAPON));
        this->items.push_back(Item(74, 8, 0, WEAPON));

        this->items.push_back(Item(13, 0, 1, ARMOR));
        this->items.push_back(Item(31, 0, 2, ARMOR));
        this->items.push_back(Item(53, 0, 3, ARMOR));
        this->items.push_back(Item(75, 0, 4, ARMOR));
        this->items.push_back(Item(102, 0, 5, ARMOR));

        this->items.push_back(Item(25, 1, 0, RING));
        this->items.push_back(Item(50, 2, 0, RING));
        this->items.push_back(Item(100, 3, 0, RING));
        this->items.push_back(Item(20, 0, 1, RING));
        this->items.push_back(Item(40, 0, 2, RING));
        this->items.push_back(Item(80, 0, 3, RING));
    }

    auto checkItems(int bitmask) -> bool
    {
        int n = this->items.size();
        int numberOfRings = 0, numberOfArmors = 0, numberOfWeapons = 0;

        for (int i = 0; i < n; ++i)
        {
            if (bitmask & (1 << i))
            {
                numberOfArmors += (this->items[i].get_type() == ARMOR);
                numberOfRings += (this->items[i].get_type() == RING);
                numberOfWeapons += (this->items[i].get_type() == WEAPON);
            }
        }

        return numberOfArmors <= 1 && numberOfRings <= 2 && numberOfWeapons == 1;
    }

    auto canWin(Player player, Player enemy)
    {
        while (player.get_hp() > 0 && enemy.get_hp() > 0)
        {
            enemy.set_hp(enemy.get_hp() - max(1, player.get_damage() - enemy.get_armor()));
            if (enemy.get_hp() <= 0)
                return true;
            player.set_hp(player.get_hp() - max(1, enemy.get_damage() - player.get_armor()));
        }

        return false;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sol = INT_MAX;
        int n = this->items.size();

        for (int i = 0; i <= (1 << n); ++i)
        {
            if (!this->checkItems(i))
                continue;

            int cost = 0, damage = 0, armor = 0;
            for (int j = 0; j < n; ++j)
            {
                if (i & (1 << j))
                {
                    cost += this->items[j].get_cost();
                    damage += this->items[j].get_damage();
                    armor += this->items[j].get_armor();
                }
            }

            if (cost > sol)
                continue;

            this->player = this->player
                               .set_hp(100)
                               .set_damage(damage)
                               .set_armor(armor)
                               .build();

            if (this->canWin(this->player, this->enemy))
                sol = min(sol, cost);
        }

        return sol;
    }

    auto part2() -> int
    {
        int sol = 0;
        int n = this->items.size();

        for (int i = 0; i <= (1 << n); ++i)
        {
            if (!this->checkItems(i))
                continue;

            int cost = 0, damage = 0, armor = 0;
            for (int j = 0; j < n; ++j)
            {
                if (i & (1 << j))
                {
                    cost += this->items[j].get_cost();
                    damage += this->items[j].get_damage();
                    armor += this->items[j].get_armor();
                }
            }

            if (cost <= sol)
                continue;

            this->player = this->player
                               .set_hp(100)
                               .set_damage(damage)
                               .set_armor(armor)
                               .build();

            if (!this->canWin(this->player, this->enemy))
                sol = max(sol, cost);
        }

        return sol;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}