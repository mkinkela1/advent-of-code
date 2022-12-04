#include<iostream>
#include<fstream>

using namespace std;

bool isOverlapping(int A, int B, int C, int D) {

    if(A > B) swap(A, B);
    if(C > D) swap(C, D);

    if(A <= D && B >= C) return true;
    if(D <= A && C >= B) return true;

    return 0;
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