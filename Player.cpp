#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Card.h"
#include "Player.h"

using namespace std;

class Simple : public Player {
private:
	const string name;
	vector <Card> hand;

public:
	Simple(string name_in)
		: name(name_in) {}

	const void print_hand()
	{
		for (size_t x = 0; x < hand.size(); x++)
		{
			cout << hand[x] << endl;
		}
	}

	const std::string& get_name() const
	{
		return name;
	}

	void add_card(const Card& c)
	{
		assert(hand.size() < MAX_HAND_SIZE);
		hand.push_back(c);
	}

	bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const
	{
		assert(round == 1 || round == 2);

		int countFace = 0;
		if (round == 1)
		{
			for (size_t x = 0; x < hand.size(); x++)
			{
				if (hand[x].is_face() && hand[x].is_trump(upcard.get_suit()))
				{
					countFace++;
				}
			}
			if (countFace >= 2)
			{
				order_up_suit = upcard.get_suit();
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			for (size_t x = 0; x < hand.size(); x++)
			{
				if (hand[x].is_face() && hand[x].is_trump(Suit_next(upcard.get_suit())))
				{
					countFace++;
				}
			}
			if (countFace >= 1 || is_dealer)
			{
				order_up_suit = Suit_next(upcard.get_suit());
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void add_and_discard(const Card& upcard)
	{
		assert(hand.size() > 0);
		hand.push_back(upcard);
		Card discard = hand[0];
		int record = 0;

		for (size_t x = 0; x < hand.size(); x++)
		{
			if (Card_less(hand[x], discard, upcard.get_suit()))
			{
				discard = hand[x];
				record = x;
			}
		}
		hand.erase(hand.begin() + record);
	}

	Card lead_card(const std::string& trump)
	{
		assert(hand.size() >= 1);

		bool allTrump = true;
		int indexOfLead = 0;
		Card highest;

		for (size_t x = 0; x < hand.size(); x++)
		{
			if (!hand[x].is_trump(trump))
			{
				allTrump = false;
			}
		}

		if (allTrump)
		{
			for (size_t x = 0; x < hand.size(); x++)
			{
				if (Card_less(highest, hand[x], trump))
				{
					highest = hand[x];
					indexOfLead = x;
				}
			}
		}
		else
		{
			highest = hand[indexOfLead];
			while (highest.is_trump(trump))
			{
				indexOfLead++;
				highest = hand[indexOfLead];
			}
			for (size_t x = 0; x < hand.size(); x++)
			{
				if (highest < hand[x] && !hand[x].is_trump(trump))
				{
					highest = hand[x];
					indexOfLead = x;
				}
			}
		}
		hand.erase(hand.begin()+ indexOfLead);
		return highest;
	}

	Card play_card(const Card& led_card, const std::string& trump)
	{
		assert(hand.size() >= 1);
		int indexOfPlay = 0;
		Card play;
		bool canFollow = false;

		for (size_t x = 0; x < hand.size(); x++)
		{
			if (hand[x].get_suit(trump) == led_card.get_suit(trump))
			{
				canFollow = true;
			}
		}
		for (size_t x = 0; x < hand.size(); x++)
		{
			if (canFollow && hand[x].get_suit(trump) == led_card.get_suit(trump) && 
				(hand[x] > play || hand[x].is_right_bower(trump) || hand[x].is_left_bower(trump)))
			{
				if ((!play.is_right_bower(trump) && !play.is_left_bower(trump)) 
					|| (play.is_left_bower(trump) && hand[x].is_right_bower(trump)))
				{
					play = hand[x];
					indexOfPlay = x;
				}
			}
		}
		if(!canFollow)
		{
			play = hand[0];
			for (size_t x = 0; x < hand.size(); x++)
			{
				if (Card_less(hand[x], play, trump))
				{
					play = hand[x];
					indexOfPlay = x;
				}
			}
		}
		hand.erase(hand.begin() + indexOfPlay);
		return play;
	}
};

class Human : public Player {
private:
	const string name;
	vector <Card> hand;

public:
	Human(string name_in)
		: name(name_in) {}

	const void print_hand(vector <Card> &copy) const
	{
		assert(copy.size() > 0);
		std::sort(copy.begin(), copy.end());
		for (size_t x = 0; x < copy.size(); x++)
		{
			cout << "Human player " << *this << "'s hand: [" << x << "] " << copy[x] << endl;
		}
	}

	const std::string& get_name() const
	{
		return name;
	}

	void add_card(const Card& c)
	{
		assert(hand.size() < MAX_HAND_SIZE);
		hand.push_back(c);
	}

	bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const
	{
		assert(round == 1 || round == 2);
		vector <Card> copy = hand;
		string input;
		this->print_hand(copy);
		cout << "Human player " << *this << ", please enter a suit, or \"pass\":" << endl;
		cin >> input;
		if (input == "pass")
		{
			return false;
		}
		else
		{
			order_up_suit = input;
			return true;
		}
	}

	void add_and_discard(const Card& upcard)
	{
		assert(hand.size() > 0);
		int input;
		this->print_hand(hand);
		cout << "Discard upcard: [-1]" << endl;
		cout << "Human player " << *this << ", please select a card to discard:" << endl;
		cin >> input;
		if (input != -1)
		{
			hand.push_back(upcard);
			hand.erase(hand.begin() + input);
		}
	}

	Card lead_card(const std::string& trump)
	{
		assert(hand.size() >= 1);
		int input;
		Card lead;
		this->print_hand(hand);
		cout << "Human player " << *this << ", please select a card:" << endl;
		cin >> input;
		lead = hand[input];
		hand.erase(hand.begin() + input);
		return lead;
	}

	Card play_card(const Card& led_card, const std::string& trump)
	{
		assert(hand.size() >= 1);
		return this->lead_card(trump);
	}
};

Player* Player_factory(const std::string& name, const std::string& strategy)
{
	assert(strategy == "Human" || strategy == "Simple");
	if (strategy == "Simple")
	{
		return new Simple(name);
	}
	else
	{
		return new Human(name);
	}
}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
	os << p.get_name();
	return os;
}

