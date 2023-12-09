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
#include <numeric>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    string instructions;
    map<string, pair<string, string>> graph;

    void parse()
    {
        string line;

        getline(this->fin, this->instructions);
        getline(this->fin, line);

        while (getline(this->fin, line))
        {
            vector<string> v = split(line, " = (");
            string curr = v[0];
            vector<string> v2 = split(v[1], ", ");
            string nextL = v2[0];
            string nextR = v2[1].substr(0, v2[1].size() - 1);

            this->graph[curr] = make_pair(nextL, nextR);
        }
    }

    auto findCycleLength(string curr) -> long long unsigned
    {
        long long unsigned sol = 0;
        int step = 0;

        while (curr.back() != 'Z')
        {
            ++sol;
            auto next = this->graph[curr];
            if (this->instructions[step] == 'L')
                curr = next.first;
            else
                curr = next.second;

            step++;
            step %= this->instructions.size();
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
        int sol = 0;
        int step = 0;
        string curr = "AAA";

        while (curr != "ZZZ")
        {
            ++sol;
            auto next = this->graph[curr];
            if (this->instructions[step] == 'L')
                curr = next.first;
            else
                curr = next.second;

            step++;
            step %= this->instructions.size();
        }

        return sol;
    }
    auto part2() -> long long unsigned
    {
        long long unsigned sol = 1LL;
        int step = 0;
        vector<string> curr;

        for (auto it = this->graph.begin(); it != this->graph.end(); ++it)
        {
            if (it->first.back() == 'A')
            {
                sol = lcm(sol, this->findCycleLength(it->first));
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