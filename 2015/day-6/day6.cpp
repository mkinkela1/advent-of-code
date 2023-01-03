#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<tuple>
#include<map>
#include<queue>
#include<stack>
#include<array>
#include<unordered_map>
#include<cmath>

using namespace std;

enum Light {
    ON,
    OFF,
    TOGGLE
};

class Solution {
    private:
        fstream fin;
        vector<tuple<int, int, int, int, Light> > orders;

        void parse() {
            string line;

            while(getline(this->fin, line)) {
                if(line[6] == 'n') { //on

                    int x1, y1, x2, y2;
                    sscanf(line.c_str(), "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2);

                    orders.push_back({x1, y1, x2, y2, ON});
                } else if(line[6] == 'f') { //off

                    int x1, y1, x2, y2;
                    sscanf(line.c_str(), "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2);

                    orders.push_back({x1, y1, x2, y2, OFF});
                } else { //toggle

                    int x1, y1, x2, y2;
                    sscanf(line.c_str(), "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);

                    orders.push_back({x1, y1, x2, y2, TOGGLE});
                }
            }
        }

        auto inside(pair<int, int> pos, pair<int, int> start, pair<int, int> end) -> bool {
            return pos.first >= start.first && pos.first <= end.first &&
                pos.second >= start.second && pos.second <= end.second;
        }

    public:
        Solution() {
            this->fin.open("input.txt", ios::in);
            this->parse();
        }

        auto part1() -> int { 
            int sol = 0;

            for(int i = 0; i < 1000; ++i) {
                for(int j = 0; j < 1000; ++j) {

                    pair<int, int> pos = {i, j};
                    bool light = false;

                    for(auto& order: orders) {
                        int x1, y1, x2, y2;
                        Light l;

                        tie(x1, y1, x2, y2, l) = order;

                        if(!inside(pos, {x1, y1}, {x2, y2})) continue;

                        if(l == ON) light = true;
                        else if(l == OFF) light = false;
                        else light = !light;
                    }

                    if(light) ++sol;
                }
            }

            return sol;
        }
        auto part2() -> uint64_t { 
            uint64_t sol = 0;

            for(int i = 0; i < 1000; ++i) {
                for(int j = 0; j < 1000; ++j) {

                    pair<int, int> pos = {i, j};
                    uint64_t light = 0;

                    for(auto& order: orders) {
                        int x1, y1, x2, y2;
                        Light l;

                        tie(x1, y1, x2, y2, l) = order;

                        if(!inside(pos, {x1, y1}, {x2, y2})) continue;

                        if(l == ON) light++;
                        else if(l == OFF) light = light >= 1 ? light - 1 : 0;
                        else light += 2;
                    }

                    sol += light;
                }
            }

            return sol;
        }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}