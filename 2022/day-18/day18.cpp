#include<iostream>
#include<map>
#include<fstream>

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
    while(getline(fin, line)) {

        int x, y, z;
        sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);

        obsidians[make_pair(make_pair(x, y), z)] = true;
    }

    _obsidians = obsidians;

    int sol = 0;
    for(auto& o : obsidians) 
        for(int i = 0; i < 6; ++i) 
            if(!_obsidians[make_pair(make_pair(o.first.first.first + dx[i], o.first.first.second + dy[i]), o.first.second + dz[i])])
                ++sol;
    
    cout << sol << endl;

    return 0;
}