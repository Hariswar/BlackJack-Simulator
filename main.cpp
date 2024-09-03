// Programmer: Hariswar Baburaj
// Date: 04/22/2024
// File: main.cpp
// Asignmnet: Homework5.cpp
// Purpose: This is the main file where it runs all the functions and the main interpretation of the game happens here.

#include "blackjack.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  int Winforblackjack = 0;
  int Lossforblackjack = 0; // specifically for blackjack
  int Tieforblackjack = 0;
  int losses = 0; // This one is for the losses(not include blackjack)
  int wins = 0;   // This one is for the win(not include blackjack)
  int ties = 0;   // This one is for the ties(not include blackjack)
  int num_of_rounds = 1;
  int player_hand_score;  // This is player hand value
  int dealer_hand_score;  // This is dealer hand value
  int player_card_number; // This is player hand card number
  int dealer_card_number; // This is dealer hand card number
  char keepPlaying;

  srand(1570);
  string user;
  cout << "What is your name? ";
  getline(cin, user);
  double playerbalance = ((rand() % 90001 + 10000) / 100.0);
  double normal_balance = playerbalance;
  cout << "Your Starting Balance is: $" << playerbalance << endl;

  do
  {
    struct card Player_hand[17] = {};
    struct card Dealer_hand[17] = {};
    dealer_card_number = 1; // Dealer's card
    player_card_number = 2; // Player's card
    player_hand_score = 0;  // Player hand value
    dealer_hand_score = 0;  // Dealer hand value

    cout << endl;
    cout << "Round " << num_of_rounds << endl;
    cout << "*******" << endl;
    cout << "Current Balance: $" << normal_balance << fixed
         << std::setprecision(2) << endl;
    double playerwager;
    cout << "Enter the ammount you would like to wager: $";
    cin >> playerwager;

    // This one is used to insert the "adviseOptimalActionOnLuck" function into the main
    string computer_advice;

    while (true)
    {
      // checks wheather they put in the correct wager amount
      if (playerwager <= normal_balance)
      {
        if (playerwager > 0)
        {
          break;
        }
        else
        {
          cout << "Invalid wager amount. Please enter a valid wager amount "
                  "that's greater than zero: ";
          cin >> playerwager;
        }
      }
      else
      {
        cout << "You can't bet more money that your initial amount. Please "
                "enter a valid wager amount: ";
        cin >> playerwager;
      }
    }
    cout << endl;

    Player_hand[0] = Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
    Player_hand[1] = Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
    Dealer_hand[0] = Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);

    cout << "Player's Hand: ";
    printHand(Player_hand, player_card_number);
    cout << "Dealer's Hand: ";
    printHand(Dealer_hand, dealer_card_number);
    Dealer_hand[1] = Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
    dealer_card_number += 1;
    player_hand_score = Player_hand[0].value + Player_hand[1].value;
    dealer_hand_score = Dealer_hand[0].value + Dealer_hand[1].value;
    cout << endl;

    char choosing_option;
    char firstOption;

    // Checks if the player has got an a BlackJack.
    if (isBlackjack(player_hand_score) && !isBlackjack(dealer_hand_score))
    {
      updatePlayerBalance("playerBlackJack", normal_balance, playerwager, 'n',
                          "none");
      Winforblackjack += 1;
    }
    else if (!isBlackjack(player_hand_score) &&
             isBlackjack(dealer_hand_score))
    {
      updatePlayerBalance("dealerBlackJack", normal_balance, playerwager, 'n',
                          "none");
      Lossforblackjack += 1;
    }
    else if (isBlackjack(player_hand_score) &&
             isBlackjack(dealer_hand_score))
    {
      updatePlayerBalance("tieBlackJack", normal_balance, playerwager, 'n',
                          "none");
      Tieforblackjack += 1;
    }
    else
    {
      // This is for the computer_advice. If they listen to advice, the balance
      // updates based on that.
      computer_advice = adviseOptimalActionOnLuck(
          (rand() % 100) + 1, Player_hand[0].num, Player_hand[1].num,
          player_hand_score, Dealer_hand[0].num);

      if (Player_hand[0].num == 1 || Player_hand[1].num == 1)
      {
        int first_total, second_total;
        if (Player_hand[0].num == 1)
        {
          first_total = getCardNum(Player_hand[1].num) + 11;
          second_total = getCardNum(Player_hand[1].num) + 1;
        }
        else
        {
          first_total = getCardNum(Player_hand[0].num) + 11;
          second_total = getCardNum(Player_hand[0].num) + 1;
        }
        cout << "Player Total: " << first_total << " or " << second_total
             << endl;
      }
      cout << computer_advice << endl;
      cout << endl;

      cout << "Would you like to hit, stand, or double down? (h/H, S/s, D/d): ";
      // If it's not h,s,d it will be counted as invalid charcter and asks you
      // to enter a valid option again.
      cin >> choosing_option;
      while (!((choosing_option == 'h') || (choosing_option == 'H') ||
               (choosing_option == 's') || (choosing_option == 'S') ||
               (choosing_option == 'd') || (choosing_option == 'D')))
      {
        cout << "Invalid option. Please enter 'h' or 'H' to hit, 's' or 'S' to "
                "stand, or 'd' or 'D' to double down: ";
        cin >> choosing_option;
      }
      cout << endl;

      // When the option is hit.
      if (((choosing_option == 'h') ||
           (choosing_option == 'H')) &&
          (player_hand_score <= 21))
      {
        // Save the first option the player chose
        firstOption = choosing_option;
        cout << "Player hits!" << endl;

        Player_hand[player_card_number] =
            Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
        player_card_number += 1;
        player_hand_score += ((Player_hand[player_card_number - 1].num == 1) &&
                              (player_hand_score + 11 > 21))
                                 ? 1
                                 : Player_hand[player_card_number - 1].value;
        cout << user << " drew: " << Player_hand[player_card_number - 1] << endl;
        cout << endl;
        cout << "Player's Hand: ";
        printHand(Player_hand, player_card_number);
        cout << endl;

        while (((choosing_option == 'h') || (choosing_option == 'H')) &&
               (player_hand_score <= 21))
        {
          cout << "Hit or Stand? (h/s): ";
          cin >> choosing_option;
          cout << endl;
          while (!((choosing_option == 'h') || (choosing_option == 'H') ||
                   (choosing_option == 's') || (choosing_option == 'S')))
          {
            cout << "Error: Choose a different option ";
            cin >> choosing_option;
          }
          if ((choosing_option == 'h') || (choosing_option == 'H'))
          {
            cout << "Player hits!" << endl;
            Player_hand[player_card_number] =
                Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
            player_card_number += 1;
            player_hand_score +=
                ((Player_hand[player_card_number - 1].num == 1) &&
                 (player_hand_score + 11 > 21))
                    ? 1
                    : Player_hand[player_card_number - 1].value;
            cout << user
                 << " drew: " << Player_hand[player_card_number - 1] << endl;
            cout << endl;
            cout << "Player's Hand: ";
            printHand(Player_hand, player_card_number);
            cout << endl;
          }
          else if ((choosing_option == 's') || (choosing_option == 'S'))
          {
            cout << "Player stands." << endl;
            cout << endl;
          }
        }
      }

      // When the player double down.
      else if (((choosing_option == 'd') ||
                (choosing_option == 'D')) &&
               (player_hand_score <= 21))
      {
        firstOption = choosing_option;
        playerwager *= 2;
        cout << "Player doubles down!" << endl;
        cout << "The new wager is " << playerwager << endl;
        Player_hand[player_card_number] =
            Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
        player_card_number += 1;
        player_hand_score += ((Player_hand[player_card_number - 1].num == 1) &&
                              (player_hand_score + 11 > 21))
                                 ? 1
                                 : Player_hand[player_card_number - 1].value;
        cout << "Card Drawn: " << Player_hand[player_card_number - 1] << endl;
        cout << endl;
        cout << "Player's Hand: ";
        printHand(Player_hand, player_card_number);
        cout << endl;
        cout << "player stands." << endl;
        cout << "" << endl;
      }
      // When the player stands.
      else if (((choosing_option == 's') ||
                (choosing_option == 'S')) &&
               (player_hand_score <= 21))
      {
        firstOption = choosing_option;
        cout << "Player stands.\n"
             << endl;
      }

      // When there is a chance for player Bust!
      if (player_hand_score > 21)
      {
        updatePlayerBalance("playerBust", normal_balance, playerwager,
                            firstOption, computer_advice);
        losses += 1;
      }
      else
      {
        cout << "Dealer shows his second card: " << Dealer_hand[1] << endl;
        cout << endl;

        if (dealer_hand_score <= 16)
        {
          while (dealer_hand_score <= 16)
          {
            cout << "Dealer hits!" << endl;
            Dealer_hand[dealer_card_number] =
                Card_is_Valid(MIN, MAX, Player_hand, Dealer_hand);
            dealer_card_number += 1;
            dealer_hand_score +=
                (Dealer_hand[dealer_card_number - 1].num == 1) &&
                        (dealer_hand_score + 11 > 21)
                    ? 1
                    : Dealer_hand[dealer_card_number - 1].value;
            cout << "Dealer Drew: " << Dealer_hand[dealer_card_number - 1] << endl;
            cout << endl;
          }
        }
        if (dealer_hand_score > 21)
        {
          updatePlayerBalance("dealerBust", normal_balance, playerwager,
                              firstOption, computer_advice);
          wins += 1;
        }
        else
        {
          cout << "Dealer stands.\n"
               << endl;
          cout << endl;

          // Prints the player and dealer's hand
          cout << "Player's Hand: ";
          printHand(Player_hand, player_card_number);
          cout << "Dealer's Hand: ";
          printHand(Dealer_hand, dealer_card_number);

          cout << user << "'s Hand Total: " << player_hand_score << endl;
          cout << "The Dealer's Hand Total: " << dealer_hand_score << endl;
          cout << endl;

          // Based on dealer's hand and player's hand. The game determines if
          // the player has won or loss.
          if (dealer_hand_score > player_hand_score)
          {
            updatePlayerBalance("playerLoss", normal_balance, playerwager,
                                firstOption, computer_advice);
            losses += 1;
          }
          else if (dealer_hand_score < player_hand_score)
          {
            updatePlayerBalance("playerWin", normal_balance, playerwager,
                                firstOption, computer_advice);
            wins += 1;
          }
          else
          {
            updatePlayerBalance("playerTie", normal_balance, playerwager,
                                firstOption, computer_advice);
            ties += 1;
          }
        }
      }
    }
    cout << endl;
    num_of_rounds += 1;

    // You run out of money when the user goes below zero.
    if (normal_balance <= 0)
    {
      cout << endl;
      cout << "You have run out of money!" << endl;
      break;
    }
    cout << "\nWould you like to play again? (y/n): ";
    cin >> keepPlaying;

    while (keepPlaying != 'Y' && keepPlaying != 'y' && keepPlaying != 'N' &&
           keepPlaying != 'n')
    {
      cout << "Please enter the correct value (y or n): ";
      cin >> keepPlaying;
    }
    // Displays the Game summary when the player doesn't want to continue.
  } while ((keepPlaying != 'N') && (keepPlaying != 'n') &&
           (normal_balance > 0));
  cout << endl;
  displayGameSummary(num_of_rounds, Winforblackjack, Lossforblackjack,
                     Tieforblackjack, losses, wins, ties, playerbalance,
                     normal_balance);
}
