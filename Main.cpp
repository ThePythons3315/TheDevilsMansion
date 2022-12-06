// Version 4.01

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Parser.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Inventory.h"
#include "Monster.h"
#include "Attack.h"

int main()
{
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
	bool inBattle = false; // variable will be set to true when the player enters battle against a monster

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of strings that will be used throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////
	std::string versionText = "Welcome to The Devil's Mansion version 4.01\n\n";
	std::string getCharacterNameText = "Hello there you fabulous person, please enter the name you would like your character to have: ";
	std::string endOfGameText = "Thanks for playing The Devils Mansion.\n\n\n\n";
	std::string playerLostText = "\nThe Devil has reappeared.\n"
		"He has the widest grin stuck on his face.\n\n"
		"Ha Ha Ha Ha Ha...... Another one bites the dust.\n"
		"That was the worst attempt at getting through my mansion that I have ever seen.\n"
		"Have fun in the depths of hell, scum.\n";
	std::string askUserToMove = "Please enter `move up` to go through the door: ";
	std::string blueberryOnFloor = "Please enter `collect blueberry` to pick up the blueberry: ";
	std::string droppedBlueberryText = "It seems as though the devil dropped something on the ground.\n"
									   "It looks to be a blueberry.\n"
									   "That would probably be something cool to pick up.\n\n";
	std::string endOfIntro = "\nYou are now aware of how to move and how to pick up items.\n"
							 "If you forget the commands or need any help on attacking/using items enter 'help' at any time.\n"
							 "Please continue with the game on your own...\n";
	std::string devilsSpiel = "Standing before you is the devil.\n"
							  "The devil is a tall, crimson red, and overwhelmingly handsome man.\n\n"
							  "Welcome to my mansion!!\n"
							  "I am the Devil and you have died in real life.\n"
							  "This has resulted in you being sent down to my mansion to play a little game.\n"
							  "I have minions all over my mansion from skeletons to lava hounds.\n"
							  "You will have to face all of my minions in battle to make it through the mansion.\n"
							  "If you successfully make it out, you will have won your life back.\n\n"
							  "Since this is a video game and everything is fake, I don't need to tell you the controls.\n"
							  "You can just type `help` to see them for yourself.\n\n"
							  "That is the end of my spiel. Hopefully you can figure out the rest. Good luck (not)\n"
							  "...The devil zoomed away\n\n";

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of item objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Health items
	Item blueberry("blueberry", 100, 0);
	Item paralysisHeal("paralysisheal", 0, 1);
	Item burnHeal("burnheal", 0, 2);

	// Non health items
	Item devilskey("devilskey", 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of attack objects
	///////////////////////////////////////////////////////////////////////////////////////////

	Attack punch("punch", -20, 95, 0, 0);
	Attack kick("kick", -100, 95, 0, 0);
	Attack bowshot("bowshot", -20, 95, 0, 0);
	Attack bite("bite", -20, 95, 1, 95);
	Attack firebreath("firebreath", -20, 95, 2, 95);
	Attack flamethrower("flamethrower", -20, 95, 2, 95);
	Attack fireball("fireball", -20, 95, 2, 95);
	Attack slash("slash", -20, 95, 0, 0);
	Attack slam("slam", -20, 80, 0, 0);
	Attack shadowball("shadowball", -20, 80, 0, 0);
	Attack eruption("eruption", -20, 80, 0, 0);
	Attack overheat("overheat", -20, 80, 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of inventory objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Room inventories
	Inventory startingStepsInventory;
	Inventory startingRoomInventory;
	Inventory skeletonRoomInventory;
	Inventory hellhoundRoomInventory;
	Inventory chimeraRoomInventory;
	Inventory archDemonRoomInventory;
	Inventory dragonRoomInventory;
	Inventory reaperRoomInventory;
	Inventory mimicRoomInventory;
	Inventory spiritRoomInventory;
	Inventory hydraRoomInventory;
	Inventory devilRoomInventory;

	// Monster inventories
	Inventory skeletonInventory;
	Inventory hellhoundInventory;
	Inventory chimeraInventory;
	Inventory dragonInventory;
	Inventory archDemonInventory;
	Inventory reaperInventory;
	Inventory mimicInventory;
	Inventory spiritInventory;
	Inventory hydraInventory;
	Inventory devilInventory;

	// Player inventory
	Inventory playerInventory;

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of adding items and attacks to inventory objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Add items to room inventories
	startingRoomInventory.addItem(blueberry);
	startingRoomInventory.addItem(paralysisHeal);
	startingRoomInventory.addItem(burnHeal);
	hellhoundRoomInventory.addItem(devilskey);

	// Add attacks to player
	playerInventory.addAttack(console, punch);
	playerInventory.addAttack(console, kick);

	// Add attacks to the monsters
	skeletonInventory.addAttack(console, bowshot);
	hellhoundInventory.addAttack(console, bite);
	chimeraInventory.addAttack(console, firebreath);
	dragonInventory.addAttack(console, flamethrower);
	archDemonInventory.addAttack(console, fireball);
	reaperInventory.addAttack(console, slash);
	mimicInventory.addAttack(console, slam);
	spiritInventory.addAttack(console, shadowball);
	hydraInventory.addAttack(console, eruption);
	devilInventory.addAttack(console, overheat);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of monster objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the monster objects
	Monster skeleton("skeleton", "skeleton description", 100, 100, true, 0, 20);
	Monster hellhound("hellhound", "hellhound description", 100, 100, true, 0, 20);
	Monster chimera("chimera", "chimera description", 100, 100, true, 0, 20);
	Monster dragon("dragon", "dragon description", 100, 100, true, 0, 20);
	Monster archdemon("archdemon", "archdemon description", 100, 100, true, 0, 20);
	Monster reaper("reaper", "reaper description", 100, 100, true, 0, 20);
	Monster mimic("mimic", "mimic description", 100, 100, true, 0, 20);
	Monster spirit("spirit", "spirit description", 100, 100, true, 0, 20);
	Monster hydra("hydra", "hydra description", 100, 100, true, 0, 20);
	Monster devil("devil", "devil description", 100, 100, true, 0, 20);

	// Set monster objects with their appropriate inventories
	skeleton.setInventory(skeletonInventory);
	hellhound.setInventory(hellhoundInventory);
	chimera.setInventory(chimeraInventory);
	dragon.setInventory(dragonInventory);
	archdemon.setInventory(archDemonInventory);
	reaper.setInventory(reaperInventory);
	mimic.setInventory(mimicInventory);
	spirit.setInventory(spiritInventory);
	hydra.setInventory(hydraInventory);
	devil.setInventory(devilInventory);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of room objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the room objects
	Room nullRoom("", "", false);
	Room startingSteps("Starting Steps", "Starting Steps Description.\n", false);
	Room startingRoom("Starting Room", "Starting Room Description.\n", false);
	Room skeletonRoom("Skeleton Room", "Skeleton Room Description.\n", false);
	Room hellhoundRoom("Hellhound Room", "Hellhound Room Description.\n", false);
	Room chimeraRoom("Chimera Room", "Chimera Room Description.\n", true); // door between ChimeraRoom and DragonRoom is locked
	Room archDemonRoom("ArchDemon Room", "ArchDemon Room Description.\n", false);
	Room dragonRoom("Dragon Room", "Dragon Room Description.\n", false);
	Room reaperRoom("Reaper Room", "Reaper Room Decription.\n", false);
	Room mimicRoom("Mimic Room", "Mimic Room Description\n", false);
	Room spiritRoom("Spirit Room", "Spirit Room Description\n", false);
	Room hydraRoom("Hydra Room", "Hydra Room Description\n", false);
	Room devilRoom("Devil Room", "Devil Room Description\n", false);

	// Set room objects with their appropriate monsters
	skeletonRoom.setMonster(skeleton);
	hellhoundRoom.setMonster(hellhound);
	chimeraRoom.setMonster(chimera);
	archDemonRoom.setMonster(archdemon);
	dragonRoom.setMonster(dragon);
	reaperRoom.setMonster(reaper);
	mimicRoom.setMonster(mimic);
	spiritRoom.setMonster(spirit);
	hydraRoom.setMonster(hydra);
	devilRoom.setMonster(devil);

	// Set up all of the rooms to their correct orientations of each other.
	// Input room order: left, up , right, down
	startingSteps.setOrientations(nullRoom, startingRoom, nullRoom, nullRoom);
	startingRoom.setOrientations(nullRoom, skeletonRoom, nullRoom, startingSteps);
	skeletonRoom.setOrientations(hellhoundRoom, chimeraRoom, archDemonRoom, startingRoom);
	hellhoundRoom.setOrientations(nullRoom, reaperRoom, skeletonRoom, nullRoom);
	chimeraRoom.setOrientations(reaperRoom, dragonRoom, mimicRoom, skeletonRoom);
	archDemonRoom.setOrientations(skeletonRoom, mimicRoom, nullRoom, nullRoom);
	dragonRoom.setOrientations(nullRoom, spiritRoom, nullRoom, chimeraRoom);
	reaperRoom.setOrientations(nullRoom, nullRoom, chimeraRoom, hellhoundRoom);
	mimicRoom.setOrientations(chimeraRoom, nullRoom, nullRoom, archDemonRoom);
	spiritRoom.setOrientations(nullRoom, nullRoom, hydraRoom, dragonRoom);
	hydraRoom.setOrientations(hydraRoom, devilRoom, nullRoom, nullRoom);
	devilRoom.setOrientations(nullRoom, nullRoom, nullRoom, hydraRoom);

	// Set up all room objects with their correct inventories
	startingSteps.setInventory(startingStepsInventory);
	startingRoom.setInventory(startingRoomInventory);
	skeletonRoom.setInventory(skeletonRoomInventory);
	hellhoundRoom.setInventory(hellhoundRoomInventory);
	chimeraRoom.setInventory(chimeraRoomInventory);
	archDemonRoom.setInventory(archDemonRoomInventory);
	dragonRoom.setInventory(dragonRoomInventory);
	reaperRoom.setInventory(reaperRoomInventory);
	mimicRoom.setInventory(mimicRoomInventory);
	spiritRoom.setInventory(spiritRoomInventory);
	hydraRoom.setInventory(hydraRoomInventory);
	devilRoom.setInventory(devilRoomInventory);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Start of the introduction
	///////////////////////////////////////////////////////////////////////////////////////////

	// Print the current version of the game
	console.writeOutput(versionText);

	// Get the player's	name from the user, this name will be used throughout the game
	do {
		userInputString = console.getUserInput(getCharacterNameText);
	} while (userInputString == "");

	// Create the main player object and set the starting steps as their current room
	Player player(userInputString, 200, 200, true, 0, 50);
	player.setInventory(playerInventory);

	// Set the current room pointer to the starting room which is also initialized with the player
	startingRoom.setPlayer(player);

	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////

	// Change the need to strings to include the player's name
	std::string startingDescription = "Hello there " + player.getName() + ".\n"
									  "You have just died and been sent down to The Devils Mansion.\n"
									  "Currently you are outside of the mansion and standing on the starting steps.\n\n";
	std::string movedStartingRoomText = player.getName() + " has moved into the starting room.\n\n"
										"You are now in the Starting Room.\n\n"
										"The starting room is a large open dark room with spider webs everywhere.\n"
										"Someone should really dust in here.\n\n";
	
	// Display the starting description to the screen
	console.writeOutput(startingDescription);

	// Once the user enters `move up`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	do {
		userInputString = console.getUserInput(askUserToMove);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "move up");

	// Move into the starting room
	roomPointer = &startingRoom;
	console.writeOutput(movedStartingRoomText);

	// Display the devil's spiel
	console.writeOutput(devilsSpiel);

	// Let the player know the devil dropped a blueberry on the ground
	console.writeOutput(droppedBlueberryText);

	// Let the player see there is a blueberry on the ground.
	do {
		userInputString = console.getUserInput(blueberryOnFloor);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "collect blueberry");

	// Move the blueberry from the room to the player
	roomPointer->pickupItem(console, "blueberry", &inBattle);

	// Show the end of the introduction statement, the player is on there own for 
	// the most part from now on.
	console.writeOutput(endOfIntro);

	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////

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
			///////////////////////////////////////////////////////////////////////////////////////////
			// 1 Command Key Words
			///////////////////////////////////////////////////////////////////////////////////////////
		case Parser::INVENTORY:
			roomPointer->getPlayer()->getInventory()->displayItemInventory(console, "Player");
			break;
		case Parser::HEALTH:
			roomPointer->getPlayer()->displayBothHealth(console);
			break;
		case Parser::ATTACKS:
			roomPointer->getPlayer()->getInventory()->displayAttackInventory(console, "Player");
			break;
		case Parser::HELP:
			parser.displayHelpText(console, &inBattle);
			break;
		case Parser::ROOM:
			roomPointer->printRoomInfo(console, &inBattle);
			break;
		case Parser::PLAYER:
			roomPointer->printPlayerAttributes(console, &inBattle);
			break;
		case Parser::QUIT:
			break;
		case Parser::ERROR1:
			parser.incorrectMainCommand(console, &inBattle);
			break;

			///////////////////////////////////////////////////////////////////////////////////////////
			// 2 Command Key Words
			///////////////////////////////////////////////////////////////////////////////////////////
		case Parser::MOVE:
			switch (parserOutput->command2)
			{
			case Parser::LEFT:
				roomPointer->moveRoom(console, &roomPointer, "left", &inBattle);
				break;
			case Parser::UP:
				roomPointer->moveRoom(console, &roomPointer, "up", &inBattle);
				break;
			case Parser::RIGHT:
				roomPointer->moveRoom(console, &roomPointer, "right", &inBattle);
				break;
			case Parser::DOWN:
				roomPointer->moveRoom(console, &roomPointer, "down", &inBattle);
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
				roomPointer->pickupItem(console, "blueberry", &inBattle);
				break;
			case Parser::DEVILSKEY:
				roomPointer->pickupItem(console, "devilskey", &inBattle);
				break;
			case Parser::PARALYSISHEAL:
				roomPointer->pickupItem(console, "paralysisheal", &inBattle);
				break;
			case Parser::BURNHEAL:
				roomPointer->pickupItem(console, "burnheal", &inBattle);
				break;
			case Parser::BOWSHOT:
				roomPointer->pickupAttack(console, "bowshot", &inBattle);
				break;
			case Parser::PUNCH:
				roomPointer->pickupAttack(console, "punch", &inBattle);
				break;
			case Parser::KICK:
				roomPointer->pickupAttack(console, "kick", &inBattle);
				break;
			case Parser::BITE:
				roomPointer->pickupAttack(console, "bite", &inBattle);
				break;
			case Parser::FIREBREATH:
				roomPointer->pickupAttack(console, "firebreath", &inBattle);
				break;
			case Parser::FLAMETHROWER:
				roomPointer->pickupAttack(console, "flamethrower", &inBattle);
				break;
			case Parser::FIREBALL:
				roomPointer->pickupAttack(console, "fireball", &inBattle);
				break;
			case Parser::SLASH:
				roomPointer->pickupAttack(console, "slash", &inBattle);
				break;
			case Parser::SLAM:
				roomPointer->pickupAttack(console, "slam", &inBattle);
				break;
			case Parser::SHADOWBALL:
				roomPointer->pickupAttack(console, "shadowball", &inBattle);
				break;
			case Parser::ERUPTION:
				roomPointer->pickupAttack(console, "eruption", &inBattle);
				break;
			case Parser::OVERHEAT:
				roomPointer->pickupAttack(console, "overheat", &inBattle);
				break;
			case Parser::ERROR2:
				parser.incorrectItemCommand(console);
				break;
			}
			break;

		case Parser::USE:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				roomPointer->getPlayer()->useHealthItem(console, "blueberry");
				break;
			case Parser::DEVILSKEY:
				roomPointer->useKey(console, "devilskey", &inBattle);
				break;
			case Parser::PARALYSISHEAL:
				roomPointer->healStatusEffect(console);
				break;
			case Parser::BURNHEAL:
				roomPointer->healStatusEffect(console);
				break;
			case Parser::PUNCH:
				roomPointer->useAttack(console, "punch", &inBattle, parserOutput);
				break;
			case Parser::KICK:
				roomPointer->useAttack(console, "kick", &inBattle, parserOutput);
				break;
			case Parser::BOWSHOT:
				roomPointer->useAttack(console, "bowshot", &inBattle, parserOutput);
				break;
			case Parser::BITE:
				roomPointer->useAttack(console, "bite", &inBattle, parserOutput);
				break;
			case Parser::FIREBREATH:
				roomPointer->useAttack(console, "firebreath", &inBattle, parserOutput);
				break;
			case Parser::FLAMETHROWER:
				roomPointer->useAttack(console, "flamethrower", &inBattle, parserOutput);
				break;
			case Parser::FIREBALL:
				roomPointer->useAttack(console, "fireball", &inBattle, parserOutput);
				break;
			case Parser::SLASH:
				roomPointer->useAttack(console, "slash", &inBattle,parserOutput);
				break;
			case Parser::SLAM:
				roomPointer->useAttack(console, "slam", &inBattle, parserOutput);
				break;
			case Parser::SHADOWBALL:
				roomPointer->useAttack(console, "shadowball", &inBattle, parserOutput);
				break;
			case Parser::ERUPTION:
				roomPointer->useAttack(console, "eruption", &inBattle, parserOutput);
				break;
			case Parser::OVERHEAT:
				roomPointer->useAttack(console, "overheat", &inBattle, parserOutput);
				break;
			case Parser::ERROR2:
				parser.incorrectItemCommand(console);
				break;
			}
			break;

		case Parser::DROP:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				roomPointer->dropItem(console, "blueberry", &inBattle);
				break;
			case Parser::DEVILSKEY:
				roomPointer->dropItem(console, "devilskey", &inBattle);
				break;
			case Parser::PARALYSISHEAL:
				roomPointer->dropItem(console, "paralysisheal", &inBattle);
				break;
			case Parser::BURNHEAL:
				roomPointer->dropItem(console, "burnheal", &inBattle);
				break;
			case Parser::BOWSHOT:
				roomPointer->dropAttack(console, "bowshot", &inBattle);
				break;
			case Parser::PUNCH:
				roomPointer->dropAttack(console, "punch", &inBattle);
				break;
			case Parser::KICK:
				roomPointer->dropAttack(console, "kick", &inBattle);
				break;
			case Parser::BITE:
				roomPointer->dropAttack(console, "bite", &inBattle);
				break;
			case Parser::FIREBREATH:
				roomPointer->dropAttack(console, "firebreath", &inBattle);
				break;
			case Parser::FLAMETHROWER:
				roomPointer->dropAttack(console, "flamethrower", &inBattle);
				break;
			case Parser::FIREBALL:
				roomPointer->dropAttack(console, "fireball", &inBattle);
				break;
			case Parser::SLASH:
				roomPointer->dropAttack(console, "slash", &inBattle);
				break;
			case Parser::SLAM:
				roomPointer->dropAttack(console, "slam", &inBattle);
				break;
			case Parser::SHADOWBALL:
				roomPointer->dropAttack(console, "shadowball", &inBattle);
				break;
			case Parser::ERUPTION:
				roomPointer->dropAttack(console, "eruption", &inBattle);
				break;
			case Parser::OVERHEAT:
				roomPointer->dropAttack(console, "overheat", &inBattle);
				break;
			case Parser::ERROR2:
				parser.incorrectItemCommand(console);
				break;
			}
			break;

		case Parser::BATTLE:
			switch (parserOutput->command2)
			{
			case Parser::SKELETON:
				roomPointer->battleMonster(console, "skeleton", &inBattle);
				break;
			case Parser::HELLHOUND:
				roomPointer->battleMonster(console, "hellhound", &inBattle);
				break;
			case Parser::CHIMERA:
				roomPointer->battleMonster(console, "chimera", &inBattle);
				break;
			case Parser::DRAGON:
				roomPointer->battleMonster(console, "dragon", &inBattle);
				break;
			case Parser::ARCHDEMON:
				roomPointer->battleMonster(console, "archdemon", &inBattle);
				break;
			case Parser::REAPER:
				roomPointer->battleMonster(console, "reaper", &inBattle);
				break;
			case Parser::MIMIC:
				roomPointer->battleMonster(console, "mimic", &inBattle);
				break;
			case Parser::SPIRIT:
				roomPointer->battleMonster(console, "spirit", &inBattle);
				break;
			case Parser::HYDRA:
				roomPointer->battleMonster(console, "hydra", &inBattle);
				break;
			case Parser::DEVIL:
				roomPointer->battleMonster(console, "devil", &inBattle);
				break;
			case Parser::ERROR2:
				parser.incorrectMonsterCommand(console);
				break;
			}
			break;

		default:
			parser.incorrectMainCommand(console, &inBattle);
			break;
		};
	} while (parserOutput->command1 != Parser::QUIT);

	// If the player died to lose the game, add extra statement telling them how they failed
	if (player.getAlive() == false)
	{
		console.writeOutput(playerLostText);
	}

	// Thank the user for playing the game
	console.writeOutput(endOfGameText);
}