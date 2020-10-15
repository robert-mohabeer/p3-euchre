// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

bool isValid(const string &a, const char* const arr[], int size, int start)
{
	for (int x = start; x < size; x++)
	{
		if (a == arr[x])
		{
			return true;
		}
	}
	return false;
}

string Suit_next(const string &suit)
{
	assert(isValid(suit, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	if (suit == Card::SUIT_SPADES)
	{
		return Card::SUIT_CLUBS;
	}
	else if (suit == Card::SUIT_HEARTS)
	{
		return Card::SUIT_DIAMONDS;
	}
	else if (suit == Card::SUIT_CLUBS)
	{
		return Card::SUIT_SPADES;
	}
	return Card::SUIT_HEARTS;
}

Card::Card()
	:rank(RANK_TWO), suit(SUIT_SPADES) {
}

Card::Card(const string &rank_in, const string &suit_in)
	:rank(rank_in), suit(suit_in) {
	assert(isValid(rank, RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));
	assert(isValid(suit, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
}

string Card::get_rank() const
{
	assert(isValid(rank, RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));
	return rank;
}

string Card::get_suit() const
{
	assert(isValid(suit, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	return suit;
}

std::string Card::get_suit(const std::string& trump) const
{
	assert(isValid(suit, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	if (this->is_left_bower(trump))
	{
		return trump;
	}
	else
	{
		return suit;
	}
}

bool Card::is_face() const
{
	return isValid(rank, RANK_NAMES_BY_WEIGHT, NUM_RANKS, 9);
}

bool Card::is_right_bower(const std::string& trump) const
{
	assert(isValid(trump, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	if (suit == trump && rank == Card::RANK_JACK)
	{
		return true;
	}
	return false;
}

bool Card::is_left_bower(const std::string& trump) const
{
	assert(isValid(trump, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	if (suit == Suit_next(trump) && rank == Card::RANK_JACK)
	{
		return true;
	}
	return false;
}

bool Card::is_trump(const std::string& trump) const
{
	assert(isValid(trump, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	if (suit == trump || this->is_left_bower(trump))
	{
		return true;
	}
	return false;
}

bool operator<(const Card& lhs, const Card& rhs)
{
	assert(isValid(lhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(lhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));
	assert(isValid(rhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(rhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));

	int power1 = 0;
	int power2 = 0;
	for (int x = 0; x < NUM_RANKS; x++)
	{
		if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[x])
		{
			power1 = x;
		}
		if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[x])
		{
			power2 = x;
		}
	}

	if (power1 != power2)
	{
		if (power1 < power2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		power1 = 0;
		power2 = 0;
		for (int x = 0; x < NUM_SUITS; x++)
		{
			if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[x])
			{
				power1 = x;
			}
			if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[x])
			{
				power2 = x;
			}
		}
		if (power1 < power2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool operator>(const Card& lhs, const Card& rhs)
{
	assert(isValid(lhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(lhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));
	assert(isValid(rhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(rhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));

	if (lhs == rhs || lhs < rhs)
	{
		return false;
	}
	return true;
}

bool operator==(const Card& lhs, const Card& rhs)
{
	assert(isValid(lhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(lhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));
	assert(isValid(rhs.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(rhs.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));

	if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit())
	{
		return true;
	}
	return false;
}

bool operator!=(const Card& lhs, const Card& rhs)
{
	return (!(lhs == rhs));
}

ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.get_rank() << " of " << card.get_suit();
	return os;
}

bool Card_less(const Card& a, const Card& b, const std::string& trump)
{
	assert(isValid(trump, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));

	if (a == b)
	{
		return false;
	}
	else if (a.is_right_bower(trump))
	{
		return false;
	}
	else if (b.is_right_bower(trump))
	{
		return true;
	}
	else if (a.is_left_bower(trump))
	{
		return false;
	}
	else if (b.is_left_bower(trump))
	{
		return true;
	}
	else
	{
		if (a.get_suit(trump) == b.get_suit(trump))
		{
			return a < b;
		}
		else if (b.get_suit(trump) == trump)
		{
			return true;
		}
		else if (a.get_suit(trump) == trump)
		{
			return false;
		}
		else
		{
			return a < b;
		}
	}
}

bool Card_less(const Card& a, const Card& b, const Card& led_card,
	const std::string& trump)
{
	assert(isValid(trump, SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(led_card.get_suit(), SUIT_NAMES_BY_WEIGHT, NUM_SUITS, 0));
	assert(isValid(led_card.get_rank(), RANK_NAMES_BY_WEIGHT, NUM_RANKS, 0));

	return false;
}

