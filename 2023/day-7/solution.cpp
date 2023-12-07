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

    auto isFiveOfAKind(bool useJocker = false) -> bool
    {
        if (useJocker)
        {
            return this->sortedCards.size() == 2 && this->sortedCards['J'] > 1 || this->sortedCards.size() == 1;
        }
        else
            return this->sortedCards.size() == 1;
    }

    auto isFourOfAKind(bool useJocker = false) -> bool
    {
        for (auto card : this->sortedCards)
        {
            if (card.second == 4 || useJocker && card.first != 'J' && card.second + this->sortedCards['J'] == 4)
            {
                return true;
            }
        }

        return false;
    }

    auto isFullHouse(bool useJocker = false) -> bool
    {
        bool hasThree = false;
        int hasTwo = 0;
        for (auto card : this->sortedCards)
        {
            if (card.second == 3)
            {
                hasThree = true;
            }
            if (card.second == 2)
            {
                hasTwo++;
            }
        }

        return hasThree && hasTwo == 1 ||
               useJocker && this->sortedCards['J'] == 1 && hasTwo == 2 ||
               useJocker && this->sortedCards['J'] == 2 && hasTwo == 1 ||
               useJocker && this->sortedCards['J'] == 3 && hasTwo == 0;
    }

    auto isThreeOfAKind(bool useJocker = false) -> bool
    {
        for (auto card : this->sortedCards)
        {
            if (card.second == 3 || useJocker && card.first != 'J' && card.second + this->sortedCards['J'] == 3)
            {
                return true;
            }
        }

        return false;
    }

    auto isTwoPairs(bool useJocker = false) -> bool
    {
        int hasTwo = 0;
        for (auto card : this->sortedCards)
        {
            if (card.second == 2)
            {
                hasTwo++;
            }
        }

        if (useJocker && hasTwo == 1 && this->sortedCards['J'] >= 1)
            return true;

        if (useJocker && hasTwo == 0 && this->sortedCards['J'] == 2)
            return true;

        return hasTwo == 2;
    }

    auto isOnePair(bool useJocker = false) -> bool
    {
        for (auto card : this->sortedCards)
        {
            if (card.second == 2)
                return true;
        }

        if (useJocker && this->sortedCards['J'] == 1)
            return true;

        return false;
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

    auto highCard(Hand h1, Hand h2, bool useJocker = false) -> int
    {
        map<char, int> ranks;
        ranks['A'] = 14;
        ranks['K'] = 13;
        ranks['Q'] = 12;
        ranks['J'] = useJocker ? 1 : 11;
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
            int r1 = ranks[h1.getCards()[i]];
            int r2 = ranks[h2.getCards()[i]];
            if (r1 > r2)
            {
                return true;
            }
            else if (r1 < r2)
            {
                return false;
            }
        }

        return true;
    }

    auto cmp(Hand &lhs, Hand &rhs, bool useJocker = false) -> bool
    {
        if (lhs.isFiveOfAKind(useJocker) && !rhs.isFiveOfAKind(useJocker))
            return true;
        if (!lhs.isFiveOfAKind(useJocker) && rhs.isFiveOfAKind(useJocker))
            return false;
        if (lhs.isFiveOfAKind(useJocker) && rhs.isFiveOfAKind(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        if (lhs.isFourOfAKind(useJocker) && !rhs.isFourOfAKind(useJocker))
            return true;
        if (!lhs.isFourOfAKind(useJocker) && rhs.isFourOfAKind(useJocker))
            return false;
        if (lhs.isFourOfAKind(useJocker) && rhs.isFourOfAKind(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        if (lhs.isFullHouse(useJocker) && !rhs.isFullHouse(useJocker))
            return true;
        if (!lhs.isFullHouse(useJocker) && rhs.isFullHouse(useJocker))
            return false;
        if (lhs.isFullHouse(useJocker) && rhs.isFullHouse(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        if (lhs.isThreeOfAKind(useJocker) && !rhs.isThreeOfAKind(useJocker))
            return true;
        if (!lhs.isThreeOfAKind(useJocker) && rhs.isThreeOfAKind(useJocker))
            return false;
        if (lhs.isThreeOfAKind(useJocker) && rhs.isThreeOfAKind(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        if (lhs.isTwoPairs(useJocker) && !rhs.isTwoPairs(useJocker))
            return true;
        if (!lhs.isTwoPairs(useJocker) && rhs.isTwoPairs(useJocker))
            return false;
        if (lhs.isTwoPairs(useJocker) && rhs.isTwoPairs(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        if (lhs.isOnePair(useJocker) && !rhs.isOnePair(useJocker))
            return true;
        if (!lhs.isOnePair(useJocker) && rhs.isOnePair(useJocker))
            return false;
        if (lhs.isOnePair(useJocker) && rhs.isOnePair(useJocker))
            return this->highCard(lhs, rhs, useJocker);

        return this->highCard(lhs, rhs, useJocker);
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        sort(this->hands.begin(), this->hands.end(), [this](Hand &lhs, Hand &rhs)
             { return !this->cmp(lhs, rhs); });

        int sol = 0;
        for (int i = 0; i < this->hands.size(); ++i)
        {
            sol += (i + 1) * this->hands[i].getBid();
        }

        return sol;
    }
    auto part2() -> int
    {
        sort(this->hands.begin(), this->hands.end(), [this](Hand &lhs, Hand &rhs)
             { return !this->cmp(lhs, rhs, true); });

        int sol = 0;
        for (int i = 0; i < this->hands.size(); ++i)
        {
            sol += (i + 1) * this->hands[i].getBid();
        }

        return sol;
    }
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