#include "deck.hpp"
#include "admirer.hpp"
#include "input.hpp"
#include "reference.h"
#include "game_state.hpp"
#include "card_actions.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <limits>

using std::any_of;
using std::cin;
using std::count_if;
using std::cout;
using std::none_of;
using std::numeric_limits;
using std::sort;
using std::streamsize;
using std::to_string;
using std::vector;

int main()
{
    GameState gameState;

    cout << "\n-- WELCOME TO MISSIVE --\n\n";

    // get starting admirer count
    int player_count = -1;
    while (player_count < 2 || player_count > 6)
    {
        cout << "How many admirers will be playing: ";
        cin >> player_count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (player_count < 2 || player_count > 9)
        {
            cout << "Number must be between 2 and 6 admirers:\n";
        }
    }
    cout << '\n';

    gameState.SetPlayers(player_count);

    // game loop
    bool game_over = false;
    while (!game_over)
    {
        // main deck
        vector<Card> deck;
        Build(deck);
        Mix(deck);

        // face up deck
        vector<Card> aside;
        aside.push_back(deck.at(0));
        deck.erase(deck.begin() + 0);

        // discard deck
        vector<Card> discard;
        if (gameState.admirers_.size() == 2)
        {
            for (int i = 0; i < 2; i++)
            {
                discard.push_back(deck.at(0));
                deck.erase(deck.begin() + 0);
            }
        }

        // deal starting hand
        for (Admirer &i : gameState.admirers_)
        {
            i.Draw(deck.at(0));
            deck.erase(deck.begin() + 0);
        }

        // round count prompt
        cout << "-- ROUND " << gameState.round_count_ << " --\n\n";

        // admirer turn

        vector<Admirer *> remaining_players;
        Admirer *winner = nullptr;

        bool end_round = false;
        while (!end_round)
        {
            for (size_t i = 0; i < gameState.admirers_.size(); i++)
            {
                // set winner of previous round as starting admirer
                if (gameState.round_count_ > 1)
                {
                    for (size_t j = 0; j < gameState.admirers_.size(); j++)
                    {
                        if (gameState.admirers_.at(j).Starting())
                        {
                            i = j;
                            gameState.admirers_.at(i).SetStarting(0);
                        }
                    }
                }

                // access to admirer object during play
                Admirer *current_admirer = &gameState.admirers_.at(i);

                if (current_admirer->Status())
                {
                    current_admirer->SetProtection(0);

                    // draw input
                    char draw = ' ';
                    while (draw != 'd')
                    {
                        cout << current_admirer->GetName() << " draw a card (d): ";
                        cin >> draw;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (draw != 'd')
                        {
                            cout << "Input MUST be 'd':\n";
                        }
                    }

                    // current admirer draw card
                    // current_player->Draw(deck.at(0));
                    deck.erase(deck.begin() + 0);

                    current_admirer->Draw(Card("HANDMAID", 4, "REF"));

                    // print game state
                    cout << "\nDeck size: \n";
                    cout << deck.size() << '\n';

                    cout << "\nDiscard pile:\n";
                    if (discard.empty())
                    {
                        cout << "EMPTY" << '\n';
                    }
                    else
                    {
                        if (discard.size() == 1)
                        {
                            cout << discard.at(0).GetName() << '\n';
                        }
                        else
                        {
                            for (size_t i = 0; i < discard.size(); i++)
                            {
                                if (i < discard.size() - 1)
                                {
                                    cout << discard.at(i).GetName() << ", ";
                                }
                                else
                                {
                                    cout << discard.at(i).GetName() << '\n';
                                }
                            }
                        }
                    }

                    cout << "\nOpponents:\n";
                    for (size_t i = 0; i < gameState.admirers_.size(); i++)
                    {
                        if (gameState.admirers_.at(i).Status())
                        {
                            if (gameState.admirers_.size() == 2 && gameState.admirers_.at(i).GetValue() != current_admirer->GetValue())
                            {
                                cout << gameState.admirers_.at(i).GetName() << '\n';
                            }
                            else
                            {
                                if (gameState.admirers_.at(i).GetValue() != current_admirer->GetValue())
                                {
                                    if (i == gameState.admirers_.size() - 1)
                                    {
                                        cout << gameState.admirers_.at(i).GetName() << '\n';
                                    }
                                    else
                                    {
                                        cout << gameState.admirers_.at(i).GetName() << ", ";
                                    }
                                }
                            }
                        }
                    }

                    cout << "\nDamsel protection:\n";
                    bool players_have_damsel = any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.ProtectionStatus(); });
                    if (players_have_damsel)
                    {
                        int damsel_count = count_if(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.ProtectionStatus(); });
                        if (damsel_count == 1)
                        {
                            for (size_t i = 0; i < gameState.admirers_.size(); i++)
                            {
                                Admirer *damselPlayer = &gameState.admirers_.at(i);
                                if (damselPlayer->ProtectionStatus() && (damselPlayer->GetValue() != current_admirer->GetValue()))
                                {
                                    cout << damselPlayer->GetName() << '\n';
                                    break;
                                }
                            }
                        }
                        else
                        {
                            int damsel_tally = 1;
                            for (size_t i = 0; i < gameState.admirers_.size(); i++)
                            {
                                Admirer *iPlayer = &gameState.admirers_.at(i);
                                if (iPlayer->ProtectionStatus() && (iPlayer->GetValue() != current_admirer->GetValue()))
                                {
                                    if (damsel_tally != damsel_count)
                                    {
                                        cout << iPlayer->GetName() << ", ";
                                    }
                                    else
                                    {
                                        cout << iPlayer->GetName() << '\n';
                                    }
                                    damsel_tally++;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "NONE\n";
                    }

                    cout << "\nEmissary Bonus:\n";
                    bool players_have_emissary = any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.HasEmissaryBonus(); });
                    if (players_have_emissary)
                    {
                        int emissary_count = count_if(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.HasEmissaryBonus(); });
                        if (emissary_count == 1)
                        {
                            for (size_t i = 0; i < gameState.admirers_.size(); i++)
                            {
                                Admirer *emissaryPlayer = &gameState.admirers_.at(i);
                                if (gameState.admirers_.at(i).HasEmissaryBonus())
                                {
                                    cout << emissaryPlayer->GetName() << '\n';
                                    break;
                                }
                            }
                        }
                        else
                        {
                            int emissary_tally = 1;
                            for (size_t i = 0; i < gameState.admirers_.size(); i++)
                            {
                                Admirer *iPlayer = &gameState.admirers_.at(i);
                                if (iPlayer->GetValue() != current_admirer->GetValue() && iPlayer->HasEmissaryBonus())
                                {
                                    if (emissary_tally == 1)
                                    {
                                        cout << iPlayer->GetName() << ", ";
                                        emissary_tally++;
                                    }
                                    else
                                    {
                                        cout << iPlayer->GetName() << '\n';
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "NONE\n";
                    }

                    current_admirer->PrintHand();

                    // log cards already in hand
                    vector<int> in_hand;
                    for (Card iCard : *current_admirer->GetHand())
                    {
                        in_hand.push_back(iCard.GetValue());
                    }

                    // duchess restriction check
                    bool duchess = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 8; });
                    bool emperor = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 7; });
                    bool archduke = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 5; });

                    bool correct_input = false;
                    int card = 0;
                    while (!correct_input)
                    {
                        cout << current_admirer->GetName() << " play a card: ";
                        cin >> card;
                        SanitizeCard(card, -1);

                        if ((duchess && emperor) || (duchess && archduke))
                        {
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "You MUST play the Duchess.\n";
                        }
                        else
                        {
                            for (Card &iCard : *current_admirer->GetHand())
                            {
                                if (iCard.GetValue() == card)
                                {
                                    correct_input = true;
                                    break;
                                }
                            }
                            if (!correct_input)
                            {
                                cout << "Not in hand.\n";
                            }
                        }
                    }

                    // discard card
                    current_admirer->Discard(card, discard);

                    // play card action
                    switch (card)
                    {
                    case 0:
                        Emissary(current_admirer);
                        break;
                    case 1:
                        Defender(gameState, current_admirer, discard);
                        break;
                    case 2:
                        Cleric(gameState, current_admirer);
                        break;
                    case 3:
                        Lord(gameState, current_admirer, discard);
                        break;
                    case 4:
                        Damsel(current_admirer);
                        break;
                    case 5:
                        Archduke(gameState, current_admirer, discard);
                        break;
                    case 6:
                        Adjudicator(discard, current_admirer);
                        break;
                    case 7:
                        Emperor(gameState, current_admirer);
                        break;
                    case 8:
                        Duchess(current_admirer);
                        break;
                    case 9:
                        GrandDuchess(current_admirer, discard);
                        break;
                    }
                    cout << '\n';
                }

                // reset remaining admirers, so as not to stack remainders
                remaining_players.erase(remaining_players.begin(), remaining_players.end());

                // check how many standing admirers
                for (Admirer &iPlayer : gameState.admirers_)
                {
                    if (iPlayer.Status())
                    {
                        remaining_players.push_back(&iPlayer);
                    }
                }

                // round end check
                if (deck.empty() || remaining_players.size() == 1)
                {
                    end_round = true;
                    break;
                }
            }
        }

        // increase round count
        gameState.round_count_ += 1;

        // round end

        // deck is empty, admirers compare hands, highest hand wins the round
        if (deck.size() == 0)
        {
            cout << "Deck is empty, admirers compare hands!\n";
            for (size_t i = 0; i < gameState.admirers_.size(); i++)
            {
                Admirer *iPlayer = &gameState.admirers_.at(i);
                if (i < gameState.admirers_.size() - 1)
                {
                    if (iPlayer->GetHand()->at(0).GetValue() > gameState.admirers_.at(i + 1).GetHand()->at(0).GetValue())
                    {
                        winner = &gameState.admirers_.at(i);
                    }
                }
            }
            cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << '\n';
            winner->Addtoken();
            winner->Winner(1);
        }

        // emissary bonus
        int emissary_count = 0;
        if (any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &iPlayer) { return iPlayer.HasEmissaryBonus(); }))
        {
            Admirer *emissary_bonus = nullptr;
            for (Admirer &iPlayer : gameState.admirers_)
            {
                if (iPlayer.Status() && iPlayer.HasEmissaryBonus() && emissary_count < 2)
                {
                    emissary_bonus = &iPlayer;
                    emissary_count++;
                }
            }
            if (emissary_count >= 2)
            {
                cout << "Multiple admirers had the Emissary, no one gets a bonus\n";
            }
            else if (emissary_count == 1)
            {
                cout << emissary_bonus->GetName() << " had the Emissary!\n";
                emissary_bonus->Addtoken();
                cout << emissary_bonus->GetName() << " token count: " << emissary_bonus->GetTokenCount() << '\n';
            }
        }

        // celebrate the last admirer standing
        for (Admirer &iPlayer : gameState.admirers_)
        {
            if (iPlayer.Status())
            {
                winner = &iPlayer;
            }
        }

        cout << winner->GetName() << " was the last admirer standing!\n";
        winner->Addtoken();
        cout << winner->GetName() << " token count: " << winner->GetTokenCount() << "\n\n";
        winner->SetStarting(1);

        // set admirers to base
        if (gameState.round_count_ > 1)
        {
            for (Admirer &i : gameState.admirers_)
            {
                i.Reset();
            }
        }

        // check that admirer has winning token count
        for (Admirer &iPlayer : gameState.admirers_)
        {
            if (iPlayer.GetTokenCount() == gameState.winning_token_count_)
            {
                cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!\n";
                cout << iPlayer.GetName() << " wins the game!\n";
                game_over = true;
                break;
            }
        }
    }

    return 0;
}
