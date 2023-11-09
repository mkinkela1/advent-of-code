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
    vector<string> input;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
        }
    }

    auto getRoomId(string line) -> int
    {
        return stoi(line.substr(line.find_last_of('-') + 1, line.find_first_of('[') - line.find_last_of('-') - 1));
    }

    auto checkChecksum(string line) -> bool
    {
        string checksum = line.substr(line.find_first_of('[') + 1, line.find_last_of(']') - line.find_first_of('[') - 1);
        string roomName = line.substr(0, line.find_last_of('-'));

        unordered_map<char, int> charCount;

        for (auto c : roomName)
        {
            if (c == '-')
                continue;
            charCount[c]++;
        }

        vector<pair<char, int>> charCountVec(charCount.begin(), charCount.end());
        sort(charCountVec.begin(), charCountVec.end(), [](auto &left, auto &right)
             {
            if (left.second == right.second)
                return left.first < right.first;
            return left.second > right.second; });

        string calculatedChecksum = "";
        for (int i = 0; i < 5; i++)
        {
            calculatedChecksum += charCountVec[i].first;
        }

        return calculatedChecksum == checksum;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        int sum = 0;

        for (auto line : this->input)
        {
            int rooomId = this->getRoomId(line);
            if (this->checkChecksum(line))
                sum += rooomId;
        }

        return sum;
    }
    auto part2() -> int
    {
        for (auto line : this->input)
        {
            int rooomId = this->getRoomId(line);
            string roomName = line.substr(0, line.find_last_of('-'));
            for (auto &c : roomName)
            {
                if (c == '-')
                    continue;
                c = (c - 'a' + rooomId) % 26 + 'a';
            }
            if (roomName.find("northpole") != string::npos)
                return rooomId;
        }
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}