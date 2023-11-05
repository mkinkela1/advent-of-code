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

const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

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

    auto numberOfLightsOn(vector<string> input) -> int
    {
        int sol = 0;

        for (auto line : input)
            for (auto c : line)
                if (c == '#')
                    ++sol;

        return sol;
    }

    auto checkNeighbours(int x, int y, vector<string> input) -> int
    {
        int n = input.size();
        int m = input[0].size();
        int sol = 0;

        for (int i = 0; i < 8; ++i)
        {
            int posX = x + dx[i];
            int posY = y + dy[i];

            if (posX < 0 || posX >= n || posY < 0 || posY >= m)
                continue;

            if (input[posX][posY] == '#')
                ++sol;
        }

        return sol;
    }

    auto isCorner(int x, int y, int n, int m) -> bool
    {
        if (x == 0 && y == 0)
            return true;
        if (x == 0 && y == m - 1)
            return true;
        if (x == n - 1 && y == 0)
            return true;
        if (x == n - 1 && y == m - 1)
            return true;

        return false;
    }

    auto step(vector<string> &input, bool shouldCheckCorners = true) -> void
    {
        int n = input.size();
        int m = input[0].size();

        vector<string> currentInput = input;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (shouldCheckCorners == false && this->isCorner(i, j, n, m))
                    continue;

                int numberOfNeighboursOn = this->checkNeighbours(i, j, currentInput);

                // on
                if (input[i][j] == '#')
                {
                    if (numberOfNeighboursOn == 2 || numberOfNeighboursOn == 3)
                        input[i][j] = '#';
                    else
                        input[i][j] = '.';
                }
                // off
                else
                {
                    if (numberOfNeighboursOn == 3)
                        input[i][j] = '#';
                    else
                        input[i][j] = '.';
                }
            }
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        vector<string> input = this->input;

        for (int i = 0; i < 100; ++i)
            this->step(input);

        return this->numberOfLightsOn(input);
    }
    auto part2() -> int
    {
        vector<string> input = this->input;
        int n = input.size();
        int m = input[0].size();

        input[0][0] = '#';
        input[0][m - 1] = '#';
        input[n - 1][0] = '#';
        input[n - 1][m - 1] = '#';

        for (int i = 0; i < 100; ++i)
            this->step(input, false);

        return this->numberOfLightsOn(input);
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}