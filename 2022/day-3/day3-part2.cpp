#include<iostream>
#include<fstream>
#include<map>

using namespace std;

int getValue(char C) {
    if(isupper(C)) return C - 'A' + 27;
    return C - 'a' + 1;
}

int calc(string str1, string str2, string str3) {

    map<char, int> M1, M2, M3;

    for(auto& str: str1) 
        M1[str] = 1;

    for(auto& str: str2) 
        if(M1[str])
            M2[str] = 1;

    for(auto& str: str3) 
        if(M2[str])
            return getValue(str);
}

int main(void) {

    fstream fin;
    fin.open("day3-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line1, line2, line3;
    int sol = 0;
    while(fin >> line1 >> line2 >> line3) 
        sol += calc(line1, line2, line3);

    cout << sol << endl;

    return 0;
}