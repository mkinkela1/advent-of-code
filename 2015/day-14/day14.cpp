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

class Raindeer
{
private:
    string name;
    int speed;
    int flyTime;
    int restTime;
    int distance;
    int timeInCurrentMode;
    bool isFlying;
    int points;

public:
    Raindeer(string name, int speed, int flyTime, int restTime)
    {
        this->name = name;
        this->speed = speed;
        this->flyTime = flyTime;
        this->restTime = restTime;
        this->distance = 0;
        this->timeInCurrentMode = 0;
        this->isFlying = true;
        this->points = 0;
    }

    auto getDistance() -> int { return this->distance; }
    auto getPoints() -> int { return this->points; }
    auto addPoint() -> void { this->points++; }
    auto reset() -> void
    {
        this->distance = 0;
        this->timeInCurrentMode = 0;
        this->isFlying = true;
        this->points = 0;
    }

    auto calculateDistance() -> void
    {
        if (this->isFlying)
        {
            this->distance += this->speed;
            this->timeInCurrentMode++;

            if (this->timeInCurrentMode == this->flyTime)
            {
                this->timeInCurrentMode = 0;
                this->isFlying = false;
            }
        }
        else
        {
            this->timeInCurrentMode++;

            if (this->timeInCurrentMode == this->restTime)
            {
                this->timeInCurrentMode = 0;
                this->isFlying = true;
            }
        }
    }
};

class Solution
{
private:
    fstream fin;
    vector<Raindeer> raindeers;

    void parse()
    {
        string line;

        while (getline(this->fin, line))
        {
            char name[50];
            int speed, flyTime, restTime;

            sscanf(line.c_str(), "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", name, &speed, &flyTime, &restTime);

            this->raindeers.push_back(Raindeer(name, speed, flyTime, restTime));
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        int sol = 0;

        for (int time = 0; time < 2503; ++time)
            for (int i = 0; i < this->raindeers.size(); ++i)
                this->raindeers[i].calculateDistance();

        for (int i = 0; i < this->raindeers.size(); ++i)
            sol = max(sol, this->raindeers[i].getDistance());

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        for (int i = 0; i < this->raindeers.size(); ++i)
            this->raindeers[i].reset();

        for (int time = 0; time < 2503; ++time)
        {
            for (int i = 0; i < this->raindeers.size(); ++i)
                this->raindeers[i].calculateDistance();

            int maxDistance = 0;
            for (int i = 0; i < this->raindeers.size(); ++i)
                maxDistance = max(maxDistance, this->raindeers[i].getDistance());

            for (int i = 0; i < this->raindeers.size(); ++i)
                if (this->raindeers[i].getDistance() == maxDistance)
                    this->raindeers[i].addPoint();
        }

        for (int i = 0; i < this->raindeers.size(); ++i)
            sol = max(sol, this->raindeers[i].getPoints());

        return sol;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}