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
#include <regex>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

class Solution
{
private:
    fstream fin;
    string molecule;
    set<string> molecules;
    vector<pair<string, string>> replacements;

    void parse()
    {
        string line;
        char from[20], to[20];
        while (getline(this->fin, line))
        {
            if (line.empty())
                break;
            sscanf(line.c_str(), "%s => %s", from, to);
            this->replacements.push_back({from, to});
        }

        getline(this->fin, molecule);
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
        for (auto replacement : this->replacements)
        {
            size_t pos = 0;
            while ((pos = this->molecule.find(replacement.first, pos)) != string::npos)
            {
                string new_molecule = this->molecule;
                new_molecule.replace(pos, replacement.first.length(), replacement.second);
                this->molecules.insert(new_molecule);
                pos += replacement.first.length();
            }
        }

        return this->molecules.size();
    }
    auto part2() -> int
    {
        sort(this->replacements.begin(), this->replacements.end(), [](auto a, auto b)
             { return a.second.length() > b.second.length(); });

        string molecule = this->molecule;
        int steps = 0;

        while (molecule != "e")
        {
            bool found = false;

            for (auto replacement : this->replacements)
            {
                size_t pos = 0;
                if ((pos = molecule.find(replacement.second, pos)) != string::npos)
                {
                    found = true;
                    molecule.replace(pos, replacement.second.length(), replacement.first);
                    steps++;
                    pos += replacement.second.length();
                }
            }

            if (!found)
            {
                std::random_device rd;
                std::mt19937 g(rd());

                shuffle(this->replacements.begin(), this->replacements.end(), g);
                molecule = this->molecule;
                steps = 0;
            }
        }

        return steps;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}