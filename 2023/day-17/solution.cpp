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

enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

class Solution
{
private:
    fstream fin;
    vector<string> input;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
        }
    }

    auto getAdj(int x, int y, Direction dir, int steps, bool isUltra = false) -> vector<tuple<int, int, int, Direction>>
    {
        vector<tuple<int, int, int, Direction>> ret;
        if (isUltra)
        {
            if (steps < 10)
                ret.push_back({x + dx[dir], y + dy[dir], steps + 1, dir});
            if (steps >= 4)
            {
                int d = (dir + 1) % 4;
                ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});

                d = (dir + 3) % 4;
                ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});
            }
        }
        else
        {
            int d = (dir + 1) % 4;
            ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});

            d = (dir + 3) % 4;
            ret.push_back({x + dx[d], y + dy[d], 1, static_cast<Direction>(d)});

            if (steps < 3)
                ret.push_back({x + dx[dir], y + dy[dir], steps + 1, dir});
        }

        return ret;
    }

    auto dijkstra(bool isUltra = false) -> vector<vector<vector<vector<int>>>>
    {
        set<tuple<int, int, int, int, Direction>> S;
        int maxStepsInOneDirection = isUltra ? 10 : 3;
        vector<vector<vector<vector<int>>>> dist(this->input.size(), vector<vector<vector<int>>>(this->input[0].size(), vector<vector<int>>(maxStepsInOneDirection + 1, vector<int>(4, INT_MAX))));

        for (auto dir : {UP, DOWN, LEFT, RIGHT})
        {
            S.insert(make_tuple(0, 0, 0, 0, dir));
            dist[0][0][0][dir] = 0;
        }

        while (!S.empty())
        {
            auto [d, x, y, steps, dir] = *S.begin();
            S.erase(S.begin());

            if (d > dist[x][y][steps][dir])
                continue;

            for (auto [nx, ny, nsteps, ndir] : getAdj(x, y, dir, steps, isUltra))
            {
                if (nx < 0 || nx >= this->input.size() || ny < 0 || ny >= this->input[0].size())
                    continue;

                if (nsteps > maxStepsInOneDirection)
                    continue;

                int weight = this->input[nx][ny] - '0';
                if (dist[nx][ny][nsteps][ndir] > dist[x][y][steps][dir] + weight)
                {
                    dist[nx][ny][nsteps][ndir] = dist[x][y][steps][dir] + weight;
                    S.insert({dist[nx][ny][nsteps][ndir], nx, ny, nsteps, ndir});
                }
            }
        }

        return dist;
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
        int sol = INT_MAX;

        vector<vector<vector<vector<int>>>> dist = this->dijkstra();

        for (auto dir : {UP, DOWN, LEFT, RIGHT})
            for (auto steps : {0, 1, 2, 3})
                sol = min(sol, dist[this->input.size() - 1][this->input[0].size() - 1][steps][dir]);

        return sol;
    }
    auto part2() -> int
    {
        int sol = INT_MAX;

        vector<vector<vector<vector<int>>>> dist = this->dijkstra(true);

        for (auto dir : {UP, DOWN, LEFT, RIGHT})
            for (int steps = 4; steps <= 10; ++steps)
                sol = min(sol, dist[this->input.size() - 1][this->input[0].size() - 1][steps][dir]);

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