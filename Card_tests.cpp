// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST_MAIN()

// public tests
TEST (test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), TWO);
    ASSERT_EQUAL(two_spades.get_suit(), SPADES);

    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), THREE);
    ASSERT_EQUAL(three_spades.get_suit(), SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_extraction) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card b(JACK, SPADES);
    ASSERT_EQUAL(JACK, b.get_rank());
    ASSERT_EQUAL(SPADES,b.get_suit());

    Card a(NINE, CLUBS);
    ASSERT_EQUAL(NINE, a.get_rank());
    ASSERT_EQUAL(CLUBS, a.get_suit());
}

TEST(left_and_right_bowers) {
    Card left(JACK, DIAMONDS);
    Card right(JACK, HEARTS);
    ASSERT_TRUE(Card_less(left, right, HEARTS));

    Card left2(ACE, HEARTS);
    Card right2(JACK, HEARTS);
    ASSERT_TRUE(Card_less(left2, right2, HEARTS));

    Card left3(KING, SPADES);
    Card right3(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(left3, right3, HEARTS));

    
}

TEST(card_operators_base) {
    Card c1 = Card(JACK, DIAMONDS);
    Card c2 = Card(NINE, SPADES);
    ASSERT_TRUE(c1 > c2);
    ASSERT_TRUE(c1 >= c2);
    ASSERT_FALSE(c1 < c2);
    ASSERT_FALSE(c1 <= c2);
    ASSERT_TRUE(c1 != c2);
    ASSERT_FALSE(c1 == c2);
}

TEST(card_operators_same_rank) {
    Card c1 = Card(JACK, DIAMONDS);
    Card c2 = Card(JACK, CLUBS);
    ASSERT_TRUE(c1 > c2);
    ASSERT_TRUE(c1 >= c2);
    ASSERT_FALSE(c1 < c2);
    ASSERT_FALSE(c1 <= c2);
    ASSERT_TRUE(c1 != c2);
    ASSERT_FALSE(c1 == c2);
}

TEST(card_operators_same_card) {
    Card c1 = Card(JACK, DIAMONDS);
    ASSERT_FALSE(c1 > c1);
    ASSERT_TRUE(c1 >= c1);
    ASSERT_FALSE(c1 < c1);
    ASSERT_TRUE(c1 <= c1);
    ASSERT_FALSE(c1 != c1);
    ASSERT_TRUE(c1 == c1);
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

TEST(min_cards) {
    Card c1(NINE, SPADES);
    Card c2(NINE, CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, DIAMONDS));
}

TEST(get_suit_and_rank)
{
    Card c1(TWO, SPADES);
    Card c2(KING, CLUBS);
    Card c3(ACE, HEARTS);
    ASSERT_EQUAL(SPADES, c1.get_suit());
    ASSERT_EQUAL(CLUBS, c2.get_suit());
    ASSERT_EQUAL(HEARTS, c3.get_suit());
    ASSERT_EQUAL(TWO, c1.get_rank());
    ASSERT_EQUAL(KING, c2.get_rank());
    ASSERT_EQUAL(ACE, c3.get_rank());
}

TEST(card_input) {

}