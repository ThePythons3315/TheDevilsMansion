// Version 2.03

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
void itemFromRoomToPlayer(Room*& room, string itemName);
void itemFromPlayerToRoom(Room*& room, string itemName);
bool checkIfItemIsInRoom(Room*& room, string itemName);

int main() {
	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of code that creates various variables and objects that will be used 
	// throughout the game. These variables are for running the game, and will not be used
	// as attributes in creating other objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Loop variable that starts off as true. While the variable is true the mainloop will
	// run the game and continuoulsy ask for user input.
	bool mainLoop = true;

	// Temporary string used to hold the value being returned when a user
	// is entering input.
	string input = "";

	// Vector of keywords that will be valid inputs when playing the game.
	// Eventually this will be broken up into different vectors with each vector
	// holding specific types of key words. Ex. movement vector, items in use vector, etc.
	vector <string> keyWords = { "q", "quit", "left", "center", "right", "back", "inventory", "drop blueberry", "blueberry" };

	// Pointer variable that will point to the current room the player is in
	Room* roomPointer = nullptr;

	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface ui;


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all string variables of text that will be used as dialog throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////

	string version = "Welcome to the Devil's Mansion V2.03\n";
	string endSentence = "\nThanks for playing The Devil's Mansion!!";
	string askCharacterName = "Hello there, please enter the name you would like your character to have: ";
	string askUserToMove = "Please enter `center` to go through the door: ";
	string blueberryOnFloor = "Please enter `blueberry` to pick up the blueberry: ";
	string checkInventory = "Please now type `inventory` to see what you have in your inventory: ";
	string endOfIntro = "\nYou are now aware of how to move and how to pick up items.\n"
						"Please continue with the game on your own...\n";
	string incorrectRoom = "\nThat was not a valid room.\nThe player will stay in the current room.\n";
	string startingDescription = ""; //Will be given a value after player has entered their name


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create inventory objects that will be used in various players, monsters, rooms, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Inventory playerInventory;
	Inventory roomInventory1;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create health objects that will be used in various players, monsters, items, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Health playerHealth(90, 100);
	Health blueberryHealth(10, 10);


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create item objects that will be used in various player inventories, room inventories
	// and monster inventories
	///////////////////////////////////////////////////////////////////////////////////////////
	Item blueberry("blueberry", blueberryHealth);


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create room objects that will be used to move through by the player throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the starting steps. This will be the first area the player is dropped in
	// at the start of the game.
	Room startingSteps("Starting Steps", "\nYou are currently at the starting steps.\n"
										 "The starting steps lead up to a large and tall mansion in front of you.\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible.\n"
									     "Before you is a door.\n", 0);
	// Create the starting room. This is the 2nd location that the user can go to.
	// This room will come after the starting steps and will house the devil.
	// In this room the devil will explain the rules of the game to you.
	Room startingRoom("Starting Room",  "\nYou are now in the starting room.\n"
										"The starting room is a large open dark room with spider webs everywhere.\n"
										"Someone should really dust in here.\n"
										"Standing before you is the devil.\n", 1);
	Room testRoom1("TEST ROOM 1", "TEST ROOM 1 - DESCRIPTION", 2);
	Room testRoom2("TEST ROOM 2", "TEST ROOM 2 - DESCRIPTION", 3);
	Room testRoom3("TEST ROOM 3", "TEST ROOM 3 - DESCRIPTION", 4);
	Room testRoom4("TEST ROOM 4", "TEST ROOM 4 - DESCRIPTION", 5);
	
	// Starting Steps - associated rooms
	startingSteps.setCenterRoom(startingRoom);

	// Starting Room - associated rooms
	startingRoom.setBackRoom(startingSteps);
	startingRoom.setCenterRoom(testRoom1);

	// Test Room 1 - associated rooms
	testRoom1.setBackRoom(startingRoom);
	testRoom1.setLeftRoom(testRoom2);
	testRoom1.setCenterRoom(testRoom3);
	testRoom1.setRightRoom(testRoom4);

	// Other Rooms - associated rooms
	testRoom2.setRightRoom(testRoom1);
	testRoom3.setBackRoom(testRoom1);
	testRoom4.setLeftRoom(testRoom1);

	// Create an item called a blue berry. This item will eventually be able to be eaten and
	// give the player health points.
	roomInventory1.addItem(blueberry);
	startingRoom.setInventory(roomInventory1);


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create monster objects that will be used to battle the player throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the Devil who will be the main villain of the game. He will also be the one
	// to give the player info on how to play the game.
	Monster devil("Devil", "The devil is a tall, crimson red, and overwhelmingly handsome man.\n", "");
	devil.setDialogOpening("Welcome to my mansion!!\n"
						   "I am the Devil and you have died in real life.\n"
						   "This has resulted in you being sent down to my mansion to play a little game.\n"
						   "I have minions all over my mansion from skeletons to lava hounds.\n"
						   "You will have to face all of my minions in battle to make it through the mansion.\n"
						   "If you successfully make it out, you will have won your life back.\n\n"
						   "Since this is a video game and everything is fake, I guess i'll tell you the controls.\n"
						   "To move straight forward a room enter `center` and to move backwards a room enter `back`.\n"
						   "To move left a room enter `left` and to move right a room enter `right`.\n"
						   "To pick up an item, type the name of the item.\n"
						   "To show your inventory enter `inventory`.\n\n"
						   "That is the end of my spiel. Hopefully you can figure out the rest. Good luck (not)\n"
						   "...The devil zoomed away\n");


	///////////////////////////////////////////////////////////////////////////////////////////
	// Introduction for the game. Ask the user to enter their name. 
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////

	// Print the current version of the game
	ui.printString(version);

	// Get the name the user would like to play with
	do {
		input = ui.getUnstandardizedUserInput(askCharacterName);
	} while (input == "");
	
	// Create the main player object and set the starting steps as their current room
	Player player(input, playerInventory, playerHealth);
	startingSteps.setPlayer(player);
	roomPointer = &startingSteps;

	// TODO: Remove
	//cout << "PLayer's current health: " << roomPointer->getPlayer().getPlayerHealth().getHealth() << endl;
	//cout << "PLayer's current  MAX health: " << roomPointer->getPlayer().getPlayerHealth().getMaxHealth() << endl;

	// Print the starting descriptions of the game to the screen. 
	startingDescription = "\nHello there " + player.getName() + ".\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.";
	ui.printString(startingDescription);
	ui.printString(startingSteps.getRoomDescription());

	// Once the user enters `center`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	do {
		input = ui.getStandardizedUserInput(askUserToMove);
	} while (input != "center");
	roomPointer->moveRoom(input);
	roomPointer = roomPointer->getCenterRoom();
	ui.printString(roomPointer->getRoomDescription());
	ui.printString(devil.getMonsterDescription());
	ui.printString(devil.getDialogOpening());
	
	// TODO: Remove
	roomPointer->getRoomInformation();

	// TODO: Remove
	//cout << "PLayer's current health: " << roomPointer->getPlayer().getPlayerHealth().getHealth() << endl;
	//cout << "PLayer's current  MAX health: " << roomPointer->getPlayer().getPlayerHealth().getMaxHealth() << endl;



	// Reset the room so the devil is not displayed after the first entrance
	roomPointer->setRoomDescription("\nYou are now in the starting room.\n"
									"The starting room is a large open dark room with spider webs everywhere.\n");
	
	ui.printString("It seems as though the devil dropped something on the ground.\n"
				   "It looks to be a blueberry.\n"
		           "That would probably be something cool to pick up.\n");

	// Let the player see there is a blueberry on the ground.
	do {
		input = ui.getStandardizedUserInput(blueberryOnFloor);
	} while (input != "blueberry");

	// ToDo: Move the blueberry from the room to the player
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
			input = ui.getStandardizedUserInput();
		} while (validateInput(keyWords, input) == false);

		// If the user enter's `q`, then break the main loop and end the game.
		if (input == "q" || input == "quit") {
			break;
		}
		// Lets the player move to the room to the left
		else if (input == "left") {
			if (roomPointer->validatePossibleRoom(input)) {
				roomPointer->moveRoom("left");
				roomPointer = roomPointer->getLeftRoom();
				roomPointer->getRoomInformation();
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move to the room to the center
		else if (input == "center") {
			if (roomPointer->validatePossibleRoom(input)) {
				roomPointer->moveRoom("center");
				roomPointer = roomPointer->getCenterRoom();
				roomPointer->getRoomInformation();
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move to the room to the right
		else if (input == "right") {
			if (roomPointer->validatePossibleRoom(input)) {
				roomPointer->moveRoom("right");
				roomPointer = roomPointer->getRightRoom();
				roomPointer->getRoomInformation();
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move back a room
		else if (input == "back") {
			if (roomPointer->validatePossibleRoom(input)) {
				roomPointer->moveRoom("back");
				roomPointer = roomPointer->getBackRoom();
				roomPointer->getRoomInformation();
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the user redisplay their inventory
		else if (input == "inventory") {
			roomPointer->getPlayer().getInventory().displayInventory();
		}
		// Lets the user pick up the blueberry
		else if (input == "blueberry"){
			if (checkIfItemIsInRoom(roomPointer, "blueberry") == true) {
				itemFromRoomToPlayer(roomPointer, "blueberry");
			}
			else {
				cout << "The item you have entered is not in this room.\n";
				cout << "Check the other rooms or your inventory it may be in there.\n";
			}
		}
		// Lets the user drop the blueberry
		else if (input == "drop blueberry") {
			itemFromPlayerToRoom(roomPointer,"blueberry");
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
	tempPlayer.setPlayerHealth(room->getPlayer().getPlayerHealth());
	room->setPlayer(tempPlayer);

	// Display the inventories of the room and the player
	cout << "\nYou have just picked up a " << itemName << "\nType 'drop ItemName' to drop that item " << endl;
	cout << "\nRoom Inventory is now: " << endl;
	room->getInventory().displayInventory();
	cout << "Player Inventory is now: " << endl;
	room->getPlayer().getInventory().displayInventory();
}

// Moves a specified item from the playher's inventory to the rooms's
// inventory. It adds the item to the player's inventory and removes it
// from the room's inventory.
void itemFromPlayerToRoom(Room*& room, string itemName)
{
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
	size = playerInventory.getSize();
	items = playerInventory.getInventory();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			// Add the item to the room's inventory
			roomInventory.addItem(items.at(i));

			// Remove the item from the player
			playerInventory.removeItem(i);
		}
	}

	// Set the room's inventory to the updated room inventory
	room->setInventory(roomInventory);

	// Set the player's inventory to the updated player's inventory
	tempPlayer.setInventory(playerInventory);
	tempPlayer.setName(room->getPlayer().getName());
	tempPlayer.setPlayerHealth(room->getPlayer().getPlayerHealth());
	room->setPlayer(tempPlayer);

	// Display the inventories of the room and the player
	cout << "\nYou have just dropped " << itemName << endl;
	cout << "\nRoom Inventory is now: " << endl;
	room->getInventory().displayInventory();
	cout << "Player Inventory is now: " << endl;
	room->getPlayer().getInventory().displayInventory();
}

// Checks if a specified item is already in a room. Returns true if 
// the item is already in the room and false if it is not.
bool checkIfItemIsInRoom(Room*& room, string itemName)
{
	//Variables
	Inventory roomInventory;
	vector<Item> items;
	int size;
	bool found = false;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomInventory = room->getInventory();
	size = roomInventory.getSize();
	items = roomInventory.getInventory();

	// Checks the inventory of the room to see if the item is in the room or not, if the
	// item is in the room then it will return true and allow player to pick it up.
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			found = true;
			break;
		}
	}
	return found;
}
