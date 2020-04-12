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
#include "game_util.h"

using std::string;
using std::vector;

class ConsoleOutUtil
{
public:
    static void PrintWelcome();
    static void PrintStartingPlayerPrompt();
    static void PrintInvalidInput(int output);
    static void PrintExitPrompt();
    static void PrintPlayerGuessPrompt(int output);
    static void PrintNameGuess(string name);
    static void PrintCorrectGuessPrompt(string name);
    static void PrintRound(int output);
    static void PrintPlayerTurn(int output);
    static void PrintString(string output);
    static void PrintUpPile(vector<CardUtl> up_pile);
    static void PrintDownPile(vector<CardUtl> down_pile);
    static void PrintMultipleWinners(vector<PlyrUtl> players, int range);
    static void PrintClosestGuess(int target, PlyrUtl player);
    static void PrintDeckTotal(DeckUtl deckUtil);
    static void PrintRivalPlayers(GameUtil gameUtil);
    static void PrintRivalsWithSpy(GameUtil gameUtil);
    static void PrintPlayerHand(PlyrUtl plyrUtl);

private:
};

#endif