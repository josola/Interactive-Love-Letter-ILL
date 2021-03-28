# Missive 🖥️

Missive is an open source, text-based, single-admirer, card game based on the popular game Love Letter. You play as an admirer of the Emperor's daughter The Grand Duchess of Mannheim. But you aren't the only one fighting for her father's seal of approval, and her heart. Other admirers are vying for her attention alongside you. This is unacceptable, you must take action. Knock out your opponents by utilizing the specialized skills of your entourage: Defender, Cleric, Lord, Damsel, Archduke, Emperor, Duchess, Emissary, and The Grand Duchess herself. Knock out the other admirers to be the last one standing and you shall win the heart of the Grand Duchess!

## Project Structure

This project is written entirely in native C++ code. No external libraries, no mixing of languages. The purpose of this is to keep things as simple as possible. Missive uses Object Oriented paradigms to function in a clean and straightforward manner. There are five classes you can work with: Card, Converter, GameState, Admirer, and Reference. Here is a quick overview of each file in the project and its purpose:

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
  - Checks raw input from the human admirer and determines whether it is viable and modifies input to work within overall program structure.

- admirer.cpp (class)
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

3. The `admirer_count` is populated in a local variable.
   
    ```cpp
    int admirer_count = -1;
    while (admirer_count < 2 || admirer_count > 6)
    {
        cout << "How many admirers will be playing: ";
        cin >> admirer_count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (admirer_count < 2 || admirer_count > 9)
        {
            cout << "Number must be between 2 and 6 admirers:\n";
        }
    }
    cout << '\n';
    ```

4. The number of admirers for the current session gets set in the `GameState`.

    ```cpp
    gameState.SetAdmirers(admirer_count);
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

8. The `discard` pile is loaded onto the stack. If there are more than two admirers, the discard pile remains empty until it gets used later on. If there are only two admirers, two cards are pushed from the main deck to the discard pile.

    ```cpp
        vector<Card> discard;
        if (gameState.admirers_.size() == 2)
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
    for (Admirer &i : gameState.admirers_)
          {
              i.Draw(deck.at(0));
              deck.erase(deck.begin() + 0);
          }
    ```
10. A prompt is given denoting the current round.

    ```cpp
    cout << "-- ROUND " << gameState.round_count_ << " --\n\n";
    ```

11. The admirer turn begins. An empty vector container, that will hold the remaining admirers in the match, and an empty `Admirer` object, that will hold the winning admirer object, are loaded onto the stack.

    ```cpp
    vector<Admirer *> remaining_admirers;
    Admirer *winner = nullptr;
    ```

12. An `end_round` flag is set to false, the round has just begun. This will be set to true if there is only one admirer left standing or there are no more cards in the main deck. The round logic is contained within a `while` loop. The number of remaining admirers is checked by obtaining the size of the `remaining_admirers` vector.

    ```cpp
    bool end_round = false;
    while !(end_round)
    {
      // round logic
      ...

      if (deck.empty() || remaining_admirers.size() == 1)
      {
          end_round = true;
          break;
      }
    }
    ```

13. Admirers execute their turns in order from the starting admirer to the plaer with the lowest position. This is done in a loop that iterates through the vector container with the Admirer objects.

    ```cpp
    for (size_t i = 0; i < gameState.admirers_.size(); i++)
    {
        ...
    }
    ```

14. If the current round is the second or later, the winner of the last round becomes the starting admirer of the current round.

    ```cpp
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
    ```

15. Create a pointer to where the current admirer resides in the admirer container. This makes manipulating the current admirer's state, as well as game-play interactions, easier to write and simpler to understand.

    ```cpp
    Admirer *current_admirer = &gameState.admirers_.at(i);
    ```

16. The "current admirer" has their `Status()` checked to make sure they are actually playing. This is necessary to avoid having to physically remove admirer objects that are not playing in the current session from the admirer object container. There is no `else` attached to this `if` statement as if the statement is fales, the turn will sompliy move onto the next admirer.

    ```cpp
    if (current_admirer->Status())
    {
        ...
    }

17. Remove the current admirer's protections from their previous turn.

    ```cpp
    current_admirer->SetProtection(0);
    ```

18. Input is taken as a character `d` from the human admirer. This increases a feeling of interaction with the innards of the game.

    ```cpp
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
    ```

19. The card object at the front/top of the main deck object is deleted from the container's memory. Then the current admirer object takes a card object into its state/hand.

    ```cpp
    deck.erase(deck.begin() + 0);

    current_admirer->Draw(Card("HANDMAID", 4, "REF"));
    ```

20. The following bullets are included in printing the game state. Printing the game state occurs at once.

    - Print the size of the deck. Allows human admirers to try to count remaining cards and what cards are out in the playing field. This is just the size of the main deck container.

    ```cpp
    cout << "\nDeck size: \n";
    cout << deck.size() << '\n';
    ```

    - Print the discard pile. In a real life game of Missive, admirers have access to view the cards contained within the discard pile, as they are discarded face-up on the table. Extra code is involved to determine whether the discard pile is empty, has only one card, or has more than one card. This allows selective formatting when printing the discard pile's information to the standard output.

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

    - Print the remaining opponents in the current session. This allows human admirers to keep track of who is playing and who has been knocked out.

    ```cpp
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
    ```

    - Print admirers who have Damsel protection. Admirers with Damsel protection cannot be targeted by aggresive cards.

    ```cpp
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
    ```

    - Print Admirers with a Emissary bonus. Admirers with Emissary bonus gain a favor token at the end of the round whether they won the round or not, as long as they are not knocked out by another admirer. This makes them a target to be taken out by others. This is useful information for the current Admirer's tactical decision maemperor.

    ```cpp
    cout << "\nEmissary Bonus:\n";
    bool admirers_have_emissary = any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.EmissaryStatus(); });
    if (admirers_have_emissary)
    {
        int emissary_count = count_if(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.EmissaryStatus(); });
        if (emissary_count == 1)
        {
            for (size_t i = 0; i < gameState.admirers_.size(); i++)
            {
                Admirer *emissaryAdmirer = &gameState.admirers_.at(i);
                if (gameState.admirers_.at(i).EmissaryStatus())
                {
                    cout << emissaryAdmirer->GetName() << '\n';
                    break;
                }
            }
        }
        else
        {
            int emissary_tally = 1;
            for (size_t i = 0; i < gameState.admirers_.size(); i++)
            {
                Admirer *iAdmirer = &gameState.admirers_.at(i);
                if (iAdmirer->GetValue() != current_admirer->GetValue() && iAdmirer->EmissaryStatus())
                {
                    if (emissary_tally == 1)
                    {
                        cout << iAdmirer->GetName() << ", ";
                        emissary_tally++;
                    }
                    else
                    {
                        cout << iAdmirer->GetName() << '\n';
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

    - Print the current admirers hand.

    ```cpp
    current_admirer->PrintHand();
    ```

21. Get the contents of the current admirer's hand for ease of use in main logic.

    ```cpp
    vector<int> in_hand;
    for (Card iCard : *current_admirer->GetHand())
    {
        in_hand.push_back(iCard.GetValue());
    }
    ```

22. Set some flags, that will be checked during the current admirer's input phase, to restrict the playing of a Duchess if the admirer has either a Emperor or a Archduke in their hand.

    ```cpp
    vector<int> in_hand;
    for (Card iCard : *current_admirer->GetHand())
    {
        in_hand.push_back(iCard.GetValue());
    }
    ```

23. Set a flag that will control whether the human admirer has given the program a proper input. The input is checked and forced to be corrected within the `while` loop. The human admirer is asked to input a number `card` that will play a card in their hand. If their input does not match a card in their hand, or they have a Duchess and either a Emperor or Archduke, they are prompted to input a correct number that matches a card in their hand and matches a card that they are free to use.

    ```cpp
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
    ```

24. After the current admirer has correctly chosen a card in their hand to play, that card is discarded into the discard pile and removed from their hand.

    ```cppp
    current_admirer->Discard(card, discard);
    ```

25. `card`'s value is fed into a switch that then decides which card action to execute for the admirer's card choice. These actions contain logic that goes into further game-play between the current admirer and other admirers.

    ```cpp
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
        Chancellor(discard, current_admirer);
        break;
    case 7:
        Emperor(gameState, current_admirer);
        break;
    case 8:
        Duchess(current_admirer);
        break;
    case 9:
        Archdukess(current_admirer, discard);
        break;
    }
    cout << '\n';
    ```

26. Reset the remaining admirer vector container so as not to place duplicate admirer objects when determining who is left in the round and who needs to be omitted.

    ```cpp
    remaining_admirers.erase(remaining_admirers.begin(), remaining_admirers.end());
    ```

27. Add standing admirers to `remaining_admirers` vector container. Essentially resetting the container to omit admirers who are not playing after this round.

    ```cpp
    for (Admirer &iAdmirer : gameState.admirers_)
    {
        if (iAdmirer.Status())
        {
            remaining_admirers.push_back(&iAdmirer);
        }
    }
    ```

28. If the main `deck` is empty or their is only one admirer left after the current admirer's turn ends the round is over.

    ```cpp
    if (deck.empty() || remaining_admirers.size() == 1)
    {
        end_round = true;
        break;
    }
    ```

29. After the round ends, the round count goes up one.

    ```cpp
    gameState.round_count_ += 1;
    ```

30. If the deck is empty at the end of the round, remaining admirers must compare the values of their hands. Whoever has the hand with the highest value wins the round and is marked as the winner for the start of the next round.

    ```cpp
    if (deck.size() == 0)
    {
        cout << "Deck is empty, admirers compare hands!\n";
        for (size_t i = 0; i < gameState.admirers_.size(); i++)
        {
            Admirer *iAdmirer = &gameState.admirers_.at(i);
            if (i < gameState.admirers_.size() - 1)
            {
                if (iAdmirer->GetHand()->at(0).GetValue() > gameState.admirers_.at(i + 1).GetHand()->at(0).GetValue())
                {
                    winner = &gameState.admirers_.at(i);
                }
            }
        }
        cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << '\n';
        winner->Addtoken();
        winner->Winner(1);
    }
    ```

31. If a remaining admirer at the end of the round has a emissary bonus, they gain an extra favor token on top of whatever winnings they had already received.

    ```cpp
    int emissary_count = 0;
    if (any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &iAdmirer) { return iAdmirer.EmissaryStatus(); }))
    {
        Admirer *emissary_bonus = nullptr;
        for (Admirer &iAdmirer : gameState.admirers_)
        {
            if (iAdmirer.Status() && iAdmirer.EmissaryStatus() && emissary_count < 2)
            {
                emissary_bonus = &iAdmirer;
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
    ```

32. If the deck is not empty, set the last admirer standing as the winner.

    ```cpp
    for (Admirer &iAdmirer : gameState.admirers_)
    {
        if (iAdmirer.Status())
        {
            winner = &iAdmirer;
        }
    }
    ```

33. Give a final prompt celebrating the winning admirer.

    ```cpp
    cout << winner->GetName() << " was the last admirer standing!\n";
    winner->Addtoken();
    cout << winner->GetName() << " token count: " << winner->GetTokenCount() << "\n\n";
    winner->SetStarting(1);
    ```

34. Reset the status of admirers who were knocked out from not playing to playing so that they can join the next round.

    ```cpp
    if (gameState.round_count_ > 1)
    {
        for (Admirer &i : gameState.admirers_)
        {
            i.Reset();
        }
    }
    ```

35. If the winner of the previous round has the number of favor tokens to trigger the end of the game, they are celebrated as the winner of the entire game session. Then the game is set to `game_over` and ends.

    ```cpp
    for (Admirer &iAdmirer : gameState.admirers_)
    {
        if (iAdmirer.GetTokenCount() == gameState.winning_token_count_)
        {
            cout << iAdmirer.GetName() << " has " << iAdmirer.GetTokenCount() << " tokens!\n";
            cout << iAdmirer.GetName() << " wins the game!\n";
            game_over = true;
            break;
        }
    }
    ```

36. Program execution ends.

    ```cpp
    return 0;
    ```