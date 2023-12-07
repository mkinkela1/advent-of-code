#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <unordered_map>

using namespace std;

class Hand
{
private:
    string cards;
    map<char, int> sortedCards;
    int bid;

public:
    Hand(string cards, int bid)
    {
        this->cards = cards;
        this->bid = bid;

        for (auto card : cards)
        {
            this->sortedCards[card]++;
        }
    }

    auto getBid() -> int
    {
        return this->bid;
    }

    auto getCards() -> string
    {
        return this->cards;
    }

    auto isFiveOfAKind() -> bool
    {
        return this->sortedCards.size() == 1;
    }

    auto isFourOfAKind() -> bool
    {
        if (this->sortedCards.size() != 2)
            return false;

        bool hasFour = false;
        bool hasOne = false;
        for (auto card : this->sortedCards)
        {
            if (card.second == 4)
            {
                hasFour = true;
            }
            else if (card.second == 1)
            {
                hasOne = true;
            }
        }

        return hasFour && hasOne;
    }

    auto isFullHouse() -> bool
    {
        if (this->sortedCards.size() != 2)
            return false;

        bool hasThree = false;
        bool hasTwo = false;
        for (auto card : this->sortedCards)
        {
            if (card.second == 3)
            {
                hasThree = true;
            }
            else if (card.second == 2)
            {
                hasTwo = true;
            }
        }

        return hasThree && hasTwo;
    }

    auto isThreeOfAKind() -> bool
    {
        if (this->sortedCards.size() != 3)
            return false;

        bool hasThree = false;
        bool hasOne = false;
        for (auto card : this->sortedCards)
        {
            if (card.second == 3)
            {
                hasThree = true;
            }
            else if (card.second == 1)
            {
                hasOne = true;
            }
        }

        return hasThree && hasOne;
    }

    auto isTwoPairs() -> bool
    {
        if (this->sortedCards.size() != 3)
            return false;

        int hasTwo = 0;
        bool hasOne = false;
        for (auto card : this->sortedCards)
        {
            if (card.second == 2)
            {
                hasTwo++;
            }
            else if (card.second == 1)
            {
                hasOne = true;
            }
        }

        return hasTwo == 2 && hasOne;
    }

    auto isOnePair() -> bool
    {
        bool hasOne = false;
        for (auto card : this->sortedCards)
        {
            if (card.second == 1)
            {
                hasOne = true;
            }
        }

        return hasOne;
    }
};

class Solution
{
private:
    fstream fin;
    vector<Hand> hands;

    void parse()
    {
        string line;
        char cards[20];
        int bid;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%s %d", cards, &bid);
            this->hands.push_back(Hand(cards, bid));
        }
    }

    auto highCard(Hand h1, Hand h2) -> int
    {
        map<char, int> ranks;
        ranks['A'] = 14;
        ranks['K'] = 13;
        ranks['Q'] = 12;
        ranks['J'] = 11;
        ranks['T'] = 10;
        ranks['9'] = 9;
        ranks['8'] = 8;
        ranks['7'] = 7;
        ranks['6'] = 6;
        ranks['5'] = 5;
        ranks['4'] = 4;
        ranks['3'] = 3;
        ranks['2'] = 2;

        for (int i = 0; i < 5; i++)
        {
            if (ranks[h1.getCards()[i]] < ranks[h2.getCards()[i]])
            {
                return -1;
            }
            else if (ranks[h1.getCards()[i]] > ranks[h2.getCards()[i]])
            {
                return 1;
            }
        }
    }

    friend bool operator<(Hand &lhs, Hand &rhs)
    {
        if (lhs.isFiveOfAKind() && !rhs.isFiveOfAKind())
            return true;
        if (lhs.isFiveOfAKind() && rhs.isFiveOfAKind())
            return lhs.highCard() < rhs.highCard();

        if (lhs.isFourOfAKind() && !rhs.isFourOfAKind())
            return true;
        if (lhs.isFourOfAKind() && rhs.isFourOfAKind())
            return lhs.highCard() < rhs.highCard();

        if (lhs.isFullHouse() && !rhs.isFullHouse())
            return true;
        if (lhs.isFullHouse() && rhs.isFullHouse())
            return lhs.highCard() < rhs.highCard();

        if (lhs.isThreeOfAKind() && !rhs.isThreeOfAKind())
            return true;
        if (lhs.isThreeOfAKind() && rhs.isThreeOfAKind())
            return lhs.highCard() < rhs.highCard();

        if (lhs.isTwoPairs() && !rhs.isTwoPairs())
            return true;
        if (lhs.isTwoPairs() && rhs.isTwoPairs())
            return lhs.highCard() < rhs.highCard();

        if (lhs.isOnePair() && !rhs.isOnePair())
            return true;
        if (lhs.isOnePair() && rhs.isOnePair())
            return lhs.highCard() < rhs.highCard();

        return lhs.highCard() < rhs.highCard();
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> string { return "Not solved"; }
    auto part2() -> string { return "Not solved"; }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1() << endl;
    cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}