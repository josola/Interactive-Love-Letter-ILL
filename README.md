# Missive 🖥️

Missive is an open source, text-based, single-player, card game based on the popular game Love Letter. You play as an admirer of the Emperor's daughter The Grand Duchess of Mannheim. But you aren't the only one fighting for her father's seal of approval, and her heart. Other admirers are vying for her attention alongside you. This is unacceptable, you must take action. Knock out your opponents by utilizing the specialized skills of your entourage: Defender, Cleric, Lord, Damsel, Archduke, Emperor, Duchess, and The Grand Duchess herself. Knock out the other admirers to be the last one standing and you shall win the heart of the Grand Duchess!

## Project Structure

This project is written entirely in native C++ code. No external libraries, no mixing of languages. The purpose of this is to keep things as simple as possible. Missive uses Object Oriented paradigms to function in a clean and straightforward manner. There are five classes you can work with: Card, Converter, GameState, Player, and Reference. Here is a quick overview of each file in the project and its purpose:

- main.cpp
  - The main point of entry to play the game. Everything coalesces here and executes from here.

- card_actions.cpp
  - Determines the capabilities of each card class. Determines the main interactions each card can have during game-play.

- card.cpp (class)
  - Determines the information a card object can hold. Things like: value, power, description, etc.

- converter.cpp (class)
  - Interprets number integers as Admirer objects. Returns the Admirer associated with the number being taken as an argument.

- deck.cpp
  - Determines the information a deck can hold, return, and process.

- game_state.cpp (class)
  - Holds information that is tracked as the "Game State". The Game State determines who is winning, who is out, how many cards they have in their hands, etc.

- input.cpp
  - Checks raw input from the human player and determines whether it is viable and modifies input to work within overall program structure.

- player.cpp (class)
  - Determines the capabilities, and information, an Admirer can take action on during game-play.

- reference.cpp (class)
  - Holds the reference cards that can be accessed at any time.

## Execution Structure

1. The `GameState` object is loaded onto the stack.
   
   ```cpp
   GameState gameState;
   ```

2. A welcome prompt is displayed.
   
    ```cpp
    cout << "\n-- WELCOME TO LOVE LETTER --\n\n";
    ```

3. The `player_count` is populated in a local variable.
   
    ```cpp
    int player_count = -1;
    while (player_count < 2 || player_count > 6)
    {
        cout << "How many players will be playing: ";
        cin >> player_count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (player_count < 2 || player_count > 9)
        {
            cout << "Number must be between 2 and 6 players:\n";
        }
    }
    cout << '\n';
    ```

4. The number of players for the current session gets set in the `GameState`.

    ```cpp
    gameState.SetPlayers(player_count);
    ```

5. The main game loop begins.

    ```cpp
    bool game_over = false;
    while (!game_over)
    {

    }
    ```
    
6. The `Deck` is loaded onto the stack, built, and shuffled.

    ```cpp
        vector<Card> deck;
        Build(deck);
        Mix(deck);
    ```
7. The `aside` deck object is loaded onto the stack. The cards in the `aside` are taken from the main deck.

    ```cpp
        vector<Card> aside;
        aside.push_back(deck.at(0));
        deck.erase(deck.begin() + 0);
    ```

8. The `discard` pile is loaded onto the stack. If there are more than two players, the discard pile remains empty until it gets used later on. If there are only two players, two cards are pushed from the main deck to the discard pile.

    ```cpp
        vector<Card> discard;
        if (gameState.players_.size() == 2)
        {
            for (int i = 0; i < 2; i++)
            {
                discard.push_back(deck.at(0));
                deck.erase(deck.begin() + 0);
            }
        }
    ```

9.  We deal the starting hand to each of the admirers in the current session.

    ```cpp
    for (Player &i : gameState.players_)
          {
              i.Draw(deck.at(0));
              deck.erase(deck.begin() + 0);
          }
    ```
10. A prompt is given denoting the current round.

    ```cpp
    cout << "-- ROUND " << gameState.round_count_ << " --\n\n";
    ```

11. The player turn begins. An empty vector container, that will hold the remaining players in the match, and an empty `Player` object, that will hold the winning player object, are loaded onto the stack.

    ```cpp
    vector<Player *> remaining_players;
    Player *winner = nullptr;
    ```

12. An `end_round` flag is set to false, the round has just begun. This will be set to true if there is only one admirer left standing or there are no more cards in the main deck. The round logic is contained within a `while` loop. The number of remaining players is checked by obtaining the size of the `remaining_players` vector.

    ```cpp
    bool end_round = false;
    while !(end_round)
    {
      // round logic
      ...

      if (deck.empty() || remaining_players.size() == 1)
      {
          end_round = true;
          break;
      }
    }
    ```

13. Players execute their turns in order from the starting player to the plaer with the lowest position. This is done in a loop that iterates through the vector container with the Player objects.

    ```cpp
    for (size_t i = 0; i < gameState.players_.size(); i++)
    {
        ...
    }
    ```

14. If the current round is the second or later, the winner of the last round becomes the starting player of the current round.

    ```cpp
    if (gameState.round_count_ > 1)
    {
        for (size_t j = 0; j < gameState.players_.size(); j++)
        {
            if (gameState.players_.at(j).Starting())
            {
                i = j;
                gameState.players_.at(i).SetStarting(0);
            }
        }
    }
    ```

15. Create a pointer to where the current player resides in the player container. This makes manipulating the current player's state, as well as game-play interactions, easier to write and simpler to understand.

    ```cpp
    Player *current_player = &gameState.players_.at(i);
    ```

16. The "current player" has their `Status()` checked to make sure they are actually playing. This is necessary to avoid having to physically remove player objects that are not playing in the current session from the player object container. There is no `else` attached to this `if` statement as if the statement is fales, the turn will sompliy move onto the next player.

    ```cpp
    if (current_player->Status())
    {
        ...
    }

17. Remove the current player's protections from their previous turn.

    ```cpp
    current_player->SetProtection(0);
    ```

18. Input is taken as a character `d` from the human player. This increases a feeling of interaction with the innards of the game.

    ```cpp
    char draw = ' ';
    while (draw != 'd')
    {
        cout << current_player->GetName() << " draw a card (d): ";
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
    ```

19. The card object at the front/top of the main deck object is deleted from the container's memory. Then the current player object takes a card object into its state/hand.

    ```cpp
    deck.erase(deck.begin() + 0);

    current_player->Draw(Card("HANDMAID", 4, "REF"));
    ```

20. The following bullets are included in printing the game state. Printing the game state occurs at once.

    - Print the size of the deck. Allows human players to try to count remaining cards and what cards are out in the playing field. This is just the size of the main deck container.

    ```cpp
    cout << "\nDeck size: \n";
    cout << deck.size() << '\n';
    ```

    - Print the discard pile. In a real life game of Missive, players have access to view the cards contained within the discard pile, as they are discarded face-up on the table. Extra code is involved to determine whether the discard pile is empty, has only one card, or has more than one card. This allows selective formatting when printing the discard pile's information to the standard output.

    ```cpp
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
    ```

    - Print the remaining opponents in the current session. This allows human players to keep track of who is playing and who has been knocked out.

    ```cpp
    cout << "\nOpponents:\n";
    for (size_t i = 0; i < gameState.players_.size(); i++)
    {
        if (gameState.players_.at(i).Status())
        {
            if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != current_player->GetValue())
            {
                cout << gameState.players_.at(i).GetName() << '\n';
            }
            else
            {
                if (gameState.players_.at(i).GetValue() != current_player->GetValue())
                {
                    if (i == gameState.players_.size() - 1)
                    {
                        cout << gameState.players_.at(i).GetName() << '\n';
                    }
                    else
                    {
                        cout << gameState.players_.at(i).GetName() << ", ";
                    }
                }
            }
        }
    }
    ```

    - Print admirers who have Handmaid protection. Admirers with Handmaid protection cannot be targeted by aggresive cards.

    ```cpp
    cout << "\nOpponents:\n";
    for (size_t i = 0; i < gameState.players_.size(); i++)
    {
        if (gameState.players_.at(i).Status())
        {
            if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != current_player->GetValue())
            {
                cout << gameState.players_.at(i).GetName() << '\n';
            }
            else
            {
                if (gameState.players_.at(i).GetValue() != current_player->GetValue())
                {
                    if (i == gameState.players_.size() - 1)
                    {
                        cout << gameState.players_.at(i).GetName() << '\n';
                    }
                    else
                    {
                        cout << gameState.players_.at(i).GetName() << ", ";
                    }
                }
            }
        }
    }
    ```

    - Print Admirers with a Spy bonus. Admirers with Spy bonus gain a favor token at the end of the round whether they won the round or not, as long as they are not knocked out by another admirer. This makes them a target to be taken out by others. This is useful information for the current Admirer's tactical decision making.

    ```cpp
    cout << "\nSpy Bonus:\n";
    bool players_have_spy = any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.SpyStatus(); });
    if (players_have_spy)
    {
        int spy_count = count_if(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.SpyStatus(); });
        if (spy_count == 1)
        {
            for (size_t i = 0; i < gameState.players_.size(); i++)
            {
                Player *spyPlayer = &gameState.players_.at(i);
                if (gameState.players_.at(i).SpyStatus())
                {
                    cout << spyPlayer->GetName() << '\n';
                    break;
                }
            }
        }
        else
        {
            int spy_tally = 1;
            for (size_t i = 0; i < gameState.players_.size(); i++)
            {
                Player *iPlayer = &gameState.players_.at(i);
                if (iPlayer->GetValue() != current_player->GetValue() && iPlayer->SpyStatus())
                {
                    if (spy_tally == 1)
                    {
                        cout << iPlayer->GetName() << ", ";
                        spy_tally++;
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
    ```

    - Print the current players hand.

    ```cpp
    current_player->PrintHand();
    ```

21. Get the contents of the current player's hand for ease of use in main logic.

    ```cpp
    vector<int> in_hand;
    for (Card iCard : *current_player->GetHand())
    {
        in_hand.push_back(iCard.GetValue());
    }
    ```

22. Set some flags, that will be checked during the current player's input phase, to restrict the playing of a Countess if the player has either a King or a Prince in their hand.

    ```cpp
    vector<int> in_hand;
    for (Card iCard : *current_player->GetHand())
    {
        in_hand.push_back(iCard.GetValue());
    }
    ```

23. Set a flag that will control whether the human player has given the program a proper input. The input is checked and forced to be corrected within the `while` loop. The human player is asked to input a number `card` that will play a card in their hand. If their input does not match a card in their hand, or they have a Countess and either a King or Prince, they are prompted to input a correct number that matches a card in their hand and matches a card that they are free to use.

    ```cpp
    bool correct_input = false;
    int card = 0;
    while (!correct_input)
    {
        cout << current_player->GetName() << " play a card: ";
        cin >> card;
        SanitizeCard(card, -1);

        if ((countess && king) || (countess && prince))
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "You MUST play the Countess.\n";
        }
        else
        {
            for (Card &iCard : *current_player->GetHand())
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
    ```

24. After the current player has correctly chosen a card in their hand to play, that card is discarded into the discard pile and removed from their hand.

    ```cppp
    current_player->Discard(card, discard);
    ```

25. `card`'s value is fed into a switch that then decides which card action to execute for the player's card choice. These actions contain logic that goes into further game-play between the current player and other players.

    ```cpp
    switch (card)
    {
    case 0:
        Spy(current_player);
        break;
    case 1:
        Guard(gameState, current_player, discard);
        break;
    case 2:
        Priest(gameState, current_player);
        break;
    case 3:
        Baron(gameState, current_player, discard);
        break;
    case 4:
        Handmaid(current_player);
        break;
    case 5:
        Prince(gameState, current_player, discard);
        break;
    case 6:
        Chancellor(discard, current_player);
        break;
    case 7:
        King(gameState, current_player);
        break;
    case 8:
        Countess(current_player);
        break;
    case 9:
        Princess(current_player, discard);
        break;
    }
    cout << '\n';
    ```

26. Reset the remaining player vector container so as not to place duplicate player objects when determining who is left in the round and who needs to be omitted.

    ```cpp
    remaining_players.erase(remaining_players.begin(), remaining_players.end());
    ```

27. Add standing players to `remaining_players` vector container. Essentially resetting the container to omit players who are not playing after this round.

    ```cpp
    for (Player &iPlayer : gameState.players_)
    {
        if (iPlayer.Status())
        {
            remaining_players.push_back(&iPlayer);
        }
    }
    ```

28. If the main `deck` is empty or their is only one player left after the current player's turn ends the round is over.

    ```cpp
    if (deck.empty() || remaining_players.size() == 1)
    {
        end_round = true;
        break;
    }
    ```

29. After the round ends, the round count goes up one.

    ```cpp
    gameState.round_count_ += 1;
    ```

30. If the deck is empty at the end of the round, remaining players must compare the values of their hands. Whoever has the hand with the highest value wins the round and is marked as the winner for the start of the next round.

    ```cpp
    if (deck.size() == 0)
    {
        cout << "Deck is empty, players compare hands!\n";
        for (size_t i = 0; i < gameState.players_.size(); i++)
        {
            Player *iPlayer = &gameState.players_.at(i);
            if (i < gameState.players_.size() - 1)
            {
                if (iPlayer->GetHand()->at(0).GetValue() > gameState.players_.at(i + 1).GetHand()->at(0).GetValue())
                {
                    winner = &gameState.players_.at(i);
                }
            }
        }
        cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << '\n';
        winner->Addtoken();
        winner->Winner(1);
    }
    ```

31. If a remaining player at the end of the round has a spy bonus, they gain an extra favor token on top of whatever winnings they had already received.

    ```cpp
    int spy_count = 0;
    if (any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &iPlayer) { return iPlayer.SpyStatus(); }))
    {
        Player *spy_bonus = nullptr;
        for (Player &iPlayer : gameState.players_)
        {
            if (iPlayer.Status() && iPlayer.SpyStatus() && spy_count < 2)
            {
                spy_bonus = &iPlayer;
                spy_count++;
            }
        }
        if (spy_count >= 2)
        {
            cout << "Multiple players had the Spy, no one gets a bonus\n";
        }
        else if (spy_count == 1)
        {
            cout << spy_bonus->GetName() << " had the Spy!\n";
            spy_bonus->Addtoken();
            cout << spy_bonus->GetName() << " token count: " << spy_bonus->GetTokenCount() << '\n';
        }
    }
    ```

32. If the deck is not empty, set the last player standing as the winner.

    ```cpp
    for (Player &iPlayer : gameState.players_)
    {
        if (iPlayer.Status())
        {
            winner = &iPlayer;
        }
    }
    ```

33. Give a final prompt celebrating the winning player.

    ```cpp
    cout << winner->GetName() << " was the last player standing!\n";
    winner->Addtoken();
    cout << winner->GetName() << " token count: " << winner->GetTokenCount() << "\n\n";
    winner->SetStarting(1);
    ```

34. Reset the status of players who were knocked out from not playing to playing so that they can join the next round.

    ```cpp
    if (gameState.round_count_ > 1)
    {
        for (Player &i : gameState.players_)
        {
            i.Reset();
        }
    }
    ```

35. If the winner of the previous round has the number of favor tokens to trigger the end of the game, they are celebrated as the winner of the entire game session. Then the game is set to `game_over` and ends.

    ```cpp
    for (Player &iPlayer : gameState.players_)
    {
        if (iPlayer.GetTokenCount() == gameState.winning_token_count_)
        {
            cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!\n";
            cout << iPlayer.GetName() << " wins the game!\n";
            game_over = true;
            break;
        }
    }
    ```

36. Program execution ends.

    ```cpp
    return 0;
    ```