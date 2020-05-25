/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <iostream>
#include "console_out.h"
#include "console_in.h"
#include "game.h"
#include "deck.h"

int main()
{
    bool initial_setup = true;
    bool begin_round = true;
    bool player_turn = true;
    bool game_over = false;

    while (!game_over)
    {
        GameController game;
        DeckController deck;
        DownPile downPile;
        UpPile upPile;

        while (initial_setup && !game_over)
        {
            if (game.Round() > 1 || game_over)
            {
                initial_setup = false;
                break;
            }
            ConsoleOut::PrintWelcome();
            ConsoleOut::PrintStartingPlayerPrompt();
            game.BuildPlayerCount();
            game.BuildPlayerContainer();
            game.BuildWinningTokenCount();
            ConsoleOut::PrintPlayerGuessPrompt(game.PlayerCount());
            game.BuildStartingPlayer();
            initial_setup = false;
        }

        while (begin_round && !game_over)
        {
            for (auto iPCntlr : game.Players())
            {
                if (iPCntlr.Tokens() > game.WinningTokenCount())
                {
                    game_over = true;
                    begin_round = false;
                    break;
                }
            }
            game.SetStartingPlayer(game.FindWinner());
            game.ClearWinner();
            game.ClearPlaying();
            ConsoleOut::PrintRound(game.Round());
            ConsoleOut::PrintPlayerTurn(game.CurrentPlayer()->Value());

            deck.Builder();
            deck.Shuffle();

            downPile.InsertCard(deck.GetCard(0));
            deck.RemoveCard(0);

            if (game.PlayerCount() == 2)
            {
                upPile.Builder(deck);
            }

            game.DealStartingHand(deck);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {
            game.CurrentPlayer()->SetHandmaid(false);
            if (!deck.GetDeck().empty())
            {
                ConsoleOut::PrintDeckTotal(deck);
                if (!upPile.GetDeck().empty())
                {
                    ConsoleOut::PrintDeck(upPile);
                }
                ConsoleOut::PrintRivalPlayer(game);
                ConsoleOut::PrintRivalWithSpy(game);
                ConsoleOut::PrintPlayerHand(game.CurrentPlayer()->Hand());
                ConsoleOut::PrintDrawPrompt(game.CurrentPlayer()->Name());
                if (deck.GetDeck().empty())
                {
                    game.ProcessDraw(downPile);
                }
                else
                {
                    game.ProcessDraw(deck);
                }
                ConsoleOut::PrintPlayerHand(game.CurrentPlayer()->Hand());
            }
            else
            {
                break;
            }
            ConsoleOut::PrintCardChoicePrompt(game.CurrentPlayer());
            int card_choice = 0;
            card_choice = game.ProcessCardChoice();
            player_turn = false;
        }
    }
    return 0;
}