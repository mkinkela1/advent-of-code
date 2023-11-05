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

class Ingredient
{
private:
    string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;

public:
    Ingredient(string name, int capacity, int durability, int flavor, int texture, int calories)
    {
        this->name = name;
        this->capacity = capacity;
        this->durability = durability;
        this->flavor = flavor;
        this->texture = texture;
        this->calories = calories;
    }

    auto getName() -> string { return this->name; }
    auto getCapacity() -> int { return this->capacity; }
    auto getDurability() -> int { return this->durability; }
    auto getFlavor() -> int { return this->flavor; }
    auto getTexture() -> int { return this->texture; }
    auto getCalories() -> int { return this->calories; }
};

class Solution
{
private:
    fstream fin;
    vector<Ingredient> ingredients;

    void parse()
    {
        string line;
        char name[20];
        int capacity, durability, flavor, texture, calories;

        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%s capacity %d, durability %d, flavor %d, texture %d, calories %d",
                   name, &capacity, &durability, &flavor, &texture, &calories);

            ingredients.push_back(Ingredient(name, capacity, durability, flavor, texture, calories));
        }
    }

    auto calculate(int firstIngredient, int secondIngredient, int thirdIngredient, int fourthIngredient) -> long long
    {
        long long capacity = max(0,
                                 firstIngredient * ingredients[0].getCapacity() +
                                     secondIngredient * ingredients[1].getCapacity() +
                                     thirdIngredient * ingredients[2].getCapacity() +
                                     fourthIngredient * ingredients[3].getCapacity());
        long long durability = max(0,
                                   firstIngredient * ingredients[0].getDurability() +
                                       secondIngredient * ingredients[1].getDurability() +
                                       thirdIngredient * ingredients[2].getDurability() +
                                       fourthIngredient * ingredients[3].getDurability());
        long long flavor = max(0,
                               firstIngredient * ingredients[0].getFlavor() +
                                   secondIngredient * ingredients[1].getFlavor() +
                                   thirdIngredient * ingredients[2].getFlavor() +
                                   fourthIngredient * ingredients[3].getFlavor());
        long long texture = max(0,
                                firstIngredient * ingredients[0].getTexture() +
                                    secondIngredient * ingredients[1].getTexture() +
                                    thirdIngredient * ingredients[2].getTexture() +
                                    fourthIngredient * ingredients[3].getTexture());

        long long score = capacity * durability * flavor * texture;

        return score;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long
    {
        long long sol = 0L;

        for (int firstIngredient = 0; firstIngredient <= 100; ++firstIngredient)
        {
            for (int secondIngredient = 0; secondIngredient <= 100 - firstIngredient; ++secondIngredient)
            {
                for (int thirdIngredient = 0; thirdIngredient <= 100 - firstIngredient - secondIngredient; ++thirdIngredient)
                {
                    int fourthIngredient = 100 - firstIngredient - secondIngredient - thirdIngredient;

                    sol = max(sol, this->calculate(firstIngredient, secondIngredient, thirdIngredient, fourthIngredient));
                }
            }
        }
        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0L;

        for (int firstIngredient = 0; firstIngredient <= 100; ++firstIngredient)
        {
            for (int secondIngredient = 0; secondIngredient <= 100 - firstIngredient; ++secondIngredient)
            {
                for (int thirdIngredient = 0; thirdIngredient <= 100 - firstIngredient - secondIngredient; ++thirdIngredient)
                {
                    int fourthIngredient = 100 - firstIngredient - secondIngredient - thirdIngredient;

                    long long calories = max(0,
                                             firstIngredient * ingredients[0].getCalories() +
                                                 secondIngredient * ingredients[1].getCalories() +
                                                 thirdIngredient * ingredients[2].getCalories() +
                                                 fourthIngredient * ingredients[3].getCalories());

                    if (calories != 500)
                        continue;

                    sol = max(sol, this->calculate(firstIngredient, secondIngredient, thirdIngredient, fourthIngredient));
                }
            }
        }
        return sol;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}