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
    vector<string> pipes;
    pair<int, int> start;
    vector<vector<bool>> checked;
    vector<vector<int>> dist;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->pipes.push_back(line);
            for (int i = 0; i < line.size(); i++)
                if (line[i] == 'S')
                    this->start = make_pair(this->pipes.size() - 1, i);
        }

        for (int i = 0; i < this->pipes.size(); i++)
        {

            this->checked.push_back(vector<bool>(this->pipes[0].size(), false));
            this->dist.push_back(vector<int>(this->pipes[0].size(), 0));
        }

        queue<pair<int, int>> q;

        q.push(this->start);
        while (!q.empty())
        {
            auto [x, y] = q.front();
            checked[x][y] = true;
            q.pop();
            if (this->canGoLeft(x, y))
            {
                dist[x][y - 1] = dist[x][y] + 1;
                q.push(make_pair(x, y - 1));
            }
            if (this->canGoRight(x, y))
            {
                dist[x][y + 1] = dist[x][y] + 1;
                q.push(make_pair(x, y + 1));
            }
            if (this->canGoDown(x, y))
            {
                dist[x + 1][y] = dist[x][y] + 1;
                q.push(make_pair(x + 1, y));
            }
            if (this->canGoUp(x, y))
            {
                dist[x - 1][y] = dist[x][y] + 1;
                q.push(make_pair(x - 1, y));
            }
        }
    }

    auto canGoLeft(int x, int y) -> bool
    {
        if (this->pipes[x][y] != 'S' &&
            this->pipes[x][y] != '-' &&
            this->pipes[x][y] != 'J' &&
            this->pipes[x][y] != '7')
            return false;

        if (y - 1 < 0 || this->checked[x][y - 1])
            return false;

        if (this->pipes[x][y - 1] == '-')
            return true;
        if (this->pipes[x][y - 1] == 'F')
            return true;
        if (this->pipes[x][y - 1] == 'L')
            return true;
        return false;
    }

    auto canGoRight(int x, int y) -> bool
    {
        if (this->pipes[x][y] != 'S' &&
            this->pipes[x][y] != '-' &&
            this->pipes[x][y] != 'F' &&
            this->pipes[x][y] != 'L')
            return false;

        if (y + 1 >= this->pipes[0].size() || this->checked[x][y + 1])
            return false;

        if (this->pipes[x][y + 1] == '-')
            return true;
        if (this->pipes[x][y + 1] == 'J')
            return true;
        if (this->pipes[x][y + 1] == '7')
            return true;
        return false;
    }

    auto canGoUp(int x, int y) -> bool
    {
        if (this->pipes[x][y] != 'S' &&
            this->pipes[x][y] != '|' &&
            this->pipes[x][y] != 'J' &&
            this->pipes[x][y] != 'L')
            return false;

        if (x - 1 < 0 || this->checked[x - 1][y])
            return false;

        if (this->pipes[x - 1][y] == '|')
            return true;
        if (this->pipes[x - 1][y] == 'F')
            return true;
        if (this->pipes[x - 1][y] == '7')
            return true;
        return false;
    }

    auto canGoDown(int x, int y) -> bool
    {
        if (this->pipes[x][y] != 'S' &&
            this->pipes[x][y] != '|' &&
            this->pipes[x][y] != 'F' &&
            this->pipes[x][y] != '7')
            return false;
        if (x + 1 >= this->pipes.size() || this->checked[x + 1][y])
            return false;
        if (this->pipes[x + 1][y] == '|')
            return true;
        if (this->pipes[x + 1][y] == 'J')
            return true;
        if (this->pipes[x + 1][y] == 'L')
            return true;
        return false;
    }

    auto canPutVertical(int x, int y, vector<string> new_pipes) -> bool
    {
        if (new_pipes[x][y] != '.')
            return false;

        return (new_pipes[x - 1][y] == '|' || new_pipes[x - 1][y] == 'F' || new_pipes[x - 1][y] == '7' || new_pipes[x - 1][y] == 'S') &&
               (new_pipes[x + 1][y] == '|' || new_pipes[x + 1][y] == 'J' || new_pipes[x + 1][y] == 'L' || new_pipes[x + 1][y] == 'S');
    }

    auto canPutHorizontal(int x, int y, vector<string> new_pipes) -> bool
    {
        if (new_pipes[x][y] != '.')
            return false;

        return (new_pipes[x][y - 1] == '-' || new_pipes[x][y - 1] == 'F' || new_pipes[x][y - 1] == 'L' || new_pipes[x][y - 1] == 'S') &&
               (new_pipes[x][y + 1] == '-' || new_pipes[x][y + 1] == 'J' || new_pipes[x][y + 1] == '7' || new_pipes[x][y + 1] == 'S');
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
        int maxDist = 0;
        for (int i = 0; i < this->pipes.size(); i++)
            for (int j = 0; j < this->pipes[0].size(); j++)
                if (this->dist[i][j] > maxDist)
                    maxDist = this->dist[i][j];

        return maxDist;
    }
    auto part2() -> int
    {
        int sol = 0;

        vector<string> new_pipes;
        string tmp = "";

        for (int i = 0; i < this->pipes[0].size() * 2 + 1; i++)
            tmp += ".";

        for (int i = 0; i < this->pipes.size(); i++)
        {
            new_pipes.push_back(tmp);

            string line = "";
            for (int j = 0; j < this->pipes[0].size(); j++)
            {
                line += ".";
                if (this->checked[i][j])
                    line += this->pipes[i][j];
                else
                    line += ".";
            }

            line += ".";
            new_pipes.push_back(line);
        }

        new_pipes.push_back(tmp);

        for (int i = 1; i < new_pipes.size() - 1; i++)
        {
            for (int j = 1; j < new_pipes[0].size() - 1; j++)
            {
                if (new_pipes[i][j] != '.')
                    continue;
                if (canPutVertical(i, j, new_pipes))
                {
                    new_pipes[i][j] = '|';
                }
                else if (canPutHorizontal(i, j, new_pipes))
                {
                    new_pipes[i][j] = '-';
                }
            }
        }

        queue<pair<int, int>> q;
        q.push(make_pair(0, 0));
        vector<vector<bool>> checked(new_pipes.size(), vector<bool>(new_pipes[0].size(), false));

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            checked[x][y] = true;

            for (int i = 0; i < 4; i++)
            {
                int newX = x + "0121"[i] - '1';
                int newY = y + "1210"[i] - '1';
                if (newX < 0 || newX >= new_pipes.size() || newY < 0 || newY >= new_pipes[0].size())
                    continue;
                if (checked[newX][newY])
                    continue;
                if (new_pipes[newX][newY] == '.')
                {
                    checked[newX][newY] = true;
                    q.push(make_pair(newX, newY));
                }
            }
        }

        vector<string> checked_pipes;

        for (int i = 0; i < new_pipes.size(); i++)
        {
            string line = "";
            for (int j = 0; j < new_pipes[0].size(); j++)
            {
                if (checked[i][j])
                    line += "#";
                else
                    line += new_pipes[i][j];
            }

            checked_pipes.push_back(line);
        }

        vector<string> final_pipes;
        for (int i = 1; i < checked_pipes.size(); i += 2)
        {
            string line = "";
            for (int j = 1; j < checked_pipes[0].size(); j += 2)
                line += checked_pipes[i][j];

            final_pipes.push_back(line);
        }

        for (auto line : final_pipes)
            for (auto c : line)
                if (c == '.')
                    sol++;
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