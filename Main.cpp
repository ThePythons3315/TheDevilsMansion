// Version 1.09

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
Room moveForwardRoom(vector<Room>& vect, Room currentRoom);
Room moveBackRoom(vector<Room>& vect, Room currentRoom);

int main() {
	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all the variables and objects that will be needed throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Version number of the game, will be output to console at start of game
	string version = "Welcome to the Devil's Mansion V1.09\n";

	// Loop variable that starts off as true. While the variable is true the mainloop will
	// run the game and continuoulsy ask for user input.
	bool mainLoop = true;
	// Temporary string used to hold the value being returned when a user
	// is entering input.
	string input = "";
	// Vector of keywords that will be valid inputs when playing the game.
	// Eventually this will be broken up into different vectors with each vector
	// holding specific types of key words. Ex. movement vector, item use vector, etc.
	vector <string> keyWords = { "q", "jason shupper", "move", "back", "yes"};
	// Vector of created rooms that are currently not in use. A room object that will
	// hold the current room the player is in. 
	vector<Room> notInUseRooms;
	Room currentRoom; // Make this into a pointer somehow, Then we can make the 
	// not in use rooms vector into a rooms vector and just point to the one currently
	// being used

	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface ui;

	// Create the starting steps. This will be the first area the player is dropped in
	// at the start of the game.
	Room startingSteps("Starting Steps", "\nYou are currently at the starting steps.\n"
										 "The starting steps lead up to a large and tall mansion in front of you\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible\n"
									     "Before you is a door.\n", 0);

	// Create the starting room. This is the 2nd location that the user can go to.
	// This room will come after the starting steps and will house the devil.
	// In this room the devil will explain the rules of the game to you.
	Room startingRoom("Starting Room",  "\nYou are now in the starting room.\n"
										"The starting room is a large open dark room with creepy crawlers everywhere.\n"
										"Standing before you is the devil\n", 1);
 
	// Add the non startign rooms to the not in use rooms vector
	notInUseRooms.push_back(startingRoom);

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
	ui.printString(version);

	// Get the name the user would like to play with
	string prompt = "Hello there, please enter the name you would like your character to have: ";
	string name = "";
	do {
		name = ui.getUserInput(prompt);
	} while (name == "");
	
	// Create the main player object and set the starting steps as their current room
	Player player(name);
	startingSteps.setPlayer(player);
	currentRoom = startingSteps;
	

	ui.setStartingDescription("\nHello there " + player.getName() + ".\n"
								"You have just died and been sent down to The Devils Mansion.\n"
								"Currently you are outside of the mansion and standing on the starting steps.");
	ui.printString(ui.getStartingDescription());
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
			currentRoom = moveForwardRoom(notInUseRooms, currentRoom);
			ui.printString(currentRoom.getRoomDescription());
		}
		// Move the player back to the starting room if they type back
		else if (input == "back") {
			currentRoom = moveBackRoom(notInUseRooms, currentRoom);
			ui.printString(currentRoom.getRoomDescription());
		}
	}
}

// Validate that the input from the user is a correct command.
// Correct commands will be in the keyWords vector.
bool validateInput(vector<string>& vect, string sentence) {
	for (int i = 0; i < vect.size(); i++) {
		if (vect.at(i) == sentence) {
			return true;
		}
	}
	return false;
}

// Switch the room the player is in. Take their object
// from their current room and move them into the new room
Room moveForwardRoom(vector<Room>& vect, Room currentRoom) {
	// Variables
	Room tempRoom;
	Player defaultPlayer;
	// Get the level of the next room. Level of the next room is
	// whatever the level is of the current room plus one
	int nextLevel = currentRoom.getRoomLevel() + 1;

	// Set the temp room to the room the player is moving into. Also move 
	// the player obejct to be in the new room
	for (int i = 0; i < vect.size(); i++) {
		if (nextLevel == vect.at(i).getRoomLevel()) {
			tempRoom = vect.at(i);
			tempRoom.setPlayer(currentRoom.getPlayer());
			vect.erase(vect.begin() + i);
		}
	}

	// If there was no changes made, there was no higher room level found, then return
	// the current room's object and display that you are still in the same room.
	if (tempRoom.getPlayer().getName() != currentRoom.getPlayer().getName()) {
		cout << "There is no room after this. You are still in the same room." << endl;
		return currentRoom;
	}
	// Add the room the player is moving out of into the not in use rooms vector
	currentRoom.setPlayer(defaultPlayer);
	vect.push_back(currentRoom);

	// Set the new room to be the current room
	currentRoom = tempRoom;
	return currentRoom;
}

// Switch the room the player is in. Take their object
// from their current room and move them into the new room
Room moveBackRoom(vector<Room>& vect, Room currentRoom) {
	// Variables
	Room tempRoom;
	Player defaultPlayer;
	// Get the level of the next room. Level of the next room is
	// whatever the level is of the current room plus one
	int nextLevel = currentRoom.getRoomLevel() - 1;

	// Set the temp room to the room the player is moving into. Also move 
	// the player obejct to be in the new room
	for (int i = 0; i < vect.size(); i++) {
		if (nextLevel == vect.at(i).getRoomLevel()) {
			tempRoom = vect.at(i);
			tempRoom.setPlayer(currentRoom.getPlayer());
			vect.erase(vect.begin() + i);
		}
	}

	// If there was no changes made, there was no lower room level found, then return
	// the current room's object and display that you are still in the same room.
	if (tempRoom.getPlayer().getName() != currentRoom.getPlayer().getName()) {
		cout << "There is no room after this. You are still in the same room." << endl;
		return currentRoom;
	}

	// Add the room the player is moving out of into the not in use rooms vector
	currentRoom.setPlayer(defaultPlayer);
	vect.push_back(currentRoom);

	// Set the new room to be the current room
	currentRoom = tempRoom;
	return currentRoom;
}