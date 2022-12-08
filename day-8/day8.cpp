#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void calcFromTop(int pos, vector<string> &mat, vector<vector<int> > &visible) {
    int tmp_max = INT_MIN;
    int N = mat.size();

    for(int i = 0; i < N; ++i) {
        int tmp = mat[i][pos] - '0';

        if(tmp > tmp_max) {
            tmp_max = tmp;
            visible[i][pos]++;
        }
    }
}

void calcFromBottom(int pos, vector<string> &mat, vector<vector<int> > &visible) {
    int tmp_max = INT_MIN;
    int N = mat.size();

    for(int i = N-1; i >= 0; --i) {
        int tmp = mat[i][pos] - '0';

        if(tmp > tmp_max) {
            tmp_max = tmp;
            visible[i][pos]++;
        }
    }
}

void calcFromLeft(int pos, vector<string> &mat, vector<vector<int> > &visible) {
    int tmp_max = INT_MIN;
    int N = mat.size();

    for(int i = 0; i < N; ++i) {
        int tmp = mat[pos][i] - '0';

        if(tmp > tmp_max) {
            tmp_max = tmp;
            visible[pos][i]++;
        }
    }
}

void calcFromRight(int pos, vector<string> &mat, vector<vector<int> > &visible) {
    int tmp_max = INT_MIN;
    int N = mat.size();

    for(int i = N-1; i >= 0; --i) {
        int tmp = mat[pos][i] - '0';

        if(tmp > tmp_max) {
            tmp_max = tmp;
            visible[pos][i]++;
        }
    }
}

int main(void) {

    fstream fin;
    fin.open("day8-input.txt", ios::in);

    cout << fin.is_open() << endl;

    vector<string> mat;
    vector<vector<int > > visible;
    string line;

    while(fin >> line) {

        int N = line.length();
        mat.push_back(line);

        vector<int> V(N, 0);

        visible.push_back(V);
    }

    int N = mat.size();
    int M = mat[0].size();

    cout << N << " " << M << endl;

    // N == M
    for(int i = 0; i < N; ++i) {
        calcFromTop(i, mat, visible);
        calcFromBottom(i, mat, visible);
        calcFromLeft(i, mat, visible);
        calcFromRight(i, mat, visible);
    }
    
    int sol = 0;
    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < M; ++j)
            if(visible[i][j]) 
                ++sol;

    cout << sol << endl;

    return 0;
}