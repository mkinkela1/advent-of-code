#include <string>
#include <vector>

using namespace std;

auto rotateClockwise(vector<string> grid) -> vector<string>
{
    vector<string> rotatedGrid;
    for (int i = 0; i < grid[0].size(); i++)
    {
        string row = "";
        for (int j = grid.size() - 1; j >= 0; j--)
        {
            row += grid[j][i];
        }
        rotatedGrid.push_back(row);
    }

    return rotatedGrid;
}