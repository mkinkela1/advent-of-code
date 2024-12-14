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

class Solution
{
private:
    fstream fin;
    vector<tuple<pair<int, int>, pair<int, int>>> robots;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int x1, y1, x2, y2;
            sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x1, &y1, &x2, &y2);
            this->robots.push_back({{x1, y1}, {x2, y2}});
        }
    }

    bool checkIfMoreThanHalfInACluster(vector<string> grid, int robots)
    {
        map<pair<int, int>, bool> visited;
        int maxX = grid[0].size();
        int maxY = grid.size();
        int maxCount = 0;

        for (int x = 0; x < maxX; x++)
        {
            for (int y = 0; y < maxY; y++)
            {
                if (grid[y][x] == '#' && !visited[{x, y}])
                {
                    queue<pair<int, int>> q;
                    q.push({x, y});
                    int count = 0;
                    while (!q.empty())
                    {
                        auto [x, y] = q.front();
                        q.pop();
                        if (visited[{x, y}])
                            continue;
                        visited[{x, y}] = true;
                        count++;
                        for (auto [dx, dy] : vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
                        {
                            if (x + dx < maxX && x + dx >= 0 && y + dy < maxY && y + dy >= 0 && grid[x + dx][y + dy] == '#')
                                q.push({x + dx, y + dy});
                        }
                    }
                    maxCount = max(maxCount, count);
                    if (count > 200)
                    {
                        cout << count << endl;
                        return true;
                    }
                }
            }
        }

        return false;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1(int maxX, int maxY, int time) -> uint64_t
    {
        vector<tuple<pair<int, int>, pair<int, int>>> _robots = robots;

        for (int i = 0; i < time; i++)
        {
            for (auto &robot : _robots)
            {
                auto &[pos, vel] = robot;
                pos.first += vel.first;
                pos.second += vel.second;

                pos.first += maxX;
                pos.second += maxY;
                pos.first %= maxX;
                pos.second %= maxY;
            }
        }

        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        for (auto robot : _robots)
        {
            auto [pos, vel] = robot;
            if (pos.first < maxX / 2 && pos.second < maxY / 2)
            {
                q1++;
            }
            else if (pos.first > maxX / 2 && pos.second < maxY / 2)
            {
                q2++;
            }
            else if (pos.first < maxX / 2 && pos.second > maxY / 2)
            {
                q3++;
            }
            else if (pos.first > maxX / 2 && pos.second > maxY / 2)
            {
                q4++;
            }
        }

        return q1 * q2 * q3 * q4;
    }
    auto part2(int maxX, int maxY) -> int
    {
        vector<tuple<pair<int, int>, pair<int, int>>> _robots = robots;

        for (int i = 1;; i++)
        {
            for (auto &robot : _robots)
            {
                auto &[pos, vel] = robot;
                pos.first += vel.first;
                pos.second += vel.second;

                pos.first += maxX;
                pos.second += maxY;
                pos.first %= maxX;
                pos.second %= maxY;
            }

            vector<string> grid(maxY, string(maxX, '.'));
            for (auto robot : _robots)
            {
                auto [pos, vel] = robot;
                grid[pos.second][pos.first] = '#';
            }

            if (this->checkIfMoreThanHalfInACluster(grid, this->robots.size()))
            {
                for (auto row : grid)
                    cout << row << endl;
                return i;
            }
        }
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1(11, 7, 100) << endl;
    cout << "Part 1: " << aoc.part1(101, 103, 100) << endl;
    cout << "--------------------------" << endl;
    // cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2(101, 103) << endl;

    return 0;
}