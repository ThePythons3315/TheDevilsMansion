// Version 1.14

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
using namespace std;

// Definitions of functions -- initialized below
bool validateInput(vector<string>& vect, string sentence);
void moveForwardRoom(vector<Room>& vect, Room *&currentRoom);
void moveBackRoom(vector<Room>& vect, Room *&currentRoom);
void itemFromRoomToPlayer(Room*& room, string itemName);

int main() {
	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all the variables and objects that will be needed throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Various string variables that will be used throughout the game
	string version = "Welcome to the Devil's Mansion V1.14\n";
	string endSentence = "\nThanks for playing The Devil's Mansion";
	string askCharacterName = "Hello there, please enter the name you would like your character to have: ";
	string askUserToMove = "Please enter `move` to go through the door: ";
	string blueberryOnFloor = "It seems as though the devil dropped something on the ground.\n"
							  "It looks to be a blueberry.\n"
							  "That would probably be something cool to pick up.\n"
							  "Please enter `blueberry` to pick up the blueberry: ";
	string checkInventory = "Please now type `inventory` to see what you have in your inventory: ";
	string endOfIntro = "\nYou are now aware of how to move and how to pick up items.\n"
						"Please continue with the game on your own...\n";
	string startingDescription = ""; //Will be given a value after player has entered their name

	// Loop variable that starts off as true. While the variable is true the mainloop will
	// run the game and continuoulsy ask for user input.
	bool mainLoop = true;

	// Temporary string used to hold the value being returned when a user
	// is entering input.
	string input = "";

	// Vector of keywords that will be valid inputs when playing the game.
	// Eventually this will be broken up into different vectors with each vector
	// holding specific types of key words. Ex. movement vector, items in use vector, etc.
	vector <string> keyWords = { "q", "quit", "move", "back", "inventory"};

	// Vector of created rooms that are currently not in use. A room object that will
	// hold the current room the player is in. 
	vector<Room> rooms;

	// Pointer variable that will point to the current room the player is in
	Room *roomPointer = nullptr; 

	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface ui;

	//Creates player inventory and first room inventory object's using default parameters
	Inventory playerInventory;
	Inventory roomInventory1;

	// Create a blueberry object.
	Item blueberry("blueberry");
	Item squash("squash");

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

	// Create an item called a blue berry. This item will eventually be able to be eaten and
	// give the player health points.
	roomInventory1.addItem(blueberry);
	roomInventory1.addItem(squash);
	startingRoom.setInventory(roomInventory1);
	
	// Add all of the rooms to the rooms vector. This will hold rooms that are 
	// currently being used as well as rooms that are not currently being used
	rooms.push_back(startingSteps);
	rooms.push_back(startingRoom);

	// Create the Devil who will be the main villain of the game. He will also be the one
	// to give the player info on how to play the game.
	Monster devil("Devil", "The devil is a tall, red, and overwhelmingly handsome man\n", "");
	devil.setDialogOpening("Welcome to my mansion!!\n"
						   "I am the Devil and you have died in real life.\n"
						   "This has resulted in you being sent down to my mansion to play a little game.\n"
						   "-----Enter better description of how to play the game-----\n"
						   "That is the end of my spiel. Hopefully you can figure out the rest\n"
						   "...The devil zoomed away\n");

	


	///////////////////////////////////////////////////////////////////////////////////////////
	// Introduction for the game. Ask the user to enter their name. 
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////

	// Print the current version of the game
	ui.printString(version);

	// Get the name the user would like to play with
	do {
		input = ui.getUserInput(askCharacterName);
	} while (input == "");
	
	// Create the main player object and set the starting steps as their current room
	Player player(input, playerInventory);
	startingSteps.setPlayer(player);
	roomPointer = &startingSteps;

	// Print the starting descriptions of the game to the screen. 
	startingDescription = "\nHello there " + player.getName() + ".\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.";
	ui.printString(startingDescription);
	ui.printString(startingSteps.getRoomDescription());

	// Make the user enter `move` so they go from the starting steps to the starting room
	do {
		input = ui.getUserInput(askUserToMove);
	} while (input != "move");

	// Once the user enters `move`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	if (input == "move") {
		moveForwardRoom(rooms, roomPointer);
		ui.printString(roomPointer->getRoomDescription());
		ui.printString(devil.getMonsterDescription());
		ui.printString(devil.getDialogOpening());
	}

	// Reset the room so the devil is not displayed after the first entrance
	roomPointer->setRoomDescription("\nYou are now in the starting room.\n"
									"The starting room is a large open dark room with creepy crawlers everywhere.\n");
	
	// Let the player see there is a blueberry on the ground.
	do {
		input = ui.getUserInput(blueberryOnFloor);
	} while (input != "blueberry");

	// Move the blueberry from the room to the player
	itemFromRoomToPlayer(roomPointer, "blueberry");

	// Show the end of the introduction statement, the player is on there own for 
	// the most part from now on.
	ui.printString(endOfIntro);

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
		if (input == "q" || input == "quit") {
			break;
		}
		// Move the player to the 2nd room if they type move
		else if (input == "move") {
			moveForwardRoom(rooms, roomPointer);
			ui.printString(roomPointer->getRoomDescription());
			//roomPointer->getInventory().displayInventory();
		}
		// Move the player back to the starting room if they type back
		else if (input == "back") {
			moveBackRoom(rooms, roomPointer);
			ui.printString(roomPointer->getRoomDescription());
		}
		else if (input == "inventory") {
			roomPointer->getPlayer().getInventory().displayInventory();
		}
	}

	// Thank the user for playing the game
	ui.printString(endSentence);
}




///////////////////////////////////////////////////////////////////////////////////////////
// Functions that should probably be put in some other class, but I don't know where yet.
///////////////////////////////////////////////////////////////////////////////////////////

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

// Switch the room the player is in forward one room. The function takes a vector
// that is holding all of the different rooms and it also takes a pointer that is
// pointing to the current room. The pointer will be switched to the new room the 
// player is being moved to.
void moveForwardRoom(vector<Room>& vect, Room *&currentRoom) {
	// ToDo: Combine this with the moveBackRoom function
	
	Player defaultPlayer;
	// Variable to hold the room level that is one above the current room.
	// This variable will be used to find the new room that the player will
	// be moved to. It is plus one because they are moving forward.
	int nextLevel = currentRoom->getRoomLevel() + 1;

	// Move the player to the new room, get rid of the player from the old room
	// and move the pointer from the old room to the new room
	for (int i = 0; i < vect.size(); i++) {
		if (nextLevel == vect.at(i).getRoomLevel()) {
			// Move the player object from the currentRoom to the newRoom
			vect.at(i).setPlayer(currentRoom->getPlayer());

			// Clear the player from the old room
			currentRoom->setPlayer(defaultPlayer);
		
			// Move the pointer from the old room to the new room
			currentRoom = &vect.at(i);
		}
	}
}

// Switch the room the player is in backwards one room. The function takes a vector
// that is holding all of the different rooms and it also takes a pointer that is
// pointing to the current room. The pointer will be switched to the new room the 
// player is being moved to.
void moveBackRoom(vector<Room>& vect, Room*& currentRoom) {
	// ToDo: Combine this with the moveForwardRoom function

	Player defaultPlayer;
	// Variable to hold the room level that is one below the current room.
	// This variable will be used to find the new room that the player will
	// be moved to. It is minus one because they are moving backwards.
	int nextLevel = currentRoom->getRoomLevel() - 1;

	// Move the player to the new room, get rid of the player from the old room
	// and move the pointer from the old room to the new room
	for (int i = 0; i < vect.size(); i++) {
		if (nextLevel == vect.at(i).getRoomLevel()) {
			// Move the player object from the currentRoom to the newRoom
			vect.at(i).setPlayer(currentRoom->getPlayer());

			// Clear the player from the old room
			currentRoom->setPlayer(defaultPlayer);

			// Move the pointer from the old room to the new room
			currentRoom = &vect.at(i);
		}
	}
}

// Moves a specified item from the room's inventory to the player's
// inventory. It adds the item to the player's inventory and removes it
// from the room's inventory.
void itemFromRoomToPlayer(Room*& room, string itemName) {
	// Variables
	Player tempPlayer;
	Inventory roomInventory;
	Inventory playerInventory;
	vector<Item> items;
	int size;
	
	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomInventory = room->getInventory();
	playerInventory = room->getPlayer().getInventory();
	size = roomInventory.getSize();
	items = roomInventory.getInventory();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			// Add the item to the player's inventory
			playerInventory.addItem(items.at(i));

			// Remove the item from the room
			roomInventory.removeItem(i);
		}
	}

	// Set the room's inventory to the updated room inventory
	room->setInventory(roomInventory);

	// Set the player's inventory to the updated player's inventory
	tempPlayer.setInventory(playerInventory);
	tempPlayer.setName(room->getPlayer().getName());
	room->setPlayer(tempPlayer);

	// Display the inventories of the room and the player
	cout << "\nYou have just picked up a " << itemName << endl;
	cout << "\nRoom Inventory is now: " << endl;
	room->getInventory().displayInventory();
	cout << "Player Inventory is now: " << endl;
	room->getPlayer().getInventory().displayInventory();
}