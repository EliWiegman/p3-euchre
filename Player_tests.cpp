// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;
/*
test_player_add_and_discard_card
test_player_add_card
test_player_get_name
test_player_insertion
test_simple_player_lead_card
test_simple_player_make_trump
test_simple_player_play_card
*/

TEST(get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(NINE, CLUBS));

  // Bob plays a card
  Card jack_hearts(JACK, HEARTS);
  Card card_played = bob->play_card(
    jack_hearts,  // Nine of Diamonds is led
    DIAMONDS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}

TEST(add_card)
{
  Player * a = Player_factory("Bob", "Simple");
  vector<Card> hand;
  a->add_card(Card(ACE, HEARTS));
  hand.push_back(Card(ACE, HEARTS));
  ASSERT_EQUAL(hand[0], Card(ACE, HEARTS));
}

TEST(insertion)
{
  Player * x = Player_factory("Rishab", "Human");
  ostringstream out;
  out << *x;
  ASSERT_EQUAL("Rishab", out.str());
}

TEST(make_trump)
{
  
}

TEST_MAIN()
