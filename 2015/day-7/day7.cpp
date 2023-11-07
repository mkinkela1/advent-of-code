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
    AND,
    OR,
    NOT,
    LSHIFT,
    RSHIFT,
    ASSIGN
};

class Instruction
{
private:
    Operation operation;
    int value;
    int shift;
    string input1, input2;

public:
    Instruction()
    {
        this->value = -1;
    }

    auto setOperation(Operation operation) -> Instruction
    {
        this->operation = operation;
        return *this;
    }

    auto setValue(int value) -> Instruction
    {
        this->value = value;
        return *this;
    }

    auto setInput1(string input1) -> Instruction
    {
        this->input1 = input1;
        return *this;
    }

    auto setInput2(string input2) -> Instruction
    {
        if (this->operation != Operation::AND && this->operation != Operation::OR)
            throw "Input2 can be set only for AND and OR operations";
        this->input2 = input2;
        return *this;
    }

    auto setShift(int shift) -> Instruction
    {
        if (this->operation != Operation::LSHIFT && this->operation != Operation::RSHIFT)
            throw "Shift can be set only for LSHIFT and RSHIFT operations";
        this->shift = shift;
        return *this;
    }

    auto build() -> Instruction
    {
        return *this;
    }

    auto getOperation() -> Operation
    {
        return this->operation;
    }

    auto getValue() -> int
    {
        return this->value;
    }

    auto getShift() -> int
    {
        return this->shift;
    }

    auto getInput1() -> string
    {
        return this->input1;
    }

    auto getInput2() -> string
    {
        return this->input2;
    }
};

class Solution
{
private:
    fstream fin;
    map<string, Instruction> instructions;
    map<string, int> wires;

    auto is_number(const std::string &s) -> bool
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](unsigned char c)
                                          { return !std::isdigit(c); }) == s.end();
    }

    void parse()
    {
        string line;
        char input1[20], input2[20], wireName[20];
        int value, shift;
        Instruction instruction;
        string i1, i2, wire;
        while (getline(this->fin, line))
        {
            Operation operation = this->getOperation(line);

            switch (operation)
            {
            case Operation::AND: // x AND y -> z
                sscanf(line.c_str(), "%s AND %s -> %s", input1, input2, wireName);
                i1 = (string)input1;
                i2 = (string)input2;
                wire = (string)wireName;

                instruction = Instruction()
                                  .setOperation(Operation::AND)
                                  .setInput1(i1)
                                  .setInput2(i2)
                                  .build();
                instructions[wire] = instruction;
                break;
            case Operation::OR: // x OR y -> z
                sscanf(line.c_str(), "%s OR %s -> %s", input1, input2, wireName);
                i1 = (string)input1;
                i2 = (string)input2;
                wire = (string)wireName;

                instruction = Instruction()
                                  .setOperation(Operation::OR)
                                  .setInput1(i1)
                                  .setInput2(i2)
                                  .build();
                instructions[wire] = instruction;
                break;
            case Operation::NOT: // NOT x -> z
                sscanf(line.c_str(), "NOT %s -> %s", input1, wireName);
                i1 = (string)input1;
                wire = (string)wireName;

                instruction = Instruction()
                                  .setOperation(Operation::NOT)
                                  .setInput1(i1)
                                  .build();
                instructions[wire] = instruction;
                break;
            case Operation::LSHIFT: // x LSHIFT 2 -> f
                sscanf(line.c_str(), "%s LSHIFT %d -> %s", input1, &shift, wireName);
                i1 = (string)input1;
                wire = (string)wireName;

                instruction = Instruction()
                                  .setOperation(Operation::LSHIFT)
                                  .setInput1(i1)
                                  .setShift(shift)
                                  .build();
                instructions[wire] = instruction;
                break;
            case Operation::RSHIFT: // y RSHIFT 2 -> g
                sscanf(line.c_str(), "%s RSHIFT %d -> %s", input1, &shift, wireName);
                i1 = (string)input1;
                wire = (string)wireName;

                instruction = Instruction()
                                  .setOperation(Operation::RSHIFT)
                                  .setInput1(i1)
                                  .setShift(shift)
                                  .build();
                instructions[wire] = instruction;
                break;
            case Operation::ASSIGN: // 123 -> x
                sscanf(line.c_str(), "%s -> %s", &input1, wireName);
                wire = (string)wireName;
                i1 = (string)input1;

                instruction = Instruction()
                                  .setOperation(Operation::ASSIGN);

                if (is_number(i1))
                {
                    value = stoi(i1);
                    instruction.setValue(value);
                }
                else
                    instruction.setInput1(i1);

                instructions[wire] = instruction;
                break;
            }
        }

        this->fin.close();
    }

    void reset()
    {
        for (auto &instruction : this->instructions)
            wires[instruction.first] = instruction.second.getValue();
    }

    auto getOperation(string line) -> Operation
    {
        if (line.find("AND") != string::npos)
            return Operation::AND;
        if (line.find("OR") != string::npos)
            return Operation::OR;
        if (line.find("NOT") != string::npos)
            return Operation::NOT;
        if (line.find("LSHIFT") != string::npos)
            return Operation::LSHIFT;
        if (line.find("RSHIFT") != string::npos)
            return Operation::RSHIFT;
        return Operation::ASSIGN;
    }

    auto solve(string wireName) -> int
    {
        Instruction instruction = this->instructions[wireName];
        int &ref = wires[wireName];

        if (ref != -1)
            return ref;
        else
        {
            switch (instruction.getOperation())
            {
            case Operation::AND:
                if (instruction.getInput1() == "1")
                    ref = 1 & this->solve(instruction.getInput2());
                else
                    ref = this->solve(instruction.getInput1()) & this->solve(instruction.getInput2());
                break;
            case Operation::OR:
                ref = this->solve(instruction.getInput1()) | this->solve(instruction.getInput2());
                break;
            case Operation::NOT:
                ref = 65535 - this->solve(instruction.getInput1());
                break;
            case Operation::LSHIFT:
                ref = (this->solve(instruction.getInput1()) << instruction.getShift()) % 65536;
                break;
            case Operation::RSHIFT:
                ref = (this->solve(instruction.getInput1()) >> instruction.getShift()) % 65536;
                break;
            case Operation::ASSIGN:
                if (instruction.getValue() != -1)
                    ref = instruction.getValue();
                else
                    ref = this->solve(instruction.getInput1());
                break;
            }
        }

        return ref;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        this->reset();

        return this->solve("a");
    }
    auto part2() -> int
    {
        this->reset();
        int b = this->solve("a");
        this->reset();

        this->wires["b"] = b;

        return this->solve("a");
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}