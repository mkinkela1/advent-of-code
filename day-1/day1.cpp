#include<iostream>
#include<fstream>

using namespace std;

int main(void) {

    fstream fin;
    fin.open("day1-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    int sum = 0;
    int max_sum = 0;
    while(getline(fin, line)){ 
        if(line.size() == 0) {
            max_sum = max(max_sum, sum);
            sum = 0;
        } else {
            sum += atoi(line.c_str());
        }
    }

    cout << max_sum << endl;

    return 0;
}