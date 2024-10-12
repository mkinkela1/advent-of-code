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

class Password
{
public:
    int min;
    int max;
    char letter;
    string password;

    Password(int min, int max, char letter, string password)
    {
        this->min = min;
        this->max = max;
        this->letter = letter;
        this->password = password;
    }

    bool isValid()
    {
        int count = 0;
        for (char c : this->password)
        {
            if (c == this->letter)
            {
                count++;
            }
        }

        return count >= this->min && count <= this->max;
    }

    bool isValid2()
    {
        return (this->password[this->min - 1] == this->letter) ^ (this->password[this->max - 1] == this->letter);
    }
};

class Solution
{
private:
    fstream fin;
    vector<Password> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int min, max;
            char letter;
            char password[100];

            sscanf(line.c_str(), "%d-%d %c: %s", &min, &max, &letter, password);
            this->data.push_back(Password(min, max, letter, password));
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
        int count = 0;
        for (Password p : this->data)
        {
            if (p.isValid())
            {
                count++;
            }
        }

        return count;
    }
    auto part2() -> int
    {
        int count = 0;
        for (Password p : this->data)
        {
            if (p.isValid2())
            {
                count++;
            }
        }

        return count;
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