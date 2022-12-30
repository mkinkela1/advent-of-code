#include<iostream>
#include<fstream>
#include<set>

using namespace std;

int getValue(char C) {
    if(isupper(C)) return C - 'A' + 27;
    return C - 'a' + 1;
}

int calc(string str) {

    int half = str.length() / 2;
    set<char> S;

    for(int i = 0; i < half; ++i)
        S.insert(str[i]);

    for(int i = half; i < str.length(); ++i)
        if(S.find(str[i]) != S.end())
            return getValue(str[i]);
}

int main(void) {

    fstream fin;
    fin.open("day3-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    int sol = 0;
    while(fin >> line) 
        sol += calc(line);

    cout << sol << endl;

    return 0;
}