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
        vector<string> words;

        void parse() {
            string line;

            while(getline(this->fin, line))
                this->words.push_back(line);
        }

        auto has3Vowels(string word) -> bool {
            int vowels = 0;

            for(auto& c: word) 
                if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    ++vowels;

            return vowels >= 3;
        }

        auto contains(string word) -> bool {
            for(int i = 1; i < word.size(); ++i)
                if(word[i-1] == word[i])
                    return true;

            return false;
        }

        auto notContains(string word) -> bool {
            if(word.find("ab") != string::npos) return false;
            if(word.find("cd") != string::npos) return false;
            if(word.find("pq") != string::npos) return false;
            if(word.find("xy") != string::npos) return false;
            return true;
        }

        auto equalWithMiddle(string word) -> bool {

            for(int i = 1; i < word.size()-1; ++i)
                if(word[i-1] == word[i+1])
                    return true;

            return false;
        }

        auto pairAppearsTwice(string word) -> bool {
            for(int i = 0; i < word.size() - 3; ++i) {
                for(int j = i + 2; j < word.size() - 1; ++j) {
                    string s1 = word.substr(i, 2);
                    string s2 = word.substr(j, 2);

                    if(s1 == s2) return true;
                }
            }

            return false;
        }

    public:
        Solution() {
            this->fin.open("input.txt", ios::in);
            this->parse();
        }

        auto part1() -> int { 
            int sol = 0;

            for(auto& word: this->words)
                if(this->has3Vowels(word) && this->contains(word) && this->notContains(word))
                    ++sol;

            return sol;
        }
        auto part2() -> int { 
            int sol = 0;

            for(auto& word: this->words)
                if(this->pairAppearsTwice(word) && this->equalWithMiddle(word))
                    ++sol;

            return sol;
        }
};

auto main() -> int {

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}