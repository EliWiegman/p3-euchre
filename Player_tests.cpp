// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;


TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_player_get_name) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}




TEST(get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;

    Player * rishab = Player_factory("Rishab", "Human");
    ASSERT_EQUAL("Rishab", rishab->get_name());
    delete alice;
}

TEST(add_card)
{
  Player * a = Player_factory("A", "Simple");
  vector<Card> hand;
  a->add_card(Card(ACE, HEARTS));
  hand.push_back(Card(ACE, HEARTS));
  ASSERT_EQUAL(hand[0], Card(ACE, HEARTS));

  a->add_card(Card(KING, CLUBS));
  hand.push_back(Card(KING, CLUBS));
  ASSERT_EQUAL(hand[1], Card(KING, CLUBS));

  a->add_card(Card(JACK, DIAMONDS));
  hand.push_back(Card(JACK, DIAMONDS));
  ASSERT_EQUAL(hand[2], Card(JACK, DIAMONDS));

  a->add_card(Card(NINE, SPADES));
  hand.push_back(Card(NINE, SPADES));
  ASSERT_EQUAL(hand[3], Card(NINE, SPADES));

  a->add_card(Card(QUEEN, HEARTS));
  hand.push_back(Card(QUEEN, HEARTS));
  ASSERT_EQUAL(hand[4], Card(QUEEN, HEARTS));
  delete a;
}

TEST(insertion)
{
  Player * x = Player_factory("Rishab", "Simple");
  ostringstream out;
  out << *x;
  ASSERT_EQUAL("Rishab", out.str());
  
  Player * y = Player_factory("Eli", "Human");
  ostringstream out1;
  out1 << *y;
  ASSERT_EQUAL("Eli", out1.str());
}

TEST(make_trump)
{
    Player * x = Player_factory("Rishab", "Simple");
    x->add_card(Card(TEN, SPADES));
    x->add_card(Card(JACK, CLUBS));
    x->add_card(Card(JACK, HEARTS));
    x->add_card(Card(QUEEN, HEARTS));
    x->add_card(Card(KING, HEARTS));

    Suit trump;
    bool orderup = x->make_trump(Card(QUEEN, HEARTS), true, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
    delete x;

    Player * x1 = Player_factory("Rishab", "Simple");
    x1->add_card(Card(TEN, SPADES));
    x1->add_card(Card(JACK, CLUBS));
    x1->add_card(Card(JACK, SPADES));
    x1->add_card(Card(QUEEN, DIAMONDS));
    x1->add_card(Card(KING, HEARTS));

    orderup = x1->make_trump(Card(QUEEN, HEARTS), true, 1, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
    delete x1;


    Player * x2 = Player_factory("Rishab", "Simple");
    x2->add_card(Card(TEN, HEARTS));
    x2->add_card(Card(JACK, CLUBS));
    x2->add_card(Card(JACK, SPADES));
    x2->add_card(Card(QUEEN, DIAMONDS));
    x2->add_card(Card(KING, SPADES));

    orderup = x2->make_trump(Card(JACK, SPADES), true, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    delete x2;


    Player * x3 = Player_factory("Rishab", "Simple");
    x3->add_card(Card(TEN, HEARTS));
    x3->add_card(Card(KING, CLUBS));
    x3->add_card(Card(JACK, DIAMONDS));
    x3->add_card(Card(QUEEN, DIAMONDS));
    x3->add_card(Card(KING, HEARTS));

    orderup = x3->make_trump(Card(JACK, SPADES), false, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);
    delete x3;

    Player * x4 = Player_factory("Rishab", "Simple");
    x4->add_card(Card(TEN, HEARTS));
    x4->add_card(Card(KING, CLUBS));
    x4->add_card(Card(JACK, SPADES));
    x4->add_card(Card(QUEEN, DIAMONDS));
    x4->add_card(Card(ACE, SPADES));

    orderup = x4->make_trump(Card(JACK, SPADES), false, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);
    delete x4;

    Player * x5 = Player_factory("Rishab", "Simple");
    x5->add_card(Card(TEN, HEARTS));
    x5->add_card(Card(KING, HEARTS));
    x5->add_card(Card(JACK, DIAMONDS));
    x5->add_card(Card(QUEEN, DIAMONDS));
    x5->add_card(Card(ACE, HEARTS));

    orderup = x5->make_trump(Card(JACK, SPADES), false, 2, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, CLUBS);
    delete x5;

    Player * x6 = Player_factory("Rishab", "Simple");
    x6->add_card(Card(TEN, HEARTS));
    x6->add_card(Card(NINE, DIAMONDS));
    x6->add_card(Card(JACK, CLUBS));
    x6->add_card(Card(QUEEN, SPADES));
    x6->add_card(Card(ACE, CLUBS));

    orderup = x6->make_trump(Card(JACK, HEARTS), false, 2, trump);
    ASSERT_FALSE(orderup);
    delete x6;

    Player * x7 = Player_factory("Rishab", "Simple");
    x7->add_card(Card(TEN, HEARTS));
    x7->add_card(Card(NINE, DIAMONDS));
    x7->add_card(Card(JACK, CLUBS));
    x7->add_card(Card(QUEEN, SPADES));
    x7->add_card(Card(ACE, CLUBS));

    orderup = x7->make_trump(Card(JACK, HEARTS), true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, DIAMONDS);
    delete x7;

    Player * x8 = Player_factory("Rishab", "Simple");
    x8->add_card(Card(TEN, HEARTS));
    x8->add_card(Card(QUEEN, DIAMONDS));
    x8->add_card(Card(NINE, CLUBS));
    x8->add_card(Card(NINE, SPADES));
    x8->add_card(Card(ACE, HEARTS));

    orderup = x8->make_trump(Card(QUEEN, SPADES), true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);
    delete x8;
}

TEST(lead_card)
{
    Player * x = Player_factory("Rishab", "Simple");
    x->add_card(Card(TEN, HEARTS));
    x->add_card(Card(JACK, CLUBS));
    x->add_card(Card(JACK, SPADES));
    x->add_card(Card(QUEEN, DIAMONDS));
    x->add_card(Card(KING, SPADES));

    Card card_led = x->lead_card(HEARTS);
    Card right(KING, SPADES);
    ASSERT_EQUAL(card_led, right); 
    delete x;

    Player * x1 = Player_factory("Rishab", "Simple");
    x1->add_card(Card(TEN, HEARTS));
    x1->add_card(Card(JACK, HEARTS));
    x1->add_card(Card(ACE, HEARTS));
    x1->add_card(Card(QUEEN, HEARTS));
    x1->add_card(Card(KING, HEARTS));

    Card card_led1 = x1->lead_card(HEARTS);
    Card right1(JACK, HEARTS);
    ASSERT_EQUAL(card_led1, right1); 
    delete x1;

    Player * x2 = Player_factory("Rishab", "Simple");
    x2->add_card(Card(TEN, HEARTS));
    x2->add_card(Card(JACK, HEARTS));
    x2->add_card(Card(ACE, HEARTS));
    x2->add_card(Card(QUEEN, DIAMONDS));
    x2->add_card(Card(KING, HEARTS));

    Card card_led2 = x2->lead_card(HEARTS);
    Card right2(QUEEN, DIAMONDS);
    ASSERT_EQUAL(card_led2, right2); 
    delete x2;

    Player * x3 = Player_factory("Rishab", "Simple");
    x3->add_card(Card(TEN, HEARTS));
    x3->add_card(Card(QUEEN, SPADES));
    x3->add_card(Card(JACK, CLUBS));
    x3->add_card(Card(QUEEN, DIAMONDS));
    x3->add_card(Card(KING, HEARTS));

    Card card_led3 = x3->lead_card(HEARTS);
    Card right3(QUEEN, DIAMONDS);
    ASSERT_EQUAL(card_led3, right3); 
    delete x3;
}

TEST(play_card) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(NINE, CLUBS));

  Card jack_hearts(JACK, HEARTS);
  Card card_played = bob->play_card(jack_hearts, DIAMONDS); 

  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;

    Player * x = Player_factory("Rishab", "Simple");
    x->add_card(Card(TEN, HEARTS));
    x->add_card(Card(JACK, CLUBS));
    x->add_card(Card(JACK, SPADES));
    x->add_card(Card(QUEEN, DIAMONDS));
    x->add_card(Card(KING, SPADES));

    Card led1 = Card(QUEEN, SPADES);
    Card right1 = x->play_card(led1, HEARTS);
    ASSERT_EQUAL(right1, Card(KING, SPADES));
    delete x;

    Player * y = Player_factory("Rishab", "Simple");
    y->add_card(Card(TEN, HEARTS));
    y->add_card(Card(JACK, HEARTS));
    y->add_card(Card(JACK, SPADES));
    y->add_card(Card(QUEEN, DIAMONDS));
    y->add_card(Card(KING, SPADES));

    Card led2 = Card(QUEEN, CLUBS);
    Card right2 = y->play_card(led2, HEARTS);
    ASSERT_EQUAL(right2, Card(JACK, SPADES));
    delete y;

    Player * z = Player_factory("Rishab", "Simple");
    z->add_card(Card(TEN, DIAMONDS));
    z->add_card(Card(JACK, HEARTS));
    z->add_card(Card(JACK, SPADES));
    z->add_card(Card(QUEEN, DIAMONDS));
    z->add_card(Card(KING, SPADES));

    Card led3 = Card(NINE, DIAMONDS);
    Card right3 = z->play_card(led3, HEARTS);
    ASSERT_EQUAL(right3, Card(QUEEN, DIAMONDS));
    delete z;

    Player * a = Player_factory("Rishab", "Simple");
    a->add_card(Card(TEN, SPADES));
    a->add_card(Card(JACK, HEARTS));
    a->add_card(Card(JACK, DIAMONDS));
    a->add_card(Card(QUEEN, CLUBS));
    a->add_card(Card(KING, SPADES));

    Card led4 = Card(QUEEN, DIAMONDS);
    Card right4 = a->play_card(led4, DIAMONDS);
    ASSERT_EQUAL(right4, Card(JACK, DIAMONDS));
    delete a;
}

TEST_MAIN()
