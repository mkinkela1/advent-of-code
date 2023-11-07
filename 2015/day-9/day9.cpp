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

class Solution
{
private:
    fstream fin;
    set<string> cities;
    map<pair<string, string>, int> distances;

    void parse()
    {
        string line;
        char from[50], to[50];
        int distance;

        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%s to %s = %d", from, to, &distance);
            this->cities.insert(from);
            this->cities.insert(to);
            this->distances[make_pair(from, to)] = distance;
            this->distances[make_pair(to, from)] = distance;
        }
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
        int sol = INT_MAX;

        vector<string> cities(this->cities.begin(), this->cities.end());

        do
        {
            int distance = 0;
            for (int i = 0; i < cities.size() - 1; i++)
                distance += this->distances[make_pair(cities[i], cities[i + 1])];
            sol = min(sol, distance);
        } while (next_permutation(cities.begin(), cities.end()));

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        vector<string> cities(this->cities.begin(), this->cities.end());

        do
        {
            int distance = 0;
            for (int i = 0; i < cities.size() - 1; i++)
                distance += this->distances[make_pair(cities[i], cities[i + 1])];
            sol = max(sol, distance);
        } while (next_permutation(cities.begin(), cities.end()));

        return sol;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}