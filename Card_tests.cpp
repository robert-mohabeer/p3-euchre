// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_face) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card d(Card::RANK_TWO, Card::SUIT_CLUBS);
    Card e(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_face());
    ASSERT_FALSE(d.is_face());
    ASSERT_FALSE(e.is_face());
    ASSERT_TRUE(f.is_face());
}

TEST(get_suit_with_trump)
{
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card f(Card::RANK_JACK, Card::SUIT_SPADES);
    Card a(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, f.get_suit(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit(Card::SUIT_HEARTS));
}

TEST(bowers)
{
    string trump = Card::SUIT_DIAMONDS;
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card e(Card::RANK_JACK, Card::SUIT_SPADES);
    Card f(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_FALSE(a.is_right_bower(trump) || a.is_left_bower(trump));

    ASSERT_FALSE(b.is_right_bower(trump) || b.is_left_bower(trump));

    ASSERT_TRUE(c.is_right_bower(trump));
    ASSERT_FALSE(c.is_left_bower(trump));

    ASSERT_FALSE(d.is_right_bower(trump));
    ASSERT_TRUE(d.is_left_bower(trump));

    ASSERT_FALSE(e.is_right_bower(trump) || e.is_left_bower(trump));
    ASSERT_FALSE(f.is_right_bower(trump) || f.is_left_bower(trump));
}

TEST(trump_tests)
{
    string trump = Card::SUIT_CLUBS;

    Card a(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card b(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(a.is_trump(trump));
    ASSERT_FALSE(b.is_trump(trump));
    ASSERT_TRUE(c.is_trump(trump));
}

TEST(less_then)
{
    Card a(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card b(Card::RANK_TEN, Card::SUIT_HEARTS);

    ASSERT_TRUE(b < a);

    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card e;
    ASSERT_TRUE(d < c);
    ASSERT_TRUE(e < d);
    ASSERT_FALSE(c < e);
    ASSERT_FALSE(c < d);
}

TEST(greater_then)
{
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_TEN, Card::SUIT_HEARTS);

    ASSERT_TRUE(a > b);

    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card e;

    ASSERT_FALSE(e > d || e > c);
    ASSERT_TRUE(c > d);
}

TEST(is_equal)
{
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_TEN, Card::SUIT_CLUBS);

    ASSERT_FALSE(a == b);

    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);

    ASSERT_FALSE(c == d);

    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(e == f);
}

TEST(not_equal)
{
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_TEN, Card::SUIT_CLUBS);

    ASSERT_TRUE(a != b);

    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);

    ASSERT_TRUE(c != d);

    Card e(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    ASSERT_FALSE(e != f);
}

TEST(next_suit)
{
    Card a(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(a.get_suit()), Card::SUIT_HEARTS);

    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_NOT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Suit_next(Card::SUIT_CLUBS)), Card::SUIT_CLUBS);// does next twice, so returns original suit
}

TEST(printer)
{
    Card a(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ostringstream oss;
    oss << a;
    ASSERT_EQUAL(oss.str(), "Nine of Diamonds");

    Card b("King", "Hearts");
    ostringstream oss2;
    oss2 << b;
    ASSERT_EQUAL(oss2.str(), "King of Hearts");
}

TEST(Card_less_test)
{
    Card a(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card b(Card::RANK_TEN, Card::SUIT_HEARTS);

    ASSERT_TRUE(Card_less(b, a, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(a, b, Card::SUIT_HEARTS));

    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);

    ASSERT_FALSE(Card_less(c, d, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(c, d, Card::SUIT_HEARTS));

    Card e(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card f(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card g(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    
    ASSERT_TRUE(Card_less(e, f, Card::SUIT_DIAMONDS));//Jack of Hearts becomes left bower
    ASSERT_TRUE(Card_less(g, f, Card::SUIT_HEARTS));//Jack of Hearts becomes right bower, diamonds becomes left
    ASSERT_TRUE(Card_less(e, g, Card::SUIT_HEARTS));//Jack of Diamonds left bower, stronger than Ace of Clubs

    Card h(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card i(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(h, i, Card::SUIT_CLUBS));
}

// Add more test cases here

TEST_MAIN()
