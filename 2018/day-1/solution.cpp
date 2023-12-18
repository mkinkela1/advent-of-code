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
    vector<int> input;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(stoi(line));
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
        int sum = 0;
        for (auto i : this->input)
        {
            sum += i;
        }
        return sum;
    }
    auto part2() -> int
    {
        map<int, int> visited;

        int sum = 0;
        visited[sum]++;

        while (true)
            for (auto i : this->input)
            {
                sum += i;
                ++visited[sum];

                if (visited[sum] > 1)
                {
                    return sum;
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