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

class Solution
{
private:
    fstream fin;
    vector<pair<char, int>> instructions;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            char action = line[0];
            int value = stoi(line.substr(1));
            this->instructions.push_back({action, value});
        }
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
        int x = 0, y = 0;
        int direction = 0;
        for (auto [action, value] : this->instructions)
        {
            switch (action)
            {
            case 'N':
                y += value;
                break;
            case 'S':
                y -= value;
                break;
            case 'E':
                x += value;
                break;
            case 'W':
                x -= value;
                break;
            case 'L':
                direction = (direction + value) % 360;
                break;
            case 'R':
                direction = (direction - value + 360) % 360;
                break;
            case 'F':
                switch (direction)
                {
                case 0:
                    x += value;
                    break;
                case 90:
                    y += value;
                    break;
                case 180:
                    x -= value;
                    break;
                case 270:
                    y -= value;
                    break;
                }
                break;
            }
        }
        return abs(x) + abs(y);
    }
    auto part2() -> uint64_t
    {
        int x = 0, y = 0;
        int wx = 10, wy = 1;
        for (auto [action, value] : this->instructions)
        {
            switch (action)
            {
            case 'N':
                wy += value;
                break;
            case 'S':
                wy -= value;
                break;
            case 'E':
                wx += value;
                break;
            case 'W':
                wx -= value;
                break;
            case 'L':
                for (int i = 0; i < value / 90; i++)
                {
                    int temp = wx;
                    wx = -wy;
                    wy = temp;
                }
                break;
            case 'R':
                for (int i = 0; i < value / 90; i++)
                {
                    int temp = wx;
                    wx = wy;
                    wy = -temp;
                }
                break;
            case 'F':
                x += wx * value;
                y += wy * value;
                break;
            }
        }
        return abs(x) + abs(y);
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