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

        auto part1() -> uint64_t {
            uint64_t sum = 0;
            uint64_t num = 0;
            int sign = 1;

            for(auto& c: this->line) {
                if(c == '-') sign = -1;
                if(isdigit(c)) {
                    num *= 10;
                    num += c - '0';
                } else {
                    if(num == 0) continue;
                    sum += num * sign;
                    num = 0;
                    sign = 1;
                }
            }

            return sum;
        }
        auto part2() -> string { return "Not solved"; }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}