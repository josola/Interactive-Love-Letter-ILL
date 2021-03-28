#include "deck.h"
#include "card.h"
#include <cassert>
#include <chrono>
#include <algorithm>
#include <random>

using std::shuffle;

void Build(vector<Card> &input)
{
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("EMISSARY", 0, "REF"));
    }
    for (int i = 0; i < 6; i++)
    {
        input.push_back(Card("DEFENDER", 1, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("CLERIC", 2, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("LORD", 3, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("DAMSEL", 4, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("ARCHDUKE", 5, "REF"));
    }
    for (int i = 0; i < 2; i++)
    {
        input.push_back(Card("ADJUDICATOR", 6, "REF"));
    }
    input.push_back(Card("EMPEROR", 7, "REF"));
    input.push_back(Card("DUCHESS", 8, "REF"));
    input.push_back(Card("GRAND DUCHESS", 9, "REF"));
}

void Mix(vector<Card> &input)
{
    assert(!input.empty());
    shuffle(input.begin(), input.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}
