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
    vector<tuple<pair<int64_t, int64_t>, pair<int64_t, int64_t>, pair<int64_t, int64_t>>> machine;

    void parse()
    {
        string line;
        pair<int64_t, int64_t> a, b, prize;

        while (getline(this->fin, line))
        {
            if (line.size() == 0)
            {
                this->machine.push_back(make_tuple(a, b, prize));
                a = make_pair(0, 0);
                b = make_pair(0, 0);
                prize = make_pair(0, 0);
                continue;
            }

            vector<string> tokens = split(line, " ");

            if (tokens[0] == "Button" && tokens[1] == "A:")
            {
                sscanf(tokens[2].c_str(), "X+%lld", &a.first);
                sscanf(tokens[3].c_str(), "Y+%lld", &a.second);
            }
            else if (tokens[0] == "Button" && tokens[1] == "B:")
            {
                sscanf(tokens[2].c_str(), "X+%lld", &b.first);
                sscanf(tokens[3].c_str(), "Y+%lld", &b.second);
            }
            else if (tokens[0] == "Prize:")
            {
                sscanf(tokens[1].c_str(), "X=%lld", &prize.first);
                sscanf(tokens[2].c_str(), "Y=%lld", &prize.second);
            }
        }

        this->machine.push_back(make_tuple(a, b, prize));
    }

    int64_t solve(bool checkIfMoreThan100 = false)
    {
        int64_t sol = 0;

        for (auto [a, b, prize] : this->machine)
        {
            int64_t result_a = 0;
            int64_t result_b = 0;

            int64_t x1 = a.first;
            int64_t x2 = a.second;
            int64_t y1 = b.first;
            int64_t y2 = b.second;
            int64_t p1 = prize.first;
            int64_t p2 = prize.second;

            int64_t ky1 = -x2 * y1;
            int64_t ky2 = x1 * y2;

            int64_t kp1 = -x2 * p1;
            int64_t kp2 = x1 * p2;

            int64_t sum_y = ky1 + ky2;
            int64_t sum_p = kp1 + kp2;

            if (sum_p % sum_y == 0)
            {
                result_b = sum_p / sum_y;
            }
            else
            {
                continue;
            }

            if ((p1 - result_b * y1) % x1 == 0)
            {
                result_a = (p2 - result_b * y2) / x2;
            }
            else
            {
                continue;
            }

            if (checkIfMoreThan100 && (result_a > 100 || result_b > 100))
            {
                continue;
            }

            if (result_a < 0 || result_b < 0)
            {
                continue;
            }
            sol += result_a * 3 + result_b;
        }

        return sol;
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
        return this->solve(true);
    }
    auto part2() -> int64_t
    {
        for (int i = 0; i < this->machine.size(); i++)
        {
            this->machine[i] = make_tuple(
                get<0>(this->machine[i]),
                get<1>(this->machine[i]),
                make_pair(get<2>(this->machine[i]).first + 10000000000000, get<2>(this->machine[i]).second + 10000000000000));
        }

        return this->solve();
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