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
    vector<string> grid;
    tuple<int, int> start, end;
    set<tuple<int, int>> intersections;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
        }

        for (int i = 0; i < this->grid[0].size(); i++)
        {
            if (this->grid[0][i] == '.')
            {
                this->start = make_tuple(0, i);
            }

            if (this->grid[this->grid.size() - 1][i] == '.')
            {
                this->end = make_tuple(this->grid.size() - 1, i);
            }
        }

        this->intersections.insert(this->start);
        this->intersections.insert(this->end);
        this->findIntersections();
    }

    auto findIntersections() -> void
    {
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < this->grid.size(); i++)
        {
            for (int j = 0; j < this->grid[i].size(); j++)
            {
                if (this->grid[i][j] == '#')
                {
                    continue;
                }

                int countNeighbors = 0;
                for (int k = 0; k < 4; k++)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];

                    if (x < 0 || x >= this->grid.size() || y < 0 || y >= this->grid[i].size())
                    {
                        continue;
                    }

                    if (this->grid[x][y] != '#')
                    {
                        countNeighbors++;
                    }
                }

                if (countNeighbors > 2)
                {
                    this->intersections.insert(make_tuple(i, j));
                }
            }
        }
    }

    auto calculateDistances(map<tuple<int, int, int, int>, int> &graph, map<char, vector<tuple<int, int>>> dirs) -> void
    {
        for (auto intersection : this->intersections)
        {
            map<tuple<int, int>, bool> visited;
            queue<tuple<int, int, int>> q;

            q.push(make_tuple(get<0>(intersection), get<1>(intersection), 0));
            visited[intersection] = true;

            while (!q.empty())
            {
                auto [x, y, dist] = q.front();
                q.pop();

                if (
                    dist != 0 &&
                    this->intersections.find(make_tuple(x, y)) != this->intersections.end())
                {
                    graph[make_tuple(get<0>(intersection), get<1>(intersection), x, y)] = dist;
                    continue;
                }

                for (auto [dx, dy] : dirs[this->grid[x][y]])
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= this->grid.size() || ny < 0 || ny >= this->grid[0].size())
                        continue;

                    if (this->grid[nx][ny] == '#')
                        continue;

                    if (visited[make_tuple(nx, ny)])
                        continue;

                    visited[make_tuple(nx, ny)] = true;
                    q.push(make_tuple(nx, ny, dist + 1));
                }
            }
        }
    }

    auto dfs(map<tuple<int, int, int, int>, int> graph, tuple<int, int> curr, set<tuple<int, int>> &visited) -> int
    {
        if (curr == this->end)
            return 0;

        int ret = INT_MIN;
        visited.insert(curr);

        for (auto [key, value] : graph)
        {
            auto [x1, y1, x2, y2] = key;

            if (make_tuple(x1, y1) != curr)
                continue;

            if (visited.find(make_tuple(x2, y2)) != visited.end())
                continue;

            ret = max(ret, value + this->dfs(graph, make_tuple(x2, y2), visited));
        }

        visited.erase(visited.find(curr));

        return ret;
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
        map<char, vector<tuple<int, int>>> dirs = {
            {'^', {{-1, 0}}},
            {'v', {{1, 0}}},
            {'<', {{0, -1}}},
            {'>', {{0, 1}}},
            {'.', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}};

        map<tuple<int, int, int, int>, int> graph;
        set<tuple<int, int>> visited;

        this->calculateDistances(graph, dirs);

        return this->dfs(graph, this->start, visited);
    }
    auto part2() -> int
    {
        int sol = 0;
        map<char, vector<tuple<int, int>>> dirs = {
            {'^', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
            {'v', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
            {'<', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
            {'>', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
            {'.', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}};

        map<tuple<int, int, int, int>, int> graph;
        set<tuple<int, int>> visited;

        this->calculateDistances(graph, dirs);

        return this->dfs(graph, this->start, visited);
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