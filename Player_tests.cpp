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

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_play_card) {
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

TEST(test_simple_player_add_card)
{
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  vector<Card> hand;
  hand.push_back(Card(NINE, SPADES));
}

// Add more tests here

TEST_MAIN()
