#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<tuple>
#include<map>
#include<queue>
#include<array>
#include<unordered_map>

using namespace std;

enum Dir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

array<int, 5> dx = {-1, 1, 0, 0, 0};
array<int, 5> dy = {0, 0, -1, 1, 0};

struct State {
    int x, y, time;

    State(int _x, int _y, int _time) {
        this->x = _x;
        this->y = _y;
        this->time = _time;
    }

    friend auto operator== (State A, pair<int, int> B) -> bool {
        return A.x == B.first && A.y == B.second;
    }

    friend auto operator< (State A, State B) -> bool {
        if(A.x != B.x) return A.x < B.x;
        if(A.y != B.y) return A.y < B.y;
        return A.time < B.time;
    }
};

class Blizzard {
    private:
        int x, y;
        Dir dir;

        void moveUp(vector<string> grid) {
            if(this->x == 1) 
                this->x = grid.size() - 2;
            else 
                this->x--;
        }

        void moveDown(vector<string> grid) {
            if(this->x == grid.size() - 2) 
                this->x = 1;
            else 
                this->x++;
        }

        void moveLeft(vector<string> grid) {
            if(this->y == 1) 
                this->y = grid[0].size() - 2;
            else 
                this->y--;
        }

        void moveRight(vector<string> grid) {
            if(this->y == grid[0].size() - 2) 
                this->y = 1;
            else 
                this->y++;
        }
    public:
        Blizzard(int _x, int _y, char _dir) {
            this->x = _x;
            this->y = _y;
            switch(_dir) {
                case '>':
                    this->dir = RIGHT;
                    break;
                case '<':
                    this->dir = LEFT;
                    break;
                case 'v':
                    this->dir = DOWN;
                    break;
                case '^':
                    this->dir = UP;
                    break;
                default:
                    cout << "Something is wrong!" << endl; 
                    break;
            }
        }

        void move(vector<string> grid) {
            switch(this->dir) {
                case UP: 
                    moveUp(grid);
                    return;
                case DOWN:
                    moveDown(grid);
                    return;
                case LEFT:
                    moveLeft(grid);
                    return;
                case RIGHT:
                    moveRight(grid);
                    return;
                default:
                    cout << "I did something wrong!" << endl;
                    return;
            }
        }

        auto operator== (State tmp) -> bool {
            return this->x == tmp.x && this->y == tmp.y;
        }

        auto operator== (pair<int, int> tmp) -> bool {
            return this->x == tmp.first && this->y == tmp.second;
        }
};

auto moveBlizzard(vector<Blizzard> &blizzards, vector<string> grid) -> void {
    for(auto& blizzard: blizzards) 
        blizzard.move(grid);
}

auto bfs(pair<int, int> start, pair<int, int> end, map<int, vector<Blizzard> > blizzardsInTime, vector<string> grid) -> int {
    queue<State> Q;
    map<State, bool> checked;
    Q.push(State(start.first, start.second, 0));

    while(!Q.empty()) {
        State tmp = Q.front();
        Q.pop();

        if(checked[tmp]) continue;
        checked[tmp] = 1;

        if(tmp == end) return tmp.time;

        for(int i = 0; i < 5; ++i) {
            int nextX = tmp.x + dx[i];
            int nextY = tmp.y + dy[i];

            if(nextX < 0 || nextX >= grid.size() || nextY < 0 || nextY >= grid[0].size()) continue;
            if(grid[nextX][nextY] == '#') continue;

            State next = State(nextX, nextY, tmp.time + 1);
            if(checked[next]) continue;

            bool ok = true;

            for(auto& blizzard: blizzardsInTime[next.time]) 
                if(blizzard == next)
                    ok = false;

            if(ok) 
                Q.push(next);
            
        }
    }
}

auto main() -> int {
    
    fstream fin;
    fin.open("day24-input.txt", ios::in);

    vector<string> grid;
    vector<Blizzard> blizzards;
    string line;
    int idx = 0;
    while(getline(fin, line)) {
        grid.push_back(line);

        for(int idy = 0; idy < line.length(); ++idy)
            if(line[idy] != '.' && line[idy] != '#')
                blizzards.push_back(Blizzard(idx, idy, line[idy]));

        ++idx;
    }

    map<int, vector<Blizzard> > blizzardsInTime;
    for(int i = 0; i < 500; ++i) {
        blizzardsInTime[i] = blizzards;
        moveBlizzard(blizzards, grid);
    }

    pair<int, int> start, end;
    int lastRow = grid.size() - 1;
    for(int i = 0; i < grid[0].size(); ++i) {
        if(grid[0][i] == '.') start = make_pair(0, i);
        if(grid[lastRow][i] == '.') end = make_pair(lastRow, i);
    }

    cout << bfs(start, end, blizzardsInTime, grid) << endl;

    return 0;
}