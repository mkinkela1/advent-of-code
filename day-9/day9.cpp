#include<iostream>
#include<fstream>
#include<map>

using namespace std;

bool isTouching(pair<int, int> head, pair<int, int> tail) {
    return abs(head.first - tail.first) <= 1 && abs(head.second - tail.second) <= 1;
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
    map<pair<int,int>, bool> tailPositions;
    pair<int,int> head = make_pair(0, 0), tail = make_pair(0, 0);

    while(fin >> dir >> nMoves) {
        tailPositions[tail] = true;

        for(int i = 0; i < nMoves; ++i) {
            
            pair<int, int> next = calcNextPosition(head, dir);
            if(!isTouching(next, tail)) {
                tail = head;
                head = next;
            }

            head = next;

            tailPositions[tail] = true;
        }
    }

    int sol = 0;
    for(auto& pos: tailPositions) 
        sol += pos.second == true;

    cout << sol << endl;


    return 0;
}