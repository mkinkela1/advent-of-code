#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<utility>

using namespace std;

int distance(pair<int, int> head, pair<int, int> tail) {
    return max(abs(head.first - tail.first), abs(head.second - tail.second));
}

pair<int, int> calcNextPosition(pair<int, int> current, char dir) {
    pair<int, int> ret = current;

    switch (dir) {
        case 'U':
            ret.first++;
            return ret;
        case 'D':
            ret.first--;
            return ret;
        case 'L':
            ret.second--;
            return ret;
        case 'R':
            ret.second++;
            return ret;
        
        default:
            return make_pair(-100000, -10000);
    }
}

int main(void) {

    fstream fin;
    fin.open("day9-input.txt", ios::in);

    cout << fin.is_open() << endl;

    char dir;
    int nMoves;
    map<pair<int,int>, bool> visitedPositions;
    vector<pair<int,int> > rope(10, make_pair(0, 0));

    visitedPositions[make_pair(0, 0)] = true;
    while(fin >> dir >> nMoves) {

        for(int i = 0; i < nMoves; ++i) {
            
            for(int j = 0; j < 10; ++j) {
                if(!j) {
                    rope[j] = calcNextPosition(rope[j], dir);
                } else {
                    pair<int, int> curr = rope[j];
                    if(distance(rope[j], rope[j-1]) > 1) {
                        if(rope[j].first != rope[j-1].first) {
                            int deltaX = rope[j-1].first - rope[j].first;
                            rope[j].first += deltaX / abs(deltaX);
                        }

                        if(rope[j].second != rope[j-1].second) {
                            int deltaY = rope[j-1].second - rope[j].second;
                            rope[j].second += deltaY / abs(deltaY);
                        }
                    }
                }
            }
            visitedPositions[rope[9]] = true;
        }
    }

    int sol = 0;
    for(auto& pos: visitedPositions) 
        sol += pos.second == true;

    cout << sol << endl;


    return 0;
}