// Version 2.10

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
#include "Battle.h"
#include "Weapon.h"
#include "Attacks.h"
using namespace std;

// Definitions of functions -- initialized below
bool validateInput(vector<string>& vect, string sentence);
void itemFromRoomToPlayer(Room*& room, string itemName);
void itemFromPlayerToRoom(Room*& room, string itemName);
void attackFromMonstertoRoom(Room*& room, string attackName);
void attackFromRoomrtoPlayer(Room*& room, string attackName);
void attackFromPlayertoRoom(Room*& room, string attackName);
bool checkIfItemIsInRoom(Room*& room, string itemName);
bool checkIfAttackIsInRoom(Room*& room, string attackName);
bool checkIfRoomIsLocked(Room*& room, string direction);
void addItemHealthToPlayer(Room*& room, string itemName);
void unlockDoor(Room*& room, string itemName);
bool checkForItem(Room*& room, string itemName);
bool checkForAttack(Room*& room, string itemName);
void helpFunction();

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
	vector <string> keyWords = { "q", "quit", "left", "center", "right", "back", "inventory", "drop blueberry", "blueberry",
								 "eat blueberry","devils key","drop devils key","use devils key", "bow", "kick", "punch", "drop bow", "drop punch", "drop kick", "health", "battle", "attacks", "help"};
	// "squash", "eat squash", "drop squash" - Tester items strings

	// Pointer variable that will point to the current room the player is in
	Room* roomPointer = nullptr;

	// Create a game instance which will allow for user input and console output
	// to be used.
	UserInterface ui;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all string variables of text that will be used as dialog throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////

	string version = "Welcome to the Devil's Mansion V2.11\n";
	string endSentence = "\nThanks for playing The Devil's Mansion!!";
	string askCharacterName = "Hello there, please enter the name you would like your character to have: ";
	string askUserToMove = "Please enter `center` to go through the door: ";
	string blueberryOnFloor = "Please enter `blueberry` to pick up the blueberry: ";
	string checkInventory = "Please now type `inventory` to see what you have in your inventory: ";
	string endOfIntro = "You are now aware of how to move and how to pick up items.\n"
						"If you forget the commands or need any help on attacking/using items enter 'help' at any time.\n"
						"Please continue with the game on your own...\n";
	string incorrectRoom = "\nThat was not a valid room.\nThe player will stay in the current room.\n";
	string startingDescription = ""; //Will be given a value after player has entered their name


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create inventory objects that will be used in various players, monsters, rooms, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Inventory playerInventory;
	Inventory roomInventory1;
	Inventory roomInventory5;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create Attacks objects that will be used in various players, monsters, rooms, etc.
	///////////////////////////////////////////////////////////////////////////////////////////
	
	Attacks playerAttack;
	Attacks roomAttacks;
	Attacks skeletonAttacks;
	Attacks devilAttacks;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create health objects that will be used in various players, monsters, items, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Health playerHealth(90, 100);
	Health blueberryHealth(10, 10);
	Health devilHealth(0, 0);
	Health devilsKeyHealth(0, 0);
	Health skeletonHealth(50, 50);
	//Health squashHealth(5, 5);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create weapon objects that will be used by the player and by monsters throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////
	Weapon punch("punch", "punch", -20, 95);
	Weapon kick("kick", "kick", -25, 90);
	Weapon bow("bow", "bow Shot", -20, 90);
	Weapon placeHolderWeapon("Temp", "Temp", 0, 0);
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// Add weapon objects to monster attacks, add monster attacks to actual monster objects
	///////////////////////////////////////////////////////////////////////////////////////////
	
	devilAttacks.addAttack(placeHolderWeapon);
	skeletonAttacks.addAttack(bow);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create item objects that will be used in various player inventories, room inventories
	// and monster inventories
	///////////////////////////////////////////////////////////////////////////////////////////
	Item blueberry("blueberry", blueberryHealth);
	Item devilsKey("devils key", devilsKeyHealth);
	//Item squash("squash", squashHealth); - Tester


	///////////////////////////////////////////////////////////////////////////////////////////
	// Create monster objects that will be used to battle the player throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the Devil who will be the main villain of the game. He will also be the one
	// to give the player info on how to play the game.
	Monster devil("Devil", "The devil is a tall, crimson red, and overwhelmingly handsome man.\n",
		"Welcome to my mansion!!\n"
		"I am the Devil and you have died in real life.\n"
		"This has resulted in you being sent down to my mansion to play a little game.\n"
		"I have minions all over my mansion from skeletons to lava hounds.\n"
		"You will have to face all of my minions in battle to make it through the mansion.\n"
		"If you successfully make it out, you will have won your life back.\n\n"
		"Since this is a video game and everything is fake, I don't need to tell you the controls.\n"
		"You can just type `help` to see them for yourself.\n\n"
		"That is the end of my spiel. Hopefully you can figure out the rest. Good luck (not)\n"
		"...The devil zoomed away\n", devilHealth, devilAttacks);
	Monster skeleton("Skeleton", "The skeleton is a 10 foot tall, skinny, white thing of bones.\n",
		"Hello there peasent, I am the skeleton.\n"
		"Welcome to my room. I am going to take you down no matter what.\n", skeletonHealth, skeletonAttacks);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create room objects that will be used to move through by the player throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the starting steps. This will be the first area the player is dropped in
	// at the start of the game.
	Room startingSteps("Starting Steps", "\nYou are currently at the Starting Steps.\n"
										 "The starting steps lead up to a large and tall mansion in front of you.\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible.\n"
									     "Before you is a door.\n", 0, false);
	// Create the starting room. This is the 2nd location that the user can go to.
	// This room will come after the starting steps and will house the devil.
	// In this room the devil will explain the rules of the game to you.
	Room startingRoom("Starting Room",  "\nYou are now in the Starting Room.\n"
										"The starting room is a large open dark room with spider webs everywhere.\n"
										"Someone should really dust in here.\n"
										"Standing before you is the devil.\n", 1, false);
	Room skeletonRoom("Room Of Unlucky Souls", "\nYou are now in the Room Of Unlucky Souls.\n"
											   "The sounds of screams are coming from every inch of the room.\n", 2, false);
	Room hellHoundRoom("Room Of The Devil's Most Loyal Friend", "\nYou are now in the Room Of The Devil's Most Loyal Friend.\n"
																"The room is filled with lava all around the perimeter.\n"
																"Someone should really do something about that.\n", 3, false);
	Room chimeraRoom("Room Of Pure Black", "\nYou are now in the Room of Pure Black.\n"
										   "..... you can't see anything....\n", 4, false);
	Room archDevilRoom("Room Of Demonic Magic", "\nYou are now in the Room Of Demonic Magic.\n"
											"Demonic magic is creeping down your spine.\n"
											"You think some kind of demon lives here???\n", 5, false);
	Room testRoom6("Test Room 6", "You are now in the 6th test room, \nClearly you have managed to unlock the door\n"
											"to access this room\n", 6, true);
	// ToDo: Make a function to do these in one line
	// Starting Steps - associated rooms
	startingSteps.setCenterRoom(startingRoom);

	// Starting Room - associated rooms
	startingRoom.setBackRoom(startingSteps);
	startingRoom.setCenterRoom(skeletonRoom);

	// Test Room 1 - associated rooms
	skeletonRoom.setBackRoom(startingRoom);
	skeletonRoom.setLeftRoom(hellHoundRoom);
	skeletonRoom.setCenterRoom(chimeraRoom);
	skeletonRoom.setRightRoom(archDevilRoom);

	// Other Rooms - associated rooms
	hellHoundRoom.setRightRoom(skeletonRoom);
	chimeraRoom.setCenterRoom(testRoom6);
	chimeraRoom.setBackRoom(skeletonRoom);
	testRoom6.setBackRoom(chimeraRoom);
	archDevilRoom.setLeftRoom(skeletonRoom);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add monster objects to respective rooms
	///////////////////////////////////////////////////////////////////////////////////////////

	skeletonRoom.setMonster(skeleton);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add item objects to room inventories, add room inventories to actual room objects
	///////////////////////////////////////////////////////////////////////////////////////////
	//roomInventory1.addItem(squash); - Tester
	roomInventory1.addItem(blueberry);
	startingRoom.setInventory(roomInventory1);
	roomInventory5.addItem(devilsKey);
	archDevilRoom.setInventory(roomInventory5);
	///////////////////////////////////////////////////////////////////////////////////////////
	// Add weapon objects to player attacks
	///////////////////////////////////////////////////////////////////////////////////////////

	playerAttack.addAttack(punch);
	playerAttack.addAttack(kick);

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
	Player player(input, playerInventory, playerHealth,playerAttack);
	startingSteps.setPlayer(player);
	roomPointer = &startingSteps;

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
				if (checkIfRoomIsLocked(roomPointer, input) == false) {
					roomPointer->moveRoom("left");
					roomPointer = roomPointer->getLeftRoom();
					roomPointer->getRoomInformation();
				}
				else {
					cout << "It looks like the " << roomPointer->getLeftRoom()->getName()
						<< " is locked.\n" << "You must have a key to unlock the door.\n\n";
				}
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move to the room to the center
		else if (input == "center") {
			if (roomPointer->validatePossibleRoom(input)) {
				if (checkIfRoomIsLocked(roomPointer, input) == false) {
					roomPointer->moveRoom("center");
					roomPointer = roomPointer->getCenterRoom();
					roomPointer->getRoomInformation();
				}
				else {
					cout << "It looks like the " << roomPointer->getCenterRoom()->getName()
						<< " is locked.\n" << "You must have a key to unlock the door.\n\n";
				}
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move to the room to the right
		else if (input == "right") {
			if (roomPointer->validatePossibleRoom(input)) {
				if (checkIfRoomIsLocked(roomPointer, input) == false) {
					roomPointer->moveRoom("right");
					roomPointer = roomPointer->getRightRoom();
					roomPointer->getRoomInformation();
				}
				else {
					cout << "It looks like the " << roomPointer->getRightRoom()->getName()
						<< " is locked.\n" << "You must have a key to unlock the door.\n\n";
				}
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the player move back a room
		else if (input == "back") {
			if (roomPointer->validatePossibleRoom(input)) {
				if (checkIfRoomIsLocked(roomPointer, input) == false) {
					roomPointer->moveRoom("back");
					roomPointer = roomPointer->getBackRoom();
					roomPointer->getRoomInformation();
				}
				else {
					cout << "It looks like the " << roomPointer->getBackRoom()->getName()
						<< " is locked.\n" << "You must have a key to unlock the door.\n\n";
				}
			}
			else {
				ui.printString(incorrectRoom);
			}
		}
		// Lets the user redisplay their inventory
		else if (input == "inventory") {
			roomPointer->getPlayer().getInventory().displayPlayerInventory();
		}
		//Lets the user see the attacks they've unlocked
		else if (input == "attacks") {
			roomPointer->getPlayer().getAttacks().displayattacks();
		}
		// Lets the user pick up the blueberry
		else if (input == "blueberry"){
			if (checkIfItemIsInRoom(roomPointer, "blueberry") == true) {
				itemFromRoomToPlayer(roomPointer, "blueberry");
			}
			else {
				cout << "\nThe item you have entered is not in this room.\n";
				cout << "Check other rooms..... or your inventory.\n\n";
			}
		}
		// Lets the user pick up the devils key
		else if (input == "devils key") {
			if (checkIfItemIsInRoom(roomPointer, "devils key") == true) {
				itemFromRoomToPlayer(roomPointer, "devils key");
			}
			else {
				cout << "\nThe item you have entered is not in this room.\n";
				cout << "Check other rooms..... or your inventory.\n\n";
			}
		}
		//Lets the user unlock the bow attack
		else if (input == "bow") {
			if (checkIfAttackIsInRoom(roomPointer, "bow") == true) {
				if (roomPointer->getPlayer().getAttacks().getSize() != 4) {
					attackFromRoomrtoPlayer(roomPointer, "bow");
				}
				else
				{
					cout << "You have the max amount of attacks that can be used at one time.\n";
				}
			}
			else {
				cout << "The attack you have entered is not in this room.\n";
				cout << "Check other rooms or your attack list,you may have unlocked it already.\n";
			}
		}
		//Lets the user unlock the kick attack
		else if (input == "kick") {
			if (checkIfAttackIsInRoom(roomPointer, "kick") == true) {
				if (roomPointer->getPlayer().getAttacks().getSize() != 4)
				{
					attackFromRoomrtoPlayer(roomPointer, "kick");
				}
				else
				{
					cout << "You have the max amount of attacks that can be used at one time.\n";
				}
			}
			else {
				cout << "The attack you have entered is not in this room.\n";
				cout << "Check other rooms or your attack list,you may have unlocked it already.\n";
			}
		}
		//Lets the user unlock the punch attack
		else if (input == "punch") {
			if (checkIfAttackIsInRoom(roomPointer, "punch") == true) {
				if (roomPointer->getPlayer().getAttacks().getSize() != 4) {
					attackFromRoomrtoPlayer(roomPointer, "punch");
				}
				else
				{
					cout << "You have the max amount of attacks that can be used at one time.\n";
				}
			}
			else {
				cout << "The attack you have entered is not in this room.\n";
				cout << "Check other rooms or your attack list,you may have unlocked it already.\n";
			}
		}
		//Lets the player drop the bow attack
		else if (input == "drop bow") {
			if (checkForAttack(roomPointer, "bow") == true) {
				attackFromPlayertoRoom(roomPointer, "bow");
			}
			else {
				cout << "You do not currently have the attack that you wish to drop.\n";
			}
		}
		//Lets the player drop the kick attack
		else if (input == "drop kick") {
			if (checkForAttack(roomPointer, "kick") == true) {
				attackFromPlayertoRoom(roomPointer, "kick");
			}
			else {
				cout << "You do not currently have the attack that you wish to drop.\n";
			}
		}
		//Lets the player drop the punch attack
		else if (input == "drop punch") {
			if (checkForAttack(roomPointer, "punch") == true) {
				attackFromPlayertoRoom(roomPointer, "punch");
			}
			else {
				cout << "You do not currently have the attack that you wish to drop.\n";
			}
		}
		// Lets the player drop the blueberry
		else if (input == "drop blueberry") {
			itemFromPlayerToRoom(roomPointer, "blueberry");
		}
		// Lets the player drop the devils key
		else if (input == "drop devils key") {
		itemFromPlayerToRoom(roomPointer, "devils key");
		}
		// Lets the player eat the blueberry and regain health
		else if (input == "eat blueberry") {
			if (checkForItem(roomPointer, "blueberry") == true) {
				addItemHealthToPlayer(roomPointer, "blueberry");
				roomPointer->getPlayer().getPlayerHealth().displayHealth();
			}
			else {
				cout << "\nThat item is not in your inventory. It cannot be used.\n\n";
			}
			
		}
		// Lets the player eat the blueberry and regain health
		else if (input == "use devils key") {
		if (checkForItem(roomPointer, "devils key") == true) {
			unlockDoor(roomPointer, "devils key");
		}
		else {
			cout << "\nThat item is not in your inventory. It cannot be used.\n\n";
		}

		}
		// Lets the player see how much health they currently have
		else if (input == "health") {
			roomPointer->getPlayer().getPlayerHealth().displayHealth();
		}
		else if (input == "battle") {
			if (roomPointer->getMonster().getName() != "" && roomPointer->getMonster().getHealth().getHealth() > 0) {
				Battle battle(roomPointer, roomPointer->getPlayer(), roomPointer->getMonster());
				battle.runBattle();
			}
			else {
				cout << "\nThere is no current monster to battle.\n\n";
			}				
			if (roomPointer->getMonster().getHealth().getHealth() < 1 && roomPointer->getAttacks().getSize() == 0) {
				attackFromMonstertoRoom(roomPointer, "bow");
			}
			else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1){
				break;
			}
		}
		else if (input == "help") {
			helpFunction();
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
	tempPlayer.setAttacks(room->getPlayer().getAttacks());
	room->setPlayer(tempPlayer);

	// Display the inventories of the room and the player
	cout << "\nYou have just picked up a " << itemName << endl;
	room->getInventory().displayRoomInventory();
	room->getPlayer().getInventory().displayPlayerInventory();
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
	tempPlayer.setAttacks(room->getPlayer().getAttacks());
	room->setPlayer(tempPlayer);

	// Display the inventories of the room and the player
	cout << "\nYou have just dropped " << itemName << endl;
	room->getInventory().displayRoomInventory();
	room->getPlayer().getInventory().displayPlayerInventory();
}

void attackFromMonstertoRoom(Room*& room, string attackName)
{
	Monster tempMonster;
	Attacks roomAttacks;
	Attacks monsterAttacks;
	vector<Weapon> attacks;
	int size;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomAttacks = room->getAttacks();
	monsterAttacks = room->getMonster().getAttacks();
	size = monsterAttacks.getSize();
	attacks = monsterAttacks.getAttacks();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		if (attacks.at(i).getName() == attackName) {
			// Add the item to the room's inventory
			roomAttacks.addAttack(attacks.at(i));

			// Remove the item from the player
			monsterAttacks.removeItem(i);
		}
	}

	// Set the room's inventory to the updated room inventory
	room->setAttacks(roomAttacks);

	// Set the player's inventory to the updated player's inventory
	tempMonster.setAttacks(monsterAttacks);
	tempMonster.setName(room->getMonster().getName());
	tempMonster.setHealth(room->getMonster().getHealth());
	tempMonster.setDialogOpening(room->getMonster().getDialogOpening());
	tempMonster.setMonsterDescription(room->getMonster().getMonsterDescription());
	room->setMonster(tempMonster);

	// Display the inventories of the room and the player
	cout << endl << room->getMonster().getName() << " has just dropped " << attackName << endl;
	cout << "Monster attacks\n";
	room->getMonster().getAttacks().displayattacks();
	cout << endl;
	cout << "Attacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
	cout << endl;
}

void attackFromRoomrtoPlayer(Room*& room, string attackName)
{
	// Variables
	Player tempPlayer;
	Attacks roomAttacks;
	Attacks playerAttacks;
	vector<Weapon> attacks;
	int size;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomAttacks = room->getAttacks();
	playerAttacks = room->getPlayer().getAttacks();
	size = roomAttacks.getSize();
	attacks = roomAttacks.getAttacks();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		if (attacks.at(i).getName() == attackName) {
			// Add the item to the player's inventory
			playerAttacks.addAttack(attacks.at(i));

			// Remove the item from the room
			roomAttacks.removeItem(i);
		}
	}

	// Set the room's attacks to the updated room attacks
	room->setAttacks(roomAttacks);

	// Set the player's attacks to the updated player's attacks
	tempPlayer.setAttacks(playerAttacks);
	tempPlayer.setName(room->getPlayer().getName());
	tempPlayer.setPlayerHealth(room->getPlayer().getPlayerHealth());
	tempPlayer.setInventory(room->getPlayer().getInventory());
	room->setPlayer(tempPlayer);

	// Display the attack lists of the room and the player
	cout << "\nYou have just picked up a " << attackName;
	cout << "\nRoom attacks " << endl;
	room->getAttacks().displayattacks();
	cout << "Player attacks is now: " << endl;
	room->getPlayer().getAttacks().displayattacks();
}

void attackFromPlayertoRoom(Room*& room, string attackName)
{
	Player tempPlayer;
	Attacks roomAttacks;
	Attacks playerAttacks;
	vector<Weapon> attacks;
	int size;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomAttacks = room->getAttacks();
	playerAttacks = room->getPlayer().getAttacks();
	size = playerAttacks.getSize();
	attacks = playerAttacks.getAttacks();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		if (attacks.at(i).getName() == attackName) {
			// Add the item to the room's inventory
			roomAttacks.addAttack(attacks.at(i));

			// Remove the item from the player
			playerAttacks.removeItem(i);
		}
	}

	// Set the room's inventory to the updated room inventory
	room->setAttacks(roomAttacks);

	// Set the player's inventory to the updated player's inventory
	tempPlayer.setAttacks(playerAttacks);
	tempPlayer.setName(room->getPlayer().getName());
	tempPlayer.setPlayerHealth(room->getPlayer().getPlayerHealth());
	tempPlayer.setInventory(room->getInventory());
	room->setPlayer(tempPlayer);

	// Display the attacks of the room and the player
	cout << endl << room->getPlayer().getName() << " has just dropped " << attackName << endl;
	cout << "Attacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
	cout << endl;
	cout << "Player attacks\n";
	room->getPlayer().getAttacks().displayattacks();
	cout << endl;
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

// Check for an item in the player's inventory
bool checkForItem(Room*& room, string itemName) {
	//Variables
	Inventory playerInventory;
	vector<Item> items;
	int size;
	bool found = false;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	playerInventory = room->getPlayer().getInventory();
	size = playerInventory.getSize();
	items = playerInventory.getInventory();

	// Checks the inventory of the player to see if the item is in the player's inventory or not, if the
	// item is in the player's inventory then it will return true and allow player to pick it up.
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			found = true;
			break;
		}
	}
	return found;
}

bool checkForAttack(Room*& room, string itemName)
{
	//Variables
	Attacks playerAttacks;
	vector<Weapon> attacks;
	int size;
	bool found = false;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	playerAttacks = room->getPlayer().getAttacks();
	size = playerAttacks.getSize();
	attacks = playerAttacks.getAttacks();

	// Checks the inventory of the player to see if the item is in the player's inventory or not, if the
	// item is in the player's inventory then it will return true and allow player to pick it up.
	for (int i = 0; i < size; i++) {
		if (attacks.at(i).getName() == itemName) {
			found = true;
			break;
		}
	}
	return found;
}

bool checkIfAttackIsInRoom(Room*& room, string attackName)
{
	//Variables
	Attacks roomAttacks;
	vector<Weapon> attacks;
	int size;
	bool found = false;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomAttacks = room->getAttacks();
	size = roomAttacks.getSize();
	attacks = roomAttacks.getAttacks();

	// Checks the inventory of the room to see if the item is in the room or not, if the
	// item is in the room then it will return true and allow player to pick it up.
	for (int i = 0; i < size; i++) {
		if (attacks.at(i).getName() == attackName) {
			found = true;
			break;
		}
	}
	return found;
}

bool checkIfRoomIsLocked(Room*& room, string direction)
{
	if (direction == "center" && room->getCenterRoom() != nullptr && room->getCenterRoom()->getLockStatus() != true) {
		return false;
	}
	else if (direction == "left" && room->getLeftRoom() != nullptr && room->getLeftRoom()->getLockStatus() != true) {
		return false;
	}
	else if (direction == "right" && room->getRightRoom() != nullptr && room->getRightRoom()->getLockStatus() != true) {
		return false;
	}
	else if (direction == "back" && room->getBackRoom() != nullptr && room->getBackRoom()->getLockStatus() != true) {
		return false;
	}
	else {
		return true;
	}
}

void addItemHealthToPlayer(Room*& room, string itemName) {
	// Variables
	Player tempPlayer;
	Inventory playerInventory;
	Health playerHealth;
	vector<Item> items;
	int size;
	int itemHealth;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	playerInventory = room->getPlayer().getInventory();
	playerHealth = room->getPlayer().getPlayerHealth();
	size = playerInventory.getSize();
	items = playerInventory.getInventory();

	// Check to make sure the item is in the player's inventory
	// ToDo: Add a type attribute to the item class, use that to check
	// if an item is a health item before trying to add health to the player

	// Add the item's health to the player and then delete the item from the
	// player's inventory
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			itemHealth = items.at(i).getHealth().getHealth();

			// Add the health to the player
			playerHealth.changeHealth(itemHealth);

			// Remove the item from the player
			playerInventory.removeItem(i);
			cout << "\nThe " << itemName << " has been used." << endl;
		}
	}

	// Set the player's inventory to the updated player's inventory
	// and set the player's health to the updated player's health
	tempPlayer.setInventory(playerInventory);
	tempPlayer.setName(room->getPlayer().getName());
	tempPlayer.setPlayerHealth(playerHealth);
	tempPlayer.setAttacks(room->getPlayer().getAttacks());
	room->setPlayer(tempPlayer);
}

void unlockDoor(Room*& room, string itemName)
{
	// Variables
	Inventory playerInventory;
	vector<Item> items;
	int size;
	bool doorIsLocked = true;

	// Set all of the variables to their corresponding values from the
	playerInventory = room->getPlayer().getInventory();
	size = playerInventory.getSize();
	items = playerInventory.getInventory();


	//Loop to look for the devils key in the players inventory.
	//If the key is found in the players inventory and there is a locked room connected to the current
	// room that the player is in, then the lock status of the locked room is updated and the room is then unlocked
	//if there is no locked room then it will output at message stating that the key can't be used cause
	//there is no room to be unlocked
	for (int i = 0; i < size; i++) {
		if (items.at(i).getName() == itemName) {
			if (room->getCenterRoom() != nullptr && room->getCenterRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getCenterRoom()->setLockStatus(doorIsLocked);
				cout << "\nYou have unlocked the door to the " << room->getCenterRoom()->getName() << " using the " << itemName << ".\n";
				cout << "Please enter 'center' to go into the " << room->getCenterRoom()->getName() << ".\n\n";
			}
			else if (room->getLeftRoom() != nullptr && room->getLeftRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getLeftRoom()->setLockStatus(doorIsLocked);
				cout << "\nYou have unlocked the door to the " << room->getLeftRoom()->getName() << " using the " << itemName << ".\n\n";
				cout << "Please enter 'left' to go into the " << room->getLeftRoom()->getName() << ".\n\n";
			}
			else if (room->getRightRoom() != nullptr && room->getRightRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getRightRoom()->setLockStatus(doorIsLocked);
				cout << "\nYou have unlocked the door to the " << room->getRightRoom()->getName() << " using the " << itemName << ".\n\n";
				cout << "Please enter 'right' to go into the " << room->getRightRoom()->getName() << ".\n\n";
			}
			else if (room->getBackRoom() != nullptr && room->getBackRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getBackRoom()->setLockStatus(doorIsLocked);
				cout << "\nYou have unlocked the door to the " << room->getBackRoom()->getName() << " using the " << itemName << ".\n\n";
				cout << "Please enter 'back' to go into the " << room->getBackRoom()->getName() << ".\n\n";
			}
		}
	}
	if (doorIsLocked == true) {
		cout << "There are currently no doors in the " << room->getName() << " that need to be unlocked.\n\n";
	}
}

void helpFunction()
{
	cout << "\nIt seems you need help, here is a list of all the controls:\n"
		<< "attacks - displays all attacks you have unlocked\n"
		<< "'attack name' - lets you unlock a attacks adds it to your attack list\n (be aware you are limited to having 4 attacks unlocked)\n"
		<< "battle - will put you into battle if there is a monster present in the room\n"
		<< "drop 'attack name' - drops the attack entered from your attack list\n"
		<< "drop 'item name' - drops the item entered from your inventory\n"
		<< "health - shows you your current health points\n"
		<< "inventory - opens your inventory to see what items accessible for use\n"
		<< "'item name' - lets you pickup the item entered and put it into your inventory\n"
		<< "kick/punch - lets you have a chance of hitting the monster\n"
		<< "left - enters the room to the left\n" << "center - enters the room in the center\n"
		<< "right - enters the room to the right\n" << "back - puts you back to the previous room you entered\n"
		<< "use devils key - lets you unlock locked doors\n"
		<< "q/quit - quits the game\n\n";
}
