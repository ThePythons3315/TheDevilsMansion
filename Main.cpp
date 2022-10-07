#include <iostream>
#include "Player.h"
using namespace std;

int main() {
	cout << "The Devil's Mansion!!" << endl;
	Player player1;
	player1.setName("Jason Shupper");
	cout << "The name of the player is " << player1.getName() << endl;
	return 0;
}