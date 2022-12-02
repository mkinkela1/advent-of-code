#include<iostream>
#include<fstream>

using namespace std;

int scoreBasedOnMyShape(char C) {
    switch (C) {
        case 'X':
            return  1;
        case 'Y':
            return 2;
        case 'Z':
            return 3;
        default:
            return 0;
    }
}

bool isDraw(char A, char B) {
    return A == 'A' && B == 'X' || A == 'B' && B == 'Y' || A == 'C' && B == 'Z';
}

int scoreBasedOnOutcome(char A, char B) {
    if(isDraw(A, B)) return 3;
    
    switch(A) {
        case 'A':
            return B == 'Y' ? 6 : 0;
        case 'B':
            return B == 'Z' ? 6 : 0;
        case 'C':
            return B == 'X' ? 6 : 0;

        default:
            return 0;
    }
}

int main(void) {

    fstream fin;
    fin.open("day2-input.txt", ios::in);

    cout << fin.is_open() << endl;

    char A, B;
    int sol = 0;
    while(fin >> A >> B) 
        sol += scoreBasedOnMyShape(B) + scoreBasedOnOutcome(A, B);

    cout << sol << endl;

    return 0;
}