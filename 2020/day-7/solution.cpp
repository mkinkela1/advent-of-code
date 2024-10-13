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
    map<string, vector<pair<int, string>>> bags;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> parts = split(line, " bags contain ");
            string color = parts[0];
            vector<pair<int, string>> contains;
            if (parts[1] != "no other bags.")
            {
                vector<string> bags = split(parts[1], ", ");
                for (string bag : bags)
                {
                    vector<string> bagParts = split(bag, " ");
                    int count = stoi(bagParts[0]);
                    string bagColor = bagParts[1] + " " + bagParts[2];
                    contains.push_back(make_pair(count, bagColor));
                }
            }
            this->bags[color] = contains;
        }
    }

    auto checkBag(string startingColor, string endingColor) -> bool
    {
        if (startingColor == endingColor)
        {
            return true;
        }

        queue<string> q;
        map<string, bool> visited;
        q.push(startingColor);

        while (!q.empty())
        {
            string current = q.front();
            q.pop();
            if (visited[current])
            {
                continue;
            }
            if (current == endingColor)
            {
                return true;
            }
            visited[current] = true;

            for (auto contained : this->bags[current])
            {
                if (!visited[contained.second])
                    q.push(contained.second);
            }
        }

        return false;
    }

    auto countBags(string startingColor) -> long long
    {
        long long count = 0LL;
        stack<pair<long long, string>> s;
        s.push(make_pair(1LL, startingColor));

        while (!s.empty())
        {
            pair<long long, string> current = s.top();
            s.pop();
            count += current.first;

            for (auto contained : this->bags[current.second])
            {
                s.push(make_pair(current.first * contained.first, contained.second));
            }
        }

        return count;
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
        for (auto bag : this->bags)
        {
            if (bag.first == "shiny gold")
                continue;
            if (checkBag(bag.first, "shiny gold"))
            {
                count++;
            }
        }
        return count;
    }
    auto part2() -> long long
    {
        return this->countBags("shiny gold") - 1;
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