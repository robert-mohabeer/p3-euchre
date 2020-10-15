#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

	//ifstream fin(argv[1]);

	//Card a("King", "Hearts");

	//cout << a.get_rank() << " of ";
	//cout << a.get_suit() << endl;
	Pack pack;
	pack.shuffle();
	
	for (int x = 0; x < 24; x++)
	{
		Card b = pack.deal_one();
		cout << b.get_rank() << " of ";
		cout << b.get_suit() << endl;
	}

}