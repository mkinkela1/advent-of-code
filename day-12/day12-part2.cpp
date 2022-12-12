#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<utility>

using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool canMove(pair<int, int> start, pair<int, int> end, vector<vector<int> > grid) {
    return (grid[end.first][end.second] - grid[start.first][start.second]) <= 1;
}

int bfs(pair<int, int> start, pair<int, int> end, vector<vector<int> > &grid) {
    vector<vector<int> > dist;
    vector<vector<bool> > checked;

    for(auto& row : grid) {
        vector<int> tmp1(row.size(), -1);
        vector<bool> tmp2(row.size(), false);

        dist.push_back(tmp1);
        checked.push_back(tmp2);
    }

    queue<pair<int, int> > Q;
    Q.push(start);
    dist[start.first][start.second] = 0;

    while(!Q.empty()) {
        pair<int, int> curr = Q.front();
        Q.pop();

        for(int i = 0; i < 4; ++i) {
            int nextX = curr.first + dx[i];
            int nextY = curr.second + dy[i];

            if(nextX < 0 || nextX >= grid.size() || nextY < 0 || nextY >= grid[0].size()) continue;
            if(checked[nextX][nextY]) continue;

            if(canMove(curr, make_pair(nextX, nextY), grid)) {

                dist[nextX][nextY] = dist[curr.first][curr.second] + 1;
                checked[nextX][nextY] = true;

                Q.push(make_pair(nextX, nextY));
            }
        }
    }

    return dist[end.first][end.second];
}


int main(void) {

    fstream fin;
    fin.open("day12-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    vector<vector<int> > grid;
    vector<pair<int, int> > starts;
    pair<int, int> end;
    for(int i = 0; getline(fin, line); ++i) {
        vector<int> row;
        for(int j = 0; j < line.length(); ++j) {
            if(line[j] == 'S' || line[j] == 'a') {
                starts.push_back(make_pair(i, j));
                row.push_back(0);
            } else if (line[j] == 'E') {
                end = make_pair(i, j);
                row.push_back('z' - 'a');
            } else 
                row.push_back(line[j] - 'a');
        }

        grid.push_back(row);
    }

    int sol = INT_MAX;
    for(auto& start : starts) {
        int curr = bfs(start, end, grid);
        if(curr > -1) 
            sol = min(sol, curr);
    }

    cout << sol << endl;

    return 0;
}