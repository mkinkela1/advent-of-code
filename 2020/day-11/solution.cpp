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
    int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
        }
    }

    auto countAdjacentOccupiedSeats(vector<string> grid, int x, int y) -> int
    {
        int count = 0;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size())
            {
                continue;
            }

            if (grid[nx][ny] == '#')
            {
                count++;
            }
        }

        return count;
    }

    auto countVisibleOccupiedSeats(vector<string> grid, int x, int y) -> int
    {
        int count = 0;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            while (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size())
            {
                if (grid[nx][ny] == '#')
                {
                    count++;
                    break;
                }
                else if (grid[nx][ny] == 'L')
                {
                    break;
                }

                nx += dx[i];
                ny += dy[i];
            }
        }

        return count;
    }

    auto changeState(vector<string> currentState, int numberOfOccupiedSeats, function<int(vector<string>, int, int)> countFunction) -> vector<string>
    {
        vector<string> nextState = currentState;
        int rows = currentState.size();
        int cols = currentState[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (currentState[i][j] == 'L' && countFunction(currentState, i, j) == 0)
                {
                    nextState[i][j] = '#';
                }
                else if (currentState[i][j] == '#' && countFunction(currentState, i, j) >= numberOfOccupiedSeats)
                {
                    nextState[i][j] = 'L';
                }
            }
        }

        return nextState;
    }

    auto equalStates(vector<string> a, vector<string> b) -> bool
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }

        return true;
    }

    auto countOccupiedSeats(vector<string> grid) -> int
    {
        int count = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == '#')
                {
                    count++;
                }
            }
        }

        return count;
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
        vector<string> gridCopy = this->grid;

        while (true)
        {
            auto countFunction = [this](vector<string> gridCopy, int x, int y)
            {
                return this->countAdjacentOccupiedSeats(gridCopy, x, y);
            };

            vector<string> currentState = gridCopy;
            vector<string> nextState = this->changeState(gridCopy, 4, countFunction);

            gridCopy = nextState;

            if (this->equalStates(currentState, nextState))
            {
                return this->countOccupiedSeats(nextState);
            }
        }
    }
    auto part2() -> int
    {
        vector<string> gridCopy = this->grid;

        while (true)
        {
            auto countFunction = [this](vector<string> gridCopy, int x, int y)
            {
                return this->countVisibleOccupiedSeats(gridCopy, x, y);
            };
            vector<string> currentState = gridCopy;
            vector<string> nextState = this->changeState(gridCopy, 5, countFunction);

            gridCopy = nextState;

            if (this->equalStates(currentState, nextState))
            {
                return this->countOccupiedSeats(nextState);
            }
        }
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