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
    vector<string> input;
    vector<string> words;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
        }

        words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    }

    int getWordDigit(string &line, int &i)
    {
        for (int j = 0; j < words.size(); j++)
        {
            if (line.substr(i, words[j].size()) == words[j])
            {
                return j + 1;
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

    auto part1() -> int
    {
        int ans = 0;
        for (auto line : this->input)
        {
            vector<int> digits;
            for (auto c : line)
            {
                if (isdigit(c))
                    digits.push_back(c - '0');
            }

            ans += digits[0] * 10 + digits[digits.size() - 1];
        }
        return ans;
    }
    auto part2() -> int
    {
        int ans = 0;
        for (auto line : this->input)
        {
            vector<int> digits;

            for (int i = 0; i < line.size(); i++)
            {
                if (isdigit(line[i]))
                {
                    digits.push_back(line[i] - '0');
                }
                else
                {
                    int digit = getWordDigit(line, i);

                    if (digit != -1)
                        digits.push_back(digit);
                }
            }

            ans += digits[0] * 10 + digits[digits.size() - 1];
        }
        return ans;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}