// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST_MAIN()

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(left_and_right_bowers) {
    Card left(JACK, DIAMONDS);
    Card right(JACK, HEARTS);
    ASSERT_TRUE(Card_less(left, right, HEARTS));
}

TEST(both_trump) {
    Card c1(QUEEN, HEARTS);
    Card c2(JACK, HEARTS);
    ASSERT_TRUE(Card_less(c1, c2, HEARTS));
}

TEST(bower_vs_trump_ace) {
    Card c1(ACE, HEARTS);
    Card c2(JACK, HEARTS);
    ASSERT_TRUE(Card_less(c1, c2, HEARTS));
}

TEST(led_suit) {
    Card c1(KING, CLUBS);
    Card c2(ACE, CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, HEARTS));
}

// stole all this from krishan
// MUST CHANGE!!!!!!!

TEST(test_card_suit_rank)
{
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_EQUAL(JACK, jack_spades.get_rank());
    ASSERT_EQUAL(SPADES, jack_spades.get_suit());
    ASSERT_NOT_EQUAL(DIAMONDS, jack_spades.get_suit(HEARTS));
}

TEST(test_card_props)
{
    Card ten_clubs = Card(TEN, CLUBS);
    ASSERT_FALSE(ten_clubs < ten_clubs);
    ASSERT_TRUE(ten_clubs <= ten_clubs);
    ASSERT_FALSE(ten_clubs > ten_clubs);
    ASSERT_TRUE(ten_clubs >= ten_clubs);
    ASSERT_TRUE(ten_clubs == ten_clubs);
    ASSERT_FALSE(ten_clubs != ten_clubs);
}

TEST(test_card_type_nonbower)
{
    Card queen_clubs = Card(QUEEN, CLUBS);
    ASSERT_TRUE(queen_clubs.is_face_or_ace());
    ASSERT_FALSE(queen_clubs.is_right_bower(CLUBS));
    ASSERT_FALSE(queen_clubs.is_left_bower(CLUBS));
    ASSERT_TRUE(queen_clubs.is_trump(CLUBS));
}

TEST(test_card_type_rbower)
{
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_TRUE(jack_hearts.is_face_or_ace());
    ASSERT_TRUE(jack_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_hearts.is_left_bower(HEARTS));
    ASSERT_TRUE(jack_hearts.is_trump(HEARTS));
}

TEST(test_card_type_lbower)
{
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    ASSERT_FALSE(jack_diamonds.is_right_bower(HEARTS));
    ASSERT_TRUE(jack_diamonds.is_left_bower(HEARTS));
    ASSERT_TRUE(jack_diamonds.is_trump(HEARTS));
}

TEST(test_suit_next)
{
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_NOT_EQUAL(CLUBS, Suit_next(HEARTS));
    ASSERT_NOT_EQUAL(SPADES, Suit_next(DIAMONDS));
    ASSERT_NOT_EQUAL(HEARTS, Suit_next(SPADES));
    ASSERT_NOT_EQUAL(DIAMONDS, Suit_next(CLUBS));
}

TEST(test_card_out)
{
    Card king_diamonds = Card(KING, DIAMONDS);
    ostringstream os;
    os << king_diamonds;
    ASSERT_EQUAL("King of Diamonds", os.str());
}

TEST(test_card_in)
{
    istringstream is("King of Diamonds");
    Card king_diamonds;
    is >> king_diamonds;
    ASSERT_EQUAL(king_diamonds, Card(KING, DIAMONDS));
}

TEST(test_rank_out)
{
    Card ace_spades = Card(ACE, SPADES);
    ostringstream os;
    os << ace_spades.get_rank();
    ASSERT_EQUAL("Ace", os.str());
}

TEST(test_rank_in)
{
    istringstream is("Two");
    Rank two;
    is >> two;
    ASSERT_EQUAL(two, TWO);
}

TEST(test_suit_out)
{
    Card ace_spades = Card(ACE, SPADES);
    ostringstream os;
    os << ace_spades.get_suit();
    ASSERT_EQUAL("Spades", os.str());
}

TEST(test_suit_in)
{
    istringstream is("Diamonds");
    Suit diamonds;
    is >> diamonds;
    ASSERT_EQUAL(diamonds, DIAMONDS);
}

TEST(test_card_less_trump)
{
    const Card a = Card(JACK, SPADES);
    const Card b = Card(JACK, CLUBS);
    const Card c = Card(ACE, SPADES);
    const Card d = Card(NINE, SPADES);
    const Card e = Card(ACE, HEARTS);
    const Card f = Card(NINE, DIAMONDS);
    ASSERT_TRUE(Card_less(b, a, SPADES));
    ASSERT_TRUE(Card_less(c, b, SPADES));
    ASSERT_TRUE(Card_less(d, c, SPADES));
    ASSERT_TRUE(Card_less(e, d, SPADES));
    ASSERT_TRUE(Card_less(f, e, SPADES));
    ASSERT_FALSE(Card_less(a, b, SPADES));
    ASSERT_FALSE(Card_less(b, c, SPADES));
    ASSERT_FALSE(Card_less(c, d, SPADES));
    ASSERT_FALSE(Card_less(d, e, SPADES));
    ASSERT_FALSE(Card_less(e, f, SPADES));
}

TEST(test_card_less_led)
{
    const Card led_card = Card(KING, DIAMONDS);
    const Card a = Card(JACK, SPADES);
    const Card b = Card(JACK, CLUBS);
    const Card c = Card(ACE, SPADES);
    const Card d = Card(NINE, SPADES);
    const Card e = Card(ACE, DIAMONDS);
    const Card f = Card(NINE, DIAMONDS);
    const Card g = Card(ACE, HEARTS);
    const Card h = Card(NINE, CLUBS);
    ASSERT_TRUE(Card_less(b, a, led_card, SPADES));
    ASSERT_TRUE(Card_less(c, b, led_card, SPADES));
    ASSERT_TRUE(Card_less(d, c, led_card, SPADES));
    ASSERT_TRUE(Card_less(e, d, led_card, SPADES));
    ASSERT_TRUE(Card_less(f, e, led_card, SPADES));
    ASSERT_TRUE(Card_less(g, f, led_card, SPADES));
    ASSERT_TRUE(Card_less(h, g, led_card, SPADES));
    ASSERT_FALSE(Card_less(a, b, led_card, SPADES));
    ASSERT_FALSE(Card_less(b, c, led_card, SPADES));
    ASSERT_FALSE(Card_less(c, d, led_card, SPADES));
    ASSERT_FALSE(Card_less(d, e, led_card, SPADES));
    ASSERT_FALSE(Card_less(e, f, led_card, SPADES));
    ASSERT_FALSE(Card_less(f, g, led_card, SPADES));
    ASSERT_FALSE(Card_less(g, h, led_card, SPADES));
}