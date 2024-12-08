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
    vector<string> data;
    map<char, vector<pair<int, int>>> antenna;

    void parse()
    {
        string line;
        int r = 0;
        while (getline(this->fin, line))
        {
            this->data.push_back(line);

            for (int c = 0; c < line.size(); c++)
            {
                if (line[c] != '.')
                {
                    this->antenna[line[c]].push_back({r, c});
                }
            }

            ++r;
        }
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
        set<pair<int, int>> antinode;

        for (auto [key, antennas] : this->antenna)
        {
            if (antennas.size() < 2)
                continue;

            for (int i = 0; i < antennas.size(); i++)
            {
                for (int j = i + 1; j < antennas.size(); j++)
                {
                    int x1 = antennas[i].first;
                    int y1 = antennas[i].second;
                    int x2 = antennas[j].first;
                    int y2 = antennas[j].second;

                    int dx = x2 - x1;
                    int dy = y2 - y1;

                    int ax1 = x1 - dx;
                    int ay1 = y1 - dy;

                    int ax2 = x2 + dx;
                    int ay2 = y2 + dy;

                    if (ax1 >= 0 && ax1 < this->data.size() && ay1 >= 0 && ay1 < this->data[0].size())
                    {
                        antinode.insert({ax1, ay1});
                    }

                    if (ax2 >= 0 && ax2 < this->data.size() && ay2 >= 0 && ay2 < this->data[0].size())
                    {
                        antinode.insert({ax2, ay2});
                    }
                }
            }
        }

        return antinode.size();
    }
    auto part2() -> int
    {
        set<pair<int, int>> antinode;

        for (auto [key, antennas] : this->antenna)
        {
            if (antennas.size() < 2)
                continue;

            for (int i = 0; i < antennas.size(); i++)
            {
                for (int j = i + 1; j < antennas.size(); j++)
                {
                    int x1 = antennas[i].first;
                    int y1 = antennas[i].second;
                    int x2 = antennas[j].first;
                    int y2 = antennas[j].second;

                    antinode.insert({x1, y1});
                    antinode.insert({x2, y2});

                    int dx = x2 - x1;
                    int dy = y2 - y1;

                    int ax1 = x1 - dx;
                    int ay1 = y1 - dy;

                    while (ax1 >= 0 && ax1 < this->data.size() && ay1 >= 0 && ay1 < this->data[0].size())
                    {
                        antinode.insert({ax1, ay1});
                        ax1 -= dx;
                        ay1 -= dy;
                    }

                    int ax2 = x2 + dx;
                    int ay2 = y2 + dy;

                    while (ax2 >= 0 && ax2 < this->data.size() && ay2 >= 0 && ay2 < this->data[0].size())
                    {
                        antinode.insert({ax2, ay2});
                        ax2 += dx;
                        ay2 += dy;
                    }
                }
            }
        }

        return antinode.size();
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