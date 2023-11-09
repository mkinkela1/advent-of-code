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

class Solution
{
private:
    fstream fin;
    vector<string> commands;

    void parse()
    {
        string line;
        getline(this->fin, line);

        this->commands = split(line, ", ");
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        int x = 0, y = 0;
        int direction = 0; // 0: north, 1: east, 2: south, 3: west

        for (auto command : this->commands)
        {
            int steps = stoi(command.substr(1));
            switch (command[0])
            {
            case 'R':
                direction = (direction + 1) % 4;
                break;
            case 'L':
                direction = (direction + 3) % 4;
                break;
            }

            switch (direction)
            {
            case 0:
                y += steps;
                break;
            case 1:
                x += steps;
                break;
            case 2:

                y -= steps;
                break;
            case 3:
                x -= steps;
                break;
            }
        }

        return abs(x) + abs(y);
    }
    auto part2() -> int
    {
        int x = 0, y = 0;
        int direction = 0; // 0: north, 1: east, 2: south, 3: west
        map<pair<int, int>, bool> visited;

        for (auto command : this->commands)
        {
            int steps = stoi(command.substr(1));
            switch (command[0])
            {
            case 'R':
                direction = (direction + 1) % 4;
                break;
            case 'L':
                direction = (direction + 3) % 4;
                break;
            }

            for (int i = 0; i < steps; i++)
            {
                if (visited[make_pair(x, y)] == true)
                {
                    return abs(x) + abs(y);
                }

                visited[make_pair(x, y)] = true;

                switch (direction)
                {
                case 0:
                    y++;
                    break;
                case 1:
                    x++;
                    break;
                case 2:

                    y--;
                    break;
                case 3:
                    x--;
                    break;
                }
            }
        }
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}