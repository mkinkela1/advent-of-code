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
#include <set>

using namespace std;

int dx[] = {1, 0, -1, 0, 1, -1, 1, -1};
int dy[] = {0, 1, 0, -1, 1, -1, -1, 1};

class Solution
{
private:
    fstream fin;
    vector<string> input;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
            this->input.push_back(line);
    }

    bool checkSymbol(int i, int j)
    {
        int n = this->input.size();
        int m = this->input[i].size();

        for (int k = 0; k < 8; k++)
        {
            if (i + dx[k] < 0 || i + dx[k] >= n || j + dy[k] < 0 || j + dy[k] >= m)
                continue;
            char tmp = this->input[i + dx[k]][j + dy[k]];
            if (!isdigit(tmp) && tmp != '.')
                return true;
        }

        return false;
    }

    pair<pair<int, int>, int> getNumber(int i, int j)
    {
        int n = this->input.size();
        int m = this->input[i].size();
        pair<int, int> begin = make_pair(i, j);
        int num = 0;

        while (j - 1 >= 0 && isdigit(this->input[i][j - 1]))
            j--;

        begin = make_pair(i, j);

        while (isdigit(this->input[i][j]))
        {
            num = num * 10 + (this->input[i][j] - '0');
            j++;
        }

        return make_pair(begin, num);
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

        for (int i = 0; i < this->input.size(); i++)
        {
            int num = 0;
            bool hasSymbol = false;
            for (int j = 0; j < this->input[i].size(); j++)
            {
                if (isdigit(this->input[i][j]))
                {
                    hasSymbol |= this->checkSymbol(i, j);
                    num = num * 10 + (this->input[i][j] - '0');
                }
                else
                {
                    if (hasSymbol)
                        sum += num;

                    num = 0;
                    hasSymbol = false;
                }

                if (j == this->input[i].size() - 1 && hasSymbol)
                    sum += num;
            }
        }

        return sum;
    }
    auto part2() -> long long
    {
        long long sum = 0;

        for (int i = 0; i < this->input.size(); i++)
        {
            for (int j = 0; j < this->input[i].size(); j++)
            {

                if (this->input[i][j] == '*')
                {
                    map<pair<int, int>, int> numbers;
                    for (int k = 0; k < 8; k++)
                    {
                        int x = i + dx[k];
                        int y = j + dy[k];
                        if (x < 0 || x >= this->input.size() || y < 0 || y >= this->input[i].size())
                            continue;

                        if (isdigit(this->input[x][y]))
                            numbers.insert(this->getNumber(x, y));
                    }
                    if (numbers.size() == 2)
                    {
                        long long prod = 1;
                        for (auto it = numbers.begin(); it != numbers.end(); it++)
                            prod *= it->second;

                        sum += prod;
                    }
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