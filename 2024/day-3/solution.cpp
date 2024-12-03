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
#include <regex>

using namespace std;

class Solution
{
private:
    fstream fin;
    string data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data += line;
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

        regex mul("mul\\((\\d+),(\\d+)\\)");

        for (sregex_iterator i = sregex_iterator(this->data.begin(), this->data.end(), mul); i != sregex_iterator(); i++)
        {
            smatch match = *i;
            long long a = stoll(match[1]);
            long long b = stoll(match[2]);
            long long res = a * b;
            sol += res;
        }

        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0;
        vector<pair<int, string>> instructions;

        regex _do("do\\(\\)");
        for (sregex_iterator i = sregex_iterator(this->data.begin(), this->data.end(), _do); i != sregex_iterator(); i++)
        {
            smatch match = *i;
            instructions.push_back({match.position(), match.str()});
        }

        regex dont("don\\'t\\(\\)");
        for (sregex_iterator i = sregex_iterator(this->data.begin(), this->data.end(), dont); i != sregex_iterator(); i++)
        {
            smatch match = *i;
            instructions.push_back({match.position(), match.str()});
        }

        regex mul("mul\\((\\d+),(\\d+)\\)");
        for (sregex_iterator i = sregex_iterator(this->data.begin(), this->data.end(), mul); i != sregex_iterator(); i++)
        {
            smatch match = *i;
            instructions.push_back({match.position(), match.str()});
        }

        sort(instructions.begin(), instructions.end());

        bool take = true;
        for (auto &instruction : instructions)
        {
            if (instruction.second == "do()")
            {
                take = true;
            }
            else if (instruction.second == "don't()")
            {
                take = false;
            }
            else
            {
                smatch match;
                regex_search(instruction.second, match, mul);
                long long a = stoll(match[1]);
                long long b = stoll(match[2]);
                if (take)
                    sol += a * b;
            }
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