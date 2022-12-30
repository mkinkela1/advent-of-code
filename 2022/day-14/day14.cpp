#include<iostream>
#include<fstream>
#include<queue>
#include<list>
#include<utility>
#include<variant>

using namespace std;

int mat[1000][1000];

vector<pair<int, int> > parse(string str) {
    
    int pos = 0;
    vector<pair<int, int> > ret;

    while(pos < str.length()) {
        int a = 0, b = 0;
        while(pos < str.length() && isdigit(str[pos])) {
            a *= 10;
            a += str[pos++] - '0';
        } 
        ++pos;
        while(pos < str.length() && isdigit(str[pos])) {
            b *= 10;
            b += str[pos++] - '0';
        } 
        ret.push_back(make_pair(b, a));
        while(pos < str.length() && !isdigit(str[pos])) ++pos;
    }

    return ret;
}

void draw(vector<pair<int, int> > V) {
    for(int i = 1; i < V.size(); ++i) {

        if(V[i-1].first == V[i].first) 
            for(int pos = min(V[i-1].second, V[i].second); pos <= max(V[i-1].second, V[i].second); ++pos)
                mat[V[i].first][pos] = 1;

        if(V[i-1].second == V[i].second) 
            for(int pos = min(V[i-1].first, V[i].first); pos <= max(V[i-1].first, V[i].first); ++pos)
                mat[pos][V[i].second] = 1;
    }
}

bool simulateSand() {
    pair<int, int> sand = make_pair(0, 500);

    while(true) {
        if(mat[sand.first+1][sand.second] == 0) {// down
            sand.first++;
            if(sand.first >= 1000)
                return true;
        } else if(mat[sand.first+1][sand.second-1] == 0) { // down-left
            sand.first++;
            sand.second--;
        } else if(mat[sand.first+1][sand.second+1] == 0) { // down-right
            sand.first++;
            sand.second++;
        } else {
            mat[sand.first][sand.second] = 2;
            if(sand.first >= 1000)
                return true;
            break;
        }
    }

    return false;
}

int main(void) {

    fstream fin;
    fin.open("day14-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    int sol = 0;
    while(getline(fin, line)) {
        vector<pair<int, int> > V = parse(line);

        draw(V);
    }

    while(true) {
        if(simulateSand()) {
            cout << sol << endl;
            return 0;
        }
        ++sol;
    }

    return 0;
}