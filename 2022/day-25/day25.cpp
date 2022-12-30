#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<tuple>
#include<map>
#include<queue>
#include<cmath>

using namespace std;

vector<uint64_t> pow5;

auto snafuToNumber(string str) -> uint64_t {
    uint64_t ret = 0;

    reverse(str.begin(), str.end());
    for(int i = 0; i < str.size(); ++i) {
        if(isdigit(str[i]))
            ret += pow5[i] * (str[i] - '0');

        if(str[i] == '-')
            ret += -pow5[i];

        if(str[i] == '=')
            ret += -2 * pow5[i];
    }

    return ret;
}

auto numberToSnafu(uint64_t num) -> string {
    string ret = "";

    while(num) {
        switch(num%5) {
            case 0:
                ret += '0';
                num /= 5;
                break;
            case 1:
                ret += '1';
                num /= 5;
                break;
            case 2:
                ret += '2';
                num /= 5;
                break;
            case 3:
                ret += '=';
                num /= 5;
                ++num;
                break;
            case 4:
                ret += '-';
                num /= 5;
                ++num;
                break;
            default:
                cout << num % 5 << endl;
                cout << "Impossible" << endl;
                break;
        }
    }

    reverse(ret.begin(), ret.end());

    return ret;
} 

auto main() -> int {
    
    fstream fin;
    fin.open("day25-input.txt", ios::in);

    pow5.push_back(1);
    for(int i = 1; i <= 21; ++i)
        pow5.push_back(pow5[i-1] * 5);

    string line;
    uint64_t sum = 0;
    int maxLen = 0;
    while(getline(fin, line)) 
        sum += snafuToNumber(line);

    cout << sum << endl;

    cout << numberToSnafu(sum) << endl;

    return 0;
}