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
    map<string, uint64_t> wires;
    vector<string> zWires;
    vector<tuple<string, string, string, string>> instructions;
    vector<pair<string, int>> instructions2;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            if (line == "")
                break;

            vector<string> parts = split(line, ": ");

            this->wires[parts[0]] = stoi(parts[1]);
            if (parts[0][0] == 'z')
                this->zWires.push_back(parts[0]);

            this->instructions2.push_back({parts[0], stoi(parts[1])});
        }

        while (getline(this->fin, line))
        {
            char a[20], b[20], c[20], d[20];
            sscanf(line.c_str(), "%s %s %s -> %s", a, b, c, d);
            this->instructions.push_back(make_tuple(string(a), string(b), string(c), string(d)));

            if (d[0] == 'z')
                this->zWires.push_back(string(d));
        }

        for (auto zWire : this->zWires)
        {
            this->wires[zWire] = -1;
        }

        for (auto instruction : this->instructions)
        {
            this->wires[get<0>(instruction)] = -1;
            this->wires[get<2>(instruction)] = -1;
            this->wires[get<3>(instruction)] = -1;
        }

        for (auto instruction : this->instructions2)
        {
            this->wires[instruction.first] = instruction.second;
        }
    }

    bool check()
    {
        for (auto zWire : this->zWires)
        {
            if (this->wires[zWire] == -1)
                return false;
        }

        return true;
    }

    void getZValues()
    {
        while (!this->check())
        {
            for (auto instruction : this->instructions)
            {
                string a = get<0>(instruction);
                string b = get<1>(instruction);
                string c = get<2>(instruction);
                string d = get<3>(instruction);

                if (this->wires[a] == -1 || this->wires[c] == -1)
                    continue;

                if (b == "XOR")
                {
                    this->wires[d] = this->wires[a] ^ this->wires[c];
                }
                else if (b == "AND")
                {
                    this->wires[d] = this->wires[a] & this->wires[c];
                }
                else if (b == "OR")
                {
                    this->wires[d] = this->wires[a] | this->wires[c];
                }
            }
        }
    }

    string find(string a, string oper, string b)
    {
        for (auto instruction : this->instructions)
        {
            if (get<0>(instruction) == a && get<1>(instruction) == oper && get<2>(instruction) == b)
            {
                return get<3>(instruction);
            }

            if (get<0>(instruction) == b && get<1>(instruction) == oper && get<2>(instruction) == a)
            {
                return get<3>(instruction);
            }
        }

        return "";
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> uint64_t
    {
        sort(this->zWires.begin(), this->zWires.end());
        this->getZValues();

        uint64_t result = 0;

        for (int i = 0; i < this->zWires.size(); i++)
            result += (this->wires[this->zWires[i]] << i);

        return result;
    }
    auto part2() -> string
    {
        vector<pair<string, string>> swaps;

        string carryIn = "";

        for (int i = 0; i < 45; ++i)
        {
            string n;
            if (i < 10)
            {
                n = "0" + to_string(i);
            }
            else
            {
                n = to_string(i);
            }

            // X1: first input bit
            // Y1: second input bit
            // C0: carry-in bit

            // M1 = X1 XOR Y1 sum without carry
            // N1 = X1 AND Y1 carry from X1 and Y1
            // R1 = C0 AND M1 carry from previous bit and sum without carry
            // Z1 = C0 XOR M1 sum with carry
            // C1 = R1 OR N1 carry out

            string carryOut = "", sumWithCarry = "", carryFromInAndSum = "";
            string sumWithoutCarry = this->find("x" + n, "XOR", "y" + n);
            string carryFromXandY = this->find("x" + n, "AND", "y" + n);

            if (carryIn != "")
            {
                carryFromInAndSum = this->find(carryIn, "AND", sumWithoutCarry);
                sumWithCarry = this->find(carryIn, "XOR", sumWithoutCarry);

                if (carryFromInAndSum == "")
                {
                    swap(carryFromXandY, sumWithoutCarry);
                    swaps.push_back({carryFromXandY, sumWithoutCarry});
                    carryFromInAndSum = this->find(carryIn, "AND", sumWithoutCarry);
                }

                if (sumWithoutCarry != "" && sumWithoutCarry[0] == 'z')
                {
                    swap(sumWithoutCarry, sumWithCarry);
                    swaps.push_back({sumWithoutCarry, sumWithCarry});
                }

                if (carryFromXandY != "" && carryFromXandY[0] == 'z')
                {
                    swap(carryFromXandY, sumWithCarry);
                    swaps.push_back({carryFromXandY, sumWithCarry});
                }

                if (carryFromInAndSum != "" && carryFromInAndSum[0] == 'z')
                {
                    swap(carryFromInAndSum, sumWithCarry);
                    swaps.push_back({carryFromInAndSum, sumWithCarry});
                }

                carryOut = this->find(carryFromInAndSum, "OR", carryFromXandY);
            }

            if (carryOut != "" && carryOut[0] == 'z' && carryOut != "z45")
            {
                swap(carryOut, sumWithCarry);
                swaps.push_back({carryOut, sumWithCarry});
            }

            carryIn = carryIn == "" ? carryFromXandY : carryOut;
        }

        vector<string> result;
        for (auto [a, b] : swaps)
        {
            result.push_back(a);
            result.push_back(b);
        }

        sort(result.begin(), result.end());

        string ret = "";
        for (int i = 0; i < result.size(); i++)
        {
            if (i == result.size() - 1)
                ret += result[i];
            else
                ret += result[i] + ",";
        }

        return ret;
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