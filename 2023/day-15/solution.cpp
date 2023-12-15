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

class Lens
{
private:
    int hash;
    string label;
    int focalLength;

    auto calculateHash() -> int
    {
        int tmp = 0;
        for (auto c : this->label)
        {
            tmp += int(c);
            tmp *= 17;
            tmp %= 256;
        }
        return tmp;
    }

public:
    Lens(string label, int focalLength = 0)
    {
        this->label = label;
        this->focalLength = focalLength;
        this->hash = this->calculateHash();
    }

    auto getHash() -> int
    {
        return this->hash;
    }

    auto getLabel() -> string
    {
        return this->label;
    }

    auto getFocalLength() -> int
    {
        return this->focalLength;
    }

    auto setFocalLength(int focalLength) -> void
    {
        this->focalLength = focalLength;
    }
};

class Solution
{
private:
    fstream fin;
    vector<string> input;

    void parse()
    {
        string line;
        getline(this->fin, line);

        this->input = split(line, ",");
    }

    auto hash(string str, long long &tmp) -> void
    {
        for (auto c : str)
        {
            tmp += int(c);
            tmp *= 17;
            tmp %= 256;
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
        long long sol = 0;

        for (auto str : this->input)
        {
            long long tmp = 0;
            this->hash(str, tmp);
            sol += tmp;
        }

        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0;

        vector<vector<Lens>> box(256);

        for (auto str : this->input)
        {
            if (str.find('-') != string::npos)
            {
                string tmp = str.substr(0, str.find('-'));
                Lens len = Lens(tmp);
                int hash = len.getHash();

                int pos = -1;
                for (int i = 0; i < box[hash].size(); i++)
                {
                    if (box[hash][i].getLabel() == tmp)
                    {
                        pos = i;
                        break;
                    }
                }

                if (pos != -1)
                    box[hash].erase(box[hash].begin() + pos);
            }
            else
            {
                vector<string> tmp = split(str, "=");
                Lens len = Lens(tmp[0], stoi(tmp[1]));
                int hash = len.getHash();

                int pos = -1;
                for (int i = 0; i < box[hash].size(); i++)
                {
                    if (box[hash][i].getLabel() == tmp[0])
                    {
                        pos = i;
                        break;
                    }
                }

                if (pos != -1)
                    box[hash][pos].setFocalLength(stoi(tmp[1]));
                else
                    box[hash].push_back(len);
            }
        }
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < box[i].size(); j++)
                sol += (i + 1) * (j + 1) * box[i][j].getFocalLength();

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