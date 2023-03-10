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
   vector<Card> hand(5);

    Player * x = Player_factory("Rishab", "Simple");
    x->add_card(Card(TEN, HEARTS));
    x->add_card(Card(JACK, CLUBS));
    x->add_card(Card(JACK, SPADES));
    x->add_card(Card(QUEEN, DIAMONDS));
    x->add_card(Card(KING, SPADES));

    Suit trump;
    bool orderup = x->make_trump(Card(QUEEN, HEARTS), true, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);
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

    Player * y = Player_factory("Rishab", "Simple");
    y->add_card(Card(TEN, HEARTS));
    y->add_card(Card(JACK, HEARTS));
    y->add_card(Card(JACK, SPADES));
    y->add_card(Card(QUEEN, DIAMONDS));
    y->add_card(Card(KING, SPADES));

    Card led2 = Card(QUEEN, CLUBS);
    Card right2 = y->play_card(led2, HEARTS);
    ASSERT_EQUAL(right2, Card(JACK, SPADES));

    Player * z = Player_factory("Rishab", "Simple");
    z->add_card(Card(TEN, DIAMONDS));
    z->add_card(Card(JACK, HEARTS));
    z->add_card(Card(JACK, SPADES));
    z->add_card(Card(QUEEN, DIAMONDS));
    z->add_card(Card(KING, SPADES));

    Card led3 = Card(NINE, DIAMONDS);
    Card right3 = z->play_card(led3, HEARTS);
    ASSERT_EQUAL(right3, Card(QUEEN, DIAMONDS));

    Player * a = Player_factory("Rishab", "Simple");
    a->add_card(Card(TEN, SPADES));
    a->add_card(Card(JACK, HEARTS));
    a->add_card(Card(JACK, DIAMONDS));
    a->add_card(Card(QUEEN, CLUBS));
    a->add_card(Card(KING, SPADES));

    Card led4 = Card(QUEEN, DIAMONDS);
    Card right4 = a->play_card(led4, DIAMONDS);
    ASSERT_EQUAL(right4, Card(JACK, DIAMONDS));
}

TEST_MAIN()
