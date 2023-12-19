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

class Rule
{
private:
    string category;
    char sign;
    int value;
    string workflow;

public:
    Rule(string category, char sign, int value, string workflow)
    {
        this->category = category;
        this->sign = sign;
        this->value = value;
        this->workflow = workflow;
    }

    auto getCategory() -> string { return this->category; }
    auto getSign() -> char { return this->sign; }
    auto getValue() -> int { return this->value; }
    auto getWorkflow() -> string { return this->workflow; }
};

class Solution
{
private:
    fstream fin;
    map<string, tuple<vector<Rule>, string>> rules;
    vector<map<string, int>> ratings;

    void parse()
    {
        bool foundEmptyLine = false;
        string line;

        while (getline(this->fin, line))
        {
            if (line == "")
            {
                foundEmptyLine = true;
                continue;
            }

            if (foundEmptyLine)
            {
                line = line.substr(1, line.size() - 2);
                vector<string> tokens = split(line, ",");
                map<string, int> rating;

                for (string token : tokens)
                {
                    vector<string> keyValue = split(token, "=");
                    string key = keyValue[0];
                    int value = stoi(keyValue[1]);

                    rating[key] = value;
                }
                this->ratings.push_back(rating);
            }
            else
            {
                vector<string> tokens = split(line, "{");
                string category = tokens[0];
                string rules = tokens[1].substr(0, tokens[1].size() - 1);

                vector<string> rulesVectorString = split(rules, ",");
                string elseFlow = rulesVectorString[rulesVectorString.size() - 1];
                rulesVectorString.pop_back();

                vector<Rule> rulesVector;
                for (string rule : rulesVectorString)
                {
                    vector<string> ruleTokens = split(rule, ":");
                    string workflow = ruleTokens[1];

                    string category = ruleTokens[0].substr(0, 1);
                    char sign = ruleTokens[0][1];
                    int value = stoi(ruleTokens[0].substr(2, ruleTokens[0].size()));

                    rulesVector.push_back(Rule(category, sign, value, workflow));
                }

                this->rules[category] = make_tuple(rulesVector, elseFlow);
            }
        }
    }

    auto getCategory(vector<Rule> rules, string elseFlow, map<string, int> rating) -> string
    {
        for (Rule rule : rules)
        {
            string category = rule.getCategory();
            char sign = rule.getSign();
            int value = rule.getValue();
            string workflow = rule.getWorkflow();

            int ratingValue = rating[category];

            if (sign == '<')
                if (ratingValue < value)
                    return workflow;
            if (sign == '>')
                if (ratingValue > value)
                    return workflow;
        }

        return elseFlow;
    }

    auto solve(map<string, int> rating) -> int
    {
        string category = "in";

        while (true)
        {
            vector<Rule> rules = get<0>(this->rules[category]);
            string elseFlow = get<1>(this->rules[category]);

            category = this->getCategory(rules, elseFlow, rating);
            if (category == "R" || category == "A")
                break;
        }

        return category == "A" ? 1 : 0;
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

        for (auto rating : this->ratings)
            if (this->solve(rating))
                sol += rating["x"] + rating["m"] + rating["a"] + rating["s"];

        return sol;
    }
    auto part2() -> long long unsigned
    {
        long long unsigned sol = 0LLU;
        queue<tuple<string, pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>>> q;
        vector<tuple<pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>>> solutions;
        q.push(make_tuple("in", make_pair(1, 4000), make_pair(1, 4000), make_pair(1, 4000), make_pair(1, 4000)));

        while (!q.empty())
        {
            auto [category, x, m, a, s] = q.front();
            q.pop();

            if (category == "A")
            {
                solutions.push_back(make_tuple(x, m, a, s));
                continue;
            }
            if (category == "R")
            {
                continue;
            }

            vector<Rule> rules = get<0>(this->rules[category]);
            string elseFlow = get<1>(this->rules[category]);

            for (Rule rule : rules)
            {
                string category = rule.getCategory();
                char sign = rule.getSign();
                int value = rule.getValue();
                string workflow = rule.getWorkflow();

                if (category == "x")
                {
                    if (sign == '<')
                    {
                        if (x.second < value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (x.first < value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, value - 1), m, a, s));
                            x.first = value;
                        }
                    }
                    else
                    {
                        if (x.first > value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (x.second > value)
                        {
                            q.push(make_tuple(workflow, make_pair(value + 1, x.second), m, a, s));
                            x.second = value;
                        }
                    }
                }
                else if (category == "m")
                {
                    if (sign == '<')
                    {
                        if (m.second < value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (m.first < value)
                        {
                            q.push(make_tuple(workflow, x, make_pair(m.first, value - 1), a, s));
                            m.first = value;
                        }
                    }
                    else
                    {
                        if (m.first > value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (m.second > value)
                        {
                            q.push(make_tuple(workflow, x, make_pair(value + 1, m.second), a, s));
                            m.second = value;
                        }
                    }
                }
                else if (category == "a")
                {
                    if (sign == '<')
                    {
                        if (a.second < value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (a.first < value)
                        {
                            q.push(make_tuple(workflow, x, m, make_pair(a.first, value - 1), s));
                            a.first = value;
                        }
                    }
                    else
                    {
                        if (a.first > value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (a.second > value)
                        {
                            q.push(make_tuple(workflow, x, m, make_pair(value + 1, a.second), s));
                            a.second = value;
                        }
                    }
                }
                else if (category == "s")
                {
                    if (sign == '<')
                    {
                        if (s.second < value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (s.first < value)
                        {
                            q.push(make_tuple(workflow, x, m, a, make_pair(s.first, value - 1)));
                            s.first = value;
                        }
                    }
                    else
                    {
                        if (s.first > value)
                        {
                            q.push(make_tuple(workflow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
                        }
                        else if (s.second > value)
                        {
                            q.push(make_tuple(workflow, x, m, a, make_pair(value + 1, s.second)));
                            s.second = value;
                        }
                    }
                }
            }

            if (elseFlow != "R")
            {
                q.push(make_tuple(elseFlow, make_pair(x.first, x.second), make_pair(m.first, m.second), make_pair(a.first, a.second), make_pair(s.first, s.second)));
            }
        }

        for (auto [x, m, a, s] : solutions)
        {
            if (x.second - x.first < 0 || m.second - m.first < 0 || a.second - a.first < 0 || s.second - s.first < 0)
                continue;
            sol += (long long unsigned)(x.second - x.first + 1) * (m.second - m.first + 1) * (a.second - a.first + 1) * (s.second - s.first + 1);
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