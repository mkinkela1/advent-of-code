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

enum Mapper
{
    SEED_TO_SOIL,
    SOIL_TO_FERTILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMPERATURE,
    TEMPERATURE_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION
};

struct Range
{
    long long destRangeStart, sourceRangeStart, rangeLength;
    Range() {}
    Range(long long destRangeStart, long long sourceRangeStart, long long rangeLength)
    {
        this->destRangeStart = destRangeStart;
        this->sourceRangeStart = sourceRangeStart;
        this->rangeLength = rangeLength;
    }
};

class Solution
{
private:
    fstream fin;
    vector<long long> seeds;
    vector<vector<Range>> ranges;
    map<long long, long long> cache;

    Mapper stringToEnum(string mapper)
    {
        if (mapper == "seed-to-soil")
            return SEED_TO_SOIL;
        else if (mapper == "soil-to-fertilizer")
            return SOIL_TO_FERTILIZER;
        else if (mapper == "fertilizer-to-water")
            return FERTILIZER_TO_WATER;
        else if (mapper == "water-to-light")
            return WATER_TO_LIGHT;
        else if (mapper == "light-to-temperature")
            return LIGHT_TO_TEMPERATURE;
        else if (mapper == "temperature-to-humidity")
            return TEMPERATURE_TO_HUMIDITY;
        else if (mapper == "humidity-to-location")
            return HUMIDITY_TO_LOCATION;

        throw "Invalid mapper";
    }

    void parse()
    {
        string line;
        getline(this->fin, line);

        vector<string> seed_input = split(line, ": ");
        vector<string> seeds = split(seed_input[1], " ");

        for (auto seed : seeds)
        {
            if (seed != "")
                this->seeds.push_back(stoll(seed));
        }

        getline(this->fin, line);

        for (int i = 0; i < 7; i++)
        {
            vector<Range> range;

            getline(this->fin, line);

            while (true)
            {
                getline(this->fin, line);
                if (line == "")
                {
                    this->ranges.push_back(range);
                    range.clear();
                    break;
                }
                long long destRangeStart, sourceRangeStart, rangeLength;
                sscanf(line.c_str(), "%lld %lld %lld", &destRangeStart, &sourceRangeStart, &rangeLength);

                range.push_back(Range(destRangeStart, sourceRangeStart, rangeLength));
            }
        }
    }

    auto getSeed(long long seed, vector<Range> mapper) -> long long
    {
        for (auto range : mapper)
            if (seed >= range.destRangeStart && seed < range.destRangeStart + range.rangeLength)
                return range.sourceRangeStart + (seed - range.destRangeStart);

        return seed;
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
        vector<long long> seeds = this->seeds;

        for (auto mapper : this->ranges)
        {
            for (auto &seed : seeds)
            {
                for (auto range : mapper)
                {
                    if (seed >= range.sourceRangeStart && seed < range.sourceRangeStart + range.rangeLength)
                    {
                        seed = range.destRangeStart + (seed - range.sourceRangeStart);
                        break;
                    }
                }
            }
        }

        long long sol = __LONG_LONG_MAX__;
        for (auto seed : seeds)
            sol = min(sol, seed);

        return sol;
    }

    auto part2() -> long long
    {
        vector<pair<long long, long long>> seeds;

        for (int i = 0; i < this->seeds.size(); i += 2)
        {
            seeds.push_back(make_pair(this->seeds[i], this->seeds[i] + this->seeds[i + 1]));
        }

        this->ranges.pop_back();
        reverse(this->ranges.begin(), this->ranges.end());

        for (int i = 0; i < 100000000; ++i)
        {
            long long seed = i;
            for (auto mapper : this->ranges)
                seed = this->getSeed(seed, mapper);

            for (auto s : seeds)
                if (seed >= s.first && seed < s.second)
                    return i;
        }
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