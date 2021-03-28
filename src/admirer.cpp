#include "admirer.h"
#include "deck.h"
#include "card.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

Admirer::Admirer(const string name, const int value, const Reference &reference) : name_(name), value_(value), reference_(reference){};

// getters
const bool Admirer::ProtectionStatus() const
{
  return handmaid_;
}

const string Admirer::GetName() const
{
  return name_;
}

vector<Card>* Admirer::GetHand()
{
  return &hand_;
}

const bool Admirer::Status() const
{
  return playing_;
}

const int Admirer::GetValue() const
{
  return value_;
}

const int Admirer::GetTokenCount() const
{
  return token_count_;
}

const bool Admirer::HasEmissaryBonus() const
{
  return spy_;
}

Converter *Admirer::GetConversion()
{
  return &convert_;
}

const bool Admirer::Starting() const
{
  return starting_;
}

// setters
void Admirer::Draw(const Card obj)
{
  hand_.push_back(obj);
}

void Admirer::SetProtection(const bool state)
{
  handmaid_ = state;
}

void Admirer::GainEmissaryBonus()
{
  spy_ = true;
}

void Admirer::Reset()
{
  hand_.clear();
  handmaid_ = false;
  spy_ = false;
  playing_ = true;
}

void Admirer::Discard(const int choice, vector<Card> &deck)
{
  for (Card &iCard : hand_)
  {
    if (iCard.GetValue() == choice)
    {
      deck.push_back(iCard);
      RemoveCard(iCard.GetValue());
      break;
    }
  }
}

void Admirer::DiscardHand(vector<Card> &deck)
{
  for (Card &iCard : hand_)
  {
    Discard(iCard.GetValue(), deck);
  }
}

void Admirer::Addtoken()
{
  token_count_++;
}

void Admirer::Winner(const bool state)
{
  winner_ = state;
}

void Admirer::RemoveCard(const int card)
{
  for (size_t i = 0; i < hand_.size(); i++)
  {
    if (hand_.at(i).GetValue() == card)
    {
      hand_.erase(hand_.begin() + i);
      break;
    }
  }
}

void Admirer::Out(vector<Card> &deck)
{
  this->DiscardHand(deck);
  this->Reset();
  this->playing_ = false;
}

void Admirer::SetStarting(const bool state)
{
  starting_ = state;
}

// printers
void Admirer::PrintHand() const
{
  cout << '\n' << this->GetName() << " hand:\n";

  if (!hand_.empty())
  {
    for (size_t i = 0; i < hand_.size(); i++)
    {
      if (i < hand_.size() - 1)
      {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << ", ";
      }
      else
      {
        cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << "\n\n";
      }
    }
  }
  else
  {
    cout << "EMPTY\n";
  }
}
