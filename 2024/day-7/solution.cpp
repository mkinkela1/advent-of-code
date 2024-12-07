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
    vector<pair<long long, vector<long long>>> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> parts = split(line, " ");
            vector<long long> values;
            for (int i = 1; i < parts.size(); i++)

                values.push_back(stoll(parts[i]));

            this->data.push_back({stoll(parts[0]), values});
        }
    }

    uint64_t concat(uint64_t a, uint64_t b)
    {
        return a * pow(10, (int)log10(b) + 1) + b;
    }

    bool oper2(uint64_t result, vector<long long> numbers, int index, uint64_t current = 0ULL)
    {
        if (index == numbers.size())
            return result == current;

        if (current > result)
            return false;

        return oper2(result, numbers, index + 1, current + numbers[index]) ||
               oper2(result, numbers, index + 1, current * numbers[index]);
    }

    bool oper3(uint64_t result, vector<long long> numbers, int index, uint64_t current = 0ULL)
    {
        if (index == numbers.size())
            return result == current;

        if (current > result || current < 0)
            return false;

        return oper3(result, numbers, index + 1, this->concat(current, numbers[index])) ||
               oper3(result, numbers, index + 1, current + (uint64_t)numbers[index]) ||
               oper3(result, numbers, index + 1, current * (uint64_t)numbers[index]);
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
        uint64_t sol = 0;
        for (auto [result, numbers] : this->data)
        {
            if (this->oper2(result, numbers, 0))
                sol += result;
        }

        return sol;
    }
    auto part2() -> uint64_t
    {
        uint64_t sol = 0;
        for (auto [result, numbers] : this->data)
        {
            if (this->oper3(result, numbers, 0))
                sol += (uint64_t)result;
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