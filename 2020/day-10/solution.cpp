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
#include <algorithm>
#include <cmath>

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<int64_t> numbers;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->numbers.push_back(stoll(line));
        }

        sort(this->numbers.begin(), this->numbers.end());
        this->numbers.insert(this->numbers.begin(), 0);
        int64_t max = *max_element(this->numbers.begin(), this->numbers.end());
        this->numbers.push_back(max + 3);
    }

    auto numberOfArrangements() -> int64_t
    {
        int n = this->numbers.size();
        vector<int64_t> dp(n, 0);

        dp[0] = 1;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n && this->numbers[j] - this->numbers[i] <= 3; j++)
            {
                dp[j] += dp[i];
            }
        }

        return dp[n - 1];
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int64_t
    {
        int64_t one = 0;
        int64_t three = 0;
        for (int i = 1; i < this->numbers.size(); i++)
        {
            if (this->numbers[i] - this->numbers[i - 1] == 1)
            {
                one++;
            }
            else if (this->numbers[i] - this->numbers[i - 1] == 3)
            {
                three++;
            }
        }
        return one * three;
    }
    auto part2() -> int64_t
    {
        return this->numberOfArrangements();
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