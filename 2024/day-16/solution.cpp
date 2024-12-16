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
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    pair<int, int> start;
    pair<int, int> end;
    map<tuple<int, int, int>, int> dist;
    map<tuple<int, int, int>, vector<tuple<int, int, int>>> predecessors;

    void parse()
    {
        string line;
        int r = 0;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
            for (int c = 0; c < line.size(); c++)
            {
                if (line[c] == 'S')
                {
                    this->start = make_pair(r, c);
                }
                if (line[c] == 'E')
                {
                    this->end = make_pair(r, c);
                }
            }
            ++r;
        }
    }

    uint64_t dijkstra()
    {
        // distance, row, col, direction
        priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> pq;
        pq.push({0, this->start.first, this->start.second, 0});

        this->dist[{this->start.first, this->start.second, 0}] = 0;

        while (!pq.empty())
        {
            auto [d, r, c, dir] = pq.top();
            pq.pop();

            if (this->grid[r][c] == 'E')
            {
                return d;
            }

            for (int i = 0; i < 4; i++)
            {
                int nr = r + this->directions[i].first;
                int nc = c + this->directions[i].second;
                int nd = d + 1;

                if (i != dir)
                    nd += 1000;

                if (nr < 0 || nc < 0 || nr >= this->grid.size() || nc >= this->grid[0].size())
                    continue;
                if (this->grid[nr][nc] == '#')
                    continue;

                auto current = make_tuple(nr, nc, i);
                if (this->dist.find(current) == this->dist.end() || nd < this->dist[current])
                {
                    this->dist[current] = nd;
                    pq.push(make_tuple(nd, nr, nc, i));
                    this->predecessors[current].clear();
                    this->predecessors[current].push_back({r, c, dir});
                }
                else if (nd == this->dist[current])
                {
                    this->predecessors[current].push_back({r, c, dir});
                }
            }
        }

        return INT_MAX;
    }

    uint64_t backtrack()
    {
        auto [r, c] = this->end;

        set<pair<int, int>> unique_tiles;
        queue<tuple<int, int, int>> q;
        q.push({r, c, 0});
        q.push({r, c, 1});
        q.push({r, c, 2});
        q.push({r, c, 3});

        while (!q.empty())
        {
            auto [cr, cc, cdir] = q.front();
            q.pop();

            unique_tiles.insert({cr, cc});

            for (const auto &pred : this->predecessors[{cr, cc, cdir}])
            {
                q.push(pred);
            }
        }

        return unique_tiles.size();
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
        return this->dijkstra();
    }
    auto part2() -> uint64_t
    {
        this->dijkstra();
        return this->backtrack();
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