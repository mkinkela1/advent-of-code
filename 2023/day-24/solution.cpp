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
#include <set>

using namespace std;

class Line
{
private:
    long double x1;
    long double y1;
    long double a;
    long double b;
    long double vx;
    long double vy;

public:
    Line(long double x1, long double y1, long double vx, long double vy)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->vx = vx;
        this->vy = vy;
        this->a = vy / vx;
        this->b = y1 - this->a * x1;
    }

    auto getA() -> long double { return this->a; }
    auto getB() -> long double { return this->b; }
    auto getX1() -> long double { return this->x1; }
    auto getY1() -> long double { return this->y1; }
    auto getVx() -> long double { return this->vx; }
    auto getVy() -> long double { return this->vy; }
};

class Line3D
{
private:
    long long x;
    long long y;
    long long z;
    long long vx;
    long long vy;
    long long vz;

public:
    Line3D(long long x, long long y, long long z, long long vx, long long vy, long long vz)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
    }

    auto getX() -> long long { return this->x; }
    auto getY() -> long long { return this->y; }
    auto getZ() -> long long { return this->z; }
    auto getVx() -> long long { return this->vx; }
    auto getVy() -> long long { return this->vy; }
    auto getVz() -> long long { return this->vz; }
};

class Solution
{
private:
    fstream fin;
    vector<Line> lines;
    vector<Line3D> lines3d;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            long double x, y, z, vx, vy, vz;
            sscanf(line.c_str(), "%Lf, %Lf, %Lf @ %Lf, %Lf, %Lf", &x, &y, &z, &vx, &vy, &vz);
            this->lines.push_back(Line(x, y, vx, vy));
            this->lines3d.push_back(Line3D(x, y, z, vx, vy, vz));
        }
    }

    auto getIntersection(Line l1, Line l2) -> pair<long double, long double>
    {
        long double x = (l2.getB() - l1.getB()) / (l1.getA() - l2.getA());
        long double y = l1.getA() * x + l1.getB();

        long double t1 = (x - l1.getX1()) / l1.getVx() + 1e-10;
        long double t2 = (x - l2.getX1()) / l2.getVx() + 1e-10;

        if (t1 < 0 || t2 < 0)
            return make_pair(0, 0);

        return make_pair(x, y);
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1(bool test = false) -> int
    {
        pair<long double, long double> range;
        if (test)
            range = make_pair(7, 27);
        else
            range = make_pair(200000000000000.00, 400000000000000.00);

        int count = 0;
        for (int i = 0; i < this->lines.size(); i++)
        {
            for (int j = i + 1; j < this->lines.size(); j++)
            {
                auto [x, y] = this->getIntersection(this->lines[i], this->lines[j]);
                if (x >= range.first && x <= range.second && y >= range.first && y <= range.second)
                    count++;
            }
        }

        return count;
    }
    auto part2() -> int
    {
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1(true) << endl;
    cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    // cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}