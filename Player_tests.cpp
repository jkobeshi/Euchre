// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player* alice = Player_factory("Alice", "Simple");
    Player* Man = Player_factory("Man", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());
    ASSERT_EQUAL("Man", Man->get_name());
    ostringstream oss;
    oss << *alice;
    ASSERT_EQUAL(oss.str(), "Alice");
    oss.str("");
    oss << *Man;
    ASSERT_EQUAL(oss.str(), "Man");
    delete Man;
    delete alice;
}
static void add_cards(Player* player) {
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    player->add_card(c1);
    player->add_card(c2);
    player->add_card(c3);
    player->add_card(c4);
    player->add_card(c5);
}
TEST(test_add_play_cards) {
    Player* Robot = Player_factory("Robot", "Simple");
    Card c1 = Card();
    Card c2 = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card lead = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Robot->add_card(c1);
    ASSERT_EQUAL(Robot->play_card(lead, Card::SUIT_CLUBS), c1);
    add_cards(Robot);
    Robot->add_and_discard(c2);
    Card cor(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card output = Robot->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(output, cor);
    Card output2 = Robot->play_card(lead, Card::SUIT_SPADES);
    Card cor2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(output2, cor2);
    delete Robot;
}
TEST(test_play_cards_1) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card lead = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card out = p1->play_card(lead, Card::SUIT_SPADES);
    ASSERT_EQUAL(out, c2);
    delete p1;
}
TEST(test_play_cards_2) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card lead = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card out = p1->play_card(lead, Card::SUIT_SPADES);
    ASSERT_EQUAL(out, c3);
    delete p1;
}
TEST(test_make_Trump_1) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_TRUE(trump == Card::SUIT_SPADES);
    delete p1;
}
TEST(test_make_Trump_2) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_TRUE(trump == Card::SUIT_CLUBS);
    delete p1;
}
TEST(test_make_Trump_3) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, true, 2, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_TRUE(trump == Card::SUIT_CLUBS);
    delete p1;
}
TEST(test_make_Trump_4) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool make_trump = p1->make_trump(upcard, true, 1, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_make_Trump_5) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    string trump;
    Card disc(Card::RANK_ACE, Card::SUIT_CLUBS);
    p1->add_and_discard(disc);
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_make_Trump_6) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
static void add_cards_2(Player* p1) {
    Card c = Card();
    for (int i = 0; i < 5; i++) {
        p1->add_card(c);
    }
}
TEST(test_make_Trump_7) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards_2(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    string trump;
    bool make_trump = p1->make_trump(upcard, true, 1, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_make_Trump_8) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards_2(p1);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    string trump;
    bool make_trump = p1->make_trump(upcard, true, 2, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_EQUAL(trump, Suit_next(upcard.get_suit()));
    delete p1;
}
TEST(test_make_Trump_9) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_make_Trump_10) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_EQUAL(trump, Suit_next(upcard.get_suit()));
    delete p1;
}
TEST(test_make_Trump_11) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_make_Trump_12) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS)
    delete p1;
}
TEST(test_make_Trump_13) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, false, 2, trump);
    ASSERT_TRUE(!make_trump);
    delete p1;
}
TEST(test_lead_card_1) {
    Player* p1 = Player_factory("P1", "Simple");
    add_cards(p1);
    Card disc(Card::RANK_JACK, Card::SUIT_SPADES);
    p1->add_and_discard(disc);
    string trump = Card::SUIT_SPADES;
    Card out1 = p1->lead_card(trump);
    Card cor1 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card out2 = p1->lead_card(trump);
    Card cor2 = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card out3 = p1->lead_card(trump);
    Card cor3 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card out4 = p1->lead_card(trump);
    Card cor4 = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card out5 = p1->lead_card(trump);
    Card cor5 = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(out1, cor1);
    ASSERT_EQUAL(out2, cor2);
    ASSERT_EQUAL(out3, cor3);
    ASSERT_EQUAL(out4, cor4);
    ASSERT_EQUAL(out5, cor5);
    delete p1;
}
TEST(test_play) {
    Player* p3 = Player_factory("p3", "Simple");
    add_cards_2(p3);
    Card disc(Card::RANK_THREE, Card::SUIT_SPADES);
    Card lead1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card lead2(Card::RANK_ACE, Card::SUIT_SPADES);
    p3->add_and_discard(disc);
    p3->add_and_discard(disc);
    p3->add_and_discard(disc);
    Card two = Card();
    string trump = Card::SUIT_SPADES;
    Card out1 = p3->lead_card(trump);
    Card out2 = p3->play_card(lead2, trump);
    Card out3 = p3->play_card(lead1, trump);
    ASSERT_EQUAL(out1, disc);
    ASSERT_EQUAL(out2, disc);
    ASSERT_EQUAL(out3, two);
    delete p3;
}
TEST(test_add_discard) {
    Player* p1 = Player_factory("Jam", "Simple");
    string trump = Card::SUIT_SPADES;
    Card c = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c1 = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    p1->add_card(c);
    p1->add_and_discard(c1);
    Card out = p1->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(out, c);
    delete p1;
}
TEST(test_make_Trump_14) {
    Player* p1 = Player_factory("P1", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_SPADES);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    p1->add_card(c1);
    p1->add_card(c2);
    p1->add_card(c3);
    p1->add_card(c4);
    p1->add_card(c5);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    string trump;
    bool make_trump = p1->make_trump(upcard, true, 1, trump);
    ASSERT_TRUE(make_trump);
    ASSERT_EQUAL(trump, upcard.get_suit());
    p1->add_and_discard(upcard);
    Card c6 = p1->lead_card(trump);
    Card c7 = p1->lead_card(trump);
    Card c8 = p1->lead_card(trump);
    Card c9 = p1->lead_card(trump);
    Card c10 = p1->lead_card(trump);
    ASSERT_EQUAL(c4, c10);
    ASSERT_EQUAL(upcard, c9);
    ASSERT_EQUAL(c5, c8);
    ASSERT_EQUAL(c2, c7);
    ASSERT_EQUAL(c3, c6);

    delete p1;
}
TEST_MAIN()
