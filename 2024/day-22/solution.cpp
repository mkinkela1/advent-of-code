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

const uint64_t MOD = (1 << 24) - 1;
const uint64_t MOD_HASH = 130321;

class Solution
{
private:
    fstream fin;
    vector<uint64_t> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data.push_back(stoull(line));
        }
    }

    void getNewSecret(uint64_t &secret)
    {
        uint64_t next = secret << 6;
        secret = (secret ^ next) & MOD;
        next = secret >> 5;
        secret = (secret ^ next) & MOD;
        next = secret << 11;
        secret = (secret ^ next) & MOD;
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
        uint64_t result = 0;

        vector<uint64_t> data = this->data;

        for (auto &secret : data)
        {
            for (int i = 0; i < 2000; ++i)
                this->getNewSecret(secret);

            result += secret;
        }

        return result;
    }
    auto part2() -> uint64_t
    {
        uint64_t result = 0;
        map<uint64_t, uint64_t> total;

        for (auto &secret : this->data)
        {
            map<uint64_t, bool> hash;
            uint64_t price = secret % 10;
            uint64_t curr = 0;

            for (int i = 0; i < 2000; ++i)
            {
                this->getNewSecret(secret);

                int new_price = secret % 10;
                int diff = new_price - price + 9;

                price = new_price;

                curr = (curr * 19 + diff) % MOD_HASH;

                if (!hash[curr])
                {
                    hash[curr] = true;
                    total[curr] += price;
                }
            }
        }

        for (auto [_, price] : total)
            result = max(result, price);

        return result;
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