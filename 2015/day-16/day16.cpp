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

class Sue
{
private:
    int id;
    unordered_map<string, int> properties;

public:
    Sue(int id, unordered_map<string, int> properties)
    {
        this->id = id;
        this->properties = properties;
    }

    auto getId() -> int { return this->id; }

    auto checkProperty(string property, int value) -> bool
    {
        if (this->properties.find(property) != this->properties.end())
        {
            return this->properties[property] == value;
        }
        return true;
    }

    auto getProperty(string property) -> int
    {
        if (this->properties.find(property) != this->properties.end())
        {
            return this->properties[property];
        }
        return -1;
    }
};

class Solution
{
private:
    fstream fin;
    vector<Sue> sues;

    void parse()
    {
        string line;
        char firstProperty[20], secondProperty[20], thirdProperty[20];
        int id, firstValue, secondValue, thirdValue;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "Sue %d: %s %d, %s %d, %s %d",
                   &id,
                   firstProperty, &firstValue,
                   secondProperty, &secondValue,
                   thirdProperty, &thirdValue);

            this->sues.push_back(
                Sue(id, {{firstProperty, firstValue},
                         {secondProperty, secondValue},
                         {thirdProperty, thirdValue}}));
        }
    }

    static auto findEqual(Sue sue) -> bool
    {
        return sue.checkProperty("children:", 3) &&
               sue.checkProperty("cats:", 7) &&
               sue.checkProperty("samoyeds:", 2) &&
               sue.checkProperty("pomeranians:", 3) &&
               sue.checkProperty("akitas:", 0) &&
               sue.checkProperty("vizslas:", 0) &&
               sue.checkProperty("goldfish:", 5) &&
               sue.checkProperty("trees:", 3) &&
               sue.checkProperty("cars:", 2) &&
               sue.checkProperty("perfumes:", 1);
    }

    static auto findReal(Sue sue) -> bool
    {
        int cats = sue.getProperty("cats:");
        int trees = sue.getProperty("trees:");
        int pomeranians = sue.getProperty("pomeranians:");
        int goldfish = sue.getProperty("goldfish:");

        if (cats != -1 && cats <= 7)
            return false;
        if (trees != -1 && trees <= 3)
            return false;

        if (pomeranians != -1 && pomeranians >= 3)

            return false;
        if (goldfish != -1 && goldfish >= 5)
            return false;

        return sue.checkProperty("children:", 3) &&
               sue.checkProperty("samoyeds:", 2) &&
               sue.checkProperty("akitas:", 0) &&
               sue.checkProperty("vizslas:", 0) &&
               sue.checkProperty("cars:", 2) &&
               sue.checkProperty("perfumes:", 1);
    }

    auto findSue(bool real = false) -> int
    {
        for (auto &sue : this->sues)
        {
            bool (*check)(Sue) = real ? this->findReal : this->findEqual;
            if (check(sue))
            {
                return sue.getId();
            }
        }
        return -1;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int { return this->findSue(); }
    auto part2() -> int { return this->findSue(true); }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}