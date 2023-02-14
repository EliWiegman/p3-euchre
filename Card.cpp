// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  is >> str;
  rank = string_to_rank(str);
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  is >> str;
  suit = string_to_suit(str);
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


  Card::Card()
  {
    rank = TWO;
    suit = SPADES;
  }

  Card::Card(Rank rank_in, Suit suit_in)
  {
    rank = rank_in;
    suit = suit_in;
  }

  Rank Card::get_rank() const
  {
    return rank;
  }

  Suit Card::get_suit() const
  {
    return suit;
  }

  Suit Card::get_suit(Suit trump) const
  {
    if (rank == JACK)
    {
      return Suit_next(trump);
    }
    return suit;
  }

  bool Card::is_face_or_ace() const
  {
    if (rank == JACK || rank == QUEEN || rank == KING ||
    rank == ACE)
    {
      return true;
    }
    return false;
  }

  bool Card::is_right_bower(Suit trump) const
  {
    if (rank == JACK && suit == trump)
    {
      return true;
    }
    return false;
  }

  bool Card::is_left_bower(Suit trump) const
  {
    if (rank == JACK && suit == Suit_next(trump))
    {
      return true;
    }
    return false;
  }

  bool Card::is_trump(Suit trump) const
  {
    if (suit == trump) 
    {
      return true;
    }
    else if (suit == is_left_bower(trump)) 
    {
      return true;
    }
    else 
    {
      return false;
    }
  }


std::ostream & operator<<(std::ostream &os, const Card &card)
{
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

std::istream & operator>>(std::istream &is, Card &card)
{
  string holder;
  string rank;
  string suit;
  is >> rank >> holder >> suit;
  card = Card(string_to_rank(rank), string_to_suit(suit));
  return is;
}

bool operator<(const Card &lhs, const Card &rhs)
{
  if (lhs.get_rank() < rhs.get_rank())
  {
    return true;
  }
  return false;
}

bool operator<=(const Card &lhs, const Card &rhs)
{
  if (lhs.get_rank() <= rhs.get_rank())
  {
    return true;
  }
  return false;
}

bool operator>(const Card &lhs, const Card &rhs)
{
    if (lhs.get_rank() > rhs.get_rank())
  {
    return true;
  }
  return false;
}

bool operator>=(const Card &lhs, const Card &rhs)
{
    if (lhs.get_rank() >= rhs.get_rank())
  {
    return true;
  }
  return false;
}

bool operator==(const Card &lhs, const Card &rhs)
{
    if (lhs.get_rank() == rhs.get_rank())
  {
    return true;
  }
  return false;
}

bool operator!=(const Card &lhs, const Card &rhs)
{
    if (lhs.get_rank() != rhs.get_rank())
  {
    return true;
  }
  return false;
}

Suit Suit_next(Suit suit)
{
  if (suit == SPADES)
  {
    return CLUBS;
  }
  else if (suit == CLUBS)
  {
    return SPADES;
  }
  else if (suit == HEARTS)
  {
    return DIAMONDS;
  }
  else
  {
    return HEARTS;
  }
}

bool Card_less(const Card &a, const Card &b, Suit trump)
{
  if (a.get_suit() != trump && b.get_suit() == trump)
  {
    return true;
  }
  if (a.get_suit() == trump && b.get_suit() == trump)
  {
    if (a.get_rank() < b.get_rank())
    {
      return true;
    }
  }
  return false;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump)
{
  if (a.get_suit() != trump && b.get_suit() == trump)
  {
    return true;
  }
  if (a.get_suit() == trump && b.get_suit() == trump)
  {
    if (a.get_rank() < b.get_rank())
    {
      return true;
    }
  }
  if (a.get_suit() != led_card.get_suit() && b.get_suit() == led_card.get_suit())
  {
    return true;
  }
  if (a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit())
  {
    if (a.get_rank() < b.get_rank())
    {
      return true;
    }
  }
  return false;
}



