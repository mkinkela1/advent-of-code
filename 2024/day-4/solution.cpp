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
    vector<string> data;
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data.push_back(line);
        }
    }

    auto isXMas(int posX, int posY) -> bool
    {
        if (this->data[posX][posY] != 'A')
            return false;

        string s1 = string(1, this->data[posX - 1][posY - 1]) + string(1, this->data[posX][posY]) + string(1, this->data[posX + 1][posY + 1]);
        string s1r = string(1, this->data[posX + 1][posY + 1]) + string(1, this->data[posX][posY]) + string(1, this->data[posX - 1][posY - 1]);
        string s2 = string(1, this->data[posX - 1][posY + 1]) + string(1, this->data[posX][posY]) + string(1, this->data[posX + 1][posY - 1]);
        string s2r = string(1, this->data[posX + 1][posY - 1]) + string(1, this->data[posX][posY]) + string(1, this->data[posX - 1][posY + 1]);

        return ((s1 == "MAS" || s1r == "MAS") && (s2 == "MAS" || s2r == "MAS"));
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
        int sol = 0;

        for (int i = 0; i < this->data.size(); i++)
        {
            for (int j = 0; j < this->data[i].size(); j++)
            {
                if (this->data[i][j] == 'X')
                {
                    for (auto dir : this->directions)
                    {
                        int x = i, y = j;
                        string s = "";
                        for (int k = 0; k < 4; k++)
                        {
                            if (x >= 0 && x < this->data.size() && y >= 0 && y < this->data[i].size())
                            {
                                s += this->data[x][y];
                            }
                            x += dir.first;
                            y += dir.second;
                        }
                        if (s == "XMAS")
                        {
                            sol++;
                        }
                    }
                }
            }
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        for (int i = 1; i < this->data.size() - 1; i++)
        {
            for (int j = 1; j < this->data[i].size() - 1; j++)
            {
                if (this->data[i][j] == 'A')
                {

                    sol += isXMas(i, j);
                }
            }
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