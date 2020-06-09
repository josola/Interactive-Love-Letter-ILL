/*
 * output.cpp
 * implementation for output.h
 * this program uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include <iostream>
#include <typeinfo>
#include "output.h"

using std::cout;

void ConsoleOut::PrintWelcome()
{
	cout << "-- Welcome to Love Letter --\n";
}
void ConsoleOut::PrintStartingPlayerPrompt()
{
	cout << "How many players will be playing?\n";
}
void ConsoleOut::PrintInvalidInput(const int output)
{
	switch (output)
	{
	case 0:
		cout << "Invalid input. Please enter an integer.\n";
		break;
	case 1:
		cout << "Invalid input. Please enter a number between 1 and 6.\n";
		break;
	case 2:
		cout << "Invalid input. Please enter a number between 1 and the max number of players: \n";
		break;
	case 3:
		cout << "Invalid input. Number already guessed.\n";
		break;
	case 4:
		cout << "Invalid input. Please enter a string of characters.\n";
		break;
	case 5:
		cout << "Invalid input. Please enter 'd'\n";
		break;
	case 6:
		cout << "Invalid input. Please enter a string.\n";
		break;
	case 7:
		cout << "Invalid input. Please input a number between 0 and 9:\n";
		break;
	case 8:
		cout << "Invalid input. Card not found in hand. Please input a card number that is in your hand:\n";
		break;
	default:
		cout << "Invalid input.\n";
		break;
	}
}
void ConsoleOut::PrintExitPrompt()
{
	cout << "Type 'E' to exit:\n";
}
void ConsoleOut::PrintPlayerGuessPrompt(const int output)
{
	cout << "Guess any number between 1 and " << output << ".\n";
}
void ConsoleOut::PrintNameGuess(const string name)
{
	cout << name << " guess: \n";
}
void ConsoleOut::PrintCorrectGuessPrompt(const string name)
{
	cout << name << " got it! " << name << " goes first!\n";
}
void ConsoleOut::PrintRound(const int output)
{
	cout << "-- ROUND " << output << " --\n";
}
void ConsoleOut::PrintPlayerTurn(const int output)
{
	switch (output)
	{
	case 1:
		cout << "-- PLAYER[1] turn --\n";
		break;
	case 2:
		cout << "-- PLAYER[2] turn --\n";
		break;
	case 3:
		cout << "-- PLAYER[3] turn --\n";
		break;
	case 4:
		cout << "-- PLAYER[4] turn --\n";
		break;
	case 5:
		cout << "-- PLAYER[5] turn --\n";
		break;
	case 6:
		cout << "-- PLAYER[6] turn --\n";
		break;
	}
}
void ConsoleOut::PrintString(const string output)
{
	cout << output << '\n';
}
void ConsoleOut::PrintDeck(Deck deck)
{
	cout << "Up pile:\n";
	for (auto iCrdCntlr : deck.GetDeck())
	{
		cout << ' ' << iCrdCntlr.GetName();
	}
	cout << '\n';
}
void ConsoleOut::PrintMultipleWinners(GameController game, const int range)
{
	cout << "There were multiple winners last round.\n";
	for (auto iPlyrCntlr : game.Players())
	{
		cout << ' ' << iPlyrCntlr.Name();
	}
	cout << " please guess a number between 1 and " << range << '\n';
}
void ConsoleOut::PrintClosestGuess(const int target, Player player)
{
	cout << player.Name() << " has the closest guess to target[" << target << "]! They get to go first this round!\n";
}
void ConsoleOut::PrintDeckTotal(DeckController deck)
{
	size_t size = deck.GetDeck().size();
	cout << "Total cards in deck: " << size << '\n';
}
void ConsoleOut::PrintRivalPlayer(GameController game)
{
	if (game.PlayerCount() == 2)
	{
		cout << "Rival player: \n";
		for (auto iPlyrCntlr : game.Players())
		{
			if (!iPlyrCntlr.Current())
			{
				cout << ' ' << iPlyrCntlr.Name();
			}
		}
		cout << '\n';
	}
	else
	{
		cout << "Rival players: \n";
		for (auto iPlyrCntlr : game.Players())
		{
			if (!iPlyrCntlr.Current())
			{
				cout << ' ' << iPlyrCntlr.Name();
			}
		}
		cout << '\n';
	}
}
void ConsoleOut::PrintRivalWithSpy(GameController controller)
{
	int spy_count(0);
	for (auto iPlyrCntlr : controller.Players())
	{
		if (iPlyrCntlr.Spy())
		{
			spy_count++;
		}
	}
	if (spy_count > 0)
	{
		cout << "Rivals with Spy: \n";
		for (auto iPlyrCntlr : controller.Players())
		{
			if (iPlyrCntlr.Spy())
			{
				cout << ' ' << iPlyrCntlr.Name();
			}
		}
		cout << '\n';
	}
}
void ConsoleOut::PrintPlayerHand(const vector<Card> hand)
{
	cout << "Player hand: \n";
	for (auto iCrdCntlr : hand)
	{
		cout << ' ' << iCrdCntlr.GetName();
	}
	cout << '\n';
}
void ConsoleOut::PrintDrawPrompt(const string name)
{
	cout << name << " please draw a card.\n";
}
void ConsoleOut::PrintCardChoicePrompt(Player *playerUtil)
{
	cout << playerUtil->Name() << " please choose a card to play: \n";
}