#include<iostream>
#include<map>
#include<fstream>
#include<queue>

using namespace std;

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

auto main() -> int {
    
    fstream fin;
    fin.open("day18-input.txt", ios::in);

    string line;
    map<pair<pair<int, int>, int>, bool> obsidians;
    map<pair<pair<int, int>, int>, bool> _obsidians;
    map<pair<pair<int, int>, int>, bool> water;
    while(getline(fin, line)) {

        int x, y, z;
        sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);

        obsidians[make_pair(make_pair(x, y), z)] = true;
    }

    _obsidians = obsidians;

    queue<pair<pair<int, int>, int> > Q;
    Q.push(make_pair(make_pair(-1, -1), -1));

    while(!Q.empty()) {
        pair<pair<int, int>, int> tmp = Q.front();
        water[tmp] = true;
        Q.pop();

        for(int i = 0; i < 6; ++i) {
            int nextX = tmp.first.first + dx[i];
            int nextY = tmp.first.second + dy[i];
            int nextZ = tmp.second + dz[i];
            if(
                nextX < -1 || 
                nextX >= 30 || 
                nextY < -1 || 
                nextY >= 30 ||
                nextZ < -1 ||
                nextZ >= 30
            ) continue;

            if(!water[make_pair(make_pair(nextX, nextY), nextZ)] && !_obsidians[make_pair(make_pair(nextX, nextY), nextZ)]) {
                water[make_pair(make_pair(nextX, nextY), nextZ)] = true;
                Q.push(make_pair(make_pair(nextX, nextY), nextZ));
            }
        }
    }

    int sol = 0;
    for(auto& o : obsidians) {
        for(int i = 0; i < 6; ++i) 
            if(water[make_pair(make_pair(o.first.first.first + dx[i], o.first.first.second + dy[i]), o.first.second + dz[i])])
                ++sol;
    }
    
    cout << sol << endl;

    return 0;
}