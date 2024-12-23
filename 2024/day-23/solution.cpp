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
#include <set>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    set<string> computers;
    set<pair<string, string>> directional;
    map<string, vector<string>> connections;
    vector<string> maxCliques;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> parts = split(line, "-");
            this->computers.insert(parts[0]);
            this->computers.insert(parts[1]);
            this->connections[parts[0]].push_back(parts[1]);
            this->connections[parts[1]].push_back(parts[0]);
            this->directional.insert({parts[0], parts[1]});
            this->directional.insert({parts[1], parts[0]});
        }
    }

    set<string> bfs(string start, set<string> &visited)
    {
        queue<string> q;
        set<string> unique;
        q.push(start);
        visited.insert(start);
        unique.insert(start);

        while (!q.empty())
        {
            string current = q.front();
            q.pop();

            unique.insert(current);

            for (auto c : this->connections[current])
            {
                if (visited.find(c) == visited.end())
                {
                    visited.insert(c);
                    q.push(c);
                }
            }
        }

        return unique;
    }

    void BronKerbosch(set<string> R, set<string> P, set<string> X)
    {
        if (P.empty() && X.empty())
        {
            if (R.size() > this->maxCliques.size())
                this->maxCliques = vector<string>(R.begin(), R.end());
            return;
        }

        string pivot = *P.begin();
        set<string> unionPX = P;
        unionPX.insert(X.begin(), X.end());

        for (auto &v : unionPX)
            if (this->connections[v].size() > this->connections[pivot].size())
                pivot = v;

        set<string> excludedNeighbors;
        for (auto &neighbor : this->connections[pivot])
            if (P.find(neighbor) != P.end())
                excludedNeighbors.insert(neighbor);

        vector<string> candidates;
        for (auto &v : P)
            if (excludedNeighbors.find(v) == excludedNeighbors.end())
                candidates.push_back(v);

        for (auto &v : candidates)
        {
            set<string> newR = R;
            newR.insert(v);

            set<string> newP, newX;

            for (auto &u : P)
                if (find(this->connections[v].begin(), this->connections[v].end(), u) != this->connections[v].end())
                    newP.insert(u);

            for (auto &u : X)
                if (find(this->connections[v].begin(), this->connections[v].end(), u) != this->connections[v].end())
                    newX.insert(u);

            BronKerbosch(newR, newP, newX);

            P.erase(v);
            X.insert(v);
        }
    }

    vector<string> findMaxClique()
    {
        set<string> R, P, X;

        for (auto c : this->computers)
            P.insert(c);

        BronKerbosch(R, P, X);

        return this->maxCliques;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sol = 0;
        set<tuple<string, string, string>> visited;
        for (auto c1 : this->computers)
        {
            for (auto c2 : this->computers)
            {
                if (c1 == c2)
                    continue;

                if (this->directional.find({c1, c2}) == this->directional.end())
                    continue;

                for (auto c3 : this->computers)
                {
                    if (c3 == c1 || c3 == c2)
                        continue;

                    if (c1[0] != 't' && c2[0] != 't' && c3[0] != 't')
                        continue;

                    if (
                        this->directional.find({c1, c2}) != this->directional.end() &&
                        this->directional.find({c2, c3}) != this->directional.end() &&
                        this->directional.find({c3, c1}) != this->directional.end() && visited.find({c1, c2, c3}) == visited.end())
                    {
                        visited.insert({c1, c2, c3});
                        visited.insert({c1, c3, c2});
                        visited.insert({c2, c1, c3});
                        visited.insert({c2, c3, c1});
                        visited.insert({c3, c1, c2});
                        visited.insert({c3, c2, c1});

                        ++sol;
                    }
                }
            }
        }
        return sol;
    };

    auto part2() -> string
    {

        string sol = "";

        vector<string> maxClique = this->findMaxClique();

        sort(maxClique.begin(), maxClique.end());

        for (int i = 0; i < maxClique.size(); i++)
        {
            sol += maxClique[i];
            if (i != maxClique.size() - 1)
                sol += ",";
        }

        return sol;
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