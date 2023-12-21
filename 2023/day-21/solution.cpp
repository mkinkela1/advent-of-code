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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

class Solution
{
private:
    fstream fin;
    vector<string> input;
    tuple<int, int> start;

    void parse()
    {
        string line;

        for (int i = 0; getline(this->fin, line); i++)
        {
            this->input.push_back(line);
            for (int j = 0; j < line.size(); j++)
                if (line[j] == 'S')
                    this->start = make_tuple(i, j);
        }
    }

    auto solve(int steps) -> int
    {
        map<int, set<tuple<int, int>>> visited;
        visited[0].insert(this->start);

        for (int dist = 1; dist <= steps; ++dist)
        {
            for (auto point : visited[dist - 1])
            {
                for (int i = 0; i < 4; ++i)
                {
                    int nx = get<0>(point) + dx[i];
                    int ny = get<1>(point) + dy[i];
                    if (nx < 0 || ny < 0 || nx >= this->input.size() || ny >= this->input[0].size())
                        continue;
                    if (this->input[nx][ny] == '#')
                        continue;
                    visited[dist].insert(make_tuple(nx, ny));
                }
            }
        }

        return visited[steps].size();
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
        return this->solve(64);
    }
    auto part2() -> long long unsigned
    {
        long long unsigned sol = 0LLU;

        int steps = 26501365; // 202300 * 131 + 65

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