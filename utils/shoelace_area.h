
#include <vector>

using namespace std;

auto calculateArea(vector<pair<long long, long long>> points) -> long long
{
    long long ret = 0;

    points.push_back(points[0]);
    for (int i = 0; i < points.size() - 1; ++i)
    {
        long long X1 = points[i].first;
        long long Y1 = points[i].second;
        long long X2 = points[i + 1].first;
        long long Y2 = points[i + 1].second;
        ret += X1 * Y2 - X2 * Y1;
    }

    ret /= 2;

    return ret;
}

// https://en.wikipedia.org/wiki/Shoelace_formula
auto getShoelaceArea(vector<pair<long long, long long>> points) -> long long
{
    vector<pair<long long, long long>> _points = points;
    points.push_back(points[0]);

    long long oneSide = calculateArea(_points);

    if (oneSide >= 0)
        return oneSide;

    // if oneSide is negative, then the points are in clockwise order
    _points = points;
    reverse(_points.begin(), _points.end());
    _points.push_back(_points[0]);

    long long otherSide = calculateArea(_points);

    return otherSide;
}