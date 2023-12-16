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

enum Directions
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

class Point
{
private:
    int x, y;
    Directions direction;

public:
    Point(int x, int y, Directions direction)
    {
        this->x = x;
        this->y = y;
        this->direction = direction;
    }
    auto getPoint() -> pair<int, int> { return {this->x, this->y}; }
    auto getDirection() -> Directions { return this->direction; }

    bool operator<(Point const &p) const
    {
        if (this->x != p.x)
            return this->x < p.x;
        if (this->y != p.y)
            return this->y < p.y;
        return this->direction < p.direction;
    }
};

class Solution
{
private:
    fstream fin;
    vector<string> grid;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
        }
    }

    auto goToNextPoint(Point curr, Directions dir, map<Point, bool> &visited, queue<Point> &q) -> Point
    {
        Point next = Point(curr.getPoint().first + dx[dir], curr.getPoint().second + dy[dir], dir);
        if (visited.find(next) == visited.end())
        {
            visited[next] = true;
            q.push(next);
        }
    }

    auto solve(Point start) -> int
    {
        queue<Point> q;
        map<Point, bool> visited;
        map<pair<int, int>, bool> visited2;
        q.push(start);

        while (!q.empty())
        {
            Point tmp = q.front();
            q.pop();

            if (tmp.getPoint().first < 0 || tmp.getPoint().first >= this->grid.size() || tmp.getPoint().second < 0 || tmp.getPoint().second >= this->grid[0].size())
                continue;

            visited[tmp] = true;
            visited2[tmp.getPoint()] = true;
            switch (this->grid[tmp.getPoint().first][tmp.getPoint().second])
            {
            case '.':
            {
                this->goToNextPoint(tmp, tmp.getDirection(), visited, q);
                break;
            }
            case '|':
            {
                if (tmp.getDirection() == NORTH || tmp.getDirection() == SOUTH)
                {
                    this->goToNextPoint(tmp, tmp.getDirection(), visited, q);
                }
                else
                {
                    this->goToNextPoint(tmp, NORTH, visited, q);
                    this->goToNextPoint(tmp, SOUTH, visited, q);
                }
                break;
            }
            case '-':
            {
                if (tmp.getDirection() == EAST || tmp.getDirection() == WEST)
                {
                    this->goToNextPoint(tmp, tmp.getDirection(), visited, q);
                }
                else
                {
                    this->goToNextPoint(tmp, EAST, visited, q);
                    this->goToNextPoint(tmp, WEST, visited, q);
                }
                break;
            }
            case '/':
            {
                if (tmp.getDirection() == NORTH)
                {
                    this->goToNextPoint(tmp, EAST, visited, q);
                }
                else if (tmp.getDirection() == EAST)
                {
                    this->goToNextPoint(tmp, NORTH, visited, q);
                }
                else if (tmp.getDirection() == SOUTH)
                {
                    this->goToNextPoint(tmp, WEST, visited, q);
                }
                else if (tmp.getDirection() == WEST)
                {
                    this->goToNextPoint(tmp, SOUTH, visited, q);
                }
                break;
            }
            case '\\':
            {
                if (tmp.getDirection() == NORTH)
                {
                    this->goToNextPoint(tmp, WEST, visited, q);
                }
                else if (tmp.getDirection() == EAST)
                {
                    this->goToNextPoint(tmp, SOUTH, visited, q);
                }
                else if (tmp.getDirection() == SOUTH)
                {
                    this->goToNextPoint(tmp, EAST, visited, q);
                }
                else if (tmp.getDirection() == WEST)
                {
                    this->goToNextPoint(tmp, NORTH, visited, q);
                }
                break;
            }
            default:
                throw "Unknown character";
            }
        }

        int sol = 0;
        for (auto it = visited2.begin(); it != visited2.end(); it++)
        {
            if (it->second)
                sol++;
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
        Point start = Point(0, 0, EAST);
        return this->solve(start);
    }
    auto part2() -> int
    {
        int sol = 0;

        for (int i = 0; i < this->grid.size(); i++)
        {
            sol = max(sol, this->solve(Point(i, 0, EAST)));
            sol = max(sol, this->solve(Point(i, this->grid[0].size() - 1, WEST)));
        }

        for (int i = 0; i < this->grid[0].size(); i++)
        {
            sol = max(sol, this->solve(Point(0, i, SOUTH)));
            sol = max(sol, this->solve(Point(this->grid.size() - 1, i, NORTH)));
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