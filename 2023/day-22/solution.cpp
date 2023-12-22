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
#include <math.h>
#include <set>

using namespace std;

struct Brick
{
    int x1, x2;
    int y1, y2;
    int z1, z2;
};

class Solution
{
private:
    fstream fin;
    vector<Brick> bricks;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            Brick brick;
            sscanf(line.c_str(), "%d,%d,%d~%d,%d,%d", &brick.x1, &brick.y1, &brick.z1, &brick.x2, &brick.y2, &brick.z2);

            this->bricks.push_back(brick);
        }

        sort(this->bricks.begin(), this->bricks.end(), [](const Brick &a, const Brick &b)
             { return a.z1 < b.z1; });

        for (int i = 0; i < this->bricks.size(); i++)
        {
            int maxZ = 1;
            for (int j = 0; j < i; j++)
                if (this->overlap(this->bricks[i], this->bricks[j]))
                    maxZ = max(maxZ, this->bricks[j].z2 + 1);

            this->bricks[i].z2 -= this->bricks[i].z1 - maxZ;
            this->bricks[i].z1 = maxZ;
        }

        sort(this->bricks.begin(), this->bricks.end(), [](const Brick &a, const Brick &b)
             { return a.z1 < b.z1; });
    }

    auto overlap(const Brick &a, const Brick &b) -> bool
    {
        return max(a.x1, b.x1) <= min(a.x2, b.x2) &&
               max(a.y1, b.y1) <= min(a.y2, b.y2);
    }

    auto difference(set<int> s1, set<int> s2) -> set<int>
    {
        set<int> diff;

        set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(diff, diff.begin()));

        return diff;
    }

    auto isSubset(set<int> s1, set<int> s2) -> bool
    {
        for (auto x : s1)
            if (s2.find(x) == s2.end())
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
        int sol = 0;

        vector<set<int>> supports(this->bricks.size(), set<int>());
        vector<int> supported(this->bricks.size(), 0);

        for (int i = 0; i < this->bricks.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (this->overlap(this->bricks[i], this->bricks[j]) && this->bricks[i].z1 == this->bricks[j].z2 + 1)
                {
                    supports[j].insert(i);
                    supported[i]++;
                }
            }
        }

        for (int i = 0; i < this->bricks.size(); i++)
        {
            bool ok = true;
            for (auto x : supports[i])
            {
                if (supported[x] < 2)
                {
                    ok = false;
                    break;
                }
            }

            sol += ok;
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        vector<set<int>> supports(this->bricks.size(), set<int>());
        vector<set<int>> supported(this->bricks.size(), set<int>());

        for (int i = 0; i < this->bricks.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (this->overlap(this->bricks[i], this->bricks[j]) && this->bricks[i].z1 == this->bricks[j].z2 + 1)
                {
                    supports[j].insert(i);
                    supported[i].insert(j);
                }
            }
        }

        for (int i = 0; i < this->bricks.size(); i++)
        {
            queue<int> q;
            set<int> falling;

            for (auto x : supports[i])
            {
                if (supported[x].size() == 1)
                {
                    q.push(x);
                    falling.insert(x);
                }
            }

            falling.insert(i);

            while (!q.empty())
            {
                int x = q.front();
                q.pop();

                for (auto x : this->difference(supports[x], falling))
                {
                    if (this->isSubset(supported[x], falling))
                    {
                        q.push(x);
                        falling.insert(x);
                    }
                }
            }

            sol += falling.size() - 1;
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