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

class Triangle
{
public:
    int a, b, c;
    Triangle(int a, int b, int c) : a(a), b(b), c(c) {}

    auto isTriangle() -> bool
    {
        return (this->a + this->b > this->c) && (this->a + this->c > this->b) && (this->b + this->c > this->a);
    }
};

class Solution
{
private:
    fstream fin;
    vector<Triangle> triangles;

    void parse()
    {
        string line;
        int a, b, c;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%d %d %d", &a, &b, &c);
            this->triangles.push_back(Triangle(a, b, c));
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
        int count = 0;
        for (auto triangle : this->triangles)
            count += triangle.isTriangle();

        return count;
    }
    auto part2() -> int
    {
        vector<Triangle> triangles;
        int n = this->triangles.size();

        for (int i = 0; i < n - 2; i += 3)
        {
            triangles.push_back(Triangle(this->triangles[i].a, this->triangles[i + 1].a, this->triangles[i + 2].a));
            triangles.push_back(Triangle(this->triangles[i].b, this->triangles[i + 1].b, this->triangles[i + 2].b));
            triangles.push_back(Triangle(this->triangles[i].c, this->triangles[i + 1].c, this->triangles[i + 2].c));
        }

        int count = 0;
        for (auto triangle : triangles)
            count += triangle.isTriangle();
        return count;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}