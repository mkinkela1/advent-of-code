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
    vector<pair<vector<int>, vector<int>>> cards;

    void parse()
    {
        string line;
        int cardNumber;
        while (getline(this->fin, line))
        {

            vector<string> numbers = split(line, ": ");
            vector<string> input = split(numbers[1], "|");
            vector<string> winningNumbers = split(input[0], " ");
            vector<string> myNumbers = split(input[1], " ");

            vector<int> winningNumbersInt, myNumbersInt;
            for (auto number : winningNumbers)
            {
                try
                {
                    winningNumbersInt.push_back(stoi(number));
                }
                catch (const std::exception &e)
                {
                    // do nothing
                }
            }
            for (auto number : myNumbers)
                try
                {
                    myNumbersInt.push_back(stoi(number));
                }
                catch (const std::exception &e)
                {
                    // do nothing
                }

            this->cards.push_back(make_pair(winningNumbersInt, myNumbersInt));
        }
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long
    {
        long long sol = 0;

        for (auto card : this->cards)
        {
            vector<int> winningNumbers = card.first;
            vector<int> myNumbers = card.second;

            int winningCount = 0;
            for (auto number : winningNumbers)
            {
                if (find(myNumbers.begin(), myNumbers.end(), number) != myNumbers.end())
                {
                    winningCount++;
                }
            }
            if (winningCount == 1)
            {
                sol += 1;
            }
            else if (winningCount > 1)
                sol += 1 << (winningCount - 1);
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;
        queue<int> q;
        map<int, int> cache;

        for (int i = 0; i < this->cards.size(); i++)
        {
            ++cache[i];

            int winningCount = 0;
            vector<int> winningNumbers = this->cards[i].first;
            vector<int> myNumbers = this->cards[i].second;

            for (auto number : winningNumbers)
            {
                if (find(myNumbers.begin(), myNumbers.end(), number) != myNumbers.end())
                {
                    winningCount++;
                }
            }

            for (int j = 1; i + j < this->cards.size() && j <= winningCount; j++)
            {
                cache[i + j] += cache[i];
            }
        }

        for (auto it = cache.begin(); it != cache.end(); it++)
        {
            sol += it->second;
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