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

TEST(default_card) {
    Card c1(TWO, SPADES);
    Card c2(KING, CLUBS);
    ASSERT_TRUE(Card_less(c1, c2, SPADES));
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
