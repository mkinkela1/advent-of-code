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
    int input;

    void parse()
    {
        string line;
        getline(this->fin, line);
        if (line != "")
            this->input = stoi(line);
    }

    auto manhattan(pair<int, int> a, pair<int, int> b) -> int
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

    auto part1() -> int
    {
        int x = 0, y = 0;

        for (int i = 1;; i += 2)
        {
            if (i * i >= this->input)
            {
                int diff = i * i - this->input;
                int sideLenght = i - 1;
                if (diff > sideLenght)
                {
                    x -= sideLenght;
                    diff -= sideLenght;
                }
                else
                {
                    x -= diff;
                    return this->manhattan({0, 0}, {x, y});
                }

                if (diff > sideLenght)
                {
                    y += sideLenght;
                    diff -= sideLenght;
                }
                else
                {
                    y += diff;
                    return this->manhattan({0, 0}, {x, y});
                }

                if (diff > sideLenght)
                {
                    x += sideLenght;
                    diff -= sideLenght;
                }
                else
                {
                    x += diff;
                    return this->manhattan({0, 0}, {x, y});
                }

                y -= diff;
                return this->manhattan({0, 0}, {x, y});
            }
            else
            {
                x++;
                y--;
            }
        }
    }
    auto part2() -> string { return "Not solved"; }
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