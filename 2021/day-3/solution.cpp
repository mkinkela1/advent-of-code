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
    vector<string> bits;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->bits.push_back(line);
        }
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
        vector<pair<int, int>> binary(this->bits[0].size());

        for (auto bit : this->bits)
        {
            for (int i = 0; i < bit.size(); i++)
            {
                if (bit[i] == '0')
                    ++binary[i].first;
                else
                    ++binary[i].second;
            }
        }

        string gamma = "";
        string epsilon = "";

        for (auto b : binary)
        {
            if (b.first > b.second)
            {
                gamma += "0";
                epsilon += "1";
            }
            else
            {
                gamma += "1";
                epsilon += "0";
            }
        }

        long long g = stoll(gamma, nullptr, 2);
        long long e = stoll(epsilon, nullptr, 2);

        return g * e;
    }
    auto part2() -> int
    {
        vector<string> oxygen_bits = this->bits;
        int pos = 0;

        while (oxygen_bits.size() > 1)
        {
            int zero = 0, one = 0;
            for (auto bit : oxygen_bits)
            {
                if (bit[pos] == '1')
                {
                    ++one;
                }
                else
                {
                    ++zero;
                }
            }

            vector<string> new_bits;
            if (zero > one)
            {
                for (auto bit : oxygen_bits)
                {
                    if (bit[pos] == '0')
                    {
                        new_bits.push_back(bit);
                    }
                }
            }
            else
            {
                for (auto bit : oxygen_bits)
                {
                    if (bit[pos] == '1')
                    {
                        new_bits.push_back(bit);
                    }
                }
            }

            oxygen_bits = new_bits;
            ++pos;
        }

        vector<string> co2_bits = this->bits;
        pos = 0;

        while (co2_bits.size() > 1)
        {
            int zero = 0, one = 0;
            for (auto bit : co2_bits)
            {
                if (bit[pos] == '1')
                {
                    ++one;
                }
                else
                {
                    ++zero;
                }
            }

            vector<string> new_bits;
            if (zero <= one)
            {
                for (auto bit : co2_bits)
                {
                    if (bit[pos] == '0')
                    {
                        new_bits.push_back(bit);
                    }
                }
            }
            else
            {
                for (auto bit : co2_bits)
                {
                    if (bit[pos] == '1')
                    {
                        new_bits.push_back(bit);
                    }
                }
            }

            co2_bits = new_bits;
            ++pos;
        }

        int oxygen = stoi(oxygen_bits[0], nullptr, 2);
        int co2 = stoi(co2_bits[0], nullptr, 2);

        return oxygen * co2;
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