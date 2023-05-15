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
        vector<string> names;
        map<pair<string, string>, int> points;

        void parse() {
            string line;
            set<string> uniqueNames;

            while(getline(this->fin, line)) {
                char prefix[10], name1[50], name2[50];
                int happiness, pref = 1;

                sscanf(line.c_str(), "%s would %s %d happiness units by sitting next to %s.", name1, prefix, &happiness, name2);

                if(prefix[0] == 'l') pref = -1;

                string name2WithoutLastCharacter(name2);
                name2WithoutLastCharacter.pop_back();

                this->points[make_pair(name1, name2WithoutLastCharacter)] = pref * happiness;
                uniqueNames.insert(name1);
                uniqueNames.insert(name2WithoutLastCharacter);
            }

            for(auto& name: uniqueNames) 
                this->names.push_back(name);

        }
    public:
        Solution() {
            this->fin.open("input.txt", ios::in);
            this->parse();
        }

        auto part1() -> int {
            int sol = 0;
            int n = this->names.size();

            do {

                int tmp = 0;
                for(int i = 1; i < n; ++i) {
                    tmp += this->points[make_pair(this->names[i-1], this->names[i])];
                    tmp += this->points[make_pair(this->names[i], this->names[i-1])];
                }

                tmp += this->points[make_pair(this->names[n-1], this->names[0])];
                tmp += this->points[make_pair(this->names[0], this->names[n-1])];

                sol = max(sol, tmp);

            } while(next_permutation(names.begin(), names.end()));

            return sol;
        }
        auto part2() -> int { 

            for(auto& name: this->names)
                this->points[make_pair(name, "me")] = 0;

            this->names.push_back("me");
            sort(this->names.begin(), this->names.end());

            return this->part1(); 
        }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}