#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

	static const int MAX_PLAYERS = 4;

	class Game {
	private:
		Pack pack;
		string toShuffle;
		const int pointsToWin;
		vector <Player *> players;
		int team1Score;
		int team2Score;
		int hand;
		int teamTrump;
		size_t dealerIndex;
		vector <Player*> partners1;
		vector <Player*> partners2;

	public:
		
		bool round1 = false;

		Game(char* input[])
			: toShuffle(string(input[2])), pointsToWin(atoi(input[3])), 
			team1Score(0), team2Score(0), hand(0), teamTrump(0), dealerIndex(0)
		{
			ifstream fin("pack.in");
			pack = Pack(fin);

			for (size_t x = 4; x < ((MAX_PLAYERS * 2) + 4); x += 2)
			{
				players.push_back(Player_factory(input[x], input[x + 1]));
			}
			partners1.push_back(players[0]);
			partners1.push_back(players[2]);
			partners2.push_back(players[1]);
			partners2.push_back(players[3]);
		}

		void playHand()
		{
			string trump = "";
			if (toShuffle == "shuffle")
			{
				pack.shuffle();
			}
			cout << *players[dealerIndex] << " deals" << endl;
			dealToPlayers();

			Card upcard = pack.deal_one();
			cout << upcard << " turned up" << endl;
			trump = makingTrump(upcard);
			if (round1 == true)
			{
				players[dealerIndex]->add_and_discard(upcard);
			}
			cout << endl;
			trickTaking(trump);
			cout << *players[0] << " and " << *players[2] << " have " << team1Score
				<< " points" << endl;
			cout << *players[1] << " and " << *players[3] << " have " << team2Score
				<< " points" << endl;
			cout << endl;
			pack.reset();
			round1 = false;
			if (dealerIndex == 3)
			{
				dealerIndex = 0;
			}
			else
			{
				++dealerIndex;
			}
			++hand;
		}

		string makingTrump(const Card& upcard)
		{
			string trump = "";
			for (int y = 1; y < 3; y++)
			{
				for (size_t x = dealerIndex + 1; x < dealerIndex + 5; x++)
				{
					if (players[x % 4]->make_trump(upcard, (x % 4 == dealerIndex), y, trump))
					{
						if (x % 4 == 0 || x % 4 == 2)
						{
							teamTrump = 1;
						}
						else if (x % 4 == 1 || x % 4 == 3)
						{
							teamTrump = 2;
						}
						if (y == 1)
						{
							round1 = true;
						}
						else
						{
							round1 = false;
						}
						cout << *players[x % 4] << " orders up " << trump << endl;
						return trump;
					}
					else
					{
						cout << *players[x % 4] << " passes" << endl;
					}
				}
			}
			return trump;
		}

		void trickTaking(const string& trump)
		{
			int tricks1 = 0;
			int tricks2 = 0;
			size_t winnerIndex = dealerIndex + 1;
			Card led;
			Card played;
			vector <Card> cardsToCompare(4, led);
			for (int y = 0; y < 5; y++)
			{
				for (size_t x = winnerIndex; x < winnerIndex + 4; x++)
				{
					if (x == winnerIndex)
					{
						led = players[x % 4]->lead_card(trump);
						cout << led << " led by " << *players[x % 4] << endl;
						cardsToCompare[x % 4] = led;
					}
					else
					{
						played = players[x % 4]->play_card(led, trump);
						cout <<  played << " played by " << *players[x % 4] << endl;
						cardsToCompare[x % 4] = played;
					}
				}
				winnerIndex = returnWinner(cardsToCompare , led, trump);
				cout << *players[winnerIndex] << " takes the trick" << endl;
				cout << endl;
				if (winnerIndex == 0 || winnerIndex == 2)
				{
					tricks1++;
				}
				else if (winnerIndex == 1 || winnerIndex == 3)
				{
					tricks2++;
				}
			}
			pointAdder(tricks1, tricks2);
		}

		void pointAdder(const int tricks1, const int tricks2)
		{
			assert(tricks1 + tricks2 == 5);
			if (tricks1 > tricks2)
			{
				cout << *players[0] << " and " << *players[2]
					<< " win the hand" << endl;
				if (teamTrump == 1)
				{
					if (tricks1 == 5)
					{
						cout << "march! " << endl;
						team1Score += 2;
					}
					else
					{
						team1Score++;
					}
				}
				else
				{
					cout << "euchred!" << endl;
					team1Score += 2;
				}
			}
			else if (tricks1 < tricks2)
			{
				cout << *players[1] << " and " << *players[3]
					<< " win the hand" << endl;
				if (teamTrump == 2)
				{
					if (tricks2 == 5)
					{
						cout << "march!" << endl;
						team2Score += 2;
					}
					else
					{
						team2Score++;
					}
				}
				else
				{
					cout << "euchred!" << endl;
					team2Score += 2;
				}
			}
		}

		int returnWinner(vector <Card> cards, const Card led, const string trump)
		{
			Card highest = cards[0];
			int index = 0;
			for (size_t x = 0; x < cards.size(); x++)
			{
				if (Card_less(highest, cards[x], led, trump))
				{
					highest = cards[x];
					index = x;
				}
			}
			return index;
		}

		void dealToPlayers()
		{
			for (size_t x = dealerIndex + 1; x < dealerIndex + 5; x++)
			{
				if ((x - dealerIndex) % 2 == 1)
				{
					for (int y = 0; y < 3; y++)
					{
						players[x % 4]->add_card(pack.deal_one());
					}
				}
				else
				{
					for (int y = 0; y < 2; y++)
					{
						players[x % 4]->add_card(pack.deal_one());
					}
				}
			}
			for (size_t x = dealerIndex + 1; x < dealerIndex + 5; x++)
			{
				if ((x - dealerIndex) % 2 == 1)
				{
					for (int y = 0; y < 2; y++)
					{
						players[x % 4]->add_card(pack.deal_one());
					}
				}
				else
				{
					for (int y = 0; y < 3; y++)
					{
						players[x % 4]->add_card(pack.deal_one());
					}
				}
			}
		}

		int getTeamScore(int team) const
		{
			assert(team == 1 || team == 2);
			if (team == 1)
			{
				return team1Score;
			}
			else
			{
				return team2Score;
			}
		}

		int getGoal() const
		{
			assert(pointsToWin >= 1);
			return pointsToWin;
		}

		int getHand() const
		{
			assert(hand >= 0);
			return hand;
		}

		vector <Player*> getPlayers() const
		{
			return players;
		}

	};

	for (int x = 0; x < argc; x++)
	{
		cout << argv[x] << " ";
	}
	cout << endl;

	Game theGame = Game(argv);

	while (theGame.getTeamScore(1) < theGame.getGoal() 
		&& theGame.getTeamScore(2) < theGame.getGoal())
	{
		cout << "Hand " << theGame.getHand() << endl;
		theGame.playHand();
	}

	if (theGame.getTeamScore(1) > theGame.getTeamScore(2))
	{
		cout << *theGame.getPlayers()[0] << " and " 
			<< *theGame.getPlayers()[2] << " win!" << endl;
	}
	else
	{
		cout << *theGame.getPlayers()[1] << " and " 
			<< *theGame.getPlayers()[3] << " win!" << endl;
	}


}