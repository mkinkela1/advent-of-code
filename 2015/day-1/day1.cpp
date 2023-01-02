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
            int floor = 0;

            for(auto& c: this->line)
                floor += c == '(' ? 1 : -1;

            return floor;
        }
        auto part2() -> int {
            int floor = 0;

            for(int i = 0; i < this->line.size(); ++i) {
                floor += this->line[i] == '(' ? 1 : -1;
                if(floor == -1) return i + 1;
            }
        }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}