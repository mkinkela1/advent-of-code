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
#include <tuple>
#include "../../utils/split.h"

using namespace std;

enum Color
{
    RED,
    GREEN,
    BLUE
};

class Solution
{
private:
    fstream fin;
    map<int, vector<tuple<int, Color>>> games;

    auto getColor(string color) -> Color
    {
        if (color == "red")
            return RED;
        else if (color == "green")
            return GREEN;
        else if (color == "blue")
            return BLUE;
        else
        {
            cout << color << endl;
        }
    }

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int gameId;
            string record;
            vector<string> game = split(line, ": ");
            sscanf(game[0].c_str(), "Game %d", &gameId);

            vector<string> subsets = split(game[1], "; ");

            vector<tuple<int, Color>> games;

            for (auto subset : subsets)
            {
                vector<string> marbels = split(subset, ", ");
                for (auto marbel : marbels)
                {
                    int count;
                    char color[50];
                    sscanf(marbel.c_str(), "%d %s", &count, color);

                    games.push_back(make_tuple(count, this->getColor(color)));
                }

                this->games[gameId] = games;
            }
        }
    }

    auto checkGameValidity(vector<tuple<int, Color>> game, int maxRed, int maxGreen, int maxBlue) -> bool
    {
        for (auto [count, color] : game)
        {
            if (color == RED && count > maxRed)
                return false;
            if (color == GREEN && count > maxGreen)
                return false;
            if (color == BLUE && count > maxBlue)
                return false;
        }

        return true;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sol = 0;
        int maxRed = 12, maxGreen = 13, maxBlue = 14;

        for (auto game : this->games)
            if (this->checkGameValidity(game.second, maxRed, maxGreen, maxBlue))
                sol += game.first;

        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0;

        for (auto game : this->games)
        {
            int minRed = 0, minGreen = 0, minBlue = 0;
            for (auto [count, color] : game.second)
            {
                if (color == RED && count > minRed)
                    minRed = count;
                if (color == GREEN && count > minGreen)
                    minGreen = count;
                if (color == BLUE && count > minBlue)
                    minBlue = count;
            }

            sol += minRed * minGreen * minBlue;
        }

        return sol;
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