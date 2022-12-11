#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<utility>

using namespace std;

long long MOD = 1;

class Monkey {
public:
    vector<long long> currentItems, newItems;
    char operation;
    long long newWorry;
    long long testDivisibleBy;
    int ifTrue, ifFalse;
    long long nOperations;

    Monkey(
        string startingItems,
        string operation,
        string test,
        string isTrue,
        string isFalse
    ) {

        // solve for true
        int ifTrue;
        sscanf(isTrue.c_str(), "    If true: throw to monkey %lld", &ifTrue);
        this->ifTrue = ifTrue;

        //solve for false
        sscanf(isFalse.c_str(), "    If false: throw to monkey %lld", &this->ifFalse);

        // solve for test
        sscanf(test.c_str(), "  Test: divisible by %lld", &this->testDivisibleBy);

        MOD *= this->testDivisibleBy;

        //solve for operation
        char s[50];
        sscanf(operation.c_str(), "  Operation: new = old %c %s", &this->operation, &s);

        if(s[0] == 'o')
            this->operation = 'x';
        else 
            this->newWorry = atoll(s);

        //solve for starting items
        startingItems = startingItems.substr(startingItems.find(": ") + 1);
        size_t pos = 0;
        string item;
        while ((pos = startingItems.find(", ")) != std::string::npos) {
            item = startingItems.substr(0, pos);
            this->currentItems.push_back(atoll(item.c_str()));
            startingItems.erase(0, 4);
        }

        this->currentItems.push_back(atoll(startingItems.c_str()));

        this->nOperations = 0;
    }
};

int main(void) {

    fstream fin;
    fin.open("day11-input.txt", ios::in);

    cout << fin.is_open() << endl;

    string monkey, startingItems, operation, test, isTrue, isFalse;
    string line;
    map<int, Monkey*> monkeys;
    while(
        getline(fin, monkey) &&
        getline(fin, startingItems) &&
        getline(fin, operation) &&
        getline(fin, test) &&
        getline(fin, isTrue) &&
        getline(fin, isFalse)
    ) {
        int no;
        sscanf(monkey.c_str(), "Monkey %d:", &no);

        monkeys[no] = new Monkey(startingItems, operation, test, isTrue, isFalse);

        getline(fin, line);
    }


    for(int i = 0; i < 10000; ++i) {
        for(auto& currentMonkey : monkeys) {
            for(auto& item: currentMonkey.second->currentItems) {
                if(currentMonkey.second->operation == '+') 
                    item = (item % MOD + currentMonkey.second->newWorry % MOD) % MOD;
                else if(currentMonkey.second->operation == '*') 
                    item = (item % MOD * currentMonkey.second->newWorry % MOD) % MOD;
                else item = (item % MOD * item % MOD) % MOD;

                if(item % currentMonkey.second->testDivisibleBy == 0)
                    monkeys[currentMonkey.second->ifTrue]->currentItems.push_back(item);
                else 
                    monkeys[currentMonkey.second->ifFalse]->currentItems.push_back(item);

                currentMonkey.second->nOperations++;
            }
            currentMonkey.second->currentItems.clear();
        }
    }

    vector<int> nOperations;
    for(auto& currentMonkey : monkeys)
        nOperations.push_back(currentMonkey.second->nOperations);

    sort(nOperations.begin(), nOperations.end(), greater<int>());

    cout << nOperations[0] << "*" << nOperations[1] << endl;

    return 0;
}