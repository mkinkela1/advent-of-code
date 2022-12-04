#include<iostream>
#include<fstream>

using namespace std;

bool isOverlapping(int A, int B, int C, int D) {

    if(A > B) swap(A, B);
    if(C > D) swap(C, D);

    if(A >= C && B <= D) return true;
    if(C >= A && D <= B) return true;

    return false;
}

int main(void) {

    fstream fin;
    fin.open("day4-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    int sol = 0;
    while(fin >> line) {

        int A, B, C, D;
        sscanf(line.c_str(), "%d-%d,%d-%d", &A, &B, &C, &D);

        sol += isOverlapping(A, B, C, D);
    }

    cout << sol << endl;

    return 0;
}