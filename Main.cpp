// Version 4.01

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
void dropMonsterInventoryToRoom(Room*& room);
void attackFromMonstertoRoom(Room*& room);
void attackFromRoomToPlayer(Room*& room, string attackName);
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

	// Strings that are not associated with user input
	string version = "Welcome to the Devil's Mansion V3.01\n\n";
	string incorrectRoom = "That was not a valid room.\nThe player will stay in the current room.\n";
	string quitGame = "You have quit the game...\n";

	// Strings associated with user input
	string askCharacterName = "Hello there you fabulous person, please enter the name you would like your character to have: ";
	string askUserToMove = "Please enter `move center` to go through the door: ";
	string blueberryOnFloor = "Please enter `collect blueberry` to pick up the blueberry: ";
	string checkInventory = "Please enter `inventory` to see what you have in your inventory: ";
	string inputPrompt = "What would you like to do: ";

	// Strings that need a \n at the start too
	string endSentence = "\nThanks for playing The Devil's Mansion!!\n";
	string endOfIntro = "\nYou are now aware of how to move and how to pick up items.\n"
		"If you forget the commands or need any help on attacking/using items enter 'help' at any time.\n"
		"Please continue with the game on your own...\n";

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create inventory objects that will be used in various players, monsters, rooms, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Inventory playerInventory;
	Inventory roomInventory1;
	Inventory roomInventory5;
	Inventory hellhoundInventory;
	Inventory chimeraInventory;
	Inventory dragonInventory;
	Inventory archDemonInventory;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create Attacks objects that will be used in various players, monsters, rooms, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Attacks playerAttack;

	Attacks roomAttacks;

	Attacks devilAttacks;
	Attacks skeletonAttacks;
	Attacks hellhoundAttacks;
	Attacks chimeraAttacks;
	Attacks dragonAttacks;
	Attacks archDemonAttacks;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create health objects that will be used in various players, monsters, items, etc.
	///////////////////////////////////////////////////////////////////////////////////////////

	Health playerHealth(200, 200);

	Health blueberryHealth(100, 100);
	Health fireFangHealth(30, 30);
	Health devilsKeyHealth(0, 0);

	Health devilHealth(0, 0);
	Health skeletonHealth(50, 50);
	Health hellhoundHealth(80, 80);
	Health chimeraHealth(80, 80);
	Health dragonHealth(80, 80);
	Health archDemonHealth(80, 80);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create weapon objects that will be used by the player and by monsters throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////
	Weapon punch("punch", "punch", -25, 95);
	Weapon kick("kick", "kick", -25, 95);
	Weapon bow("bow", "bow Shot", -35, 90);
	Weapon bite("bite", "bite", -25, 85);
	Weapon firebreath("firebreath", "firebreath", -30, 90);
	Weapon flamethrower("flamethrower", "flamethrower", -35, 50);
	Weapon fireball("fireball", "fireball", -25, 99);
	Weapon placeHolderWeapon("Temp", "Temp", 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add weapon objects to monster attacks, add monster attacks to actual monster objects
	///////////////////////////////////////////////////////////////////////////////////////////

	devilAttacks.addAttack(placeHolderWeapon);
	skeletonAttacks.addAttack(bow);
	hellhoundAttacks.addAttack(bite);
	chimeraAttacks.addAttack(firebreath);
	dragonAttacks.addAttack(flamethrower);
	archDemonAttacks.addAttack(fireball);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create item objects that will be used in various player inventories, room inventories
	// and monster inventories
	///////////////////////////////////////////////////////////////////////////////////////////
	Item blueberry("blueberry", blueberryHealth);
	Item devilsKey("devilsKey", devilsKeyHealth);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add item objects to monster inventories, add room inventories to actual room objects
	///////////////////////////////////////////////////////////////////////////////////////////
	//hellhoundInventory.addItem(fireFang); // ToDo: Re-Add Back in

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
		"...The devil zoomed away\n\n", devilHealth, devilAttacks);
	Monster skeleton("Skeleton", "The skeleton is a 10 foot tall, skinny, white thing of bones.\n",
		"Hello there peasent, I am the skeleton.\n"
		"Welcome to my room. I am going to take you down no matter what.\n\n", skeletonHealth, skeletonAttacks);
	Monster hellhound("Hellhound", "The devils most loyal beasts. They patrol his manor, sniffing out any intruder who dares to wander these cursed halls.\n",
		"Hellow there you no life scum, I am the Hellhound.\n"
		"Welcome to my room. I am going to send you to the depths of hell no matter the cost.\n\n",
		hellhoundHealth, hellhoundAttacks);
	Monster chimera("Chimera", "Chimera Description.\n",
		"More Chimera Description.\n"
		"More Chimera Description.\n\n",
		chimeraHealth, chimeraAttacks);
	Monster dragon("Dragon", "Dragon Description.\n",
		"More Dragon Description.\n"
		"More Dragon Description.\n\n",
		dragonHealth, dragonAttacks);
	Monster archDemon("ArchDemon", "ArchDemon Description.\n",
		"More ArchDemon Description.\n"
		"More ArchDemon Description.\n\n",
		archDemonHealth, archDemonAttacks);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create room objects that will be used to move through by the player throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////

	Room startingSteps("Starting Steps", "You are currently at the Starting Steps.\n"
		"The starting steps lead up to a large and tall mansion in front of you.\n"
		"The mansion is dark, mysterious and gives you a chill you did not think possible.\n"
		"Before you is a door.\n\n", false);
	Room startingRoom("Starting Room", "You are now in the Starting Room.\n"
		"The starting room is a large open dark room with spider webs everywhere.\n"
		"Someone should really dust in here.\n"
		"Standing before you is the devil.\n\n", false);
	Room skeletonRoom("Room Of Unlucky Souls", "You are now in the Room Of Unlucky Souls.\n"
		"The sounds of screams are coming from every inch of the room.\n\n", false);
	Room hellHoundRoom("Room Of The Devil's Most Loyal Friend", "You are now in the Room Of The Devil's Most Loyal Friend.\n"
		"The room is filled with lava all around the perimeter.\n"
		"Someone should really do something about that.\n\n", false);
	Room chimeraRoom("Room Of Pure Black", "You are now in the Room of Pure Black.\n"
		"........you can't see anything........\n\n", false);
	Room archDemonRoom("Room Of Demonic Magic", "You are now in the Room Of Demonic Magic.\n"
		"Demonic magic is creeping down your spine.\n"
		"You think some kind of demon lives here???\n\n", false);
	Room dragonRoom("Room of Dragon(s)???", "You are now in The Room of Dragon(s)???.\n"
		"It is really hot in here and there is gold everywhere.\n"
		"Seems fit for a room with a dragon? or dragons????\n\n", true);

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
	skeletonRoom.setRightRoom(archDemonRoom);

	// Other Rooms - associated rooms
	hellHoundRoom.setRightRoom(skeletonRoom);
	chimeraRoom.setCenterRoom(dragonRoom);
	chimeraRoom.setBackRoom(skeletonRoom);
	dragonRoom.setBackRoom(chimeraRoom);
	archDemonRoom.setLeftRoom(skeletonRoom);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add monster objects to respective rooms
	///////////////////////////////////////////////////////////////////////////////////////////

	skeletonRoom.setMonster(skeleton);
	hellHoundRoom.setMonster(hellhound);
	chimeraRoom.setMonster(chimera);
	dragonRoom.setMonster(dragon);
	archDemonRoom.setMonster(archDemon);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add item objects to room inventories, add room inventories to actual room objects
	///////////////////////////////////////////////////////////////////////////////////////////

	roomInventory1.addItem(blueberry);
	startingRoom.setInventory(roomInventory1);
	roomInventory5.addItem(devilsKey);
	archDemonRoom.setInventory(roomInventory5);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Add weapon objects to player attacks
	///////////////////////////////////////////////////////////////////////////////////////////

	playerAttack.addAttack(punch);
	playerAttack.addAttack(kick);

	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	// Introduction for the game. Ask the user to enter their name. 
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////

	// Print the current version of the game
	console.writeOutput(version);

	// Get the name the user would like to play with
	do {
		userInputString = console.getUserInput(askCharacterName);
	} while (userInputString == "");

	// Create the main player object and set the starting steps as their current room
	Player player(userInputString, playerInventory, playerHealth, playerAttack);
	startingSteps.setPlayer(player);
	roomPointer = &startingSteps;

	// Print the starting descriptions of the game to the screen. 
	string startingDescription = "Hello there " + player.getName() + ".\n"
		"You have just died and been sent down to The Devils Mansion.\n"
		"Currently you are outside of the mansion and standing on the starting steps.\n\n";
	console.writeOutput(startingDescription);
	console.writeOutput(startingSteps.getRoomDescription());

	// Once the user enters `move center`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	do {
		userInputString = console.getUserInput(askUserToMove);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "move center");

	roomPointer->moveRoom("center");
	roomPointer = roomPointer->getCenterRoom();
	console.writeOutput(roomPointer->getRoomDescription());
	console.writeOutput(devil.getMonsterDescription());
	console.writeOutput(devil.getDialogOpening());

	// Reset the room so the devil is not displayed after the first entrance
	roomPointer->setRoomDescription("You are now in the starting room.\n"
		"The starting room is a large open dark room with spider webs everywhere.\n\n");

	// Let the player know the devil dropped a blueberry on the ground
	console.writeOutput("It seems as though the devil dropped something on the ground.\n"
		"It looks to be a blueberry.\n"
		"That would probably be something cool to pick up.\n\n");

	// Let the player see there is a blueberry on the ground.
	do {
		userInputString = console.getUserInput(blueberryOnFloor);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "collect blueberry");

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
		
		case Parser::ROOM:
			roomPointer->redisplayRoom();
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
							<< " is locked.\n" << "You must have a key to unlock the door.\n";
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
							<< " is locked.\n" << "You must have a key to unlock the door.\n";
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
							<< " is locked.\n" << "You must have a key to unlock the door.\n";
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
							<< " is locked.\n" << "You must have a key to unlock the door.\n";
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
					cout << "The item you have entered is not in this room.\n";
					cout << "Check other rooms..... or your inventory.\n";
				}
				break;
			case Parser::BOW:
				// Lets the user unlock the bow attack
				if (checkIfAttackIsInRoom(roomPointer, "bow") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomToPlayer(roomPointer, "bow");
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
						attackFromRoomToPlayer(roomPointer, "punch");
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
						attackFromRoomToPlayer(roomPointer, "kick");
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
			case Parser::BITE:
				//Lets the user unlock the kick attack
				if (checkIfAttackIsInRoom(roomPointer, "bite") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomToPlayer(roomPointer, "bite");
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
			case Parser::FIREBREATH:
				//Lets the user unlock the kick attack
				if (checkIfAttackIsInRoom(roomPointer, "firebreath") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomToPlayer(roomPointer, "firebreath");
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
			case Parser::FLAMETHROWER:
				//Lets the user unlock the kick attack
				if (checkIfAttackIsInRoom(roomPointer, "flamethrower") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomToPlayer(roomPointer, "flamethrower");
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
			case Parser::FIREBALL:
				//Lets the user unlock the kick attack
				if (checkIfAttackIsInRoom(roomPointer, "fireball") == true)
				{
					if (roomPointer->getPlayer().getAttacks().getSize() != 4)
					{
						attackFromRoomToPlayer(roomPointer, "fireball");
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
				if (checkIfItemIsInRoom(roomPointer, "devilsKey") == true)
				{
					itemFromRoomToPlayer(roomPointer, "devilsKey");
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
				if (checkForItem(roomPointer, "devilsKey") == true)
				{
					unlockDoor(roomPointer, "devilsKey");
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
			case Parser::BITE:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "bite") == true)
				{
					attackFromPlayertoRoom(roomPointer, "bite");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::FIREBREATH:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "firebreath") == true)
				{
					attackFromPlayertoRoom(roomPointer, "firebreath");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::FLAMETHROWER:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "flamethrower") == true)
				{
					attackFromPlayertoRoom(roomPointer, "flamethrower");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::FIREBALL:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "fireball") == true)
				{
					attackFromPlayertoRoom(roomPointer, "fireball");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to drop.\n";
				}
				break;
			case Parser::DEVILSKEY:
				// Lets the player drop the devils key
				itemFromPlayerToRoom(roomPointer, "devilsKey");
				break;
			case Parser::ERROR2:
				// ToDo: Change this to display that a command for that item could
				// not be found
				parser.incorrectItemCommand(console);
				break;
			}
			break;
		case Parser::STATS:
			switch (parserOutput->command2)
			{
			case Parser::BOW:
				//Lets the player drop the bow attack
				if (checkForAttack(roomPointer, "bow") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("bow");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::PUNCH:
				//Lets the player drop the punch attack
				if (checkForAttack(roomPointer, "punch") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("punch");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::KICK:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "kick") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("kick");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::BITE:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "bite") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("bite");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::FIREBREATH:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "firebreath") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("firebreath");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::FLAMETHROWER:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "flamethrower") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("flamethrower");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
				break;
			case Parser::FIREBALL:
				//Lets the player drop the kick attack
				if (checkForAttack(roomPointer, "fireball") == true)
				{
					roomPointer->getPlayer().getAttacks().getAttackStats("fireball");
				}
				else
				{
					cout << "You do not currently have the attack that you wish to see stats for.\n";
				}
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
				// Check and see if the monster is in the current room before doing everything else
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
					attackFromMonstertoRoom(roomPointer);
				}
				else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1)
				{
					break;
				}
				break;
			case Parser::HELLHOUND:
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
					attackFromMonstertoRoom(roomPointer);
				}
				else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1)
				{
					break;
				}
				break;
			case Parser::CHIMERA:
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
					attackFromMonstertoRoom(roomPointer);
				}
				else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1)
				{
					break;
				}
				break;
			case Parser::DRAGON:
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
					attackFromMonstertoRoom(roomPointer);
				}
				else if (roomPointer->getPlayer().getPlayerHealth().getHealth() < 1)
				{
					break;
				}
				break;
			case Parser::ARCHDEMON:
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
					attackFromMonstertoRoom(roomPointer);
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
	} while ((parserOutput->command1 != Parser::QUIT) && (roomPointer->getPlayer().getPlayerHealth().getHealth() > 0));

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
	std::cout << "You have just picked up a " << itemName << ".\n\n";
	room->getInventory().displayRoomInventory();
	//std::cout << std::endl;
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

void dropMonsterInventoryToRoom(Room*& room)
{
	// Variables
	Monster tempMonster;
	Inventory roomInventory;
	Inventory monsterInventory;
	vector<Item> items;
	int i = 0;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomInventory = room->getInventory();
	monsterInventory = room->getMonster().getInventory();
	items = monsterInventory.getInventory();

	// Add the item to the player and remove it from the room
	while (room->getMonster().getInventory().getSize() != 0) {

		// Add the item to the room's inventory
		roomInventory.addItem(items.at(i));

		// Remove the item from the player
		monsterInventory.removeItem(i);
		i++;
	}

	// Set the room's inventory to the updated room inventory
	room->setInventory(roomInventory);

	// Set the player's inventory to the updated player's inventory
	tempMonster.setInventory(monsterInventory);
	tempMonster.setAttacks(room->getMonster().getAttacks());
	tempMonster.setName(room->getMonster().getName());
	tempMonster.setHealth(room->getMonster().getHealth());
	tempMonster.setDialogOpening(room->getMonster().getDialogOpening());
	tempMonster.setMonsterDescription(room->getMonster().getMonsterDescription());
	room->setMonster(tempMonster);


	// Display the inventories of the room and the player
	cout << "\nThe " << room->getMonster().getName() << " has just dropped it's entire inventory." << endl;
	room->getInventory().displayRoomInventory();
	room->getMonster().getInventory().displayMonsterInventory();
}

void attackFromMonstertoRoom(Room*& room)
{
	Monster tempMonster;
	Attacks roomAttacks;
	Attacks temp;
	Attacks monsterAttacks;
	vector<Weapon> attacks;
	int size;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomAttacks = room->getAttacks();
	monsterAttacks = room->getMonster().getAttacks();
	temp = monsterAttacks;
	size = monsterAttacks.getSize();
	attacks = monsterAttacks.getAttacks();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
		// Add the item to the room's inventory
		roomAttacks.addAttack(attacks.at(i));
		// Remove the item from the player
		monsterAttacks.removeItem(i);
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
	std::cout << endl << room->getMonster().getName() << " has just dropped their " << temp.getMonsterWeapon().getName() << ".\n";
	//std::cout << "Monster attacks\n"; // Dont think we need
	//room->getMonster().getAttacks().displayattacks(); // Dont think we need

	std::cout << "\nAttacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
}

void attackFromRoomToPlayer(Room*& room, string attackName)
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
	std::cout << "You have just picked up a " << attackName << ".\n";
	std::cout << "\nRoom attacks " << endl;
	room->getAttacks().displayattacks();
	std::cout << std::endl;
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
		// Add the item to the room's inventory
	}

	// Set the room's inventory to the updated room inventory
	room->setAttacks(roomAttacks);

	// Set the player's inventory to the updated player's inventory
	tempPlayer.setAttacks(playerAttacks);
	tempPlayer.setName(room->getPlayer().getName());
	tempPlayer.setPlayerHealth(room->getPlayer().getPlayerHealth());
	tempPlayer.setInventory(room->getPlayer().getInventory());
	room->setPlayer(tempPlayer);

	// Display the attacks of the room and the player
	std::cout << room->getPlayer().getName() << " has just dropped the attack " << attackName << ".\n\n";
	std::cout << "Attacks in the room that you can pickup: " << endl;
	room->getAttacks().displayattacks();
	std::cout << endl;
	std::cout << "Player attacks\n";
	room->getPlayer().getAttacks().displayattacks();
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
			std::cout << "The " << itemName << " has been used." << endl;
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
				std::cout << "You have unlocked the door to the " << room->getCenterRoom()->getName() << " using the " << itemName << ".\n";
				std::cout << "Please enter 'move center' to go into the " << room->getCenterRoom()->getName() << ".\n";
			}
			else if (room->getLeftRoom() != nullptr && room->getLeftRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getLeftRoom()->setLockStatus(doorIsLocked);
				std::cout << "You have unlocked the door to the " << room->getLeftRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'move left' to go into the " << room->getLeftRoom()->getName() << ".\n";
			}
			else if (room->getRightRoom() != nullptr && room->getRightRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getRightRoom()->setLockStatus(doorIsLocked);
				std::cout << "You have unlocked the door to the " << room->getRightRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'move right' to go into the " << room->getRightRoom()->getName() << ".\n";
			}
			else if (room->getBackRoom() != nullptr && room->getBackRoom()->getLockStatus() != false) {
				doorIsLocked = false;
				room->getBackRoom()->setLockStatus(doorIsLocked);
				std::cout << "You have unlocked the door to the " << room->getBackRoom()->getName() << " using the " << itemName << ".\n\n";
				std::cout << "Please enter 'move back' to go into the " << room->getBackRoom()->getName() << ".\n";
			}
		}
	}
	if (doorIsLocked == true) {
		std::cout << "There are currently no doors in the " << room->getName() << " that need to be unlocked.\n\n";
	}
}