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

using namespace std;

class Solution {
    private:
        fstream fin;
        vector<vector<uint64_t> > gifts;

        void parse() {
            string line;

            while(getline(this->fin, line)) {

                uint64_t a, b, c;
                vector<uint64_t> sides(3, 0);

                sscanf(line.c_str(), "%lldx%lldx%lld", &sides[0], &sides[1], &sides[2]);

                sort(sides.begin(), sides.end());

                gifts.push_back(sides);
            }
        }
    public:
        Solution() {
            this->fin.open("input.txt", ios::in);
            this->parse();
        }

        auto part1() -> uint64_t {
            uint64_t sol = 0;

            for(auto& gift: gifts) {
                sol += 2*gift[0]*gift[1] + 2*gift[0]*gift[2] + 2*gift[1]*gift[2];
                sol += gift[0]*gift[1];
            }

            return sol;
        }
        auto part2() -> uint64_t { 
            uint64_t sol = 0;

            for(auto& gift: gifts) {
                sol += gift[0] * gift[1] * gift[2];
                sol += 2*gift[0] + 2*gift[1];
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