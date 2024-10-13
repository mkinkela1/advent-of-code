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
    vector<map<string, string>> data;

    void parse()
    {
        string line;
        map<string, string> passport;
        while (getline(this->fin, line))
        {
            if (line.empty())
            {
                this->data.push_back(passport);
                passport.clear();
                continue;
            }

            vector<string> fields = split(line, " ");
            for (auto field : fields)
            {
                vector<string> key_value = split(field, ":");
                passport[key_value[0]] = key_value[1];
            }
        }

        if (!passport.empty())
            this->data.push_back(passport);
    }

    auto validFields(map<string, string> passport) -> bool
    {
        if (passport.count("byr") == 0)
            return false;
        if (passport.count("iyr") == 0)
            return false;
        if (passport.count("eyr") == 0)
            return false;
        if (passport.count("hgt") == 0)
            return false;
        if (passport.count("hcl") == 0)
            return false;
        if (passport.count("ecl") == 0)
            return false;
        if (passport.count("pid") == 0)
            return false;

        return true;
    }

    auto checkFourDigitNumber(string value, int _min, int _max) -> bool
    {
        if (value.size() != 4)
            return false;

        int num = 0;
        for (char c : value)
        {
            if (!isdigit(c))
                return false;

            num = num * 10 + (c - '0');
        }

        if (num < _min || num > _max)
            return false;

        return true;
    }

    auto checkHeight(string value) -> bool
    {
        if (value.size() < 4)
            return false;

        string unit = value.substr(value.size() - 2);
        string height = value.substr(0, value.size() - 2);

        if (unit == "cm")
        {
            int num = 0;
            for (char c : height)
            {
                if (!isdigit(c))
                    return false;

                num = num * 10 + (c - '0');
            }

            if (num < 150 || num > 193)
                return false;
        }
        else if (unit == "in")
        {
            int num = 0;
            for (char c : height)
            {
                if (!isdigit(c))
                    return false;

                num = num * 10 + (c - '0');
            }

            if (num < 59 || num > 76)
                return false;
        }
        else
        {
            return false;
        }

        return true;
    }

    auto checkHairColor(string value) -> bool
    {
        if (value.size() != 7)
            return false;
        if (value[0] != '#')
            return false;

        for (int i = 1; i < 7; i++)
        {
            if (!isxdigit(value[i]))
                return false;
        }

        return true;
    }

    auto checkEyeColor(string value) -> bool
    {
        if (value != "amb" && value != "blu" && value != "brn" && value != "gry" && value != "grn" && value != "hzl" && value != "oth")
            return false;

        return true;
    }

    auto checkPassportId(string value) -> bool
    {
        if (value.size() != 9)
            return false;

        for (char c : value)
        {
            if (!isdigit(c))
                return false;
        }

        return true;
    }

    auto validValues(map<string, string> passport) -> bool
    {
        if (!checkFourDigitNumber(passport["byr"], 1920, 2002))
            return false;
        if (!checkFourDigitNumber(passport["iyr"], 2010, 2020))
            return false;
        if (!checkFourDigitNumber(passport["eyr"], 2020, 2030))
            return false;
        if (!checkHeight(passport["hgt"]))
            return false;
        if (!checkHairColor(passport["hcl"]))
            return false;
        if (!checkEyeColor(passport["ecl"]))
            return false;
        if (!checkPassportId(passport["pid"]))
            return false;
        return true;
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
        int validPassports = 0;
        for (auto passport : this->data)
        {
            if (this->validFields(passport))
                validPassports++;
        }
        return validPassports;
    }
    auto part2() -> int
    {
        int validPassports = 0;
        for (auto passport : this->data)
        {
            if (this->validFields(passport) && this->validValues(passport))
                validPassports++;
        }
        return validPassports;
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