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

class FirstKeypad
{
private:
    int x, y;

public:
    FirstKeypad()
    {
        this->x = 1;
        this->y = 1;
    }

    auto getNumber() -> int
    {
        return (this->x * 3) + (this->y + 1);
    }

    auto move(char c) -> void
    {
        switch (c)
        {
        case 'U':
            if (this->x > 0)
                this->x--;
            break;
        case 'D':
            if (this->x < 2)
                this->x++;
            break;
        case 'L':
            if (this->y > 0)
                this->y--;
            break;
        case 'R':
            if (this->y < 2)
                this->y++;
            break;
        }
    }
};

class SecondKeypad
{
private:
    int x, y;
    vector<string> keypad = {
        "..1..",
        ".234.",
        "56789",
        ".ABC.",
        "..D.."};

public:
    SecondKeypad()
    {
        this->x = 2;
        this->y = 0;
    }

    auto getNumber() -> char
    {
        return this->keypad[this->x][this->y];
    }

    auto move(char c) -> void
    {
        switch (c)
        {
        case 'U':
            if (this->x > 0 && this->keypad[this->x - 1][this->y] != '.')
                this->x--;
            break;
        case 'D':
            if (this->x < 4 && this->keypad[this->x + 1][this->y] != '.')
                this->x++;
            break;
        case 'L':
            if (this->y > 0 && this->keypad[this->x][this->y - 1] != '.')
                this->y--;
            break;
        case 'R':
            if (this->y < 4 && this->keypad[this->x][this->y + 1] != '.')
                this->y++;
            break;
        }
    }
};

class Solution
{
private:
    fstream fin;
    vector<string> input;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> string
    {
        FirstKeypad keypad;

        string sol = "";

        for (auto line : this->input)
        {
            for (auto c : line)
                keypad.move(c);

            sol += to_string(keypad.getNumber());
        }

        return sol;
    }
    auto part2() -> string
    {
        SecondKeypad keypad;

        string sol = "";

        for (auto line : this->input)
        {
            for (auto c : line)
                keypad.move(c);

            sol += keypad.getNumber();
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