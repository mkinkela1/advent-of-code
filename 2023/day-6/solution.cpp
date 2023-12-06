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

class Record
{
private:
    long long time;
    long long distance;

public:
    Record() {}
    Record(long long time, long long distance)
    {
        this->time = time;
        this->distance = distance;
    }

    auto getTime() -> long long { return this->time; }
    auto getDistance() -> long long { return this->distance; }
};

class Solution
{
private:
    fstream fin;
    vector<Record> records;
    Record bigRecord;

    void parse()
    {
        string line;
        vector<int> time, distance;

        getline(this->fin, line);
        vector<string> input = split(line, ": ");
        vector<string> times = split(input[1], " ");
        for (auto t : times)
        {
            if (t != "")
                time.push_back(stoi(t));
        }

        getline(this->fin, line);
        input = split(line, ": ");
        vector<string> distances = split(input[1], " ");
        for (auto d : distances)
        {
            if (d != "")
                distance.push_back(stoi(d));
        }

        for (int i = 0; i < time.size(); i++)
        {
            this->records.push_back(Record(time[i], distance[i]));
        }

        string bigTime = "";
        string bigDistance = "";

        for (int i = 0; i < time.size(); i++)
        {
            bigTime += to_string(time[i]);
            bigDistance += to_string(distance[i]);
        }

        this->bigRecord = Record(stoll(bigTime), stoll(bigDistance));
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
        long long sol = 1;
        for (auto r : this->records)
        {
            long long waysToWin = 0;
            for (int time = 0; time <= r.getTime(); time++)
            {
                int distance = time * (r.getTime() - time);
                if (distance > r.getDistance())
                    ++waysToWin;
            }

            sol *= waysToWin;
        }

        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0;
        for (int time = 0; time <= this->bigRecord.getTime(); time++)
        {
            long long distance = time * (this->bigRecord.getTime() - time);
            if (distance > this->bigRecord.getDistance())
                ++sol;
        }

        return sol;
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