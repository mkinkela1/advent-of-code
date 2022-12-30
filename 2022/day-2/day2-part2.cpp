#include<iostream>
#include<fstream>

using namespace std;

int calcShape(char A) {
    switch(A) {
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        default:
            return 0;
    }
}

int scoreBasedOnMyShape(char A, char B) {
    switch (B) {
        case 'X':
            if(A == 'A') return calcShape('C');
            if(A == 'B') return calcShape('A');
            return calcShape('B');
        case 'Y':
            return calcShape(A);
        case 'Z':
            if(A == 'A') return calcShape('B');
            if(A == 'B') return calcShape('C');
            return calcShape('A');
        default:
            return 0;
    }
}

int scoreBasedOnOutcome(char C) {
    switch (C) {
        case 'X':
            return  0;
        case 'Y':
            return 3;
        case 'Z':
            return 6;
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
        sol += scoreBasedOnMyShape(A, B) + scoreBasedOnOutcome(B);

    cout << sol << endl;

    return 0;
}