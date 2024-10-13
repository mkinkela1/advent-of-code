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
    map<int, bool> data;

    int getSeatId(string line)
    {
        int row = 0;
        int col = 0;
        for (int i = 0; i < 7; i++)
        {
            if (line[i] == 'B')
                row += 1 << (6 - i);
        }
        for (int i = 0; i < 3; i++)
        {
            if (line[i + 7] == 'R')
                col += 1 << (2 - i);
        }
        return row * 8 + col;
    }

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int seatId = getSeatId(line);
            data[seatId] = true;
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
        int maxSeatId = 0;
        for (auto seat : this->data)
        {
            maxSeatId = max(maxSeatId, seat.first);
        }
        return maxSeatId;
    }
    auto part2() -> int
    {
        for (int i = 1; i < 1023; i++)
        {
            if (this->data[i - 1] && !this->data[i] && this->data[i + 1])
            {
                return i;
            }
        }
        return -1;
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