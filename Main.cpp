// Version 1.08

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
using namespace std;

// Definitions of functions -- initialized below
bool validateInput(vector<string>& vect, string sentence);
void switchRoom(Room currentRoom, Room newRoom);

int main() {
	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all the variables and objects that will be needed throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Loop variable that starts off as true. While the variable is true the mainloop will
	// run the game and continuoulsy ask for user input.
	bool mainLoop = true;
	string input = "";
	vector <string> keyWords = { "q", "jason shupper", "move", "back", "yes"};
	//vector<Room> rooms;

	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface ui;

	// Create the starting steps. This will be the first area the player is dropped in
	// at the start of the game.
	Room startingSteps("Starting Steps", "You are currently at the starting steps.\n"
										 "The starting steps lead up to a large and tall mansion in front of you\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible\n"
									     "Before you is a door.");

	// Create the starting room. This is the 2nd location that the user can go to.
	// This room will come after the starting steps and will house the devil.
	// In this room the devil will explain the rules of the game to you.
	Room startingRoom("Starting Room",  "\nYou are now in the starting room.\n"
										"The starting room is a large open dark room with creepy crawlers everywhere.\n"
										"Standing before you is the devil\n");

	// Create the Devil who will be the main villain of the game. He will also be the one
	// to give the player info on how to play the game.
	Monster devil("Devil", "The devil is a tall, red, and overwhelmingly handsome man", "");
	devil.setDialogOpening("Welcome to my mansion!!\n"
						   "My name is the Devil and you have died in real life.\n"
						   "This has resulted in you being sent down to my mansion to play a little game.\n"
						   "-----Enter better description of how to play the game-----\n");


	///////////////////////////////////////////////////////////////////////////////////////////
	// Introduction for the game. Ask the user to enter their name. 
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////
	cout << "Welcome to the Devil's Mansion V1.08" << endl;

	// Get the name the user would like to play with
	string prompt = "Hello there, please enter the name you would like your character to have: ";
	string name = "";
	do {
		name = ui.getUserInput(prompt);
	} while (name == "");
	
	// Create the main player object and output the 
	Player player(name);
	ui.setStartingDescription("\nHello there " + player.getName() + ".\n"
								"You have just died and been sent down to The Devils Mansion.\n"
								"Currently you are outside of the mansion and standing on the starting steps.\n");
	ui.printString(ui.getStartingDescription());
	startingSteps.setPlayer(player);
	ui.printString(startingSteps.getRoomDescription());

	///////////////////////////////////////////////////////////////////////////////////////////
	// Start the main loop of the game. The main loop will continuously ask the user for input.
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////
	while (mainLoop == true) {
		// Get input from the user continuously until a correct
		// key word is entered
		do {
			input = ui.getUserInput();
		} while (validateInput(keyWords, input) == false);

		// If the user enter's `q`, then break the main loop and end the game.
		if (input == "q") {
			break;
		}
		// Move the player to the 2nd room if they type move
		else if (input == "move") {
			switchRoom(startingSteps, startingRoom);
			ui.printString(startingRoom.getRoomDescription());
		}
		// Move the player back to the starting room if they type back
		else if (input == "back") {
			switchRoom(startingRoom, startingSteps);
			ui.printString(startingSteps.getRoomDescription());
		}
	}
}

// Validate that the input from the user is a correct command.
// Correct commands will be in the keyWords vector.
bool validateInput(vector<string>& vect, string sentence) {
	// ToDo: Make function be able to validate input
	for (int i = 0; i < vect.size(); i++) {
		if (vect.at(i) == sentence) {
			return true;
		}
	}
	return false;
}

// Switch the room the player is in. Take their object
// from their current room and move them into the new room
void switchRoom(Room currentRoom, Room newRoom) {
	Player tempPlayer;
	tempPlayer = currentRoom.getPlayer();
	newRoom.setPlayer(tempPlayer);
	// ToDo: Add something to take the player object out of the old room
}