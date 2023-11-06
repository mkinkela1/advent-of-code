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
#include <string>

using namespace std;

enum InstructionType
{
    HLF,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
};

class Instruction
{
private:
    InstructionType type;
    string reg;
    int value;

public:
    Instruction(InstructionType type, string reg, int value = 0)
    {
        this->type = type;
        this->reg = reg;
        this->value = value;
    }

    auto get_type() -> InstructionType { return this->type; }
    auto get_reg() -> string { return this->reg; }
    auto get_value() -> int { return this->value; }
};

class Solution
{
private:
    fstream fin;
    vector<Instruction> instructions;

    void parse()
    {
        string line;
        char type[20], reg[20];
        int value;
        char sign;
        while (getline(this->fin, line))
        {
            if (line[0] == 'h')
            {
                sscanf(line.c_str(), "%s %s", type, reg);
                this->instructions.push_back(Instruction(InstructionType::HLF, reg));
            }
            else if (line[0] == 't')
            {
                sscanf(line.c_str(), "%s %s", type, reg);
                this->instructions.push_back(Instruction(InstructionType::TPL, reg, 0));
            }
            else if (line[0] == 'i')
            {
                sscanf(line.c_str(), "%s %s", type, reg);
                this->instructions.push_back(Instruction(InstructionType::INC, reg, 0));
            }
            else if (line[0] == 'j')
            {
                if (line[1] == 'm')
                {
                    sscanf(line.c_str(), "%s %d", type, &value);
                    this->instructions.push_back(Instruction(InstructionType::JMP, "", value));
                }
                else if (line[2] == 'e')
                {
                    sscanf(line.c_str(), "%s %s %c%d", type, reg, &sign, &value);
                    if (sign == '-')
                        value *= -1;
                    string r{reg[0]};
                    this->instructions.push_back(Instruction(InstructionType::JIE, r, value));
                }
                else if (line[2] == 'o')
                {
                    sscanf(line.c_str(), "%s %s %c%d", type, reg, &sign, &value);
                    if (sign == '-')
                        value *= -1;

                    string r{reg[0]};
                    this->instructions.push_back(Instruction(InstructionType::JIO, r, value));
                }
            }
        }
    }

    auto solve(long long unsigned a, long long unsigned b) -> long long unsigned
    {
        map<string, long long unsigned> registers;
        registers["a"] = a;
        registers["b"] = b;

        int pos = 0;

        while (true)
        {
            if (pos < 0 || pos >= this->instructions.size())
                return registers["b"];

            Instruction instruction = this->instructions[pos];

            switch (instruction.get_type())
            {
            case InstructionType::HLF:
                registers[instruction.get_reg()] /= 2;
                pos++;
                break;
            case InstructionType::TPL:
                registers[instruction.get_reg()] *= 3;
                pos++;
                break;
            case InstructionType::INC:
                registers[instruction.get_reg()]++;
                pos++;
                break;
            case InstructionType::JMP:
                pos += instruction.get_value();
                break;
            case InstructionType::JIE:
                if (registers[instruction.get_reg()] % 2 == 0)
                    pos += instruction.get_value();
                else
                    pos++;
                break;
            case InstructionType::JIO:
                if (registers[instruction.get_reg()] == 1)
                    pos += instruction.get_value();
                else
                    pos++;
                break;
            }
        }

        return registers["b"];
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> long long unsigned
    {
        return this->solve(0, 0);
    }
    auto part2() -> long long unsigned { return this->solve(1, 0); }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}