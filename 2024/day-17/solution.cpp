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

class Solution
{
private:
    fstream fin;
    map<char, uint64_t> registers;
    vector<uint64_t> instructions;
    string programOutput;

    void parse()
    {
        string line;
        getline(this->fin, line);
        vector<string> parts = split(line, " ");
        registers['A'] = stoi(parts[2]);

        getline(this->fin, line);
        parts = split(line, " ");
        registers['B'] = stoi(parts[2]);

        getline(this->fin, line);
        parts = split(line, " ");
        registers['C'] = stoi(parts[2]);

        getline(this->fin, line);

        getline(this->fin, line);
        parts = split(line, " ");
        this->programOutput = parts[1];
        parts = split(parts[1], ",");

        for (auto &part : parts)
        {
            instructions.push_back(stoi(part));
        }
    }

    uint64_t getComboOperand(uint64_t operand)
    {
        if (operand <= 3)
            return operand;
        if (operand == 4)
            return this->registers['A'];
        if (operand == 5)
            return this->registers['B'];
        if (operand == 6)
            return this->registers['C'];
        return -1;
    }

    vector<uint64_t> program(uint64_t A)
    {
        vector<uint64_t> result;

        uint64_t pouint64_ter = 0;

        this->registers['A'] = A;

        while (pouint64_ter < this->instructions.size())
        {
            uint64_t code = this->instructions[pouint64_ter];
            uint64_t operand = this->instructions[pouint64_ter + 1];
            uint64_t comboOperand = this->getComboOperand(operand);
            bool jumped = false;

            if (this->instructions[pouint64_ter] == 0)
            {
                this->registers['A'] = this->registers['A'] / (1 << comboOperand);
            }
            else if (this->instructions[pouint64_ter] == 1)
            {
                this->registers['B'] = this->registers['B'] ^ operand;
            }
            else if (this->instructions[pouint64_ter] == 2)
            {
                this->registers['B'] = comboOperand % 8;
            }
            else if (this->instructions[pouint64_ter] == 3)
            {
                if (this->registers['A'] != 0)
                {
                    pouint64_ter = operand;
                    jumped = true;
                }
            }
            else if (this->instructions[pouint64_ter] == 4)
            {
                this->registers['B'] = this->registers['B'] ^ this->registers['C'];
            }
            else if (this->instructions[pouint64_ter] == 5)
            {
                result.push_back(comboOperand % 8);
            }
            else if (this->instructions[pouint64_ter] == 6)
            {
                this->registers['B'] = this->registers['A'] / (1 << comboOperand);
            }
            else if (this->instructions[pouint64_ter] == 7)
            {
                this->registers['C'] = this->registers['A'] / (1 << comboOperand);
            }

            if (!jumped)
                pouint64_ter += 2;
        }

        return result;
    }

    uint64_t rec(vector<uint64_t> program, uint64_t pouint64_ter, uint64_t curr)
    {
        for (uint64_t i = 0; i < 8; ++i)
        {
            uint64_t newCurr = (curr << 3) + i;
            vector<uint64_t> newProgram = this->program(newCurr);
            vector<uint64_t> programCut = vector<uint64_t>(program.begin() + pouint64_ter, program.end());

            if (equal(newProgram.begin(), newProgram.end(), programCut.begin()))
            {
                if (pouint64_ter == 0)
                    return newCurr;

                uint64_t result = this->rec(program, pouint64_ter - 1, newCurr);
                if (result != -1)
                    return result;
            }
        }

        return -1;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> string
    {
        vector<uint64_t> sol = this->program(this->registers['A']);
        string result = "";

        for (uint64_t i = 0; i < sol.size(); i++)
        {
            result += to_string(sol[i]);
            if (i != sol.size() - 1)
                result += ",";
        }

        return result;
    }
    auto part2() -> uint64_t
    {
        return this->rec(this->instructions, this->instructions.size() - 1, 0);
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