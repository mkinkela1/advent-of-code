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
#include "../../utils/picks_formula.h"
#include "../../utils/shoelace_area.h"

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

class Instruction
{
public:
    string op;
    int arg;
    Instruction(string op, int arg)
    {
        this->op = op;
        this->arg = arg;
    }
};

class Solution
{
private:
    fstream fin;
    vector<Instruction> instructions, instructions2;

    void parse()
    {
        string line;
        char op[200], op2[200];
        char mem[200];
        int arg;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%s %d %s", op, &arg, mem);
            this->instructions.push_back(Instruction(op, arg));

            sscanf(mem, "%s", op2);
            string l = "";
            for (int i = 0; i < strlen(op2) - 1; i++)
                l += op2[i];

            string oper = l.substr(l.size() - 1, 1);
            l.pop_back();
            l = l.substr(2, l.size() - 2);

            int arg2;
            sscanf(l.c_str(), "%x", &arg2);
            if (oper == "0")
                oper = "R";
            else if (oper == "1")
                oper = "D";
            else if (oper == "2")
                oper = "L";
            else if (oper == "3")
                oper = "U";
            this->instructions2.push_back(Instruction(oper, arg2));
        }
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long
    {
        vector<pair<long long, long long>> points;
        long long perimeter = 0LL;

        long long x = 0;
        long long y = 0;
        points.push_back(make_pair(x, y));
        for (auto instruction : this->instructions)
        {
            long long prevX = x;
            long long prevY = y;
            if (instruction.op == "U")
                x -= instruction.arg;
            else if (instruction.op == "D")
                x += instruction.arg;
            else if (instruction.op == "L")
                y -= instruction.arg;
            else if (instruction.op == "R")
                y += instruction.arg;

            points.push_back(make_pair(x, y));
            perimeter += labs(prevX - x) + labs(prevY - y);
        }

        long long area = getShoelaceArea(points);
        return getPointsInsidePolygon(area, perimeter);
    }
    auto part2() -> long long
    {
        long long perimeter = 0LL;

        long long x = 0;
        long long y = 0;

        vector<pair<long long, long long>> points;
        points.push_back(make_pair(x, y));
        for (auto instruction : this->instructions2)
        {
            long long prevX = x;
            long long prevY = y;
            if (instruction.op == "U")
                x -= instruction.arg;
            else if (instruction.op == "D")
                x += instruction.arg;
            else if (instruction.op == "L")
                y -= instruction.arg;
            else if (instruction.op == "R")
                y += instruction.arg;
            points.push_back(make_pair(x, y));
            perimeter += labs(prevX - x) + labs(prevY - y);
        }

        long long area = getShoelaceArea(points);
        return getPointsInsidePolygon(area, perimeter);
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