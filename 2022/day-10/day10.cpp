#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<utility>

using namespace std;

int main(void) {

    fstream fin;
    fin.open("day10-input.txt", ios::in);

    cout << fin.is_open() << endl;

    vector<int> signal;
    signal.push_back(1);

    string line;
    while(getline(fin, line)) {
        if(line[0] == 'n') {
            signal.push_back(signal.back());
        } else {

            int add;
            sscanf(line.c_str(), "addx %d", &add);

            int curr = signal.back();
            signal.push_back(curr);
            signal.push_back(curr + add);
        }
    }

    int sol = 0;
    for(int i = 20; i <= 220 && i < signal.size(); i += 40) 
        sol += i * signal[i-1];

    cout << sol << endl;

    return 0;
}