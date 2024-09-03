// Programmer: Hariswar Baburaj
// Date: 04/22/2024
// File: game.cpp
// Asignmnet: Homework5.cpp
// Purpose: This file includes all the function and neccessary code it needs to run the game.

#include "blackjack.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

ostream &operator<<(ostream &os, const card &card)
{
  os << card.name << " of " << card.suit;
  return os;
}

bool operator<(const card &first_card, const card &second_card)
{
  if (first_card.valueForsuit < second_card.valueForsuit)
  {
    return true;
  }
  else if (first_card.valueForsuit == second_card.valueForsuit)
  {
    if (first_card.num < second_card.num)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}
// Values for each suit
int generateValueforSuit(const string suit)
{
  if (suit == "Diamonds")
  {
    return 1;
  }
  else if (suit == "Hearts")
  {
    return 2;
  }
  else if (suit == "Clubs")
  {
    return 3;
  }
  else
  {
    return 4;
  }
}

int generateRandomCard(const int min, const int max)
{
  // Generate a random number between min and max (inclusive)
  int RandomCard = rand() % (max - min + 1) + min;
  return RandomCard;
}

void printHand(struct card hand[], const int size_of_hand)
{
  int minValuepos;
  card temp_var;
  for (int i = 0; i < size_of_hand; i++)
  {
    minValuepos = i;
    for (int j = i + 1; j < size_of_hand; j++)
    {
      if (hand[j] < hand[minValuepos])
      {
        minValuepos = j;
      }
    }
    if (minValuepos != i)
    {
      temp_var = hand[minValuepos];
      hand[minValuepos] = hand[i];
      hand[i] = temp_var;
    }
  }
  for (int i = 0; i < size_of_hand; i++)
  {
    cout << hand[i];
    if (i < size_of_hand - 1)
    {
      cout << ", ";
    }
  }
  if (size_of_hand == 1)
  {
    cout << ", [Hidden Card]" << endl;
  }
  else
  {
    cout << endl;
  }
}

string generatefourCardSuit()
{
  // Randomizes the card suit between the 4 of them.
  int cardsuit = (rand() % 4);
  switch (cardsuit)
  {
  case 0:
    return "Spades";
  case 1:
    return "Hearts";
  case 2:
    return "Clubs";
  default:
    return "Diamonds";
  }
}

bool isBlackjack(const int handTotal)
{
  if (handTotal == 21)
  {
    return true;
  }
  else
  {
    return false;
  }
}

string generateCardStyles(const int cardValue)
{
  // Create a new function to keep track of the card styles
  switch (cardValue)
  {
  case 1:
    return "Ace";
  case 11:
    return "Jack";
  case 12:
    return "Queen";
  case 13:
    return "King";
  default:
    return to_string(cardValue);
  }
}

// Card Value
int getCardNum(const int cardValue)
{
  int num;
  // number of the card.
  switch (cardValue)
  {
  case 1:
    num = 11;
    break;
  case 11:
  case 12:
  case 13:
    num = 10;
    break;
  default:
    num = cardValue;
  }
  return num;
}

// This function generates the cards that are valid.
card Card_is_Valid(const int minimumCard, const int maximumCard,
                   struct card Player_hand[17], struct card Dealer_hand[17])
{
  card randCard;
  string Suit;
  int num_of_card;
  bool new_card;
  do
  {
    num_of_card = generateRandomCard(minimumCard, maximumCard);
    Suit = generatefourCardSuit();
    new_card = true;

    for (int i = 0; i < 17; i++)
    {
      if ((num_of_card == Dealer_hand[i].num) &&
          (Suit == Dealer_hand[i].suit))
      {
        new_card = false;
      }
    }
    for (int i = 0; i < 17; i++)
    {
      if ((num_of_card == Player_hand[i].num) &&
          (Suit == Player_hand[i].suit))
      {
        new_card = false;
      }
    }
  } while (new_card == false);
  randCard.suit = Suit;
  randCard.num = num_of_card;
  randCard.valueForsuit = generateValueforSuit(Suit);
  randCard.value = getCardNum(randCard.num);
  randCard.name = generateCardStyles(randCard.num);
  return randCard;
}

void updatePlayerBalance(const string message, double &normal_balance,
                         const double playerwager, const char choosing_option,
                         const string computer_advice)
{
  float payout;
  string computer_option;

  if (choosing_option == 'S' || choosing_option == 's')
  {
    computer_option = "The game advices you to Stand";
  }
  else if (choosing_option == 'H' || choosing_option == 'h')
  {
    computer_option = "The game advices you to Hit";
  }
  else if (choosing_option == 'D' || choosing_option == 'd')
  {
    computer_option = "The game advices you to Double Down";
  }

  if (message == "playerBlackJack")
  {
    // 1.5x wager
    payout = (playerwager * 1.5);
    normal_balance += payout;
    displayOutcome("playerBlackJack", (playerwager * 1.5) + playerwager,
                   normal_balance);
  }
  else if (message == "dealerBlackJack")
  {
    // Lose wager
    payout = playerwager;
    normal_balance -= payout;
    displayOutcome("dealerBlackJack", payout, normal_balance);
  }
  else if (message == "tieBlackJack")
  {
    // No change
    payout = 0;
    displayOutcome("tieBlackJack", payout, normal_balance);
  }
  else if (message == "playerTie")
  {
    payout = 0;
    displayOutcome("playerTie", payout, normal_balance);
  }
  else if ((computer_advice == computer_option) &&
           (message == "playerBust" || message == "playerLoss"))
  {
    payout = playerwager * 0.8;
    normal_balance -= payout;
    if (message == "playerBust")
    {
      displayOutcome("playerBust", payout, normal_balance);
    }
    else
    {
      displayOutcome("playerLoss", payout, normal_balance);
    }
  }
  else if ((computer_advice == computer_option) &&
           (message == "DealerBust" || message == "playerWin"))
  {
    payout = playerwager;
    normal_balance += payout;
    if (message == "DealerBust")
    {
      displayOutcome("DealerBust", payout, normal_balance);
    }
    else
    {
      displayOutcome("playerWin", payout, normal_balance);
    }
  }
  else if ((computer_advice != computer_option) &&
           (message == "dealerBust" || message == "playerWin"))
  {
    payout = playerwager * 1.8;
    normal_balance += payout;
    if (message == "dealerBust")
    {
      displayOutcome("dealerBust", payout, normal_balance);
    }
    else
    {
      displayOutcome("playerWin", payout, normal_balance);
    }
  }
  else if ((computer_advice != computer_option) &&
           (message == "playerBust" || message == "playerLoss"))
  {
    payout = playerwager * 1.2;
    normal_balance -= payout;
    if (message == "playerBust")
    {
      displayOutcome("playerBust", payout, normal_balance);
    }
    else
    {
      displayOutcome("playerLoss", payout, normal_balance);
    }
  }
  else
  {
    if (message == "dealerBust" || message == "playerWin")
    {
      payout = playerwager;
      normal_balance += payout;
      if (message == "dealerBust")
      {
        displayOutcome("dealerBust", payout, normal_balance);
      }
      else
      {
        displayOutcome("playerWin", payout, normal_balance);
      }
    }
    else if (message == "playerBust" || message == "playerLoss")
    {
      payout = playerwager;
      normal_balance -= payout;
      if (message == "playerBust")
      {
        displayOutcome(message, payout, normal_balance);
      }
      else
      {
        displayOutcome(message, payout, normal_balance);
      }
    }
  }
}

void displayOutcome(const string message, const double money_update,
                    const double New_balance)
{
  if (message == "dealerBlackJack")
  {
    cout << "The dealer hit a Blackjack!" << endl;
    cout << "Balance Update: -$" << money_update << endl;
  }
  else if (message == "playerBlackJack")
  {
    cout << "You hit Blackjack!" << endl;
    cout << "Balance Update: +$" << money_update << endl;
  }
  else if (message == "tieBlackJack")
  {
    cout << "Both You and the Dealer hit a Blackjack!" << endl;
    cout << "Balance Update: +$0" << endl;
  }
  else if (message == "dealerBust")
  {
    cout << "The Dealer Busted! You Win!" << endl;
    cout << "Balance Update: +$" << money_update << endl;
  }
  else if (message == "playerBust")
  {
    cout << "You Busted! The Dealer Wins" << endl;
    cout << "Balance Update: -$" << money_update << endl;
  }
  else if (message == "playerLoss")
  {
    cout << "The Dealer Wins!" << endl;
    cout << "Balance Update: -$" << money_update << endl;
  }
  else if (message == "playerWin")
  {
    cout << "The Player Wins!" << endl;
    cout << "Balance Update: +$" << money_update << endl;
  }
  else if (message == "playerTie")
  {
    cout << "You and the Dealer Tied!" << endl;
    cout << "Balance Update: +$0" << endl;
  }
  cout << "New Balance is $" << New_balance << endl;
}

void displayGameSummary(const int num_of_rounds, const int Winforblackjack,
                        const int Lossforblackjack, const int Tieforblackjack,
                        const int losses, const int wins, const int ties,
                        const double playerbalance,
                        const double overallbalance)
{

  double Gain_loss = overallbalance - playerbalance;
  cout << endl;
  cout << "=== Game Summary ===" << endl;
  cout << "Total Rounds Played: " << num_of_rounds - 1 << endl;
  cout << "Total Wins (Regular): " << wins << endl;
  cout << "Total Wins (Blackjack): " << Winforblackjack << endl;
  cout << "Total Losses (Regular): " << losses << endl;
  cout << "Total Losses (Blackjack): " << Lossforblackjack << endl;
  cout << "Total Ties (Regular): " << ties << endl;
  cout << "Total Ties (Blackjack): " << Tieforblackjack << endl;
  cout << "Final Balance: " << ((overallbalance < 0) ? "$0" : "+$")
       << overallbalance
       << endl; // Used ternary operator, so that if the overall balance is less
                // than 0, it will display $0, otherwise it will display the
                // actual balance with + in front.
  cout << "Net Gain/Loss: ";
  cout << ((Gain_loss < 0) ? "-$" : "+$")
       << ((Gain_loss < 0) ? (Gain_loss * -1) : (Gain_loss)) << endl;
}
