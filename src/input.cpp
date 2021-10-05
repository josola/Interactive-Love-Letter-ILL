#include "input.h"
#include "game_state.hpp"
#include "admirer.hpp"

#include <cassert>
#include <iostream>

using std::cin;
using std::cout;

const bool CheckCard(const int card)
{
    if (card < 0 || card > 9 || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FixCard(int &card)
{
    while (card < 0 || card > 9 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Card must be between 0 and 9.\n";
        cin >> card;
    }
}

void SanitizeCard(int &target, const int originator)
{
    switch (originator)
    {
        case 1:
        {
            while (!CheckCard(target) || target == 1)
            {
                cout << "You cannot choose a Guard.\n";
                FixCard(target);
            }
        }
        default:
        {
            while (!CheckCard(target))
            {
                FixCard(target);
            }
        }
    }
}

const bool CheckTarget(const int input, const GameState &state)
{
    if (input < 1 || input > state.admirers_.size() || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void FixTarget(int &input, const GameState &state)
{
    while (input < 1 || input > state.admirers_.size())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << "Number must be between 1 and " << state.admirers_.size() << '\n';
        cin >> input;
    }
}

void SanitizeTarget(int &target, const GameState &state, const int card, Admirer *aggressor)
{
    assert(card >= 0 && card <= 9);
    
    bool good_target = false;
    while (!good_target)
    {
        if (!CheckTarget(target, state))
        {
            FixTarget(target, state);
        }
        else
        {
            good_target = true;
        }
    }
}

const bool OpponentsProtected(Admirer *aggressor, GameState &state)
{
    int protected_count = 0;
    for (Admirer &iPlayer : state.admirers_)
    {
        if (iPlayer.ProtectionStatus() && (iPlayer.GetValue() != aggressor->GetValue()))
        {
            protected_count++;
        }
    }
    if (protected_count == state.admirers_.size() - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Admirer *GetTarget(Admirer *aggressor, GameState &state, const int card)
{
    assert(card >= 0 && card <= 9);

    Admirer *target_player = nullptr;
    
    bool protected_target = true;
    while (protected_target)
    {
        cout << aggressor->GetName() << " choose a target admirer: ";
        
        int target = 0;
        cin >> target;
        SanitizeTarget(target, state, card, aggressor);
        
        target_player = aggressor->GetConversion()->NumPlayer(target, state);
        
        if (target_player->ProtectionStatus() && (target_player->GetValue() != aggressor->GetValue()))
        {
            cout << target_player->GetName() << " has Handmaid protection.\n";
        }
        else if (!target_player->Status())
        {
            cout << target_player->GetName() << " is out.\n";
        }
        else if (card != 5 && (target_player->GetValue() == aggressor->GetValue()))
        {
            cout << "You cannot choose yourself.\n";
        }
        else
        {
            protected_target = false;
        }
    }
    return target_player;
}

const bool CheckCharacter(const char input, const char target)
{
    if (input == target)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FixCharacter(char &input, const char target)
{
    while (input != target)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Input must be '" << target << "'\n";
        cin >> input;
    }
}

void SanitizeCharacter(char &input, const char target)
{
    while (!CheckCharacter(input, target))
    {
        FixCharacter(input, target);
    }
}
