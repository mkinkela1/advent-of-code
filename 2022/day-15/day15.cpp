#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<map>

using namespace std;

int dist(pair<int, int> s, pair<int, int> b) {
    return abs(s.first - b.first) + abs(s.second - b.second);
}

bool checkSensors(map<pair<int, int>, int> sensors, pair<int, int> beacon) {
    for(auto& sensor : sensors) {
        if(dist(sensor.first, beacon) <= sensor.second)
            return false;
    }

    return true;
}

int main(void) {

    ifstream fin("day15-input.txt");

    string line;
    map<pair<int, int>, int> sensors;
    map<pair<int, int>, bool> beacons;
    int minX = INT_MAX, maxX = INT_MIN;
    while(getline(fin, line)) {
        int sx, sy, bx, by;
        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx, &sy, &bx, &by);

        int distance = dist(make_pair(sx, sy), make_pair(bx, by));
        sensors[make_pair(sx, sy)] = distance;
        beacons[make_pair(bx, by)] = true;

        minX = min(minX, sx - distance);
        maxX = max(maxX, sx + distance);
    }

    cout << minX << " " << maxX << endl;

    const int y = 2000000;
    int sol = 0;

    for(int x = minX; x <= maxX; ++x) {
        pair<int, int> beacon = make_pair(x, y);

        if(!checkSensors(sensors, beacon) && beacons[beacon] == false) 
            sol++; 
    }

    cout << sol << endl;

    return 0;
}