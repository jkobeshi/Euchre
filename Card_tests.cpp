// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_get_func) {
    Card two_spades = Card();
    Card c3(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(two_spades, c3)
    string trump = Card::SUIT_DIAMONDS;
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(trump, c1.get_suit(trump));
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(trump));
}
TEST(test_operators) {
    Card c1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(c2 < c1);
    ASSERT_TRUE(c2 <= c1);
    ASSERT_FALSE(c2 > c1);
    ASSERT_FALSE(c2 >= c1);
    ASSERT_FALSE(c1 == c2);
    ASSERT_TRUE(c1 != c2);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}
TEST(test_suit_next_func) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}
TEST(test_is_face) {
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c1.is_face());
    ASSERT_TRUE(c2.is_face());
    ASSERT_TRUE(c3.is_face());
    ASSERT_TRUE(c4.is_face());
    ASSERT_TRUE(c1 > c2);
    ASSERT_TRUE(c3 < c2);
    ASSERT_TRUE(c3 >= c4);
    ASSERT_TRUE(c4 <= c1);
}
TEST(test_Card_less_func) {
    string trump = Card::SUIT_SPADES;
    Card right_bow = Card(Card::RANK_JACK, trump);
    Card left_bow = Card(Card::RANK_JACK, Suit_next(trump));
    Card c1(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c4(Card::RANK_FOUR, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(left_bow.is_trump(trump));
    ASSERT_TRUE(left_bow.is_left_bower(trump));
    ASSERT_TRUE(right_bow.is_right_bower(trump));
    ASSERT_TRUE(right_bow.is_face());
    ASSERT_TRUE(left_bow.is_face());

    ASSERT_TRUE(Card_less(left_bow, right_bow, trump));
    ASSERT_FALSE(Card_less(right_bow, left_bow, trump));
    ASSERT_TRUE(Card_less(c2, left_bow, trump));
    ASSERT_TRUE(Card_less(c2, c3, trump));
    ASSERT_TRUE(Card_less(c3, c4, trump));
    ASSERT_TRUE(Card_less(c2, c1, trump));
    ASSERT_TRUE(Card_less(c1, c4, trump));

    Card lead(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(Card_less(left_bow, right_bow, lead, trump));
    ASSERT_FALSE(Card_less(right_bow, left_bow, lead, trump));
    ASSERT_TRUE(Card_less(c2, left_bow, lead, trump));
    ASSERT_TRUE(Card_less(c5, left_bow, lead, trump));
    ASSERT_TRUE(Card_less(c2, c3, lead, trump));
    ASSERT_TRUE(Card_less(c3, c4, lead ,trump));
    ASSERT_FALSE(Card_less(c2, c1, lead, trump));
    ASSERT_TRUE(Card_less(c1, c4, lead, trump));
    ASSERT_TRUE(Card_less(c5, c4, lead, trump));
    ASSERT_TRUE(Card_less(lead, c3, lead, trump));
}
TEST(test_card_insertion) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ostringstream oss;
    oss << two_spades;
    ASSERT_EQUAL(oss.str(), "Two of Spades");
}
TEST(test_random) {
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(c2, c1, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c2, c3, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c3, c1, Card::SUIT_SPADES));
}


// Add more test cases here

TEST_MAIN()
