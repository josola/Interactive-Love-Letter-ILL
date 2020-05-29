/*
 * Helper utility for game state.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GAME_h
#define GAME_h

#include <string>
#include "player.h"
#include "deck.h"

using std::string;

class Game
{
public:
    //getters
    const int PlayerCount();
    const int Round();
    const int OriginalPlayerCount();
    const int WinningTokenCount();
    vector<Player> Players();
    Player* CurrentPlayer();
    int FindWinner();

    //setters
    void SetPlayerCount(const int value);
    void SetOriginalPlayerCount(const int value);
    void SetPlayers(const vector<Player> input);
    void SetWinningTokenCount(const int value);
    void SetStartingPlayer(const int value);

private:
    int player_count_ = 0;
    int original_player_count_ = 0;
    int round_count_ = 1;
    vector<Player> players_;
    int winning_token_count_ = 0;
};

class GameController : public Game
{
public:
    void BuildPlayerCount();
    void BuildPlayerContainer();
    bool PlayerCountCorrect(int input);
    void FixPlayerCount();
    void BuildWinningTokenCount();
    void BuildStartingPlayer();
    int GenerateNumberWithinRange(int range);
    int GetPlayerGuess();
    bool CorrectGuessInput(int output);
    void FixGuessInput(int input);
    bool DuplicateGuess(vector<int> guess_container, int guess);
    void DealStartingHand(DeckController &deck);
    void ClearWinner();
    void ClearPlaying();
    void ProcessDraw(Deck &deck);
    char DrawInput();
    bool CorrectDrawInput(char input);
    char FixDrawInput();
    int ProcessCardChoice();
    bool CorrectChoiceInput(int input);
    int FixChoiceInput();
};

#endif