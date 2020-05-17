/*
 * Executes the program.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

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
        GameController gameController;
        DeckController deckController;
        DownController downController;
        UpController upController;

        while (initial_setup && !game_over)
        {
            if (gameController.Round() > 1 || game_over)
            {
                initial_setup = false;
                break;
            }
            ConsoleOut::PrintWelcome();
            ConsoleOut::PrintStartingPlayerPrompt();
            gameController.BuildPCount();
            gameController.BuildPContainer();
            gameController.BuildWinningTokenCount();
            ConsoleOut::PrintPlayerGuessPrompt(gameController.PlayerCount());
            gameController.BuildStartingPlayer();
            initial_setup = false;
        }

        while (begin_round && !game_over)
        {
            for (auto iPCntlr : gameController.Players())
            {
                if (iPCntlr.Tokens() > gameController.WinningTokenCount())
                {
                    game_over = true;
                    begin_round = false;
                    break;
                }
            }
            gameController.SetStartingPlayer(gameController.FindWinner());
            gameController.ClearWinner();
            gameController.ClearPlaying();
            ConsoleOut::PrintRound(gameController.Round());
            ConsoleOut::PrintPlayerTurn(gameController.PlayerCurrent().Value());

            deckController.Builder();
            deckController.Shuffle();

            downController.InsertCard(deckController.GetCard(0));

            if (gameController.PlayerCount() == 2)
            {
                upController.Builder(deckController);
            }

            gameController.DealStartingHand(deckController);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {
            gameController.PlayerCurrent().NoHandmaid();
            if (!deckController.GetDeck().empty())
            {
                ConsoleOut::PrintDeckTotal(deckController);
                if (!upController.GetDeck().empty())
                {
                    ConsoleOut::PrintDeck(upController);
                }
                ConsoleOut::PrintRivalPlayer(gameController);
                ConsoleOut::PrintRivalWithSpy(gameController);
                ConsoleOut::PrintPlayerHand(gameController.PlayerCurrent().Hand());
                ConsoleOut::PrintDrawPrompt(gameController.PlayerCurrent().Name());
                if (deckController.GetDeck().empty())
                {
                    gameController.ProcessDraw(downController);
                }
                else
                {
                    gameController.ProcessDraw(deckController);
                }
                ConsoleOut::PrintPlayerHand(gameController.PlayerCurrent().Hand());
            }
            else
            {
                break;
            }
            ConsoleOut::PrintCardChoicePrompt(gameController.PlayerCurrent());
            int card_choice = 0;
            card_choice = gameController.ProcessCardChoice();
            player_turn = false;
        }
    }
    return 0;
}