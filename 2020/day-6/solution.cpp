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
    vector<map<char, int>> data;
    vector<int> numberOfPeople;

    void parse()
    {
        string line;
        map<char, int> answers;
        int cnt = 0;
        while (getline(this->fin, line))
        {
            if (line.empty())
            {
                this->data.push_back(answers);
                this->numberOfPeople.push_back(cnt);
                cnt = 0;
                answers.clear();
                continue;
            }

            for (char c : line)
            {
                answers[c]++;
            }
            cnt++;
        }

        this->data.push_back(answers);
        this->numberOfPeople.push_back(cnt);
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
        for (auto answers : this->data)
        {
            sum += answers.size();
        }
        return sum;
    }
    auto part2() -> int
    {
        int sum = 0;
        for (int i = 0; i < this->data.size(); i++)
        {
            for (auto [key, value] : this->data[i])
            {
                if (this->numberOfPeople[i] == value)
                {
                    sum++;
                }
            }
        }
        return sum;
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