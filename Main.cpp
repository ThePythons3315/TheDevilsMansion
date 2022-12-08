// Version 4.01

#include <iostream>
#include <string>
#include <Windows.h>
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

	GameUI console; // UI encapsulation - rather than directly writing to console
	Parser parser; // command parser - pass it a string - parser knows command format & returns struct
	Parser::InputStruct* parserOutput; // struct of commands that will tell the main loop what to do
	Room* roomPointer = nullptr; // Pointer variable that will point to the current room the player is in
	std::string userInputString; // raw user input - retrived from UI & redirected to parser for processing
	bool inBattle = false; // variable will be set to true when the player enters battle against a monster

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of strings that will be used throughout the game
	///////////////////////////////////////////////////////////////////////////////////////////
	std::string versionText = "Welcome to The Devil's Mansion version 4.10.\n\n";
	std::string getCharacterNameText = "Hello there you fabulous person, please enter the name you would like your character to have: ";
	std::string thanksText = "Thanks for playing The Devils Mansion.\n";
	std::string playerLostText = "\nThe Devil has reappeared.\n"
								 "He has the widest grin stuck on his face.\n\n"
								 "Ha Ha Ha Ha Ha...... Another one bites the dust.\n"
								 "That was the worst attempt at getting through my mansion that I have ever seen.\n"
								 "Have fun in the depths of hell, scum.\n\n";
	std::string askUserToMove = "Please enter `move up` to go through the door: ";
	std::string blueberryOnFloor = "Please enter `collect blueberry` to pick up the blueberry: ";
	std::string droppedBlueberryText = "It seems as though the devil dropped something on the ground.\n"
									   "It looks to be a blueberry.\n"
									   "That would probably be something cool to pick up.\n\n";
	std::string endOfIntro = "\nYou are now aware of how to move and how to pick up items.\n"
							 "If you forget the commands or need any help on attacking/using items enter 'help' at any time.\n"
							 "Please continue with the game on your own...\n";
	std::string endOfGame = "\nDamn........................................................\n"
							"You actually beat my game...................................\n\n"
							"Welp, I guess I have to send you back up.\n"
							"Have fun up there, I better not see you again.\n\n";
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
							  "That is the end of my spiel. Hopefully you can figure out the rest. Good luck (not).\n"
							  "...The devil zoomed away.\n\n";
	std::string playerWon = "You have won.\n";
	std::string playerLost = "You have lost.\n";

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of item objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Health items
	Item blueberry("blueberry", "A flavorful fruit that replenishes you with 60 health.", 60, 0);
	Item cookie("cookie", "A sweet treat that replenishes you with 70 health.", 70, 0);
	Item brownie("brownie", "A sweet treat that replenishes you with 80 health.", 80, 0);
	Item burger("burger", "A juicy creation from god that replenishes you with 100 health.", 100, 0);
	Item advil("advil", "A healing item that gets rid of your paralysis status effect.", 0, 1);
	Item dayquil("dayquil", "A healing item that gets rid of your paralysis status effect.", 0, 1);
	Item ice("ice", "A healing item that gets rid of your burn status effect.", 0, 2);
	Item icepack("icepack", "A healing item that gets rid of your burn status effect.", 0, 2);
	Item smoothie("smoothie", "A healing item that gets rid of your burn status effect.", 0, 2);

	// Non health items
	Item dragonkey("dragonkey", "It is a key shaped like a dragon.", 0, 0);
	Item devilkey("devilkey", "It is a key shaped like the devil.", 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Section of attack objects
	///////////////////////////////////////////////////////////////////////////////////////////

	// Player attacks
	Attack punch("punch", "Throws a wicked punch.", -15, 100, 0, 0);
	Attack kick("kick", "Performs a flamboyant kick.", -20, 90, 0, 0);

	// Monster attacks
	Attack bowshot("bowshot", "Shoots an arrow at the opponent.", -20, 90, 0, 0);
	Attack bite("bite", "Puts them chompers to good use.", -15, 85, 1, 20);
	Attack firebreath("firebreath", "You should probably invest in toothpaste cause your breath stank.", -20, 80, 2, 20);
	Attack flamethrower("flamethrower", "Shoots fire out ya mouth.", -20, 85, 2, 20);
	Attack fireball("fireball", "You literally throw a ball of fire.", -20, 80, 2, 20);
	Attack slash("slash", "Your hand is pretty sharp, might as well swing it at the opponent.", -25, 95, 0, 0);
	Attack slam("slam", "You use your fat ass to put the opponent into the ground.", -20, 95, 1, 20);
	Attack shadowball("shadowball", "IDK how it works, but a ball of shadows is definitely thrown.", -25, 90, 1, 20);
	Attack eruption("eruption", "The earth shakes with excitement, also it hurts the opponent.", -30, 85, 2, 20);
	Attack overheat("overheat", "Is it hot in here? Nah it's just the attacker. Somehow this hurts the opponent.", -35, 90, 2, 20);

	// On the ground attacks
	Attack longshot("longshot", "If it hits, that would be pretty dope. Only if it hits though.", -60, 20, 0, 20);
	Attack oneshot("oneshot", "Might as well buy a lottery ticket, but it will kill anything if it hits.", -300, 1, 0, 20);

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
	Inventory treasureRoomInventory1;
	Inventory treasureRoomInventory2;
	Inventory treasureRoomInventory3;

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
	treasureRoomInventory1.addItem(cookie);
	treasureRoomInventory2.addItem(brownie);
	treasureRoomInventory3.addItem(burger);
	reaperRoomInventory.addItem(advil);
	mimicRoomInventory.addItem(dayquil);
	dragonRoomInventory.addItem(icepack);
	hydraRoomInventory.addItem(smoothie);

	// Add attacks to room inventories
	treasureRoomInventory2.addAttack(console, longshot);
	treasureRoomInventory3.addAttack(console, oneshot);

	// Add items to monster inventories
	hellhoundInventory.addItem(dragonkey);
	spiritInventory.addItem(devilkey);
	archDemonInventory.addItem(ice);

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
	Monster skeleton("skeleton", "All of his bones aren't even connected, they're just floating near each other.\n"
								 "I guess gravity doesn't make sense down here.", 40, 40, true, 0, 20);
	Monster hellhound("hellhound", "I guess dogs are the devil's best friend too.\n"
								   "The hellhound looks like a great dane, but with fire.",50, 50, true, 0, 20);
	Monster chimera("chimera", "This thing is u to the g to the l to the y, ugly.\n"
							   "It's like a lion, but with a goat, and throw in a little snake too.", 60, 60, true, 0, 20);
	Monster dragon("dragon", "Whatever you think a dragon looks like, double the scariness.\n"
							 "This thing's like 40 feet tall and its scales shimmer with your fear.", 75, 75, true, 0, 20);
	Monster archdemon("archdemon", "Why is this dude not wearing any clothes?\n"
								   "I guess cause a human mixed with a dragon type of creature doesn't wear pants.", 50, 50, true, 0, 20);
	Monster reaper("reaper", "Where the hell is his scythe?\n"
							 "Ope.... apparently he can pull it out of his dark cloak.", 60, 60, true, 0, 20);
	Monster mimic("mimic", "Its like looking in a mirror.\n"
						   "Perhaps you should start moisturizing, them wrinkles getting out of control.", 60, 60, true, 0, 20);
	Monster spirit("spirit", "This thing looks like it uses the elevator a lot.\n"
							 "Cause elevators lift spirits. (get it? get it? I'll see myself out).", 75, 75, true, 0, 20);
	Monster hydra("hydra", "There is at least 3 heads on this snake monster thing.\n"
						   "But definitely less than 276 heads. So it's somewhere in that range.", 80, 80, true, 0, 20);
	Monster devil("devil", "Ya know the devil described himself as overwhelmingly handsome earlier.\n"
						   "But I am just not seeing it. He ugly ugly.", 100, 100, true, 0, 20);

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
	Room startingSteps("Starting Steps", "The starting steps lead up to a large and tall mansion in front of you.\n"
										 "The mansion is dark, mysterious and gives you a chill you did not think possible.\n", false);
	Room startingRoom("Starting Room", "The starting room is a large open dark room with spider webs everywhere.\n"
									   "Someone should really dust in here.\n", false);
	Room skeletonRoom("Room Of Unlucky Souls", "The feeling of dread comes over you as you hear screams.\n"
											   "Shattered bones are scattered across the floor.\n", false);
	Room hellhoundRoom("Room Of The Devil's Most Loyal Friend", "The room is filled with lava all around the perimeter.\n"
																"Someone should really do something about that.\n", false);
	Room chimeraRoom("Room of Weird", "The walls are covered with pictures of you.\n"
									  "Haha... get it? Cause you're a weird ****.\n", true); // door between ChimeraRoom and DragonRoom is locked
	Room archDemonRoom("Room Of Demonic Magic", "Demonic magic is creeping down your spine.\n"
												"You think some kind of demon lives here???\n", false);
	Room dragonRoom("Room of Gold", "There is literally gold everywhere in this room.\n"
									"It is really unfortunate you can't take any of it.\n", false);
	Room reaperRoom("Room of Death", "The room brings an eerie silence.\n"
									 "Is this what death feels like?\n", false);
	Room mimicRoom("Room of Mirrors", "Every inch of the room is covered by a mirror.\n"
									  "You have never felt so popular, yet so alone.\n", false);
	Room spiritRoom("Room of Ghouls", "The shrieks of those below you can be heard from this room\n"
									  "They should really invest in some acoustic foam.\n", false);
	Room hydraRoom("Room of Snakes", "There are some really sneaky looking snakes in this room.\n"
									 "Most of them are garden snakes though. Should'nt they be like cobras or something?\n", 
									 true); // door between HydraRoom and DevilRoom is locked
	Room devilRoom("Room of The Devil", "This looks to be the last room in the mansion.\n"
										"It is warm, but not too warm. And it is decorated beautifully.\n"
										"There is even a bed in the corner. Wait does The Devil sleep in here?\n", false); 
	Room treasureRoom1("Treasure Room", "Huh. This room is actually pretty nice.\n"
										"It even feels like its air conditioned.\n", false);
	Room treasureRoom2("Valuables Room", "Damn there is some nice stuff in here.\n"
										 "They even got a sweet treat for me.\n", false);
	Room treasureRoom3("Riches Room", "Did the dragon not know about this room?\n"
									  "There is like way more gold in here then he had in his room.\n", false);

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
	hellhoundRoom.setOrientations(treasureRoom1, reaperRoom, skeletonRoom, nullRoom);
	chimeraRoom.setOrientations(reaperRoom, dragonRoom, mimicRoom, skeletonRoom);
	archDemonRoom.setOrientations(skeletonRoom, mimicRoom, nullRoom, nullRoom);
	dragonRoom.setOrientations(nullRoom, spiritRoom, nullRoom, chimeraRoom);
	reaperRoom.setOrientations(nullRoom, nullRoom, chimeraRoom, hellhoundRoom);
	mimicRoom.setOrientations(chimeraRoom, nullRoom, treasureRoom2, archDemonRoom);
	spiritRoom.setOrientations(treasureRoom3, nullRoom, hydraRoom, dragonRoom);
	hydraRoom.setOrientations(spiritRoom, devilRoom, nullRoom, nullRoom);
	devilRoom.setOrientations(nullRoom, nullRoom, nullRoom, hydraRoom);
	treasureRoom1.setOrientations(nullRoom, nullRoom, hellhoundRoom, nullRoom);
	treasureRoom2.setOrientations(mimicRoom, nullRoom, nullRoom, nullRoom);
	treasureRoom3.setOrientations(nullRoom, nullRoom, spiritRoom, nullRoom);

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
	treasureRoom1.setInventory(treasureRoomInventory1);
	treasureRoom2.setInventory(treasureRoomInventory2);
	treasureRoom3.setInventory(treasureRoomInventory3);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Start of the introduction
	///////////////////////////////////////////////////////////////////////////////////////////

	// Print the current version of the game
	console.outputByCharacter(versionText);

	// Get the player's	name from the user, this name will be used throughout the game
	do {
		userInputString = console.getUserInput(getCharacterNameText);
	} while (userInputString == "");

	// Create the main player object and set the starting steps as their current room
	Player player(userInputString, 250, 250, true, 0, 25);
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
	console.outputByCharacter(startingDescription);

	// Once the user enters `move up`, send them into the starting room and have the devil 
	// give his little spiel about how the game works and runs.
	do {
		userInputString = console.getUserInput(askUserToMove);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "move up");

	// Move into the starting room
	roomPointer = &startingRoom;
	console.outputByCharacter(movedStartingRoomText);

	// Display the devil's spiel
	console.outputByCharacter(devilsSpiel);

	// Let the player know the devil dropped a blueberry on the ground
	console.outputByCharacter(droppedBlueberryText);

	// Let the player see there is a blueberry on the ground.
	do {
		userInputString = console.getUserInput(blueberryOnFloor);
		userInputString = parser.convertLower(userInputString);
	} while (userInputString != "collect blueberry");

	// Move the blueberry from the room to the player
	roomPointer->pickupItem(console, "blueberry", &inBattle);

	// Show the end of the introduction statement, the player is on there own for 
	// the most part from now on.
	console.outputByCharacter(endOfIntro);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Start the main loop of the game. The main loop will continuously ask the user for input.
	// The user input will be used to run the game and progress throughout the game.
	///////////////////////////////////////////////////////////////////////////////////////////
	do
	{
		// Get input from the user and parse it into a suitable form
		userInputString = console.getUserInput("\nWhat would you like to do: ");
		parserOutput = parser.parseInput(userInputString);

		switch (parserOutput->command1)
		{
			///////////////////////////////////////////////////////////////////////////////////////////
			// 1 Command Key Words
			///////////////////////////////////////////////////////////////////////////////////////////
		case Parser::INVENTORY:
			roomPointer->getPlayer()->getInventory()->displayItemInventory(console, "Player");
			break;
		case Parser::MAP:
			roomPointer->showMap(console, &inBattle);
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
			case Parser::COOKIE:
				roomPointer->pickupItem(console, "cookie", &inBattle);
				break;
			case Parser::BROWNIE:
				roomPointer->pickupItem(console, "brownie", &inBattle);
				break;
			case Parser::BURGER:
				roomPointer->pickupItem(console, "burger", &inBattle);
				break;
			case Parser::ADVIL:
				roomPointer->pickupItem(console, "advil", &inBattle);
				break;
			case Parser::DAYQUIL:
				roomPointer->pickupItem(console, "dayquil", &inBattle);
				break;
			case Parser::ICE:
				roomPointer->pickupItem(console, "ice", &inBattle);
				break;
			case Parser::ICEPACK:
				roomPointer->pickupItem(console, "icepack", &inBattle);
				break;
			case Parser::SMOOTHIE:
				roomPointer->pickupItem(console, "smoothie", &inBattle);
				break;
			case Parser::DRAGONKEY:
				roomPointer->pickupItem(console, "dragonkey", &inBattle);
				break;
			case Parser::DEVILKEY:
				roomPointer->pickupItem(console, "devilkey", &inBattle);
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
			case Parser::LONGSHOT:
				roomPointer->pickupAttack(console, "longshot", &inBattle);
				break;
			case Parser::ONESHOT:
				roomPointer->pickupAttack(console, "oneshot", &inBattle);
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
			case Parser::COOKIE:
				roomPointer->getPlayer()->useHealthItem(console, "cookie");
				break;
			case Parser::BROWNIE:
				roomPointer->getPlayer()->useHealthItem(console, "brownie");
				break;
			case Parser::BURGER:
				roomPointer->getPlayer()->useHealthItem(console, "burger");
				break;
			case Parser::ADVIL:
				roomPointer->healStatusEffect(console, advil.getStatusEffect(), "advil");
				break;
			case Parser::DAYQUIL:
				roomPointer->healStatusEffect(console, dayquil.getStatusEffect(), "dayquil");
				break;
			case Parser::ICE:
				roomPointer->healStatusEffect(console, ice.getStatusEffect(), "ice");
				break;
			case Parser::ICEPACK:
				roomPointer->healStatusEffect(console, icepack.getStatusEffect(), "icepack");
				break;
			case Parser::SMOOTHIE:
				roomPointer->healStatusEffect(console, smoothie.getStatusEffect(), "smoothie");
				break;
			case Parser::DRAGONKEY:
				roomPointer->useKey1(console, "dragonkey", &inBattle);
				break;
			case Parser::DEVILKEY:
				roomPointer->useKey2(console, "devilkey", &inBattle);
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
			case Parser::LONGSHOT:
				roomPointer->useAttack(console, "longshot", &inBattle, parserOutput);
				break;
			case Parser::ONESHOT:
				roomPointer->useAttack(console, "oneshot", &inBattle, parserOutput);
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
			case Parser::COOKIE:
				roomPointer->dropItem(console, "cookie", &inBattle);
				break;
			case Parser::BROWNIE:
				roomPointer->dropItem(console, "brownie", &inBattle);
				break;
			case Parser::BURGER:
				roomPointer->dropItem(console, "burger", &inBattle);
				break;
			case Parser::ADVIL:
				roomPointer->dropItem(console, "advil", &inBattle);
				break;
			case Parser::DAYQUIL:
				roomPointer->dropItem(console, "dayquil", &inBattle);
				break;
			case Parser::ICE:
				roomPointer->dropItem(console, "ice", &inBattle);
				break;
			case Parser::ICEPACK:
				roomPointer->dropItem(console, "icepack", &inBattle);
				break;
			case Parser::SMOOTHIE:
				roomPointer->dropItem(console, "smoothie", &inBattle);
				break;
			case Parser::DRAGONKEY:
				roomPointer->dropItem(console, "dragonkey", &inBattle);
				break;
			case Parser::DEVILKEY:
				roomPointer->dropItem(console, "devilkey", &inBattle);
				break;
			case Parser::PUNCH:
				roomPointer->dropAttack(console, "punch", &inBattle);
				break;
			case Parser::KICK:
				roomPointer->dropAttack(console, "kick", &inBattle);
				break;
			case Parser::BOWSHOT:
				roomPointer->dropAttack(console, "bowshot", &inBattle);
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
			case Parser::LONGSHOT:
				roomPointer->dropAttack(console, "longshot", &inBattle);
				break;
			case Parser::ONESHOT:
				roomPointer->dropAttack(console, "oneshot", &inBattle);
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

		case Parser::VIEW:
			switch (parserOutput->command2)
			{
			case Parser::BLUEBERRY:
				blueberry.viewItemDescription(console);
				break;
			case Parser::COOKIE:
				cookie.viewItemDescription(console);
				break;
			case Parser::BROWNIE:
				brownie.viewItemDescription(console);
				break;
			case Parser::BURGER:
				burger.viewItemDescription(console);
				break;
			case Parser::ADVIL:
				advil.viewItemDescription(console);
				break;
			case Parser::DAYQUIL:
				dayquil.viewItemDescription(console);
				break;
			case Parser::ICE:
				ice.viewItemDescription(console);
				break;
			case Parser::ICEPACK:
				icepack.viewItemDescription(console);
				break;
			case Parser::SMOOTHIE:
				smoothie.viewItemDescription(console);
				break;
			case Parser::DRAGONKEY:
				dragonkey.viewItemDescription(console);
				break;
			case Parser::DEVILKEY:
				devilkey.viewItemDescription(console);
				break;
			case Parser::PUNCH:
				punch.displayAttackStats(console);
				break;
			case Parser::KICK:
				kick.displayAttackStats(console);
				break;
			case Parser::BOWSHOT:
				bowshot.displayAttackStats(console);
				break;
			case Parser::BITE:
				bite.displayAttackStats(console);
				break;
			case Parser::FIREBREATH:
				firebreath.displayAttackStats(console);
				break;
			case Parser::FLAMETHROWER:
				flamethrower.displayAttackStats(console);
				break;
			case Parser::FIREBALL:
				fireball.displayAttackStats(console);
				break;
			case Parser::SLASH:
				slash.displayAttackStats(console);
				break;
			case Parser::SLAM:
				slam.displayAttackStats(console);
				break;
			case Parser::SHADOWBALL:
				shadowball.displayAttackStats(console);
				break;
			case Parser::ERUPTION:
				eruption.displayAttackStats(console);
				break;
			case Parser::OVERHEAT:
				overheat.displayAttackStats(console);
				break;
			case Parser::LONGSHOT:
				longshot.displayAttackStats(console);
				break;
			case Parser::ONESHOT:
				oneshot.displayAttackStats(console);
				break;
			case Parser::SKELETON:
				skeleton.viewMonster(console, &inBattle);
				break;
			case Parser::HELLHOUND:
				hellhound.viewMonster(console, &inBattle);
				break;
			case Parser::CHIMERA:
				chimera.viewMonster(console, &inBattle);
				break;
			case Parser::DRAGON:
				dragon.viewMonster(console, &inBattle);
				break;
			case Parser::ARCHDEMON:
				archdemon.viewMonster(console, &inBattle);
				break;
			case Parser::REAPER:
				reaper.viewMonster(console, &inBattle);
				break;
			case Parser::MIMIC:
				mimic.viewMonster(console, &inBattle);
				break;
			case Parser::SPIRIT:
				spirit.viewMonster(console, &inBattle);
				break;
			case Parser::HYDRA:
				hydra.viewMonster(console, &inBattle);
				break;
			case Parser::DEVIL:
				devil.viewMonster(console, &inBattle);
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

		// When the devil dies, end the loop
		if (devil.getAlive() == false)
		{
			parserOutput->command1 = Parser::QUIT;
		}

	} while (parserOutput->command1 != Parser::QUIT);

	// Change the console color back to white: in case the player quits while in battle
	console.changeToNormalColors();

	// When the devil dies, end the loop
	if (devil.getAlive() == false)
	{
		// Make the text green
		console.changeColor(2);

		// Output the end of game rant
		console.outputByCharacter(playerWon);
		console.outputByCharacter(endOfGame);
		
		// Change back to white
		console.changeToNormalColors();
	}

	// If the player died to lose the game, add extra statement telling them how they failed
	if (player.getAlive() == false)
	{
		// Change the ending text to red cause you died
		console.changeToBattleColors();

		console.outputByCharacter(playerLost);
		console.outputByCharacter(playerLostText);
		
		// Change back to white
		console.changeToNormalColors();
	}

	// Thank the user for playing the game
	console.outputByCharacter(thanksText);

	// Sleep for 10 seconds so the window doesn't automatically go away
	Sleep(10000);
}