// Version 3.01

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "GameUI.h"
#include "Room.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
#include "Battle.h"
#include "Weapon.h"
#include "Attacks.h"
#include "Parser.h"
using namespace std;

// Definitions of functions -- initialized below
void itemFromRoomToPlayer(Room*& room, string itemName);
void itemFromPlayerToRoom(Room*& room, string itemName);
void attackFromMonstertoRoom(Room*& room, string attackName);
void attackFromRoomrtoPlayer(Room*& room, string attackName);
void attackFromPlayertoRoom(Room*& room, string attackName);
bool checkIfItemIsInRoom(Room*& room, string itemName);
bool checkIfAttackIsInRoom(Room*& room, string attackName);
bool checkIfRoomIsLocked(Room*& room, string direction);
void unlockDoor(Room*& room, string itemName);
bool checkForItem(Room*& room, string itemName);
bool checkForAttack(Room*& room, string itemName);

void addItemHealthToPlayer(Room*& room, string itemName);

int main() {
	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of code that creates various variables and objects that will be used 
	// throughout the game. These variables are for running the game, and will not be used
	// as attributes in creating other objects
	///////////////////////////////////////////////////////////////////////////////////////////

	GameUI console;    // UI encapsulation - rather than directly writing to console - ToDo fix issues in parser class
	Parser parser;      // command parser - pass it a string - parser knows command format & returns struct
	Parser::InputStruct* parserOutput; // struct of commands that will tell the main loop what to do
	Room* roomPointer = nullptr; // Pointer variable that will point to the current room the player is in
	std::string userInputString;   // raw user input - retrived from UI & redirected to parser for processing

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create all string variables of text that will be used as dialog throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////

	string version = "Welcome to the Devil's Mansion V3.01\n";
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
	string quitGame = "You have quit the game...\n";
	string inputPrompt = "What would you like to do: ";

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
									     "Before you is a door.\n", false);
	// Create the starting room. This is the 2nd location that the user can go to.
	// This room will come after the starting steps and will house the devil.
	// In this room the devil will explain the rules of the game to you.
	Room startingRoom("Starting Room",  "\nYou are now in the Starting Room.\n"
										"The starting room is a large open dark room with spider webs everywhere.\n"
										"Someone should really dust in here.\n"
										"Standing before you is the devil.\n", false);
	Room skeletonRoom("Room Of Unlucky Souls", "\nYou are now in the Room Of Unlucky Souls.\n"
											   "The sounds of screams are coming from every inch of the room.\n", false);
	Room hellHoundRoom("Room Of The Devil's Most Loyal Friend", "\nYou are now in the Room Of The Devil's Most Loyal Friend.\n"
																"The room is filled with lava all around the perimeter.\n"
																"Someone should really do something about that.\n", false);
	Room chimeraRoom("Room Of Pure Black", "\nYou are now in the Room of Pure Black.\n"
										   "..... you can't see anything....\n", false);
	Room archDevilRoom("Room Of Demonic Magic", "\nYou are now in the Room Of Demonic Magic.\n"
											"Demonic magic is creeping down your spine.\n"
											"You think some kind of demon lives here???\n", false);
	Room testRoom6("Test Room 6", "You are now in the 6th test room, \nClearly you have managed to unlock the door\n"
											"to access this room\n", true);
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
	console.writeOutput(version);

	// Get the name the user would like to play with
	do {
		userInputString = console.getUserInput(askCharacterName);
	} while (userInputString == "");
	
	// Create the main player object and set the starting steps as their current room
	Player player(userInputString, playerInventory, playerHealth,playerAttack);
	startingSteps.setPlayer(player);
	roomPointer = &startingSteps;

	// Print the starting descriptions of the game to the screen. 
	startingDescription = "\nHello there " + player.getName() + ".\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.";
	console.writeOutput(startingDescription);
	console.writeOutput(startingSteps.getRoomDescription());

	// Once the user enters `center`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	do {
		userInputString = console.getUserInput(askUserToMove);
	} while (userInputString != "center");
	roomPointer->moveRoom(userInputString);
	roomPointer = roomPointer->getCenterRoom();
	console.writeOutput(roomPointer->getRoomDescription());
	console.writeOutput(devil.getMonsterDescription());
	console.writeOutput(devil.getDialogOpening());

	// Reset the room so the devil is not displayed after the first entrance
	roomPointer->setRoomDescription("\nYou are now in the starting room.\n"
									"The starting room is a large open dark room with spider webs everywhere.\n");
	
	console.writeOutput("It seems as though the devil dropped something on the ground.\n"
						"It looks to be a blueberry.\n"
						"That would probably be something cool to pick up.\n");


	// Let the player see there is a blueberry on the ground.
	do {
		userInputString = console.getUserInput(blueberryOnFloor);
	} while (userInputString != "blueberry");

	// Move the blueberry from the room to the player
	itemFromRoomToPlayer(roomPointer, "blueberry");

	// Show the end of the introduction statement, the player is on there own for 
	// the most part from now on.
	console.writeOutput(endOfIntro);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Start the main loop of the game. The main loop will continuously ask the user for input.
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////
	do
	{
		// Get input from the user and parse it into a suitable form
		userInputString = console.getUserInput("\nWhat would you like to do: ");
		parserOutput = parser.parseInput(userInputString);   // parserOutput is a pointer to memory created on the heap

		switch (parserOutput->command1)
		{
		// 1 command Key Words
		case Parser::INVENTORY:
			// Lets the user redisplay their inventory
			roomPointer->getPlayer().getInventory().displayPlayerInventory();
			break;

		case Parser::HEALTH:
			// Lets the player see how much health they currently have
			roomPointer->getPlayer().getPlayerHealth().displayHealth();
			break;

		case Parser::ATTACKS:
			//Lets the user see the attacks they've unlocked
			roomPointer->getPlayer().getAttacks().displayattacks();
			break;

		case Parser::HELP:
			parser.displayHelpText(console);
			break;

		case Parser::QUIT:
			console.writeOutput(quitGame);
			break;

		case Parser::ERROR1:
			parser.incorrectMainCommand(console);
			break;

		// 2 command Key Words
		case Parser::MOVE:
			// Move the player based off the direction entered
			switch (parserOutput->command2)
			{
			case Parser::LEFT:
				// ToDo: Refactor into a single function
				// Add extra variable with the direction you are moving

				// Lets the player move to the room to the left
				if (roomPointer->validatePossibleRoom("left")) // ToDo: Get rid of hardcoded direction
				{
					if (checkIfRoomIsLocked(roomPointer, "left") == false)
					{
						roomPointer->moveRoom("left");
						roomPointer = roomPointer->getLeftRoom();
						roomPointer->getRoomInformation();
					}
					else
					{
						cout << "It looks like the " << roomPointer->getLeftRoom()->getName()
							 << " is locked.\n" << "You must have a key to unlock the door.\n\n";
					}
				}
				else
				{
					console.writeOutput(incorrectRoom);
				}
				break;

			case Parser::CENTER:
				// ToDo: Refactor into a single function
				// Add extra variable with the direction you are moving

				// Lets the player move to the room to the center
				if (roomPointer->validatePossibleRoom("center")) // ToDo: Get rid of hardcoded direction
				{
					if (checkIfRoomIsLocked(roomPointer, "center") == false)
					{
						roomPointer->moveRoom("center");
						roomPointer = roomPointer->getCenterRoom();
						roomPointer->getRoomInformation();
					}
					else
					{
						cout << "It looks like the " << roomPointer->getCenterRoom()->getName()
							 << " is locked.\n" << "You must have a key to unlock the door.\n\n";
					}
				}
				else
				{
					console.writeOutput(incorrectRoom);
				}
				break;

			case Parser::RIGHT:
				// ToDo: Refactor into a single function
				// Add extra variable with the direction you are moving

				// Lets the player move to the room to the right
				if (roomPointer->validatePossibleRoom("right")) // ToDo: Get rid of hardcoded direction
				{
					if (checkIfRoomIsLocked(roomPointer, "right") == false)
					{
						roomPointer->moveRoom("right");
						roomPointer = roomPointer->getRightRoom();
						roomPointer->getRoomInformation();
					}
					else
					{
						cout << "It looks like the " << roomPointer->getRightRoom()->getName()
							 << " is locked.\n" << "You must have a key to unlock the door.\n\n";
					}
				}
				else
				{
					console.writeOutput(incorrectRoom);
				}
				break;

			case Parser::BACK:
				// ToDo: Refactor into a single function
				// Add extra variable with the direction you are moving

				// Lets the player move back a room
				if (roomPointer->validatePossibleRoom("back")) // ToDo: Get rid of hardcoded direction
				{
					if (checkIfRoomIsLocked(roomPointer, "back") == false)
					{
						roomPointer->moveRoom("back");
						roomPointer = roomPointer->getBackRoom();
						roomPointer->getRoomInformation();
					}
					else
					{
						cout << "It looks like the " << roomPointer->getBackRoom()->getName()
							<< " is locked.\n" << "You must have a key to unlock the door.\n\n";
					}
				}
				else
				{
					console.writeOutput(incorrectRoom);
				}
				break;

			case Parser::ERROR2:
				parser.incorrectDirectionCommand(console);
				break;
			}
			break;

		case Parser::COLLECT:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				// Lets the user pick up the blueberry
				if (checkIfItemIsInRoom(roomPointer, "blueberry") == true) {
					itemFromRoomToPlayer(roomPointer, "blueberry");
				}
				else {
					cout << "\nThe item you have entered is not in this room.\n";
					cout << "Check other rooms..... or your inventory.\n\n";
				}
				break;
			case Parser::BOW:
				// Lets the user unlock the bow attack
				if (checkIfAttackIsInRoom(roomPointer, "bow") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomrtoPlayer(roomPointer, "bow");
					}
					else
					{
						cout << "You have the max amount of attacks that can be used at one time.\n";
					}
				}
				else
				{
					cout << "The attack you have entered is not in this room.\n";
					cout << "Check other rooms or your attack list, you may have unlocked it already.\n";
				}
				break;
			case Parser::PUNCH:
				//Lets the user unlock the punch attack
				if (checkIfAttackIsInRoom(roomPointer, "punch") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomrtoPlayer(roomPointer, "punch");
					}
					else
					{
						cout << "You have the max amount of attacks that can be used at one time.\n";
					}
				}
				else
				{
					cout << "The attack you have entered is not in this room.\n";
					cout << "Check other rooms or your attack list,you may have unlocked it already.\n";
				}
				break;
			case Parser::KICK:
				//Lets the user unlock the kick attack
				if (checkIfAttackIsInRoom(roomPointer, "kick") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomrtoPlayer(roomPointer, "kick");
					}
					else
					{
						cout << "You have the max amount of attacks that can be used at one time.\n";
					}
				}
				else
				{
					cout << "The attack you have entered is not in this room.\n";
					cout << "Check other rooms or your attack list,you may have unlocked it already.\n";
				}
				break;
			case Parser::DEVILSKEY:
				// Lets the user pick up the devils key
				if (checkIfItemIsInRoom(roomPointer, "devils key") == true)
				{
					itemFromRoomToPlayer(roomPointer, "devils key");
				}
				else
				{
					cout << "\nThe item you have entered is not in this room.\n";
					cout << "Check other rooms..... or your inventory.\n\n";
				}
				break;

			case Parser::ERROR2:
				// ToDo: Change this to display that a command for that item could
				// not be found
				parser.incorrectItemCommand(console);
				break;
			}
			break;

		case Parser::USE:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				// Lets the player eat the blueberry and regain health
				if (checkForItem(roomPointer, "blueberry") == true) {
					addItemHealthToPlayer(roomPointer, "blueberry");
					roomPointer->getPlayer().getPlayerHealth().displayHealth();
				}
				else {
					cout << "\nThat item is not in your inventory. It cannot be used.\n\n";
				}
				break;
			case Parser::DEVILSKEY:
				// Lets the player eat the blueberry and regain health
				if (checkForItem(roomPointer, "devils key") == true)
				{
					unlockDoor(roomPointer, "devils key");
				}
				else
				{
					cout << "\nThat item is not in your inventory. It cannot be used.\n\n";
				}
				break;

			case Parser::ERROR2:
				// ToDo: Change this to display that a command for that item could
				// not be found
				parser.incorrectItemCommand(console);
				break;
			}
			break;

		case Parser::DROP:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				// Lets the player drop the blueberry
				itemFromPlayerToRoom(roomPointer, "blueberry");
				break;
			case Parser::BOW:
				//Lets the player drop the bow attack
				if (checkForAttack(roomPointer, "bow") == true)
				{
					attackFromPlayertoRoom(roomPointer, "bow");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::PUNCH:
				//Lets the player drop the punch attack
				if (checkForAttack(roomPointer, "punch") == true)
				{
					attackFromPlayertoRoom(roomPointer, "punch");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::KICK:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "kick") == true)
				{
					attackFromPlayertoRoom(roomPointer, "kick");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::DEVILSKEY:
				// Lets the player drop the devils key
				itemFromPlayerToRoom(roomPointer, "devils key");
				break;
			case Parser::ERROR2:
				// ToDo: Change this to display that a command for that item could
				// not be found
				parser.incorrectItemCommand(console);
				break;
			}
			break;
		case Parser::BATTLE:
			switch (parserOutput->command2)
			{
			case Parser::SKELETON:

				if (roomPointer->getMonster().getName() != "" && roomPointer->getMonster().getHealth().getHealth() > 0)
				{
					Battle battle(roomPointer, roomPointer->getPlayer(), roomPointer->getMonster());
					battle.runBattle();
				}
				else
				{
					cout << "\nThere is no current monster to battle.\n\n";
				}

				if (roomPointer->getMonster().getHealth().getHealth() < 1 && roomPointer->getAttacks().getSize() == 0)
				{
					attackFromMonstertoRoom(roomPointer, "bow");
				}
				else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1)
				{
					break;
				}
				break;

			case Parser::ERROR2:
				// ToDo: Change this to display that a command for that monster could
				// not be found
				parser.incorrectMonsterCommand(console);
				break;
			}
			break;
		default:
			parser.incorrectMainCommand(console);
			break;
		};
	} while (parserOutput->command1 != Parser::QUIT);

	// Thank the user for playing the game
	console.writeOutput(endSentence);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Functions that should probably be put in some other class, but I don't know where yet.
///////////////////////////////////////////////////////////////////////////////////////////

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
	std::cout << "\nYou have just picked up a " << itemName << endl;
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
	std::cout << "\nYou have just dropped " << itemName << endl;
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
	std::cout << endl << room->getMonster().getName() << " has just dropped " << attackName << endl;
	std::cout << "Monster attacks\n";
	room->getMonster().getAttacks().displayattacks();
	std::cout << endl;
	std::cout << "Attacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
	std::cout << endl;
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
	std::cout << "\nYou have just picked up a " << attackName;
	std::cout << "\nRoom attacks " << endl;
	room->getAttacks().displayattacks();
	std::cout << "Player attacks is now: " << endl;
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
	std::cout << endl << room->getPlayer().getName() << " has just dropped " << attackName << endl;
	std::cout << "Attacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
	std::cout << endl;
	std::cout << "Player attacks\n";
	room->getPlayer().getAttacks().displayattacks();
	std::cout << endl;
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
			std::cout << "\nThe " << itemName << " has been used." << endl;
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
				std::cout << "\nYou have unlocked the door to the " << room->getCenterRoom()->getName() << " using the " << itemName << ".\n";
				std::cout << "Please enter 'center' to go into the " << room->getCenterRoom()->getName() << ".\n\n";
			}
			else if (room->getLeftRoom() != nullptr && room->getLeftRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getLeftRoom()->setLockStatus(doorIsLocked);
				std::cout << "\nYou have unlocked the door to the " << room->getLeftRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'left' to go into the " << room->getLeftRoom()->getName() << ".\n\n";
			}
			else if (room->getRightRoom() != nullptr && room->getRightRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getRightRoom()->setLockStatus(doorIsLocked);
				std::cout << "\nYou have unlocked the door to the " << room->getRightRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'right' to go into the " << room->getRightRoom()->getName() << ".\n\n";
			}
			else if (room->getBackRoom() != nullptr && room->getBackRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getBackRoom()->setLockStatus(doorIsLocked);
				std::cout << "\nYou have unlocked the door to the " << room->getBackRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'back' to go into the " << room->getBackRoom()->getName() << ".\n\n";
			}
		}
	}
	if (doorIsLocked == true) {
		std::cout << "There are currently no doors in the " << room->getName() << " that need to be unlocked.\n\n";
	}
}