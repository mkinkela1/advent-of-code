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

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

class Instruction
{
public:
    string op;
    int arg;
    Instruction(string op, int arg)
    {
        this->op = op;
        this->arg = arg;
    }
};

class Solution
{
private:
    fstream fin;
    vector<Instruction> instructions, instructions2;

    void parse()
    {
        string line;
        char op[200], op2[200];
        char mem[200];
        int arg;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%s %d %s", op, &arg, mem);
            this->instructions.push_back(Instruction(op, arg));

            sscanf(mem, "%s", op2);
            string l = "";
            for (int i = 0; i < strlen(op2) - 1; i++)
                l += op2[i];

            string oper = l.substr(l.size() - 1, 1);
            l.pop_back();
            l = l.substr(2, l.size() - 2);

            int arg2;
            sscanf(l.c_str(), "%x", &arg2);
            if (oper == "0")
                oper = "R";
            else if (oper == "1")
                oper = "D";
            else if (oper == "2")
                oper = "L";
            else if (oper == "3")
                oper = "U";
            this->instructions2.push_back(Instruction(oper, arg2));
        }
    }

    auto calculate(vector<pair<int, int>> points) -> long long
    {
        long long ret = 0;

        points.push_back(points[0]);
        for (int i = 0; i < points.size() - 1; ++i)
        {
            int X1 = points[i].first;
            int Y1 = points[i].second;
            int X2 = points[i + 1].first;
            int Y2 = points[i + 1].second;
            ret += X1 * Y2 - X2 * Y1;
        }

        ret /= 2;

        return ret;
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
        map<pair<int, int>, int> grid;

        int x = 0;
        int y = 0;
        int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
        for (auto instruction : this->instructions)
        {
            if (!grid[make_pair(x, y)])
                ++sol;
            if (instruction.op == "U")
            {
                for (int i = 0; i < instruction.arg; i++)
                {
                    x--;
                    grid[make_pair(x, y)] = 1;
                }
            }
            else if (instruction.op == "D")
            {
                for (int i = 0; i < instruction.arg; i++)
                {
                    x++;
                    grid[make_pair(x, y)] = 1;
                }
            }
            else if (instruction.op == "L")
            {
                for (int i = 0; i < instruction.arg; i++)
                {
                    y--;
                    grid[make_pair(x, y)] = 1;
                }
            }
            else if (instruction.op == "R")
            {
                for (int i = 0; i < instruction.arg; i++)
                {
                    y++;
                    grid[make_pair(x, y)] = 1;
                }
            }

            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
        }
        vector<string> grid2(maxX - minX + 1, string(maxY - minY + 1, '.'));
        for (auto it : grid)
        {
            grid2[it.first.first + abs(minX)][it.first.second + abs(minY)] = '#';
        }

        grid2.insert(grid2.begin(), string(grid2[0].size(), '.'));
        grid2.push_back(string(grid2[0].size(), '.'));
        for (int i = 0; i < grid2.size(); i++)
        {
            grid2[i].insert(grid2[i].begin(), '.');
            grid2[i].push_back('.');
        }

        queue<pair<int, int>> q;
        vector<vector<bool>> visited(grid2.size(), vector<bool>(grid2[0].size(), false));

        q.push(make_pair(0, 0));
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                int nx = p.first + dx[i];
                int ny = p.second + dy[i];
                if (nx < 0 || nx >= grid2.size() || ny < 0 || ny >= grid2[0].size())
                    continue;
                if (visited[nx][ny])
                    continue;
                if (grid2[nx][ny] == '#')
                    continue;

                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }

        for (int i = 0; i < grid2.size(); ++i)
            for (int j = 0; j < grid2[0].size(); ++j)
                sol += !visited[i][j];

        return sol - 1;
    }
    auto part2() -> long long
    {
        long long sol = 0LL;
        long long area = 0LL;

        int x = 0;
        int y = 0;

        vector<pair<int, int>> points;
        points.push_back(make_pair(x, y));
        for (auto instruction : this->instructions2)
        {
            int prevX = x;
            int prevY = y;
            if (instruction.op == "U")
                x -= instruction.arg;
            else if (instruction.op == "D")
                x += instruction.arg;
            else if (instruction.op == "L")
                y -= instruction.arg;
            else if (instruction.op == "R")
                y += instruction.arg;
            points.push_back(make_pair(x, y));
            area += abs(prevX - x) + abs(prevY - y);
        }

        long long tmp = this->calculate(points);
        reverse(points.begin(), points.end());
        tmp = max(tmp, this->calculate(points));

        tmp += area;

        sol = tmp - points.size() / 2 + 1;

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