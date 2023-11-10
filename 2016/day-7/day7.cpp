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
#include <set>

using namespace std;

class IPv7
{
private:
    vector<pair<string, bool>> parts;

    auto isAbba(string s) -> bool
    {
        for (int i = 0; i < s.size() - 3; i++)
            if (s[i] == s[i + 3] && s[i + 1] == s[i + 2] && s[i] != s[i + 1])
                return true;
        return false;
    }

    void findAllAbas(string s, set<string> &abas)
    {
        for (int i = 0; i < s.size() - 2; ++i)
            if (s[i] == s[i + 2] && s[i] != s[i + 1])
                abas.insert(s.substr(i, 3));
    }

    auto turnAbaIntoBab(string aba) -> string
    {
        return string({aba[1], aba[0], aba[1]});
    }

public:
    IPv7(string input)
    {
        string part = "";
        bool isHypernet = false;

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == '[')
            {
                this->parts.push_back(make_pair(part, isHypernet));
                part = "";
                isHypernet = true;
            }
            else if (input[i] == ']')
            {
                this->parts.push_back(make_pair(part, isHypernet));
                part = "";
                isHypernet = false;
            }
            else
                part += input[i];
        }

        this->parts.push_back(make_pair(part, isHypernet));
    }

    auto isLts() -> bool
    {
        bool hasAbbaOutsideOfBrackets = false;
        for (auto part : this->parts)
        {
            if (part.second && this->isAbba(part.first))
                return false;
            if (!part.second && this->isAbba(part.first))
                hasAbbaOutsideOfBrackets = true;
        }

        return hasAbbaOutsideOfBrackets;
    }

    auto isSsl() -> bool
    {
        set<string> abas;
        set<string> babs;

        for (auto part : this->parts)
        {
            if (part.second)
                findAllAbas(part.first, abas);
            else
                findAllAbas(part.first, babs);
        }

        for (auto aba : abas)
            if (babs.find(this->turnAbaIntoBab(aba)) != babs.end())
                return true;

        return false;
    }
};

class Solution
{
private:
    fstream fin;
    vector<IPv7> addresses;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
            this->addresses.push_back(IPv7(line));
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
        int count = 0;

        for (auto address : this->addresses)
            count += address.isLts();

        return count;
    }
    auto part2() -> int
    {
        int count = 0;

        for (auto address : this->addresses)
            count += address.isSsl();

        return count;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}