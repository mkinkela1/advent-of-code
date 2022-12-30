#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<tuple>
#include<map>

using namespace std;

map<string, long long> numValues;
map<string, tuple<string, char, string> > expressions;

auto calc(string root) -> long long {
    if(numValues.count(root)) return numValues[root];
    else {
        tuple<string, char, string> expression = expressions[root];
        string left = get<0>(expression), right = get<2>(expression);
        char oper = get<1>(expression);

        switch(oper) {
            case '+':
                return calc(left) + calc(right);
            case '-':
                return calc(left) - calc(right);
            case '*':
                return calc(left) * calc(right);
            case '/':
                return calc(left) / calc(right);
            default:
                exit(1);
        }
    }
}

auto main() -> int {
    
    fstream fin;
    fin.open("day21-input.txt", ios::in);

    string line;
    while(getline(fin, line)) {
        if(isdigit(line[6])) {

            char name[10];
            long long value;
            sscanf(line.c_str(), "%04s: %lld", name, &value);

            numValues[name] = value;
        } else {
            char name[10], left[10], right[10], oper;
            sscanf(line.c_str(), "%04s: %04s %c %04s", name, left, &oper, right);

            expressions[name] = {left, oper, right};
        }
    } 

    cout << calc("root") << endl;

    return 0;
}