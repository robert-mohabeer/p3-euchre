// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(return_names) {
    Player* bobby = Player_factory("Bobby", "Simple");
    Player* chris = Player_factory("cHris", "Human");
    ASSERT_EQUAL("Bobby", bobby->get_name());
    ASSERT_EQUAL("cHris", chris->get_name());

    delete bobby;
    delete chris;
}

TEST(print_players)
{
    Player* bobby = Player_factory("Bobby", "Simple");
    Player* chris = Player_factory("Chris", "Human");
    ostringstream oss;
    oss << *bobby;
    ASSERT_EQUAL(oss.str(), "Bobby");
    oss.str("");
    oss << *chris;
    ASSERT_EQUAL(oss.str(), "Chris");
}

TEST(simple_player_test_make_trump)
{
    Player* alice = Player_factory("Alice", "Simple");
    string suit = Card::SUIT_CLUBS;
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    Card upcard(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    alice->add_card(c);
    alice->add_card(d);
    ASSERT_TRUE(alice->make_trump(upcard, true, 1, suit));
    ASSERT_EQUAL(suit, Card::SUIT_HEARTS);
    delete alice;
}

TEST(simple_player_lead)
{
    Player* alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    Card e(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card f(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card g(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card upcard(Card::RANK_NINE, Card::SUIT_HEARTS);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_card(f);
    alice->add_card(g);
    ASSERT_EQUAL(alice->lead_card(upcard.get_suit()), c);
    delete alice;
}

TEST(simple_player_lead2)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card nineofclubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card queenofclubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card jackofhearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    alice->add_card(nineofclubs);
    alice->add_card(queenofclubs);
    alice->add_card(queenofhearts);
    alice->add_card(jackofhearts);
    ASSERT_EQUAL(alice->lead_card(trump), queenofclubs);
    delete alice;
}

TEST(simple_player_lead3)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card nineofclubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card queenofclubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card queenofhearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card jackofhearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    alice->add_card(nineofclubs);
    alice->add_card(queenofclubs);
    alice->add_card(queenofhearts);
    alice->add_card(jackofhearts);
    ASSERT_EQUAL(alice->lead_card(trump), queenofclubs);
    delete alice;
}

TEST(simple_player_play)
{
    Player* alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    Card e(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card f(Card::RANK_TEN, Card::SUIT_SPADES);
    Card g(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ledcard(Card::RANK_ACE, Card::SUIT_SPADES);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_card(f);
    alice->add_card(g);
    ASSERT_EQUAL(alice->play_card(ledcard, Card::SUIT_HEARTS), f);
    delete alice;
}

TEST(simple_player_play2)
{
    Player* alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card f(Card::RANK_TEN, Card::SUIT_SPADES);
    Card g(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ledcard(Card::RANK_ACE, Card::SUIT_HEARTS);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_card(f);
    alice->add_card(g);
    ASSERT_EQUAL(alice->play_card(ledcard, Card::SUIT_CLUBS), c);
    delete alice;
}

TEST(simple_player_play3)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ledcard(Card::RANK_JACK, Card::SUIT_HEARTS);
    alice->add_card(ace_spades);
    alice->add_card(ace_clubs);
    alice->add_card(ace_diamonds);
    alice->add_card(ace_hearts);
    ASSERT_EQUAL(alice->play_card(ledcard, trump), ace_diamonds);
    delete alice;
}

TEST(simple_player_add_and_discard)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card queen_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card upcard(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    alice->add_card(jack_hearts);
    alice->add_card(queen_clubs);

    alice->add_and_discard(upcard);

    ASSERT_EQUAL(alice->lead_card(trump), upcard);
    delete alice;
}

TEST(simple_making)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card upcard(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    alice->add_card(queen_hearts);
    alice->add_card(ten_clubs);
    alice->add_card(ace_spades);

    ASSERT_FALSE(alice->make_trump(upcard, false, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    delete alice;
}

TEST(simple_making2)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card upcard(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    alice->add_card(queen_diamonds);
    alice->add_card(king_diamonds);
    alice->add_card(ace_spades);
    alice->add_card(ten_clubs);
    alice->add_card(jack_spades);

    ASSERT_TRUE(alice->make_trump(upcard, false, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    delete alice;
}

TEST(simple_making3)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_CLUBS;
    Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card upcard(Card::RANK_JACK, Card::SUIT_CLUBS);
    alice->add_card(king_clubs);
    alice->add_card(nine_diamonds);
    alice->add_card(ace_hearts);
    alice->add_card(ten_clubs);
    alice->add_card(jack_spades);

    ASSERT_TRUE(alice->make_trump(upcard, true, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    delete alice;
}

TEST(screw_the_dealer)
{
    Player* alice = Player_factory("Alice", "Simple");
    string trump = Card::SUIT_CLUBS;
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card upcard(Card::RANK_JACK, Card::SUIT_CLUBS);
    alice->add_card(king_hearts);
    alice->add_card(nine_diamonds);
    alice->add_card(ten_diamonds);

    ASSERT_FALSE(alice->make_trump(upcard, false, 2, trump));
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    ASSERT_TRUE(alice->make_trump(upcard, true, 2, trump));//screws the dealer
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    delete alice;
}

TEST(complex_test)
{
    Player* alice = Player_factory("Alice", "Simple");
    Player* bill = Player_factory("bill", "Simple");
    string trump;
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card upcard_nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);

    alice->add_card(king_spades);
    bill->add_card(nine_diamonds);
    alice->add_card(ace_spades);
    bill->add_card(ten_clubs);
    alice->add_card(jack_clubs);
    bill->add_card(jack_spades);
    ASSERT_TRUE(alice->make_trump(upcard_nine_spades, false, 1, trump));

    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    Card led = alice->lead_card(trump);
    ASSERT_EQUAL(led, jack_clubs);
    Card play = bill->play_card(led, trump);
    ASSERT_EQUAL(play, jack_spades);
}


// Add more tests here

TEST_MAIN()
