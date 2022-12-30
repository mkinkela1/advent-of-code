#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(void) {

    fstream fin;
    fin.open("day1-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    int sum = 0;
    int max_sum = 0;
    vector<int> V;
    while(getline(fin, line)){ 
        if(line.size() == 0) {
            V.push_back(sum);
            sum = 0;
        } else {
            sum += atoi(line.c_str());
        }
    }

    sort(V.begin(), V.end(), greater<int>());

    cout << V[0] + V[1] + V[2] << endl;

    return 0;
}