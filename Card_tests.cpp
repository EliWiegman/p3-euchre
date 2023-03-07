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
