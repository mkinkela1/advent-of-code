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
    vector<pair<string, int>> instructions;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            string op = line.substr(0, 3);
            int arg = stoi(line.substr(4));
            this->instructions.push_back({op, arg});
        }
    }

    auto run(vector<pair<string, int>> instructions) -> pair<int, bool>
    {
        int acc = 0, i = 0;
        vector<bool> visited(instructions.size(), false);

        while (i < instructions.size() && !visited[i])
        {
            visited[i] = true;
            if (instructions[i].first == "acc")
            {
                acc += instructions[i].second;
                i++;
            }
            else if (instructions[i].first == "jmp")
            {
                i += instructions[i].second;
            }
            else
            {
                i++;
            }
        }

        return {acc, i == instructions.size()};
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
        return this->run(this->instructions).first;
    }
    auto part2() -> int
    {
        for (int i = 0; i < this->instructions.size(); i++)
        {
            if (this->instructions[i].first == "jmp")
            {
                this->instructions[i].first = "nop";
                auto [acc, terminated] = this->run(this->instructions);
                if (terminated)
                {
                    return acc;
                }
                this->instructions[i].first = "jmp";
            }
            else if (this->instructions[i].first == "nop")
            {
                this->instructions[i].first = "jmp";
                auto [acc, terminated] = this->run(this->instructions);
                if (terminated)
                {
                    return acc;
                }
                this->instructions[i].first = "nop";
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

    cout << "Part 1 test: " << test1.part1() << endl;
    cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}