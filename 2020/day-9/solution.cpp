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
    vector<uint64_t> numbers;
    vector<uint64_t> prevSum;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->numbers.push_back(stoll(line));
        }

        this->prevSum = vector<uint64_t>(this->numbers.size(), 0);
        this->prevSum[0] = this->numbers[0];
        for (int i = 1; i < this->numbers.size(); i++)
        {
            this->prevSum[i] = this->prevSum[i - 1] + this->numbers[i];
        }
    }

    auto findSum(vector<uint64_t> numbers, uint64_t target) -> bool
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            for (int j = i + 1; j < numbers.size(); j++)
            {
                if (numbers[i] + numbers[j] == target)
                {
                    return true;
                }
            }
        }
        return false;
    }

    auto getContiguous(uint64_t target) -> vector<uint64_t>
    {
        for (int i = 1; i < this->numbers.size(); i++)
        {
            for (int j = i + 1; j < this->numbers.size(); j++)
            {
                if (this->prevSum[j] - this->prevSum[i - 1] == target)
                {
                    return vector<uint64_t>(numbers.begin() + i, numbers.begin() + j + 1);
                }
            }
        }

        return vector<uint64_t>();
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1(int preamble) -> uint64_t
    {
        for (int i = preamble; i < this->numbers.size(); i++)
        {
            vector<uint64_t> prev(this->numbers.begin() + i - preamble, this->numbers.begin() + i);
            if (!this->findSum(prev, this->numbers[i]))
            {
                return this->numbers[i];
            }
        }
        return -1;
    }
    auto part2(int preamble) -> uint64_t
    {
        for (int i = preamble; i < this->numbers.size(); i++)
        {
            vector<uint64_t> prev(this->numbers.begin() + i - preamble, this->numbers.begin() + i);
            if (!this->findSum(prev, this->numbers[i]))
            {
                vector<uint64_t> contiguous = getContiguous(this->numbers[i]);

                uint64_t min = *min_element(contiguous.begin(), contiguous.end());
                uint64_t max = *max_element(contiguous.begin(), contiguous.end());

                cout << "Contiguous: " << min << " " << max << endl;

                return min + max;
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

    cout << "Part 1 test: " << test1.part1(5) << endl;
    cout << "Part 1: " << aoc.part1(25) << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2(5) << endl;
    cout << "Part 2: " << aoc.part2(25) << endl;

    return 0;
}