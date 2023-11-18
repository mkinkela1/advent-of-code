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

using namespace std;

tuple<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution
{
private:
    fstream fin;
    int favNumber;

    void parse()
    {
        string line;
        getline(this->fin, line);
        this->favNumber = stoi(line);
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
        int x = 31, y = 39;
        queue<tuple<int, int>> Q;
        map<tuple<int, int>, int> dist;
        map<tuple<int, int>, bool> visited;
        Q.push({1, 1});

        while (!Q.empty())
        {
            auto [x, y] = Q.front();
            Q.pop();

            if (x == 31 && y == 39)
                return dist[{x, y}];

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || ny < 0)
                    continue;
                if (visited[{nx, ny}])
                    continue;
                visited[{nx, ny}] = true;
                if (__builtin_popcount(nx * nx + 3 * nx + 2 * nx * ny + ny + ny * ny + this->favNumber) % 2 == 1)
                    continue;
                dist[{nx, ny}] = dist[{x, y}] + 1;
                Q.push({nx, ny});
            }
        }
    }
    auto part2() -> int
    {
        int sol = 0;
        queue<tuple<int, int>> Q;
        map<tuple<int, int>, int> dist;
        map<tuple<int, int>, bool> visited;
        Q.push({1, 1});

        while (!Q.empty())
        {
            auto [x, y] = Q.front();
            Q.pop();

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || ny < 0)
                    continue;
                if (visited[{nx, ny}])
                    continue;
                visited[{nx, ny}] = true;
                if (__builtin_popcount(nx * nx + 3 * nx + 2 * nx * ny + ny + ny * ny + this->favNumber) % 2 == 1)
                    continue;
                dist[{nx, ny}] = dist[{x, y}] + 1;
                if (dist[{nx, ny}] <= 50)
                {
                    ++sol;
                    Q.push({nx, ny});
                }
            }
        }

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