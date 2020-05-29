/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
#include "game.h"
#include "console_in.h"
#include "console_out.h"

using std::any_of;
using std::distance;
using std::find;

const int Game::PlayerCount() {
    return player_count_;
}
const int Game::Round() {
    return round_count_;
}
const int Game::OriginalPlayerCount() {
    return original_player_count_;
}
const int Game::WinningTokenCount() {
return winning_token_count_;
}
vector<Player> Game::Players() {
    return players_;
}
Player* Game::CurrentPlayer() {
    Player* player = NULL;
    for (Player &iPUtil : players_)
    {
        if (iPUtil.Current())
        {
            player = &iPUtil;
            break;
        }
    }
    return player;
}
int Game::FindWinner() {
    int index(0);
    for (auto i : players_)
    {
        if (i.Winner())
        {
            index = i.Value() - 1;
        }
    }
    return index;
}
void Game::SetPlayerCount(int input) {
    player_count_ = input;
}
void Game::SetOriginalPlayerCount(int input) {
    original_player_count_ = input;
}
void Game::SetPlayers(vector<Player> input) {
    players_ = input;
}
void Game::SetWinningTokenCount(int input) {
    winning_token_count_ = input;
}
void Game::SetStartingPlayer(int output) {
    output--;
    switch (output) {
    case 0:
        players_.at(0).SetCurrent(1);
        break;
    case 1:
        players_.at(1).SetCurrent(1);
        break;
    case 2:
        players_.at(2).SetCurrent(1);
        break;
    case 3:
        players_.at(3).SetCurrent(1);
        break;
    case 4:
        players_.at(4).SetCurrent(1);
        break;
    case 5:
        players_.at(5).SetCurrent(1);
        break;
    }
}
void GameController::BuildPlayerCount() {
    int count(ConsoleIn::GetIntInput());
    if (!PlayerCountCorrect(count)) {
        FixPlayerCount();
    }
    else {
        SetPlayerCount(count);
        SetOriginalPlayerCount(count);
    }
}
bool GameController::PlayerCountCorrect(int input) {
    if (input >= 2 && input <= 6) {
        return true;
    }
    else {
        ConsoleOut::PrintInvalidInput(1);
        return false;
    }
}
void GameController::FixPlayerCount() {
    ConsoleIn::ClearInput();
    BuildPlayerCount();
}
void GameController::BuildPlayerContainer() {
    vector<Player> plyrs;
    switch (PlayerCount()) {
    case 2: {
        plyrs.push_back(Player ("PLAYER[1]", 1));
        plyrs.push_back(Player ("PLAYER[2]", 2));
        SetPlayers(plyrs);
        break;
    }
    case 3: {
        plyrs.push_back(Player ("PLAYER[1]", 1));
        plyrs.push_back(Player ("PLAYER[2]", 2));
        plyrs.push_back(Player ("PLAYER[3]", 3));
        SetPlayers(plyrs);
        break;
    }
    case 4: {
        plyrs.push_back(Player ("PLAYER[1]", 1));
        plyrs.push_back(Player ("PLAYER[2]", 2));
        plyrs.push_back(Player ("PLAYER[3]", 3));
        plyrs.push_back(Player ("PLAYER[4]", 4));
        SetPlayers(plyrs);
        break;
    }
    case 5: {
        plyrs.push_back(Player ("PLAYER[1]", 1));
        plyrs.push_back(Player ("PLAYER[2]", 2));
        plyrs.push_back(Player ("PLAYER[3]", 3));
        plyrs.push_back(Player ("PLAYER[4]", 4));
        plyrs.push_back(Player ("PLAYER[5]", 5));
        SetPlayers(plyrs);
        break;
    }
    case 6: {
        plyrs.push_back(Player ("PLAYER[1]", 1));
        plyrs.push_back(Player ("PLAYER[2]", 2));
        plyrs.push_back(Player ("PLAYER[3]", 3));
        plyrs.push_back(Player ("PLAYER[4]", 4));
        plyrs.push_back(Player ("PLAYER[5]", 5));
        plyrs.push_back(Player ("PLAYER[6]", 6));
        SetPlayers(plyrs);
        break;
    }
    default: {
        plyrs.push_back(Player("PLAYER[0]", 0));
        SetPlayers(plyrs);
        break;
    }
    }
}
void GameController::BuildWinningTokenCount() {
    switch (PlayerCount()) {
    case 2:
        SetWinningTokenCount(6);
        break;
    case 3:
        SetWinningTokenCount(5);
        break;
    case 4:
        SetWinningTokenCount(4);
        break;
    case 5:
        SetWinningTokenCount(3);
        break;
    case 6:
        SetWinningTokenCount(3);
        break;
    }
}
void GameController::BuildStartingPlayer() {
    int target(GenerateNumberWithinRange(PlayerCount()));
    vector<int> duplicate_guess{};
    int player(0);
    for (Player iPUtil : Players()) {
        ConsoleOut::PrintNameGuess(iPUtil.Name());
        int guess(GetPlayerGuess());
        while (DuplicateGuess(duplicate_guess, guess)) {
            guess = GetPlayerGuess();
        }
        if (guess == target) {
            ConsoleOut::PrintCorrectGuessPrompt(iPUtil.Name());
            duplicate_guess.erase(duplicate_guess.begin(), duplicate_guess.end());
            player = iPUtil.Value();
            break;
        }
        else {
            duplicate_guess.push_back(guess);
        }
    }
    SetStartingPlayer(player);
}
int GameController::GenerateNumberWithinRange(int range) {
    srand(static_cast<unsigned int>(time(NULL)));
    int output(rand() % range + 1);
    return output;
}
int GameController::GetPlayerGuess() {
    int output(ConsoleIn::GetIntInput());
    if (!CorrectGuessInput(output)) {
        FixGuessInput(output);
    }
    return output;
}
bool GameController::CorrectGuessInput(int output) {
    if (output >= 1 && output <= PlayerCount()) {
        return true;
    }
    else {
        ConsoleOut::PrintInvalidInput(2);
        return false;
    }
}
void GameController::FixGuessInput(int input) {
    ConsoleIn::ClearInput();
    input = GetPlayerGuess();
}
bool GameController::DuplicateGuess(vector<int> guess_container, int guess) {
    for (int iInt : guess_container) {
        if (iInt == guess) {
            ConsoleOut::PrintInvalidInput(3);
            return true;
        }
    }
    return false;
}
void GameController::DealStartingHand(DeckController& deck) {
    for (Player& iPUtl : Players()) {
        iPUtl.InsertIntoHand(deck.GetCard(0));
        deck.RemoveCard(0);
    }
}
void GameController::ClearWinner() {
    for (Player iPCNTLR : Players()) {
        iPCNTLR.SetWinner(0);
    }
}
void GameController::ClearPlaying() {
    for (Player iPCNTLR : Players()) {
        iPCNTLR.SetPlaying(0);
    }
}
void GameController::ProcessDraw(Deck& deck) {
    char input = DrawInput();
    if (!CorrectDrawInput(input)) {
        input = FixDrawInput();
    }
    else {
        for (Player& iPUtil : Players()) {
            if (iPUtil.Current()) {
                iPUtil.InsertIntoHand(deck.GetCard(0));
            }
        }
    }
}
char GameController::DrawInput() {
    return ConsoleIn::GatCharInput();
}
bool GameController::CorrectDrawInput(char input) {
    if (input == 'd') {
        return true;
    }
    else {
        ConsoleOut::PrintInvalidInput(5);
        return false;
    }
}
char GameController::FixDrawInput() {
    ConsoleIn::ClearInput();
    char output = ' ';
    bool correct = false;
    while (!correct) {
        output = DrawInput();
        if (!CorrectDrawInput(output)) {
            ConsoleIn::ClearInput();
        }
        else {
            correct = true;
        }
    }
    return output;
}
int GameController::ProcessCardChoice() {
    int choice = ConsoleIn::GetIntInput();
    if (!CorrectChoiceInput(choice)) {
        choice = FixChoiceInput();
    }
    bool in_hand = false;
    while (!in_hand) {
        vector<Card> hand = CurrentPlayer()->Hand();
        if (any_of(hand.begin(), hand.end(), [choice](Card iCUtil){ return iCUtil.GetValue() == choice; })) {
            in_hand = true;
        }
        else {
            if (choice >= 0 && choice <= 9) {
                ConsoleOut::PrintInvalidInput(8);
            }
            else {
                ConsoleOut::PrintInvalidInput(7);
            }
            choice = FixChoiceInput();
        }
    }
    return choice;
}
bool GameController::CorrectChoiceInput(int input) {
    if (input >= 0 && input <= 9) {
        return true;
    }
    else {
        ConsoleOut::PrintInvalidInput(7);
        return false;
    }
}
int GameController::FixChoiceInput() {
    int output = 0;
    bool correct = false;
    while (!correct) {
        output = ConsoleIn::GetIntInput();
        if (output >= 0 && output <= 9) {
            correct = true;
        }
        else {
            ConsoleOut::PrintInvalidInput(7);
        }
    }
    return output;
}