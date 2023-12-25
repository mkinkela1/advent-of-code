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
#include "../../utils/stoer-wagner.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<pair<int, int>> m;
    vector<vector<int>> edges;
    map<string, int> names;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> tokens = split(line, " ");
            tokens[0] = tokens[0].substr(0, tokens[0].size() - 1);

            int index = this->getIndex(tokens[0]);

            for (int i = 1; i < tokens.size(); i++)
            {
                this->m.push_back(make_pair(index, this->getIndex(tokens[i])));
            }
        }

        this->edges = vector<vector<int>>(this->names.size(), vector<int>(this->names.size(), 0));
        for (auto e : this->m)
        {
            this->edges[e.first][e.second] = 1;
            this->edges[e.second][e.first] = 1;
        }
    }

    auto getIndex(string name) -> int
    {
        if (this->names.find(name) != this->names.end())
            return this->names[name];

        int index = this->names.size();
        this->names[name] = index;
        return index;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long unsigned
    {
        long long unsigned sol = 0ULL;

        pair<int, vector<int>> ret = globalMinCut(this->edges);

        return ret.second.size() * (this->names.size() - ret.second.size());
    }
    auto part2() -> string { return "Not solved"; }
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