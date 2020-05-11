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
            ConsoleOut::PrintPlayerGuessPrompt(gameController.PCount());
            gameController.BuildStartingPlyr();
            initial_setup = false;
        }

        while (begin_round && !game_over)
        {
            for (auto iPlyrCntlr : gameController.Players())
            {
                if (iPlyrCntlr.Tokens() > gameController.WinningTokenCount())
                {
                    game_over = true;
                    begin_round = false;
                    break;
                }
            }
            gameController.SetStrtngPlyr(gameController.FindWinner());
            gameController.ClearWinner();
            gameController.ClearPlaying();
            ConsoleOut::PrintRound(gameController.Round());
            ConsoleOut::PrintPlayerTurn(gameController.PCurrent().Value());

            //deckController.Builder();
            deckController.Shuffle();

            downController.InsertCard(deckController.Card(0));

            if (gameController.PCount() == 2)
            {
                upController.Builder(deckController);
            }

            gameController.DealStartingHand(deckController);
            begin_round = false;
        }

        while (player_turn && !game_over)
        {
            gameController.PCurrent().NoHandmaid();
            if (!deckController.Deck().empty())
            {
                ConsoleOut::PrintDeckTotal(deckController);
                if (!upController.Deck().empty())
                {
                    ConsoleOut::PrintDeck(upController);
                }
                ConsoleOut::PrintRivalPlayers(gameController);
                ConsoleOut::PrintRivalsWithSpy(gameController);
                ConsoleOut::PrintPlayerHand(gameController.PCurrent().Hand());
                ConsoleOut::PrintDrawPrompt(gameController.PCurrent().Name());
                if (deckController.Deck().empty())
                {
                    gameController.ProcessDraw(downController);
                }
                else
                {
                    gameController.ProcessDraw(deckController);
                }
                ConsoleOut::PrintPlayerHand(gameController.PCurrent().Hand());
            }
            else
            {
                break;
            }
            ConsoleOut::PrintCardChoicePrompt(gameController.PCurrent());
            int card_choice = gameController.ProcessCardChoice();
            player_turn = false;
        }
    }
    return 0;
}