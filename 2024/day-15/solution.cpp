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
    vector<string> grid;
    string instructions;
    pair<int, int> position;
    map<char, pair<int, int>> directions = {
        {'^', make_pair(-1, 0)},
        {'v', make_pair(1, 0)},
        {'<', make_pair(0, -1)},
        {'>', make_pair(0, 1)}};
    map<char, char> opposite = {
        {'^', 'v'},
        {'v', '^'},
        {'<', '>'},
        {'>', '<'}};

    void parse()
    {

        string line;
        int i = 0;
        while (getline(this->fin, line))
        {
            if (line.empty())
                break;
            this->grid.push_back(line);
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == '@')
                {
                    this->position = make_pair(i, j);
                }
            }
            ++i;
        }

        while (getline(this->fin, line))
        {
            this->instructions += line;
        }
    }

    void move(vector<string> &grid, char direction, pair<int, int> &position)
    {
        pair<int, int> curr_pos = position;
        curr_pos.first += this->directions[direction].first;
        curr_pos.second += this->directions[direction].second;

        while (grid[curr_pos.first][curr_pos.second] == 'O')
        {
            curr_pos.first += this->directions[direction].first;
            curr_pos.second += this->directions[direction].second;
        }

        if (grid[curr_pos.first][curr_pos.second] == '#')
        {
            return;
        }

        while (curr_pos.first != position.first || curr_pos.second != position.second)
        {
            pair<int, int> next_pos = make_pair(
                curr_pos.first + this->directions[this->opposite[direction]].first,
                curr_pos.second + this->directions[this->opposite[direction]].second);

            swap(grid[curr_pos.first][curr_pos.second], grid[next_pos.first][next_pos.second]);

            curr_pos = next_pos;
        }

        position = make_pair(position.first + this->directions[direction].first,
                             position.second + this->directions[direction].second);
    }

    bool checkBlock(vector<string> grid, char direction, pair<int, int> position)
    {
        pair<int, int> curr_pos = position;
        curr_pos.first += this->directions[direction].first;
        curr_pos.second += this->directions[direction].second;

        if (grid[curr_pos.first][curr_pos.second] == '.')
            return true;
        if (grid[curr_pos.first][curr_pos.second] == '#')
            return false;
        if (grid[curr_pos.first][curr_pos.second] == '[')
            return checkBlock(grid, direction, curr_pos) &&
                   (this->directions[direction].second + 1 == 0
                        ? true
                        : checkBlock(grid, direction, make_pair(curr_pos.first, curr_pos.second + 1)));
        if (grid[curr_pos.first][curr_pos.second] == ']')
            return checkBlock(grid, direction, curr_pos) &&
                   (this->directions[direction].second - 1 == 0
                        ? true
                        : checkBlock(grid, direction, make_pair(curr_pos.first, curr_pos.second - 1)));

        return false;
    }

    void moveBlock(vector<string> &grid, char direction, pair<int, int> position)
    {
        pair<int, int> curr_pos = position;
        curr_pos.first += this->directions[direction].first;
        curr_pos.second += this->directions[direction].second;

        if (grid[curr_pos.first][curr_pos.second] == '.')
        {
            grid[curr_pos.first][curr_pos.second] = grid[position.first][position.second];
            grid[position.first][position.second] = '.';
        }
        else if (grid[curr_pos.first][curr_pos.second] == '[')
        {
            moveBlock(grid, direction, curr_pos);
            if (this->directions[direction].second == 0)
                moveBlock(grid, direction, make_pair(curr_pos.first, curr_pos.second + 1));

            grid[curr_pos.first][curr_pos.second] = grid[position.first][position.second];
            grid[position.first][position.second] = '.';
        }
        else if (grid[curr_pos.first][curr_pos.second] == ']')
        {
            moveBlock(grid, direction, curr_pos);
            if (this->directions[direction].second == 0)
                moveBlock(grid, direction, make_pair(curr_pos.first, curr_pos.second - 1));

            grid[curr_pos.first][curr_pos.second] = grid[position.first][position.second];
            grid[position.first][position.second] = '.';
        }
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
        uint64_t sol = 0;

        vector<string> grid = this->grid;

        for (auto instruction : this->instructions)
            this->move(grid, instruction, this->position);

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == 'O')
                    sol += i * 100 + j;

        return sol;
    }
    auto part2() -> uint64_t
    {
        uint64_t sol = 0;
        vector<string> grid;

        for (auto line : this->grid)
        {
            string row = "";
            for (auto c : line)
            {
                if (c == '@')
                    row.append("@.");
                else if (c == '#')
                    row.append("##");
                else if (c == '.')
                    row.append("..");
                else if (c == 'O')
                    row.append("[]");
            }

            grid.push_back(row);
        }

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == '@')
                    this->position = {i, j};

        for (auto instruction : this->instructions)
            if (this->checkBlock(grid, instruction, this->position))
            {
                this->moveBlock(grid, instruction, this->position);
                this->position = {this->position.first + this->directions[instruction].first,
                                  this->position.second + this->directions[instruction].second};
            }

        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                if (grid[i][j] == '[')
                    sol += i * 100 + j;

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