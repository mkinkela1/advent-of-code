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
#include <cmath>
#include <algorithm>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<int> data1, data2;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> temp = split(line, "   ");

            this->data1.push_back(stoi(temp[0]));
            this->data2.push_back(stoi(temp[1]));
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
        int diff = 0;

        sort(this->data1.begin(), this->data1.end());
        sort(this->data2.begin(), this->data2.end());

        for (int i = 0; i < this->data1.size(); i++)
        {
            long d = this->data1[i] - this->data2[i];
            diff += abs(d);
        }

        return diff;
    }
    auto part2() -> long long
    {
        long long sol = 0;

        sort(this->data1.begin(), this->data1.end());
        sort(this->data2.begin(), this->data2.end());

        for (int i = 0; i < this->data1.size(); i++)
        {
            long long cnt = 0;
            for (int j = 0; j < this->data1.size(); j++)
            {
                if (this->data1[i] == this->data2[j])
                {
                    cnt++;
                }
            }

            sol += cnt * this->data1[i];
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