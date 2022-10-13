// Version 1.03

#include <iostream>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
using namespace std;

int main() {
	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface game;
	//cout << Game.getStartingDescription() << endl;

	// Create the player object of the main character in the game. This player will
	// be the one playing through the entirety of the game, fighting bosses, finding items, etc.
	Player mainCharacter;

	// Create the starting steps. This will be the first area the player is dropped in
	// at the start of the game.
	Room startingSteps("Starting Steps", "The starting steps lead up to a large and tall mansion in front of you\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible\n"
									     "Before you is a door. You enter it.\n");

	// Create the Devil who will be the main villain of the game. He will also be the one
	// to give the player info on how to play the game.
	Monster devil("Devil", "The devil is a tall, red, and overwhelmingly handsome man", "");
	devil.setDialogOpening("Welcome to my mansion!!\n"
						   "My name is the Devil and you have died in real life.\n"
						   "This has resulted in you being sent down to my mansion to play a little game.\n"
						   "-----Enter better description of how to play the game-----\n");

	cout << game.getStartingDescription() << endl;
	cout << startingSteps.getRoomDescription() << endl;
	cout << devil.getDialogOpening();
	return 0;
}