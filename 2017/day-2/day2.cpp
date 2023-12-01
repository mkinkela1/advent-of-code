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
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<vector<int>> spreadsheet;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<int> row;

            for (auto number : split(line, "\t"))
                row.push_back(stoi(number));

            this->spreadsheet.push_back(row);
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sum = 0;

        for (auto row : this->spreadsheet)
            sum += *max_element(row.begin(), row.end()) - *min_element(row.begin(), row.end());

        return sum;
    }
    auto part2() -> int
    {
        int sum = 0;

        for (auto row : this->spreadsheet)
            for (int i = 0; i < row.size(); i++)
                for (int j = 0; j < row.size(); j++)
                    if (i != j && row[i] % row[j] == 0)
                        sum += row[i] / row[j];

        return sum;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}