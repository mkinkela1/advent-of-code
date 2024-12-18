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
    vector<pair<int, int>> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int x, y;
            sscanf(line.c_str(), "%d,%d", &x, &y);

            this->data.push_back({x, y});
        }
    }

    int bfs(int sx, int sy, int ex, int ey, int t)
    {
        pair<int, int> start = {sx, sy};
        pair<int, int> end = {ex, ey};

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<int>> grid(ex + 1, vector<int>(ey + 1, 0));
        vector<vector<int>> visited(ex + 1, vector<int>(ey + 1, 0));
        vector<vector<int>> dist(ex + 1, vector<int>(ey + 1, 0));

        for (int i = 0; i <= t; ++i)
        {
            grid[this->data[i].first][this->data[i].second] = 1;
        }

        queue<pair<pair<int, int>, int>> q;
        q.push({start, 0});
        visited[start.first][start.second] = 1;

        while (!q.empty())
        {
            auto [curr, d] = q.front();
            q.pop();

            if (curr == end)
            {
                return d;
            }

            for (auto dir : directions)
            {
                int x = curr.first + dir.first;
                int y = curr.second + dir.second;

                if (x < 0 || x > ex || y < 0 || y > ey || visited[x][y] || grid[x][y])
                    continue;

                visited[x][y] = 1;
                dist[x][y] = d + 1;
                q.push({{x, y}, d + 1});
            }
        }

        if (!visited[end.first][end.second])
            return -1;

        return dist[end.first][end.second];
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1(int sx, int sy, int ex, int ey, int t) -> int
    {
        return this->bfs(sx, sy, ex, ey, t - 1);
    }
    auto part2(int sx, int sy, int ex, int ey, int t) -> string
    {
        int ans = 0;
        for (int i = t; i < this->data.size(); ++i)
        {
            int d = this->bfs(sx, sy, ex, ey, i);
            if (d == -1)
            {
                return to_string(this->data[i].first) + "," + to_string(this->data[i].second);
            }
        }
        return "No solution";
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1(0, 0, 6, 6, 12) << endl;
    cout << "Part 1: " << aoc.part1(0, 0, 70, 70, 1024) << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2(0, 0, 6, 6, 12) << endl;
    cout << "Part 2: " << aoc.part2(0, 0, 70, 70, 1024) << endl;

    return 0;
}