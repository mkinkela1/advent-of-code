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
    int minNumberOfGifts;
    int weight;
    vector<int> houses;

    void parse()
    {
        this->minNumberOfGifts = 29000000;
    }

    void reset(int weight)
    {
        this->houses.clear();

        this->weight = weight;
        this->houses.resize(this->minNumberOfGifts / this->weight, 0);
    }

public:
    Solution()
    {
        this->parse();
    }

    auto part1() -> int
    {
        this->reset(10);

        for (int i = 1; i < this->minNumberOfGifts / this->weight; ++i)
            for (int j = i; j < this->minNumberOfGifts / this->weight; j += i)
                this->houses[j] += i * this->weight;

        for (int i = 0; i < this->houses.size(); ++i)
            if (this->houses[i] >= this->minNumberOfGifts)
                return i;
    }
    auto part2() -> int
    {
        this->reset(11);

        for (int i = 1; i < this->minNumberOfGifts / this->weight; ++i)
            for (int j = i, k = 0; j < this->minNumberOfGifts / this->weight && k < 50; j += i, ++k)
                this->houses[j] += i * this->weight;

        for (int i = 0; i < this->houses.size(); ++i)
            if (this->houses[i] >= this->minNumberOfGifts)
                return i;
    }
};

auto main() -> int
{
    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}