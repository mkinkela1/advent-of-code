#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <set>

using namespace std;

class Solution
{
private:
    fstream fin;
    string input;

    void parse()
    {
        getline(this->fin, this->input);
    }

    auto getNextPassword(string password) -> string
    {
        int idx = password.size() - 1;

        while (idx >= 0 && password[idx] == 'z')
        {
            password[idx] = 'a';
            idx--;
        }

        password[idx]++;

        return password;
    }

    auto checkPassword(string password) -> bool
    {
        return this->hasStraight(password) && this->hasNoInvalidChars(password) && this->hasTwoPairs(password);
    }

    auto hasStraight(string password) -> bool
    {
        for (int i = 0; i < password.size() - 2; ++i)
        {
            if (password[i] == password[i + 1] - 1 && password[i] == password[i + 2] - 2)
            {
                return true;
            }
        }

        return false;
    }

    auto hasNoInvalidChars(string password) -> bool
    {
        return password.find_first_of("iol") == string::npos;
    }

    auto hasTwoPairs(string password) -> bool
    {
        int count = 0;
        set<char> pairs;
        for (int i = 0; i < password.size() - 1; ++i)
        {
            if (password[i] == password[i + 1])
            {
                i++;
                pairs.insert(password[i]);
            }
        }

        return pairs.size() >= 2;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> string
    {
        string password = this->input;
        do
        {
            password = this->getNextPassword(password);
        } while (!this->checkPassword(password));

        return password;
    }
    auto part2() -> string
    {
        string password = this->part1();
        do
        {
            password = this->getNextPassword(password);
        } while (!this->checkPassword(password));

        return password;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}