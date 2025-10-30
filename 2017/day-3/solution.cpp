#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
private:
  fstream fin;
  int input;

  void parse()
  {
    string line;
    getline(this->fin, line);
    if (line != "")
      this->input = stoi(line);
  }

  auto manhattan(pair<int, int> a, pair<int, int> b) -> int
  {
    return abs(a.first - b.first) + abs(a.second - b.second);
  }

  auto nextDirection(char direction) -> char
  {
    switch (direction)
    {
    case 'R':
      return 'U';
    case 'D':
      return 'R';
    case 'L':
      return 'D';
    case 'U':
      return 'L';
    default:
      exit(1);
    }
  }

  auto nextPosition(char direction, int x, int y) -> pair<int, int>
  {
    switch (direction)
    {
    case 'R':
      return {x + 1, y};
    case 'L':
      return {x - 1, y};
    case 'U':
      return {x, y + 1};
    case 'D':
      return {x, y - 1};
    default:
      exit(1);
    }
  }

  auto shouldChangeDirection(int x, int y, map<pair<int, int>, int> &grid,
                             char direction) -> bool
  {
    switch (direction)
    {
    case 'R':
      return grid[{x, y + 1}] == 0;
    case 'L':
      return grid[{x, y - 1}] == 0;
    case 'U':
      return grid[{x - 1, y}] == 0;
    case 'D':
      return grid[{x + 1, y}] == 0;
    }

    return false;
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
    int x = 0, y = 0;

    for (int i = 1;; i += 2)
    {
      if (i * i >= this->input)
      {
        int diff = i * i - this->input;
        int sideLenght = i - 1;
        if (diff > sideLenght)
        {
          x -= sideLenght;
          diff -= sideLenght;
        }
        else
        {
          x -= diff;
          return this->manhattan({0, 0}, {x, y});
        }

        if (diff > sideLenght)
        {
          y += sideLenght;
          diff -= sideLenght;
        }
        else
        {
          y += diff;
          return this->manhattan({0, 0}, {x, y});
        }

        if (diff > sideLenght)
        {
          x += sideLenght;
          diff -= sideLenght;
        }
        else
        {
          x += diff;
          return this->manhattan({0, 0}, {x, y});
        }

        y -= diff;
        return this->manhattan({0, 0}, {x, y});
      }
      else
      {
        x++;
        y--;
      }
    }
  }

  auto part2() -> int
  {
    int x = 1, y = 0;
    map<pair<int, int>, int> grid;

    grid[{0, 0}] = 1;

    char direction = 'U';

    while (true)
    {

      cout << "x: " << x << ", y: " << y << endl;

      grid[{x, y}] = grid[{x - 1, y}] + grid[{x, y - 1}] + grid[{x + 1, y}] +
                     grid[{x, y + 1}] + grid[{x - 1, y - 1}] +
                     grid[{x + 1, y - 1}] + grid[{x - 1, y + 1}] +
                     grid[{x + 1, y + 1}];

      if (grid[{x, y}] > this->input)
      {
        return grid[{x, y}];
      }

      bool shouldChangeDirection =
          this->shouldChangeDirection(x, y, grid, direction);

      if (shouldChangeDirection)
      {
        direction = this->nextDirection(direction);
        auto [nx, ny] = this->nextPosition(direction, x, y);

        x = nx;
        y = ny;
      }
      else
      {
        auto [nx, ny] = this->nextPosition(direction, x, y);
        x = nx;
        y = ny;
      }
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
  cout << "Part 1: " << aoc.part1() << endl;
  cout << "--------------------------" << endl;
  cout << "Part 2 test: " << test2.part2() << endl;
  cout << "Part 2: " << aoc.part2() << endl;

  return 0;
}