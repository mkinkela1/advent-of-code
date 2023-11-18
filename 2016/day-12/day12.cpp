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

enum Operation
{
    CPY,
    INC,
    DEC,
    JNZ
};

class Solution
{
private:
    fstream fin;
    vector<tuple<Operation, string, string>> instructions;

    void parse()
    {
        string line;

        while (getline(this->fin, line))
        {
            Operation op;
            char arg1[20], arg2[20];

            if (line.find("cpy") != string::npos)
            {
                sscanf(line.c_str(), "cpy %s %s", arg1, arg2);
                this->instructions.push_back(make_tuple(Operation::CPY, arg1, arg2));
            }
            else if (line.find("inc") != string::npos)
            {
                sscanf(line.c_str(), "inc %s", arg1);
                this->instructions.push_back(make_tuple(Operation::INC, arg1, ""));
            }
            else if (line.find("dec") != string::npos)
            {
                sscanf(line.c_str(), "dec %s", arg1);
                this->instructions.push_back(make_tuple(Operation::DEC, arg1, ""));
            }
            else if (line.find("jnz") != string::npos)
            {
                sscanf(line.c_str(), "jnz %s %s", arg1, arg2);
                this->instructions.push_back(make_tuple(Operation::JNZ, arg1, arg2));
            }
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        map<string, int> registers = {
            {"a", 0},
            {"b", 0},
            {"c", 0},
            {"d", 0}};

        int pos = 0;

        while (pos < this->instructions.size())
        {
            auto [op, arg1, arg2] = this->instructions[pos];

            switch (op)
            {
            case Operation::CPY:
                if (registers.find(arg2) != registers.end())
                {
                    if (registers.find(arg1) != registers.end())
                    {
                        registers[arg2] = registers[arg1];
                    }
                    else
                    {
                        registers[arg2] = stoi(arg1);
                    }
                }
                ++pos;
                break;
            case Operation::INC:
                if (registers.find(arg1) != registers.end())
                {
                    registers[arg1]++;
                }
                ++pos;
                break;
            case Operation::DEC:
                if (registers.find(arg1) != registers.end())
                {
                    registers[arg1]--;
                }
                ++pos;
                break;
            case Operation::JNZ:
                if (registers.find(arg1) != registers.end())
                {
                    if (registers[arg1] != 0)
                        pos += stoi(arg2);
                    else
                        ++pos;
                }
                else
                {
                    if (stoi(arg1) != 0)
                        pos += stoi(arg2);
                    else
                        ++pos;
                }
                break;
            }
        }

        return registers["a"];
    }
    auto part2() -> int
    {
        map<string, int> registers = {
            {"a", 0},
            {"b", 0},
            {"c", 1},
            {"d", 0}};

        int pos = 0;

        while (pos < this->instructions.size())
        {
            auto [op, arg1, arg2] = this->instructions[pos];

            switch (op)
            {
            case Operation::CPY:
                if (registers.find(arg2) != registers.end())
                {
                    if (registers.find(arg1) != registers.end())
                    {
                        registers[arg2] = registers[arg1];
                    }
                    else
                    {
                        registers[arg2] = stoi(arg1);
                    }
                }
                ++pos;
                break;
            case Operation::INC:
                if (registers.find(arg1) != registers.end())
                {
                    registers[arg1]++;
                }
                ++pos;
                break;
            case Operation::DEC:
                if (registers.find(arg1) != registers.end())
                {
                    registers[arg1]--;
                }
                ++pos;
                break;
            case Operation::JNZ:
                if (registers.find(arg1) != registers.end())
                {
                    if (registers[arg1] != 0)
                        pos += stoi(arg2);
                    else
                        ++pos;
                }
                else
                {
                    if (stoi(arg1) != 0)
                        pos += stoi(arg2);
                    else
                        ++pos;
                }
                break;
            }
        }

        return registers["a"];
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}