#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <unordered_map>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    map<string, vector<string>> nodes;
    map<pair<string, string>, int> dist;
    vector<string> usefulNodes;
    map<string, int> rates;
    map<tuple<uint64_t, uint64_t, uint64_t>, uint64_t> cache;
    map<uint64_t, uint64_t> bestForMask;

    void bfs(string start)
    {
        queue<tuple<string, int>> q;
        unordered_map<string, bool> visited;

        q.push({start, 0});
        visited[start] = true;

        while (!q.empty())
        {
            auto [node, d] = q.front();
            q.pop();

            this->dist[{start, node}] = d;

            for (auto n : this->nodes[node])
            {
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push({n, d + 1});
                }
            }
        }
    }

    void parse()
    {
        string line;
        
        this->usefulNodes.push_back("AA");

        while (getline(this->fin, line))
        {
            char valve[10];
            int rate;
            char tunnels[1000];
            sscanf(line.c_str(), "Valve %s has flow rate=%d;%*[^A-Z]%[^\n]", valve, &rate, tunnels);

            this->nodes[string(valve)] = split(string(tunnels), ", ");
            this->rates[string(valve)] = rate;
            if (rate > 0)
                this->usefulNodes.push_back(string(valve));
        }

        this->bfs("AA");

        for (auto node : this->usefulNodes)
            this->bfs(node);
    }

    uint64_t solve(int pos = 0, int timeLeft = 30, uint64_t mask = 0)
    {
        int n = this->usefulNodes.size();
        if(timeLeft <= 0) return 0;

        auto key = make_tuple(uint64_t(pos), uint64_t(timeLeft), mask);
        if(this->cache.count(key)) return this->cache[key];

        uint64_t best = 0;
        
        for(int next = 1; next < n; next++)
        {
            if(mask & (1ULL << next)) continue;

            int travelTime = this->dist[{this->usefulNodes[pos], this->usefulNodes[next]}];
            int newTime = timeLeft - travelTime - 1;
            if(newTime <= 0) continue;

            uint64_t gained = this->rates[this->usefulNodes[next]] * newTime;
            
            best = max(best, gained + this->solve(next, newTime, mask | (1ULL << next)));
        }
        
        return this->cache[key] = best;
    }


    uint64_t solve2(int pos = 0, int timeLeft = 26, uint64_t mask = 0, uint64_t totalPressure = 0)
    {
        int n = this->usefulNodes.size();
        
        this->bestForMask[mask] = max(this->bestForMask[mask], totalPressure);
        
        if(timeLeft <= 0) return totalPressure;

        uint64_t best = totalPressure;
        
        for(int next = 1; next < n; next++)
        {
            if(mask & (1ULL << next)) continue;

            int travelTime = this->dist[{this->usefulNodes[pos], this->usefulNodes[next]}];
            int newTime = timeLeft - travelTime - 1;
            if(newTime <= 0) continue;

            uint64_t gained = this->rates[this->usefulNodes[next]] * newTime;
            
            best = max(best, this->solve2(next, newTime, mask | (1ULL << next), totalPressure + gained));
        }
        
        return best;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> uint64_t
    {
        return this->solve(0, 30, 0);
    }
    auto part2() -> uint64_t { 

        this->cache.clear();
        this->bestForMask.clear();

        this->solve2(0, 26, 0, 0);

        uint64_t best = 0;
        for(auto &[mask1, val1] : this->bestForMask) {
            for(auto &[mask2, val2] : this->bestForMask) {
                if((mask1 & mask2) == 0) 
                best = max(best, val1 + val2);
            }
        }

        return best;
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1() << endl;
    cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}