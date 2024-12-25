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
#include <set>

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<pair<char, int>> wire1, wire2;
    map<char, pair<int, int>> directions = {
        {'U', {0, 1}},
        {'D', {0, -1}},
        {'L', {-1, 0}},
        {'R', {1, 0}}};

    void parse()
    {
        string line;
        vector<string> parts;

        getline(this->fin, line);
        parts = split(line, ",");

        for (auto part : parts)
            this->wire1.push_back({part[0], stoi(part.substr(1))});

        getline(this->fin, line);
        parts = split(line, ",");

        for (auto part : parts)
            this->wire2.push_back({part[0], stoi(part.substr(1))});
    }

    uint64_t manhattanDistance(pair<int, int> a, pair<int, int> b)
    {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> uint64_t
    {
        pair<int, int> pos1 = {0, 0}, pos2 = {0, 0};

        set<pair<int, int>> wire1Points, wire2Points;

        for (auto [dir, steps] : this->wire1)
        {
            auto [dx, dy] = this->directions[dir];

            for (int i = 0; i < steps; i++)
            {
                pos1.first += dx;
                pos1.second += dy;
                wire1Points.insert(pos1);
            }
        }

        wire1Points.erase({0, 0});

        for (auto [dir, steps] : this->wire2)
        {
            auto [dx, dy] = this->directions[dir];

            for (int i = 0; i < steps; i++)
            {
                pos2.first += dx;
                pos2.second += dy;
                wire2Points.insert(pos2);
            }
        }

        wire2Points.erase({0, 0});

        uint64_t minDistance = UINT64_MAX;
        for (auto point : wire1Points)
            if (wire2Points.find(point) != wire2Points.end())
                minDistance = min(minDistance, this->manhattanDistance({0, 0}, point));

        return minDistance;
    }
    auto part2() -> int
    {
        pair<int, int> pos1 = {0, 0}, pos2 = {0, 0};

        map<pair<int, int>, int> wire1Points, wire2Points;

        int steps = 0;
        for (auto [dir, step] : this->wire1)
        {
            auto [dx, dy] = this->directions[dir];

            for (int i = 0; i < step; i++)
            {
                pos1.first += dx;
                pos1.second += dy;
                steps++;
                if (wire1Points.find(pos1) == wire1Points.end())
                    wire1Points[pos1] = steps;
            }
        }

        steps = 0;
        for (auto [dir, step] : this->wire2)
        {
            auto [dx, dy] = this->directions[dir];

            for (int i = 0; i < step; i++)
            {
                pos2.first += dx;
                pos2.second += dy;
                steps++;
                if (wire2Points.find(pos2) == wire2Points.end())
                    wire2Points[pos2] = steps;
            }
        }

        int minSteps = INT_MAX;
        for (auto [point, steps1] : wire1Points)
            if (wire2Points.find(point) != wire2Points.end())
                minSteps = min(minSteps, steps1 + wire2Points[point]);
        return minSteps;
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