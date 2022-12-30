#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<map>

using namespace std;

const int C = 4000000;

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

int calcTuningFreq(pair<int, int> pos) {
    return C * pos.first + pos.second;
}

bool inRange(pair<int, int> pos) {
    return pos.first >= 0  && pos.first <= C && pos.second >= 0 && pos.second <= C;
}

int main(void) {

    ifstream fin("day15-input.txt");

    string line;
    map<pair<int, int>, int> sensors;
    map<pair<int, int>, bool> beacons;
    while(getline(fin, line)) {
        int sx, sy, bx, by;
        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx, &sy, &bx, &by);

        int distance = dist(make_pair(sx, sy), make_pair(bx, by));
        sensors[make_pair(sx, sy)] = distance;
        beacons[make_pair(bx, by)] = true;
    }

    int sol = 0;
    for(auto& sensor : sensors) {
        pair<int, int> topPoint = make_pair(sensor.first.first, sensor.first.second - sensor.second - 1);
        pair<int, int> bottomPoint = make_pair(sensor.first.first, sensor.first.second + sensor.second + 1);
        pair<int, int> leftPoint = make_pair(sensor.first.first - sensor.second - 1, sensor.first.second);
        pair<int, int> rightPoint = make_pair(sensor.first.first + sensor.second + 1, sensor.first.second);

        // checking NE side
        while(inRange(topPoint) && dist(topPoint, sensor.first) == sensor.second + 1) {
            if(checkSensors(sensors, topPoint)) {
                cout << topPoint.first << " " << topPoint.second << endl;
                cout << calcTuningFreq(topPoint) << endl;
                return 0;
            }

            ++topPoint.first;
            ++topPoint.second;
        }

        // checking SE side
        while(inRange(rightPoint) && dist(rightPoint, sensor.first) == sensor.second + 1) {
            if(checkSensors(sensors, rightPoint)) {
                cout << rightPoint.first << " " << rightPoint.second << endl;
                cout << calcTuningFreq(rightPoint) << endl;
                return 0;
            }

            --rightPoint.first;
            ++rightPoint.second;
        }

        // checking SW side
        while(inRange(bottomPoint) && dist(bottomPoint, sensor.first) == sensor.second + 1) {
            if(checkSensors(sensors, bottomPoint)) {
                cout << bottomPoint.first << " " << bottomPoint.second << endl;
                cout << calcTuningFreq(bottomPoint) << endl;
                return 0;
            }

            --bottomPoint.first;
            --bottomPoint.second;
        }

        // checking NW side
        while(inRange(leftPoint) && dist(leftPoint, sensor.first) == sensor.second + 1) {
            if(checkSensors(sensors, leftPoint)) {
                cout << leftPoint.first << " " << leftPoint.second << endl;
                cout << calcTuningFreq(leftPoint) << endl;
                return 0;
            }

            ++leftPoint.first;
            --leftPoint.second;
        }
    }

    cout << sol << endl;

    return 0;
}