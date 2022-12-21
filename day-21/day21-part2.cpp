#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<tuple>
#include<map>
#include<cmath>

using namespace std;

map<string, long double> numValues;
map<string, tuple<string, char, string> > expressions;

auto calc(string root, long double humn) -> long double {
    if(root == "root") {
        tuple<string, char, string> expression = expressions[root];
        string left = get<0>(expression), right = get<2>(expression);
        long double A = calc(left, humn), B = calc(right, humn);

        if(fabs(A - B) < 1e-5) return 0;
        if(A < B) return -1;
        else return 1;
    }
    else if(root == "humn") return humn;
    else if(numValues.count(root)) return numValues[root];
    else {
        tuple<string, char, string> expression = expressions[root];
        string left = get<0>(expression), right = get<2>(expression);
        char oper = get<1>(expression);

        switch(oper) {
            case '+':
                return calc(left, humn) + calc(right, humn);
            case '-':
                return calc(left, humn) - calc(right, humn);
            case '*':
                return calc(left, humn) * calc(right, humn);
            case '/':
                return calc(left, humn) / calc(right, humn);
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

    uint64_t low = 0, high = 1ULL << 62;
    while(high - low > 0) {
        long long mid = (low + high) >> 1;
        long long tmp = calc("root", mid);
        if(tmp == 0) {
            cout << mid << endl;
            return 0;
        } 
        if(tmp < 0) 
            high = mid - 1;
        else low = mid + 1;
    }

    return 0;
}