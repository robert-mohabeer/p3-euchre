#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Pack.h"
#include "Card.h"

using namespace std;

Pack::Pack(): next(0)
{
	int cardNum = 0;
	for (int suits = 0; suits < NUM_SUITS; suits++)
	{
		for (int ranks = 7; ranks < NUM_RANKS; ranks++)
		{
			cards[cardNum++] = Card(RANK_NAMES_BY_WEIGHT[ranks], SUIT_NAMES_BY_WEIGHT[suits]);
		}
	}
	assert(cardNum == PACK_SIZE);
}

Pack::Pack(std::istream& pack_input) : next(0)
{
	vector<string> words;
	string rank, of, suit;
	int cardNum = 0;
	while (pack_input >> rank >> of >> suit)
	{
		cards[cardNum++] = Card(rank, suit);
	}
	assert(cardNum == PACK_SIZE);
}

Card Pack::deal_one()
{
	assert(!empty());
	return cards[next++];
}

void Pack::reset()
{
	next = 0;
}

void Pack::shuffle()
{
	Card copy[24];
	int adder;
	int subtract;
	for (int times = 0; times < 7; times++)
	{
		adder = 12;
		subtract = 1;

		for (int x = 0; x < 24; x++)
		{
			copy[x] = cards[x];
		}

		for (int y = 0; y < 24; y++)
		{
			if (y % 2 == 0)
			{
				cards[y] = copy[y + adder];
				--adder;
			}
			else
			{
				cards[y] = copy[y - subtract];
				++subtract;
			}
		}
	}
}

bool Pack::empty() const
{
	if (next >= 24)
	{
		return true;
	}
	else
		return false;
}

