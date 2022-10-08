// Version 1.01

#include <iostream>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
using namespace std;

int main() {
	UserInterface Game;
	cout << Game.getStartingDescription() << endl;
	Room room;
	room.setName("Starting Room");
	cout << room.getName() << endl;
	return 0;
}