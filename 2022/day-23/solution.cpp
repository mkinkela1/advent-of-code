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

class Elf
{
private:
    pair<int, int> position;
    pair<int, int> proposed_position;

public:
    Elf(pair<int, int> position)
    {
        this->position = position;
        this->proposed_position = {INT_MAX, INT_MAX};
    }

    auto move() -> void
    {
        if (this->proposed_position == make_pair(INT_MAX, INT_MAX))
            return;

        this->position = this->proposed_position;
        this->proposed_position = {INT_MAX, INT_MAX};
    }

    auto set_proposed_position(pair<int, int> position) -> void
    {
        this->proposed_position = position;
    }

    auto get_position() -> pair<int, int>
    {
        return this->position;
    }

    auto get_proposed_position() -> pair<int, int>
    {
        return this->proposed_position;
    }
};

class Solution
{
private:
    fstream fin;
    vector<string> data;
    vector<Elf> elves;
    map<string, pair<int, int>> directions = {
        {"N", {-1, 0}},
        {"S", {1, 0}},
        {"W", {0, -1}},
        {"E", {0, 1}},
        {"NE", {-1, 1}},
        {"NW", {-1, -1}},
        {"SE", {1, 1}},
        {"SW", {1, -1}}};

    void parse()
    {
        string line;
        int r = 0;
        while (getline(this->fin, line))
        {
            this->data.push_back(line);
            for (int c = 0; c < line.size(); c++)
                if (line[c] == '#')
                    this->elves.push_back(Elf({r, c}));
            r++;
        }
    }

    bool noOneAround(int r, int c, vector<Elf> &elves)
    {
        for (auto [direction, delta] : this->directions)
        {
            pair<int, int> new_position = {r + delta.first, c + delta.second};

            for (auto elf : elves)
                if (elf.get_position() == new_position)
                    return false;
        }
        return true;
    }

    bool checkPosition(int r, int c, string direction, vector<Elf> &elves)
    {
        pair<int, int> delta = this->directions[direction];
        pair<int, int> new_position = {r + delta.first, c + delta.second};

        for (auto elf : elves)
            if (elf.get_position() == new_position)
                return false;
        return true;
    }

    bool checkProposal(int r, int c, string direction, vector<Elf> &elves)
    {
        if (direction == "N")
            return checkPosition(r, c, "N", elves) && checkPosition(r, c, "NE", elves) && checkPosition(r, c, "NW", elves);
        if (direction == "S")
            return checkPosition(r, c, "S", elves) && checkPosition(r, c, "SE", elves) && checkPosition(r, c, "SW", elves);
        if (direction == "W")
            return checkPosition(r, c, "W", elves) && checkPosition(r, c, "NW", elves) && checkPosition(r, c, "SW", elves);
        if (direction == "E")
            return checkPosition(r, c, "E", elves) && checkPosition(r, c, "NE", elves) && checkPosition(r, c, "SE", elves);

        return false;
    }

    void proposeNextPosition(Elf &elf, int firstProposalId, vector<Elf> &elves)
    {
        string proposals = "NSWE";
        for (int i = 0; i < 4; ++i)
        {
            string proposal(1, proposals[(firstProposalId + i) % 4]);
            if (checkProposal(elf.get_position().first, elf.get_position().second, proposal, elves))
            {
                elf.set_proposed_position({elf.get_position().first + this->directions[proposal].first, elf.get_position().second + this->directions[proposal].second});
                return;
            }
        }
    }

    void moveToProposedPositionIfValid(Elf &elf, vector<Elf> &elves)
    {
        for (auto otherElf : elves)
            if (elf.get_position() != otherElf.get_position() && elf.get_proposed_position() == otherElf.get_proposed_position())
                return;
        elf.move();
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
        vector<Elf> elves = this->elves;

        for (int i = 0; i < 10; ++i)
        {
            for (auto &elf : elves)
            {
                if (this->noOneAround(elf.get_position().first, elf.get_position().second, elves))
                    elf.set_proposed_position(elf.get_position());
                else
                    this->proposeNextPosition(elf, i, elves);
            }

            for (auto &elf : elves)
                this->moveToProposedPositionIfValid(elf, elves);

            for (auto &elf : elves)
                elf.set_proposed_position({INT_MAX, INT_MAX});
        }

        int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;

        for (auto elf : elves)
        {
            minX = min(minX, elf.get_position().first);
            minY = min(minY, elf.get_position().second);
            maxX = max(maxX, elf.get_position().first);
            maxY = max(maxY, elf.get_position().second);
        }

        return (maxX - minX + 1) * (maxY - minY + 1) - this->elves.size();
    }
    auto part2() -> int
    {
        vector<Elf> elves = this->elves;

        for (int i = 0;; ++i)
        {
            int cnt = 0;
            for (auto &elf : elves)
            {
                if (this->noOneAround(elf.get_position().first, elf.get_position().second, elves))
                    elf.set_proposed_position(elf.get_position());
                else
                    this->proposeNextPosition(elf, i, elves);
            }

            for (auto &elf : elves)
            {
                if (elf.get_proposed_position() == elf.get_position())
                    cnt++;
                this->moveToProposedPositionIfValid(elf, elves);
            }

            if (cnt == elves.size())
                return i + 1;

            for (auto &elf : elves)
                elf.set_proposed_position({INT_MAX, INT_MAX});
        }

        return 0;
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1() << endl;
    // cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}