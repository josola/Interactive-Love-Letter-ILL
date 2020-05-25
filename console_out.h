/*
 * Helper utility for console out.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_OUT_UTIL_h
#define CONSOLE_OUT_UTIL_h

#include <string>
#include <vector>
#include "card.h"
#include "player.h"
#include "deck.h"
#include "game.h"

using std::string;
using std::vector;

class ConsoleOut
{
public:
    static void PrintWelcome();
    static void PrintStartingPlayerPrompt();
    static void PrintInvalidInput(const int output);
    static void PrintExitPrompt();
    static void PrintPlayerGuessPrompt(const int output);
    static void PrintNameGuess(const string name);
    static void PrintCorrectGuessPrompt(const string name);
    static void PrintRound(const int output);
    static void PrintPlayerTurn(const int output);
    static void PrintString(const string output);
    static void PrintDeck(Deck deck);
    static void PrintMultipleWinners(GameController game, const int range);
    static void PrintClosestGuess(const int target, Player player);
    static void PrintDeckTotal(DeckController deckUtil);
    static void PrintRivalPlayer(GameController controller);
    static void PrintRivalWithSpy(GameController controller);
    static void PrintPlayerHand(const vector<Card> hand);
    static void PrintDrawPrompt(const string name);
    static void PrintCardChoicePrompt(Player* playerUtil);

private:
};

#endif