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

    auto solve(int steps, bool multiple = false) -> long long unsigned
    {
        int n = this->input.size();
        int m = this->input[0].size();

        set<tuple<int, int>> seen;
        vector<tuple<int, int>> ret;
        queue<tuple<int, int, int>> q;

        q.push(make_tuple(steps, get<0>(this->start), get<1>(this->start)));
        seen.insert(this->start);

        while (!q.empty())
        {
            auto [steps, x, y] = q.front();
            q.pop();

            if (steps % 2 == 0)
                ret.push_back(make_tuple(x, y));

            if (steps == 0)
                continue;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                int nnx = nx;
                int nny = ny;

                if (multiple)
                {
                    while (nx < 0)
                        nx += n;
                    while (ny < 0)
                        ny += m;

                    nx = (nx + n) % n;
                    ny = (ny + m) % m;
                }

                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;

                if (this->input[nx][ny] == '#')
                    continue;

                if (seen.find(make_tuple(nnx, nny)) != seen.end())
                    continue;

                seen.insert(make_tuple(nnx, nny));
                q.push(make_tuple(steps - 1, nnx, nny));
            }
        }

        return ret.size();
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

        long long unsigned steps = 26501365LLU - 65LLU;

        long long unsigned a0 = (long long unsigned)this->solve(0 * 131 + 65, true);
        long long unsigned a1 = (long long unsigned)this->solve(1 * 131 + 65, true);
        long long unsigned a2 = (long long unsigned)this->solve(2 * 131 + 65, true);

        long long unsigned b0 = a0;
        long long unsigned b1 = a1 - a0;
        long long unsigned b2 = a2 - a1;

        long long unsigned x = steps / 131LLU;

        return ((b0 + b1 * x + (x * (x - 1) / 2) * (b2 - b1)));
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