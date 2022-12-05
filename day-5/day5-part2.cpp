#include<iostream>
#include<fstream>

using namespace std;

int main(void) {

    fstream fin;
    fin.open("day5-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string line;
    string stack[10];
    while(getline(fin, line)){ 
        if(isdigit(line[1])) break;

        for(int pos = 1, i = 0; pos < line.length(); ++i, pos += 4) 
            if(isalpha(line[pos]))
                stack[i] += line[pos];
    }

    for(auto& s: stack)
        reverse(s.begin(), s.end());

    while(getline(fin, line)) {

        if(line.length() == 0) continue;

        int howMany, from, to;
        sscanf(line.c_str(), "move %d from %d to %d", &howMany, &from, &to);

        --from;
        --to;

        stack[to] += stack[from].substr(stack[from].length() - howMany);
        stack[from].erase(stack[from].length() - howMany);
    }

    string sol = "";
    for(auto& s: stack)
        if(s.length() > 0)
            sol += s.back();

    cout << sol << endl;

    return 0;
}