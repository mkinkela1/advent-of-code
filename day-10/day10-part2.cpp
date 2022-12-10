#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<utility>

using namespace std;

void draw(int signal, string &row, int &cycle) {

    if(cycle > 39) {
        cout << row << endl;
        cycle = 0;
        row = "";
    }

    if(row.length() >= signal-1 && row.length() <= signal+1)
        row += '#';
    else row += '.';
}

int main(void) {

    fstream fin;
    fin.open("day10-input.txt", ios::in);

    cout << fin.is_open() << endl;

    vector<int> signal;
    signal.push_back(1);

    string line;
    int cycle = 0;
    string row = "";
    while(getline(fin, line)) {
        if(line[0] == 'n') {
            draw(signal.back(), row, cycle);
            signal.push_back(signal.back());
            ++cycle;
        } else {

            int add;
            sscanf(line.c_str(), "addx %d", &add);

            int curr = signal.back();

            draw(signal.back(), row, cycle);
            signal.push_back(curr);
            ++cycle;

            draw(signal.back(), row, cycle);
            signal.push_back(curr + add);
            ++cycle;
        }
    }

    cout << row << endl;

    return 0;
}