// Version 1.02

#include <iostream>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
using namespace std;

int main() {
	// Create a game instance and output the starting description for the game
	UserInterface Game;
	cout << Game.getStartingDescription() << endl;

	// Create the starting room for the game
	Room room("Starting Room", "You have entered the starting room.");
	cout << room.getName() << "\n" << room.getRoomDescription() << endl << endl;

	// Create a Monster object -- Will be the Devil and he will explain the game
	Monster Devil("Devil", "Tall individual standing at 6 ft. Skin is a dark maroon red with a tint of black.");
	cout << "Hello there I am the " << Devil.getName() << endl << "The devil is a " << Devil.getDescription() << endl;

	return 0;
}