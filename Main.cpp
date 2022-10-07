#include <iostream>
#include "Player.h"
#include "UserInterface.h"
using namespace std;

int main() {
	UserInterface Game;
	cout << Game.getStartingDescription() << endl;
	return 0;
}