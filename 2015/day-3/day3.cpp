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
#include<set>

using namespace std;

class Solution {
    private:
        fstream fin;
        string line;

        void parse() {
            getline(this->fin, this->line);
        }
    public:
        Solution() {
            this->fin.open("input.txt", ios::in);
            this->parse();
        }

        auto part1() -> int {
            set<pair<int, int>> locations;
            int x = 0, y = 0;

            locations.insert({x, y});

            for(auto& c: this->line) {
                switch(c) {
                    case '<':
                        --x;
                        break;
                    case '>':
                        ++x;
                        break;
                    case 'v':
                        --y;
                        break;
                    case '^':
                        ++y;
                        break;
                    default:
                        exit(1);
                }

                locations.insert({x, y});
            }

            return locations.size();
        }
        auto part2() -> int { 
            set<pair<int, int>> locations;
            int xs = 0, ys = 0, xr = 0, yr = 0;

            locations.insert({0, 0});
            
            for(int i = 0; i < this->line.size(); ++i) {
                if(i%2 == 0) {
                    switch(this->line[i]) {
                        case '<':
                            --xs;
                            break;
                        case '>':
                            ++xs;
                            break;
                        case 'v':
                            --ys;
                            break;
                        case '^':
                            ++ys;
                            break;
                        default:
                            exit(1);
                    }
                    locations.insert({xs, ys});
                } else {
                    switch(this->line[i]) {
                        case '<':
                            --xr;
                            break;
                        case '>':
                            ++xr;
                            break;
                        case 'v':
                            --yr;
                            break;
                        case '^':
                            ++yr;
                            break;
                        default:
                            exit(1);
                    }
                    locations.insert({xr, yr});
                }
            }

            return locations.size();
         }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}