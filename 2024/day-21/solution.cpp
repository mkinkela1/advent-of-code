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
#include <cmath>

using namespace std;

uint64_t min(uint64_t a, uint64_t b)
{
    return a < b ? a : b;
}

class Solution
{
private:
    fstream fin;
    vector<pair<string, uint64_t>> data;
    map<char, pair<int, int>> positions = {
        {'7', {0, 0}},
        {'8', {0, 1}},
        {'9', {0, 2}},
        {'4', {1, 0}},
        {'5', {1, 1}},
        {'6', {1, 2}},
        {'1', {2, 0}},
        {'2', {2, 1}},
        {'3', {2, 2}},
        {'0', {3, 1}},
        {'A', {3, 2}},
        {'^', {0, 1}},
        {'a', {0, 2}},
        {'<', {1, 0}},
        {'v', {1, 1}},
        {'>', {1, 2}}};
    map<char, pair<int, int>> directions = {
        {'^', {-1, 0}},
        {'v', {1, 0}},
        {'<', {0, -1}},
        {'>', {0, 1}}};
    map<tuple<string, int, int>, uint64_t> cache;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data.push_back({line, stoull(line)});
        }
    }

    bool isValidPath(pair<int, int> start, pair<int, int> end, string path, pair<int, int> avoid)
    {
        pair<int, int> current = start;
        for (char c : path)
        {
            current.first += this->directions[c].first;
            current.second += this->directions[c].second;
            if (current == avoid)
                return false;
        }
        if (current != end)
            cout << path << " " << start.first << " " << start.second << " " << end.first << " " << end.second << " " << current.first << " " << current.second << endl;

        return current == end;
    }

    vector<string> getPaths(pair<int, int> start, pair<int, int> end, pair<int, int> avoid)
    {
        string path = "";
        int dx = end.first - start.first;
        int dy = end.second - start.second;

        if (dx < 0)
            path += string(-dx, '^');
        else
            path += string(dx, 'v');

        if (dy < 0)
            path += string(-dy, '<');
        else
            path += string(dy, '>');

        sort(path.begin(), path.end());

        set<string> paths;
        do
        {
            if (this->isValidPath(start, end, path, avoid))
            {
                string p = path;
                p.append("a");
                paths.insert(p);
            }

        } while (next_permutation(path.begin(), path.end()));

        if (paths.size() == 0)
            paths.insert("a");

        return vector<string>(paths.begin(), paths.end());
    }

    uint64_t shortest(vector<string> paths)
    {
        uint64_t minLen = UINT64_MAX;
        for (auto p : paths)
            minLen = min(minLen, p.size());
        return minLen;
    }

    uint64_t solve(string path, int limit = 2, int depth = 0)
    {

        uint64_t &result = this->cache[{path, limit, depth}];
        if (result != 0)
            return result;

        pair<int, int> avoid, curr;

        if (depth == 0)
        {
            avoid = {3, 0};
            curr = this->positions['A'];
        }
        else
        {
            avoid = {0, 0};
            curr = this->positions['a'];
        }

        uint64_t len = 0;
        for (auto c : path)
        {
            pair<int, int> next = this->positions[c];
            vector<string> paths = this->getPaths(curr, next, avoid);

            if (depth >= limit)
                len += this->shortest(paths);
            else
            {
                uint64_t minPath = UINT64_MAX;
                for (auto p : paths)
                    minPath = min(minPath, this->solve(p, limit, depth + 1));

                len += minPath;
            }

            curr = next;
        }

        result = len;

        return len;
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
        for (auto [line, value] : this->data)
        {
            uint64_t len = this->solve(line);
            result += len * value;
        }

        return result;
    }
    auto part2() -> uint64_t
    {
        uint64_t result = 0;
        for (auto [line, value] : this->data)
        {
            uint64_t len = this->solve(line, 25);
            result += len * value;
        }

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