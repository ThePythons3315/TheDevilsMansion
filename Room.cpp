#include <random>
#include <math.h>
#include "Room.h"

// Constructors
Room::Room()
{
	name = "";
	description = "";
	upRoomLocked = false;

	player = new Player();
	inventory = new Inventory();
	monster = new Monster();

	leftRoom = nullptr;
	upRoom = nullptr;
	rightRoom = nullptr;
	downRoom = nullptr;
}
Room::Room(std::string _name, std::string _description, bool _upRoomLocked)
{
	name = _name;
	description = _description;
	upRoomLocked = _upRoomLocked;

	player = new Player();
	inventory = new Inventory();
	monster = new Monster();

	leftRoom = nullptr;
	upRoom = nullptr;
	rightRoom = nullptr;
	downRoom = nullptr;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Room::setName(std::string _name)
{
	name = _name;
}
void Room::setDescription(std::string _description)
{
	description = _description;
}
void Room::setPlayer(Player& _player)
{
	player = &_player;
}
void Room::setLeftRoom(Room& _leftRoom)
{
	leftRoom = &_leftRoom;
}
void Room::setUpRoom(Room& _upRoom)
{
	upRoom = &_upRoom;
}
void Room::setRightRoom(Room& _rightRoom)
{
	rightRoom = &_rightRoom;
}
void Room::setDownRoom(Room& _downRoom)
{
	downRoom = &_downRoom;
}
void Room::setInventory(Inventory& _inventory)
{
	inventory = &_inventory;
}
void Room::setMonster(Monster& _monster)
{
	monster = &_monster;
}
void Room::setUpRoomLocked(bool _upRoomLocked)
{
	upRoomLocked = _upRoomLocked;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Room::getName()
{
	return name;
}
std::string Room::getDescription()
{
	return description;
}
Room* Room::getLeftRoom()
{
	return leftRoom;
}
Room* Room::getUpRoom()
{
	return upRoom;
}
Room* Room::getRightRoom()
{
	return rightRoom;
}
Room* Room::getDownRoom()
{
	return downRoom;
}
Player* Room::getPlayer()
{
	return player;
}
Inventory* Room::getInventory()
{
	return inventory;
}
Monster* Room::getMonster()
{
	return monster;
}
bool Room::getUpRoomLocked()
{
	return upRoomLocked;
}

// Set all 4 of the rooms that can be moved to from this current room
void Room::setOrientations(Room& _leftRoom, Room& _upRoom, Room& _rightRoom, Room& _downRoom)
{
	leftRoom = &_leftRoom;
	upRoom = &_upRoom;
	rightRoom = &_rightRoom;
	downRoom = &_downRoom;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Displays certain attributes of the room
///////////////////////////////////////////////////////////////////////////////////////////

// Outputs all information about the current room the player is in
void Room::printRoomInfo(GameUI console, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string roomInfo = "Room's information includes:\n\n";
	std::string roomName = "Room Name: " + name + "\n\n";
	std::string roomDescription = "Room Description: " + description + "\n";
	std::string monsterDeadText = "Monster In Room: dead.\n\n";
	std::string monsterInRoom = "Monster In Room: " + monster->getName() + ".\n\n";
	std::string noMonsterInRoom = "Monster In Room: no monster in room.\n\n";
	std::string inBattleErrorText = "Sorry this funcionality is not allowed while in battle.\n";

	// Do not print the room's information if the player is in battle
	if (*inBattle == false)
	{
		// Output the basics of the room
		console.writeOutput(roomInfo);
		console.writeOutput(roomName);
		console.writeOutput(roomDescription);

		// If there is a monster in the room, display they are there
		if (monster->getName() != "")
		{
			// If the monster is already dead, let them know they are dead
			// or let the user know what monster is still alive in there
			if (monster->getHealth() <= 0)
			{
				// Display that the monster is dead
				console.writeOutput(monsterDeadText);
			}
			else
			{
				// Display that the monster is currently in the room
				console.writeOutput(monsterInRoom);
			}
		}
		else
		{
			// Display that there is no monster in the room
			console.writeOutput(noMonsterInRoom);
		}

		// Redisplay the room's items and attacks
		inventory->displayItemInventory(console, "Room");
		console.writeOutput(extraNewline);
		inventory->displayAttackInventory(console, "Room");
	}
	else
	{
		// Display that the room cannot be redisplayed while in battle
		console.writeOutput(inBattleErrorText);
	}
}

// Outputs information about the room that the player has just moved into
void Room::printBasicRoom(GameUI console, std::string direction)
{
	// Text messages to the user
	std::string extraNewline = "\n";

	if (direction == "left")
	{
		// Print the description of the room
		console.writeOutput(leftRoom->getDescription());
		console.writeOutput(extraNewline);

		// Print the items and attacks in the room
		leftRoom->getInventory()->displayItemInventory(console, "Room");
		console.writeOutput(extraNewline);
		leftRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		leftRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "up")
	{
		// Print the description of the room
		console.writeOutput(upRoom->getDescription());
		console.writeOutput(extraNewline);

		// Print the items and attacks in the room
		upRoom->getInventory()->displayItemInventory(console, "Room");
		console.writeOutput(extraNewline);
		upRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		upRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "right")
	{
		// Print the description of the room
		console.writeOutput(rightRoom->getDescription());
		console.writeOutput("\n");

		// Print the items and attacks in the room
		rightRoom->getInventory()->displayItemInventory(console, "Room");
		console.writeOutput(extraNewline);
		rightRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		rightRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "down")
	{
		// Print the description of the room
		console.writeOutput(downRoom->getDescription());
		console.writeOutput(extraNewline);

		// Print the items in and attacks the room
		downRoom->getInventory()->displayItemInventory(console, "Room");
		console.writeOutput(extraNewline);
		downRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		downRoom->getMonster()->printMonsterInRoom(console);
	}
}

// Display the player's attributes to the screen as long as the player is not in battle
void Room::printPlayerAttributes(GameUI console, bool* inBattle)
{
	// Error message
	std::string errorMessage = "Sorry this funcionality is not allowed while in battle.\n";

	// The player is not allowed to redisplay the player's attributes while in battle
	if (*inBattle == false)
	{
		// Display player's attributes
		player->printPlayerInfo(console);
	}
	else
	{
		// Display error message that the player's attributes cannot be displayed while in battle
		console.writeOutput(errorMessage);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Move the player in the direction the user wants to go to
///////////////////////////////////////////////////////////////////////////////////////////

// Moves the player into the room in the direction the player entered. If there was 
// no room in the direction the player entered, display an error message
void Room::moveRoom(GameUI console, Room** currentRoom, std::string direction, bool* inBattle)
{
	// Error messages
	std::string doorLockedErrorMessage = "Sorry, that door is currently locked.\nPerhaps you need some kind of key to open it.\n";
	std::string noRoomErrorMessage = "There is no room in this direction.\nPlease try and move another way.\n";
	std::string inBattleErrorMessage = "Sorry this funcionality is not allowed while in battle.\n";

	// As long as the player is not in battle, the player can move to a new room
	if (*inBattle == false)
	{
		// If the room in the direction the user entered is not null, change the room
		// in that direction to be the new current room
		if (direction == "left" && leftRoom->getName() != "")
		{
			console.writeOutput("You are now in the " + leftRoom->getName() + ".\n");
			leftRoom->setPlayer(*player);
			player = new Player();
			*currentRoom = &*leftRoom;
			printBasicRoom(console, "left");
		}
		else if (direction == "up" && upRoom->getName() != "")
		{
			// If the room is not locked, then allow the player to move.
			// Otherwise tell them that the door is locked and they need a key.
			if (upRoomLocked == false)
			{
				console.writeOutput("You are now in the " + upRoom->getName() + ".\n");
				upRoom->setPlayer(*player);
				player = new Player();
				*currentRoom = &*upRoom;
				printBasicRoom(console, "up");
			}
			else
			{
				// Display that the room you are trying to enter is locked
				console.writeOutput(doorLockedErrorMessage);
			}

		}
		else if (direction == "right" && rightRoom->getName() != "")
		{
			console.writeOutput("You are now in the " + rightRoom->getName() + ".\n");
			rightRoom->setPlayer(*player);
			player = new Player();
			*currentRoom = &*rightRoom;
			printBasicRoom(console, "right");
		}
		else if (direction == "down" && downRoom->getName() != "")
		{
			console.writeOutput("You are now in the " + downRoom->getName() + ".\n");
			downRoom->setPlayer(*player);
			player = new Player();
			*currentRoom = &*downRoom;
			printBasicRoom(console, "down");
		}
		else
		{
			// The direction the user entered was not a possible way to move.
			// Let them know about this and tell them to try again in a different direction.
			console.writeOutput(noRoomErrorMessage);
		}
	}
	else
	{
		// Cannot move room because the player is currently in battle
		console.writeOutput(inBattleErrorMessage);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Functions that involve items moving from one inventory to another
///////////////////////////////////////////////////////////////////////////////////////////

// Picks up an item from the room and adds it to the player's inventory.
void Room::pickupItem(GameUI console, std::string item, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string pickUpItemText = "You have picked up a " + item + "\n";
	std::string itemNotInRoomText = "That item is not in the current room.\nPlease try a different room or check your inventory.\n";
	std::string inBattleErrorMessage = "Sorry this funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot pick up any items
	if (*inBattle == false)
	{
		// If the item is in the room's inventory, then continue with picking it up
		if (inventory->searchItemInventory(item) == true)
		{
			// Let the user know that they picked up the item
			console.writeOutput(pickUpItemText);

			// Get the item from the room's inventory
			Item* itemPointer = inventory->getItem(console, item);

			// Add the item to the player's inventory
			player->getInventory()->addItem(*itemPointer);

			// Remove the item from the room's inventory
			inventory->removeItem(console, item);

			// Redisplay the player's and room's item inventories
			console.writeOutput(extraNewline);
			player->getInventory()->displayItemInventory(console, "Player");
			console.writeOutput(extraNewline);
			inventory->displayItemInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.writeOutput(itemNotInRoomText);
		}
	}
	else
	{
		// Cannot pick up item while in battle
		console.writeOutput(inBattleErrorMessage);
	}
}

// Lets the player pick up an attack out of the current room that they are in
void Room::pickupAttack(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string pickUpAttackText = "You have picked up the attack: " + attack + "\n";
	std::string tooManyAttacksText = "The player already has 4 attacks, which is the maximum amount of attacks allowed.\n"
		"Please drop an attack before trying to pick one up.\n";
	std::string itemNotInRoomText = "That attack is not in the current room.\n"
		"Please try a different room or check your inventory.\n";
	std::string inBattleErrorMessage = "Sorry this funcionality is not allowed while in battle.\n";


	// If the player is currently in battle, they cannot pick up any attacks
	if (*inBattle == false)
	{
		// If the attack is in the room's inventory, then continue with picking it up
		if (inventory->searchAttackInventory(attack) == true && player->getInventory()->getAttackInventorySize() < 4)
		{
			// Let the used know that they picked up the attack
			console.writeOutput(pickUpAttackText);

			// Get the attack from the room's inventory
			Attack* attackPointer = inventory->getAttack(console, attack);

			// Add the attack to the player's inventory
			player->getInventory()->addAttack(console, *attackPointer);

			// Remove the item from the room's inventory
			inventory->removeAttack(console, attack);

			// Redisplay the player's and room's attack inventories
			console.writeOutput(extraNewline);
			player->getInventory()->displayAttackInventory(console, "Player");
			console.writeOutput(extraNewline);
			inventory->displayAttackInventory(console, "Room");
		}
		else
		{
			// Display error messages. Either the tooManyAttacks message or the noInRoom message
			if (player->getInventory()->getAttackInventorySize() == 4)
			{
				// If there are already 4 attacks in the player's inventory
				console.writeOutput(tooManyAttacksText);
			}
			else
			{
				// If the attack is not in the inventory, then let the user know it is not being deleted
				console.writeOutput(itemNotInRoomText);
			}
		}
	}
	else
	{
		// Cannot pick up attack while in battle
		console.writeOutput(inBattleErrorMessage);
	}
}

// Drops an item from the player and adds it to the room's inventory.
void Room::dropItem(GameUI console, std::string item, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string dropItemText = "You have dropped a " + item + "\n";
	std::string missingItemText = "That item is not in your item inventory.\nYou are unable to drop that item.\n";
	std::string inBattleErrorMessage = "Sorry this funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot drop any items
	if (*inBattle == false)
	{
		// If the item is in the players's inventory, then continue with dropping it
		if (player->getInventory()->searchItemInventory(item) == true)
		{
			// Let the user know they are dropping the item
			console.writeOutput(dropItemText);

			// Get the item from the player's inventory
			Item* itemPointer = player->getInventory()->getItem(console, item);

			// Add the item to the room's inventory
			inventory->addItem(*itemPointer);

			// Remove the item from the player's inventory
			player->getInventory()->removeItem(console, item);

			// Redisplay the player's and room's room inventories
			console.writeOutput(extraNewline);
			player->getInventory()->displayItemInventory(console, "Player");
			console.writeOutput(extraNewline);
			inventory->displayItemInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.writeOutput(missingItemText);
		}
	}
	else
	{
		// Cannot drop item while in battle
		console.writeOutput(inBattleErrorMessage);
	}
}

// Drops the attack from the player to the floor of the current room
void Room::dropAttack(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string dropAttackText = "You have dropped the attack: " + attack + "\n";
	std::string missingAttackText = "That attack is not in your attack inventory.\nYou are unable to drop that attack.\n";
	std::string inBattleErrorMessage = "Sorry this funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot drop any items
	if (*inBattle == false)
	{
		// If the item is in the players's inventory, then continue with dropping it
		if (player->getInventory()->searchAttackInventory(attack) == true)
		{
			console.writeOutput(dropAttackText);

			// Get the item from the player's inventory
			Attack* attackPointer = player->getInventory()->getAttack(console, attack);

			// Add the item to the room's inventory
			inventory->addAttack(console, *attackPointer);

			// Remove the item from the player's inventory
			player->getInventory()->removeAttack(console, attack);

			// Redisplay the player's and room's attack inventories
			console.writeOutput(extraNewline);
			player->getInventory()->displayAttackInventory(console, "Player");
			console.writeOutput(extraNewline);
			inventory->displayAttackInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.writeOutput(missingAttackText);
		}
	}
	else
	{
		// Cannot drop attack while in battle
		console.writeOutput(inBattleErrorMessage);
	}
}

// Drops the attack the monster was holding to the ground
void Room::dropMonsterAttack(GameUI console)
{
	// Get the item from the monster's inventory
	Attack* attackPointer = monster->getInventory()->getAttack(console);

	// Add the item to the room's inventory
	inventory->addAttack(console, *attackPointer);

	// Remove the item from the monster's inventory
	monster->getInventory()->removeAttack(console, monster->getInventory()->getAttack(console)->getName());
}

///////////////////////////////////////////////////////////////////////////////////////////
// Functions used for battle
///////////////////////////////////////////////////////////////////////////////////////////

// Initiates the battle sequence with the monster and handles all of the error exceptions
void Room::battleMonster(GameUI console, std::string monsterName, bool* inBattle)
{
	// Text messages to the user
	std::string monsterAlreadyDeafeatedText = "The " + monster->getName() + " has already been defeated, you cannot go into battle with it.\n";
	std::string enteringBattleText = player->getName() + " is now going into battle with the " + monster->getName() + ".\n";
	std::string monsterNotInRoom = "That monster is not in this room, you cannot go into battle with it.\n";

	// Make sure the correct monster is in the current room before turning inBattle to true
	if (monster->getName() == monsterName)
	{
		// If the monster is in the room and not already defeated, enter battle
		if (monster->getHealth() <= 0)
		{
			// Tell the user that the monster in the room was already defeated
			console.writeOutput(monsterAlreadyDeafeatedText);
		}
		else
		{
			// Let the player enter battle with the monster
			console.writeOutput(enteringBattleText);
			*inBattle = true;
		}
	}
	else
	{
		// Tell the user that the monster they are trying to battle is not in the current room
		console.writeOutput(monsterNotInRoom);
	}
}

// Performs a singular round of battle. 1 player attack and 1 monster attack (if needed)
void Room::battle(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string playerDefeatedText = "\n" + player->getName() + " has been defeated.\n\nThe battle has ended.\n";
	std::string monsterDefeatedText = "\nThe " + monster->getName() + " has been defeated.\n\nThe battle has ended.\n\n";
	std::string dropMonsterAttackText = "The " + monster->getName() + " has dropped his " + monster->getInventory()->getAttack(console)->getName() + " attack.\n";

	// Player attacks the monster
	playerAttacksMonster(console, attack);

	// If the monster dies, then do not let the monster attack again. Tell the user that the
	// monster has been defeated.
	if (monster->getHealth() > 0)
	{
		// Monster attacks the player
		console.writeOutput(extraNewline);
		monsterAttacksPlayer(console);

		// If the player dies, kill the player, let the user know they have been defeated and then
		// end the battle
		if (player->getHealth() <= 0)
		{
			// The player has been defeated. Kill it
			player->kill();

			// Let the user know the player has been defeated.
			console.writeOutput(playerDefeatedText);

			// Get out of the battle state
			*inBattle = false;
		}
	}
	else
	{
		// The monster has been defeated. Kill it
		monster->kill();

		// Let the user know the monster has been defeated.
		console.writeOutput(monsterDefeatedText);

		// Drop the attack the monster was using to the ground of the room
		console.writeOutput(dropMonsterAttackText);
		dropMonsterAttack(console);

		// Get out of the battle state
		*inBattle = false;
	}
}

// Performs the error checking when a player tries using an attack in battle
void Room::useAttack(GameUI console, std::string attack, bool* inBattle, Parser::InputStruct* parserOutput)
{
	std::string notInBattleMessage = "Sorry you can only use attacks when in battle.\n";
	std::string doNotHaveAttackMessage = "Sorry you do not currently have access to that attack.\n";

	// Only run the battle sequence if the player is currently in battle
	if (*inBattle == true)
	{
		// If the player has the attack in their inventory, they can use it. Otherwise tell them
		// that they do not have access to that attack
		if (player->getInventory()->searchAttackInventory(attack) != false)
		{
			// Run the sequence of attacks
			battle(console, attack, inBattle);

			// If the player is dead, we should not continue the game
			if (player->getAlive() == false)
			{
				// The player is dead, end the game.
				parserOutput->command1 = Parser::QUIT;
			}
		}
		else
		{
			// Tell the user that they currently do not have this attack
			console.writeOutput(doNotHaveAttackMessage);
		}
	}
	else
	{
		// Tell the user they cannot use attacks when not in battle
		console.writeOutput(notInBattleMessage);
	}
}

// Allows the player to attack the monster. If the attack hits, then the monster
// will take damage.
void Room::playerAttacksMonster(GameUI console, std::string attack)
{
	// Get the amount of damage the attack will do
	int hitPoints = player->getInventory()->getAttack(console, attack)->getDamage();

	// Good messages to the user and also error messages
	std::string attackPlayerUsedText = "Player has used: " + attack + ".\n";
	std::string attackHitText = "The attack hit for " + std::to_string(hitPoints * -1) + " damage.\n";
	std::string attackMissedText = "The attack missed!! " + monster->getName() + " took no damage.\n";
	std::string monsterDiedHealthText = monster->getName() + "'s New Health: 0.\n";
	std::string monsterAlreadyParalyzed = "The monster continues to be paralyzed.\n";
	std::string playerParalyzed = "The player's paralysis prevented them from attacking.\n";

	// If the player is paralyzed and the paralysis prevents them from attacking, tell the user they could not attack 
	if (checkPlayerParalyzed() == true && hitOrMiss(player->getStatusEffectHitChance()) == true)
	{
		// Display that the player cannot attack
		console.writeOutput(playerParalyzed);
	}
	else
	{
		// Display the attack the player used to the user
		console.writeOutput(attackPlayerUsedText);

		// If the attack is going to be a hit, take hitpoints from the monster and display the 
		// new health of the monster. Otherwise say the attack missed.
		if (hitOrMiss(player->getInventory()->getAttack(console, attack)->getHitChance()) == true)
		{
			// Make the damage affect the monster
			monster->changeHealth(console, hitPoints);

			// Output that the player's attack hit
			console.writeOutput(attackHitText);

			// Completes the check to see if the monster was paralyzed from this attack
			monsterWasParalyzed(console, attack);

			// If the monster's health reaches 0 or below, output that they died with 0 health left
			if (monster->getHealth() <= 0)
			{
				// Output the health being 0
				console.writeOutput(monsterDiedHealthText);
			}
			else
			{
				// Output the monster's health after the player's attack has hit
				console.writeOutput("New Monster Health: " + std::to_string(monster->getHealth()) + ".\n");
			}
		}
		else
		{
			// Let the user know that the monster's attack missed and redisplay their health
			console.writeOutput(attackMissedText);
			if (checkMonsterParalyzed() == true)
			{
				console.writeOutput(monsterAlreadyParalyzed);
			}
			console.writeOutput("Monster Health: " + std::to_string(monster->getHealth()) + ".\n");
		}
	}
}

// Allows the monster to attack the player. If the attack hits, then the player
// will take damage.
void Room::monsterAttacksPlayer(GameUI console)
{
	// get the amount of damage the attack will do, and the attacks name
	int hitPoints = monster->getInventory()->getAttack(console)->getDamage();
	std::string attackName = monster->getInventory()->getAttack(console)->getName();

	// Good messages to the user and also error messages
	std::string attackMonsterUsedText = "Monster has used: " + attackName + ".\n";
	std::string attackHitText = "The attack hit for " + std::to_string(hitPoints * -1) + " damage.\n";
	std::string attackMissedText = "The attack missed!! " + player->getName() + " took no damage.\n";
	std::string playerDiedHealthText = player->getName() + "'s New Health: 0.\n";
	std::string playerAlreadyParalyzed = "The player continues to be paralyzed.\n";
	std::string monsterParalyzed = "The monster's paralysis prevented them from attacking.\n";

	// If the player is paralyzed and the paralysis prevents them from attacking, tell the user they could not attack 
	if (checkMonsterParalyzed() == true && hitOrMiss(monster->getStatusEffectHitChance()) == true)
	{
		// Display that the player cannot attack
		console.writeOutput(monsterParalyzed);
	}
	else
	{
		// Display the attack the monster used to the user
		console.writeOutput(attackMonsterUsedText);

		// If the attack is going to be a hit, take hitpoints from the monster and display the 
		// new health of the monster. Otherwise say the attack missed.
		if (hitOrMiss(monster->getInventory()->getAttack(console)->getHitChance()) == true)
		{
			// Make the damage affect the player
			player->changeHealth(console, hitPoints);

			// Output that the player's attack hit
			console.writeOutput(attackHitText);

			// Completes the check to see if the player was paralyzed from this attack
			playerWasParalyzed(console);

			// If the player's health reaches 0 or below, output that they died with 0 health left
			if (player->getHealth() <= 0)
			{
				// Output the health being 0
				console.writeOutput(playerDiedHealthText);
			}
			else
			{
				// Output the player's health after the monster's attack has hit
				console.writeOutput(player->getName() + "'s New Health: " + std::to_string(player->getHealth()) + ".\n");
			}
		}
		else
		{
			// Let the user know that the monster's attack missed and redisplay their health
			console.writeOutput(attackMissedText);
			if (checkPlayerParalyzed() == true)
			{
				console.writeOutput(playerAlreadyParalyzed);
			}
			console.writeOutput(player->getName() + "'s Health: " + std::to_string(player->getHealth()) + ".\n");
		}
	}
}

// Takes an integer and randomly chooses whether the attack
// will hit or miss based off of that number
bool Room::hitOrMiss(int hitChance)
{
	// Used for generating a random number
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 100.0);

	// Variable to hold the randomly generated number
	int number = 0;
	number = dist(mt);

	// Check if the random number is less than the hitChance
	// If it is, then the attack will hit and the monster will be affected.
	// If the number is higher than hitChance then the monster will be
	// left unaffected by the hit
	if (number <= hitChance) {
		return true;
	}
	return false;

}

// Checks to see if the monster was paralyzed from the attack
void Room::monsterWasParalyzed(GameUI console, std::string attack)
{
	// Text messages to the user
	std::string notAParalysisMove = "This move does not have paralysis.\n";
	std::string monsterParalyzed = "The monster has been paralyzed from the attack.\n";
	std::string monsterNotParalyzed = "The monster has not been paralyzed from the attack.\n";
	std::string monsterAlreadyParalyzed = "The monster continues to be paralyzed.\n";
	
	// Check to see if the monster is already paralyzed or not
	if (checkMonsterParalyzed() == true)
	{
		console.writeOutput(monsterAlreadyParalyzed);
	}
	else
	{
		// Make sure the attack has the paralysis effect
		if (player->getInventory()->getAttack(console, attack)->getStatusEffect() == 1)
		{
			// If the attack has the paralysis effect, then check to see if the 
			// player will be paralyzed or not
			if (hitOrMiss(player->getInventory()->getAttack(console, attack)->getStatusEffectHitChance()) == true)
			{
				// Set the monster to be paralyzed
				monster->setStatusEffect(1);
				console.writeOutput(monsterParalyzed);
			}
			else
			{
				// The monster was not paralyzed
				//console.writeOutput(monsterNotParalyzed);
			}
		}
		else
		{
			// This is not a paralysis move
			//console.writeOutput(notAParalysisMove);
		}
	}
}

// Checks to see if the player was paralyzed from the attack
void Room::playerWasParalyzed(GameUI console)
{
	// Text messages to the user
	std::string notAParalysisMove = "This move does not have paralysis.\n";
	std::string playerParalyzed = "The player has been paralyzed from the attack.\n";
	std::string playerNotParalyzed = "The player has not been paralyzed from the attack.\n";
	std::string playerAlreadyParalyzed = "The player continues to be paralyzed.\n";

	// Check to see if the player is already paralyzed or not
	if (checkPlayerParalyzed() == true)
	{
		console.writeOutput(playerAlreadyParalyzed);
	}
	else
	{
		// Make sure the attack has the paralysis effect
		if (monster->getInventory()->getAttack(console)->getStatusEffect() == 1)
		{
			// If the attack has the paralysis effect, then check to see if the 
			// player will be paralyzed or not
			if (hitOrMiss(monster->getInventory()->getAttack(console)->getStatusEffectHitChance()) == true)
			{
				// Set the monster to be paralyzed
				player->setStatusEffect(1);
				console.writeOutput(playerParalyzed);
			}
			else
			{
				// The monster was not paralyzed
				//console.writeOutput(playerNotParalyzed);
			}
		}
		else
		{
			// This is not a paralysis move
			//console.writeOutput(notAParalysisMove);
		}
	}
}

// Before allowing the monster to attack, we must first check to see if the 
// monster is paralyzed. If they are paralyzed perform the check to see if the
// monster will be allowed to attack or not
bool Room::checkMonsterParalyzed()
{
	// Check to see if the monster is paralyzed
	if (monster->getStatusEffect() == 1)
	{
		// The monster is paralyzed
		return true;
	}
	else
	{
		// The monster is not paralyzed
		return false;
	}
}

// Before allowing the player to attack, we must first check to see if the 
// player is paralyzed. If they are paralyzed perform the check to see if the
// player will be allowed to attack or not
bool Room::checkPlayerParalyzed()
{
	// Check to see if the monster is paralyzed
	if (player->getStatusEffect() == 1)
	{
		// The player is paralyzed
		return true;
	}
	else
	{
		// The player is not paralyzed
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Functions related to the usage of doors
///////////////////////////////////////////////////////////////////////////////////////////

// Lock the door of a room
void Room::lockDoor()
{
	upRoomLocked = true;
}

// Open a locked door of a room
void Room::unlockDoor()
{
	upRoomLocked = false;
}

// Tries to use the key to unlock the door
void Room::useKey(GameUI console, std::string key, bool* inBattle)
{
	// Error messages
	std::string inBattleText = "Sorry this funcionality is not allowed while in battle.\n";
	std::string openingDoorText = "You have opened the door to The " + getUpRoom()->getName() + ".\n";
	std::string doorIsAlreadyOpenText = "Sorry the door is already open, no need to use the key.\n";
	std::string itemNotInInventoryText = "Sorry you do not currently have that item in your posession.\n";

	// Check to make sure the player is not in battle before trying to use the key
	if (*inBattle == false)
	{
		// Make sure the user has the item in their inventory before trying to use it.
		if (player->getInventory()->searchItemInventory(key) == true)
		{
			// If the upRoom door is locked, then you are allowed to use the key
			if (getUpRoomLocked() == true)
			{
				// Unlock the door that is locked
				unlockDoor();

				// Let the user know that they unlocked the door
				console.writeOutput(openingDoorText);
			}
			else
			{
				// Tell the user that the key cannot be used on an open door
				console.writeOutput(doorIsAlreadyOpenText);
			}
		}
		else
		{
			// Tell the user that the item is not in their inventory
			console.writeOutput(itemNotInInventoryText);
		}
	}
	else
	{
		// The player cannot use the key to open the door when in battle
		console.writeOutput(inBattleText);
	}
}