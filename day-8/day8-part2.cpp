#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int calcFromTop(int posX, int posY, vector<string> &mat) {
    int tmp_max = mat[posX][posY] - '0';
    int N = mat.size();
    int ret = 0;

    --posX;

    while(posX >= 0) {

        int tmp = mat[posX][posY] - '0';

        if(tmp < tmp_max)
            ++ret;
        else 
            return ret + 1;

        --posX;
    }

    return ret;

}

int calcFromBottom(int posX, int posY, vector<string> &mat) {
    int tmp_max = mat[posX][posY] - '0';
    int N = mat.size();
    int ret = 0;

    ++posX;

    while(posX < N) {

        int tmp = mat[posX][posY] - '0';

        if(tmp < tmp_max)
            ++ret;
        else 
            return ret + 1;

        ++posX;
    }

    return ret;
}

int calcFromLeft(int posX, int posY, vector<string> &mat) {
    int tmp_max = mat[posX][posY] - '0';
    int N = mat.size();
    int ret = 0;

    --posY;

    while(posY >= 0) {

        int tmp = mat[posX][posY] - '0';

        if(tmp < tmp_max) {
            ++ret;
        } else 
            return ret + 1;

        --posY;
    }

    return ret;
}

int calcFromRight(int posX, int posY, vector<string> &mat) {
    int tmp_max = mat[posX][posY] - '0';
    int N = mat.size();
    int ret = 0;

    ++posY;

    while(posY < N) {

        int tmp = mat[posX][posY] - '0';

        if(tmp < tmp_max) {
            ++ret;
        } else
            return ret + 1;

        ++posY;
    }

    return ret;
}

int main(void) {

    fstream fin;
    fin.open("day8-input.txt", ios::in);

    cout << fin.is_open() << endl;

    vector<string> mat;
    string line;

    while(fin >> line)         
        mat.push_back(line);

    int N = mat.size();
    int M = mat[0].size();

    int sol = 0;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j) 
            sol = max(
                sol, 
                calcFromTop(i, j, mat) * calcFromBottom(i, j, mat) * calcFromLeft(i, j, mat) * calcFromRight(i, j, mat)
            );

    cout << sol << endl;

    return 0;
}