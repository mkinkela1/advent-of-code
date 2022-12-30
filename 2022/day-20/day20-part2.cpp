#include<iostream>
#include<vector>
#include<utility>
#include<fstream>

using namespace std;

const long long KEY = 811589153LL;

auto calc(int pos, vector<pair<long long, int> > arr) -> long long {
    return arr[pos%arr.size()].first;
}

auto decrypt(vector<pair<long long, int> > &arr) -> void {
    int mod = arr.size() - 1;
    for(int i = 0; i < arr.size(); ++i) {
        int pos = 0;
        while(pos < arr.size() && arr[pos].second != i) ++pos;

        int pos2 = (pos + arr[pos].first) % mod;

        pair<long long, int> tmp = arr[pos];

        if(pos2 < 0)
            pos2 += mod;
        if(pos2 >= mod)
            pos2 -= mod;

        arr.erase(arr.begin() + pos);
        arr.insert(arr.begin() + pos2, tmp);
    }
}

auto main() -> int {
    
    fstream fin;
    fin.open("day20-input.txt", ios::in);

    vector<pair<long long, int> > arr;
    int num, pos = 0;
    while(fin >> num) 
        arr.push_back({num * KEY, pos++});

    for(int i = 0; i < 10; ++i)
        decrypt(arr);

    int posZero = 0;
    for(int i = 0; i < arr.size(); ++i)
        if(arr[i].first == 0) { posZero = i; break; }

    cout << calc(posZero + 1000, arr) + calc(posZero + 2000, arr) + calc(posZero + 3000, arr) << endl; 

    return 0;
}