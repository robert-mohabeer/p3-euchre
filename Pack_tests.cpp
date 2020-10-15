// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    Card sec = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    ASSERT_EQUAL(Card::RANK_TEN, sec.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, sec.get_suit());
}

TEST(reset) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());//creates the first card in the pack (Nine of Spades)

    for (int x = 0; x < 18; x++)//Goes through an arbitrary number of cards (called deal_one() rather than simply next++ to test deal_one() function and avoid effecting private variables)
    {
        Card more = pack.deal_one();
    }
    Card more = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, more.get_rank());//the card created after the loop is the Ten of Diamonds
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, more.get_suit());

    pack.reset();//resets the pack, meaning the next card dealt should be the first (Nine of Spades)
    Card again = pack.deal_one();
    ASSERT_EQUAL(again.get_rank(), first.get_rank());
    ASSERT_EQUAL(again.get_suit(), first.get_suit());
}

TEST(both_cstr) {

    ifstream fin("pack.in");
    Pack pack;//creates a pack from default constructor
    Pack pack2(fin);//creates a pack from .in file
    for (int x = 0; x < 24; x++)//takes the next card from both packs and makes sure they are the same rank and suit
    {
        Card from_pack = pack.deal_one();
        Card from_pack2 = pack2.deal_one();

        ASSERT_EQUAL(from_pack.get_rank(), from_pack2.get_rank());
        ASSERT_EQUAL(from_pack.get_suit(), from_pack2.get_suit())
    }//will only return true if each card is the same
}

TEST(empty) {

    Card a;
    Pack pack;//creates a pack from default constructor
    for (int x = 0; x < 24; x++)//deals each card in deck
    {
        ASSERT_FALSE(pack.empty())//will check before each deal if the pack is empty
        a = pack.deal_one();
    }
    ASSERT_EQUAL(a.get_rank(), Card::RANK_ACE);//makes sure the last card is the Ace of Diamonds (last card from default constructor)
    ASSERT_EQUAL(a.get_suit(), Card::SUIT_DIAMONDS);
    ASSERT_TRUE(pack.empty());//should be empty at the very end
    
}
// Add more tests here

TEST_MAIN()
