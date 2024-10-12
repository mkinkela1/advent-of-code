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
    vector<int> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data.push_back(stoi(line));
        }
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long
    {
        for (int i = 0; i < this->data.size(); i++)
        {
            for (int j = i + 1; j < this->data.size(); j++)
            {
                if (this->data[i] + this->data[j] == 2020)
                {
                    return this->data[i] * this->data[j];
                }
            }
        }

        return 0;
    }

    auto part2() -> long long
    {
        for (int i = 0; i < this->data.size(); i++)
        {
            for (int j = i + 1; j < this->data.size(); j++)
            {
                for (int k = j + 1; k < this->data.size(); k++)
                {
                    if (this->data[i] + this->data[j] + this->data[k] == 2020)
                    {
                        return this->data[i] * this->data[j] * this->data[k];
                    }
                }
            }
        }

        return 0;
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