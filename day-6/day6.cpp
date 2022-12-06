#include<iostream>
#include<fstream>

using namespace std;

bool check(int pos, string line) {
    string signal = line.substr(pos, 4);
    sort(signal.begin(), signal.end());
    
    return adjacent_find(signal.begin(), signal.end()) == signal.end();
}

int main(void) {

    fstream fin;
    fin.open("day6-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    while(getline(fin, line)) {
        int pos = 0;
        while(true) {
            if(check(pos, line)) {
                cout << pos + 4 << endl;
                return 0;
            }

            ++pos;
        }
    }

    return 0;
}