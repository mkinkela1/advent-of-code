// https://en.wikipedia.org/wiki/Pick%27s_theorem
auto getPointsInsidePolygon(long long area, long long boundaryPoints) -> long long
{
    long long interiorPoints = area + boundaryPoints / 2 + 1;

    return interiorPoints;
}