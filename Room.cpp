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
	std::string roomName = "Room Name: " + name + ".\n\n";
	std::string roomDescription = description + "\n";
	std::string monsterDeadText = "Monster In Room: dead.\n";
	std::string monsterInRoom = "Monster In Room: " + monster->getName() + ".\n";
	std::string noMonsterInRoom = "Monster In Room: None.\n";
	std::string inBattleErrorText = "This funcionality is not allowed while in battle.\n";

	// Do not print the room's information if the player is in battle
	if (*inBattle == false)
	{
		// Output the basics of the room
		console.outputByCharacter(roomInfo);
		console.outputByCharacter(roomName);
		console.outputByCharacter(roomDescription);

		// Redisplay the room's items and attacks
		inventory->displayItemInventory(console, "Room");
		console.outputByCharacter(extraNewline);
		inventory->displayAttackInventory(console, "Room");
		console.outputByCharacter(extraNewline);

		// If there is a monster in the room, display they are there
		if (monster->getName() != "")
		{
			// If the monster is already dead, let them know they are dead
			// or let the user know what monster is still alive in there
			if (monster->getHealth() <= 0)
			{
				// Display that the monster is dead
				console.outputByCharacter(monsterDeadText);
			}
			else
			{
				// Display that the monster is currently in the room
				console.outputByCharacter(monsterInRoom);
			}
		}
		else
		{
			// Display that there is no monster in the room
			console.outputByCharacter(noMonsterInRoom);
		}
	}
	else
	{
		// Display that the room cannot be redisplayed while in battle
		console.outputByCharacter(inBattleErrorText);
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
		console.outputByCharacter(extraNewline);
		console.outputByCharacter(leftRoom->getDescription());
		console.outputByCharacter(extraNewline);

		// Print the items and attacks in the room
		leftRoom->getInventory()->displayItemInventory(console, "Room");
		console.outputByCharacter(extraNewline);
		leftRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		leftRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "up")
	{
		// Print the description of the room
		console.outputByCharacter(extraNewline);
		console.outputByCharacter(upRoom->getDescription());
		console.outputByCharacter(extraNewline);

		// Print the items and attacks in the room
		upRoom->getInventory()->displayItemInventory(console, "Room");
		console.outputByCharacter(extraNewline);
		upRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		upRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "right")
	{
		// Print the description of the room
		console.outputByCharacter(extraNewline);
		console.outputByCharacter(rightRoom->getDescription());
		console.outputByCharacter("\n");

		// Print the items and attacks in the room
		rightRoom->getInventory()->displayItemInventory(console, "Room");
		console.outputByCharacter(extraNewline);
		rightRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		rightRoom->getMonster()->printMonsterInRoom(console);
	}
	else if (direction == "down")
	{
		// Print the description of the room
		console.outputByCharacter(extraNewline);
		console.outputByCharacter(downRoom->getDescription());
		console.outputByCharacter(extraNewline);

		// Print the items in and attacks the room
		downRoom->getInventory()->displayItemInventory(console, "Room");
		console.outputByCharacter(extraNewline);
		downRoom->getInventory()->displayAttackInventory(console, "Room");

		// If there is a monster in the room, then display the monster to the user
		downRoom->getMonster()->printMonsterInRoom(console);
	}
}

// Display the player's attributes to the screen as long as the player is not in battle
void Room::printPlayerAttributes(GameUI console, bool* inBattle)
{
	// Text messages for the user
	std::string extraNewline = "\n";
	std::string playerInfo = "Player's information includes:\n\n";
	std::string playerName = "Player Name: " + player->getName() + ".\n\n";
	std::string roomName = "Current Room: " + name + ".\n\n";
	std::string playerInBattle = player->getName() + " is currently in battle with: " + monster->getName() + ".\n\n";
	std::string notInBattle = player->getName() + " is not in battle with a monster.\n\n";

	// Show player's name
	console.outputByCharacter(playerInfo);
	console.outputByCharacter(playerName);

	// Show the room the player is currently in
	console.outputByCharacter(roomName);

	// Display if the player is in battle or not
	if (*inBattle == true)
	{
		// Is in battle
		console.outputByCharacter(playerInBattle);
	}
	else
	{
		// Is not in battle
		console.outputByCharacter(notInBattle);
	}

	// Show the player's item inventory
	player->getInventory()->displayItemInventory(console, "Player");
	console.outputByCharacter(extraNewline);

	// Show the player's attack iventory
	player->getInventory()->displayAttackInventory(console, "Player");

	// Show the player's health
	console.outputByCharacter(extraNewline);
	player->displayBothHealth(console);
}

// Shows a map of the game and the current room the player is in
void Room::showMap(GameUI console, bool* inBattle)
{
	// Error message
	std::string inBattleErrorMessage = "Why you trying to look at your map when you're in battle.\n"
									   "Your tomfoolery does not cease to amaze me.\n";

	// Dont be able to view map while in battle
	if (*inBattle == false)
	{
		// Show the maps
		if (name == "Starting Steps")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
								"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
								"|                                       |  |                                                        |\n"
								"|                                       |  |                                                        |\n"
								"|                          --     --     --                                                         |\n"
								"|                         |  | = |  | = |  |                                                        |\n"
								"|                         |  | = |  | = |  |                                                        |\n"
								"|                          --     --     --                                                         |\n"
								"|                                |  |                                                               |\n"
								"|                                |  |                                                               |\n"
								"|                          --     --     --     --                                                  |\n"
								"|                         |  | = |  | = |  | = |  |                                                 |\n"
								"|                         |  | = |  | = |  | = |  |                                                 |\n"
								"|                   --     --     --     --     --                                                  |\n"
								"|                  |  | = |  | = |  | = |  |                                                        |\n"
								"|                  |  | = |  | = |  | = |  |                                                        |\n"
								"|                   --     --     --     --                                                         |\n"
								"|                                |  |                                                               |\n"
								"|                                |  |                                                               |\n"
								"|                                 --                                                                |\n"
								"|                                |##|                                                               |\n"
								"|                                |##|                                                               |\n"
								"|                                 --                                                                |\n"
								" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Starting Room")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |##|                                                               |\n"
				"|                                |##|                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room Of Unlucky Souls")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |##| = |  |                                                        |\n"
				"|                  |  | = |  | = |##| = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room Of The Devil's Most Loyal Friend")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |##| = |  | = |  |                                                        |\n"
				"|                  |  | = |##| = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Treasure Room")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |##| = |  | = |  | = |  |                                                        |\n"
				"|                  |##| = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Death")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |##| = |  | = |  | = |  |                                                 |\n"
				"|                         |##| = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Weird")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |##| = |  | = |  |                                                 |\n"
				"|                         |  | = |##| = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Mirrors")
		{
		std::string Map = " ---------------------------------------------------------------------------------------------------\n"
			"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
			"|                                       |  |                                                        |\n"
			"|                                       |  |                                                        |\n"
			"|                          --     --     --                                                         |\n"
			"|                         |  | = |  | = |  |                                                        |\n"
			"|                         |  | = |  | = |  |                                                        |\n"
			"|                          --     --     --                                                         |\n"
			"|                                |  |                                                               |\n"
			"|                                |  |                                                               |\n"
			"|                          --     --     --     --                                                  |\n"
			"|                         |  | = |  | = |##| = |  |                                                 |\n"
			"|                         |  | = |  | = |##| = |  |                                                 |\n"
			"|                   --     --     --     --     --                                                  |\n"
			"|                  |  | = |  | = |  | = |  |                                                        |\n"
			"|                  |  | = |  | = |  | = |  |                                                        |\n"
			"|                   --     --     --     --                                                         |\n"
			"|                                |  |                                                               |\n"
			"|                                |  |                                                               |\n"
			"|                                 --                                                                |\n"
			"|                                |  |                                                               |\n"
			"|                                |  |                                                               |\n"
			"|                                 --                                                                |\n"
			" ---------------------------------------------------------------------------------------------------\n";

		console.writeOutput(Map);
		}
		else if (name == "Room Of Demonic Magic")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |##|                                                        |\n"
				"|                  |  | = |  | = |  | = |##|                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Valuables Room")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |##|                                                 |\n"
				"|                         |  | = |  | = |  | = |##|                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Gold")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |##|                                                               |\n"
				"|                                |##|                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Ghouls")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |##| = |  |                                                        |\n"
				"|                         |  | = |##| = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Riches Room")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |##| = |  | = |  |                                                        |\n"
				"|                         |##| = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of Snakes")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |  |                                                        |\n"
				"|                                       |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |##|                                                        |\n"
				"|                         |  | = |  | = |##|                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
		else if (name == "Room of The Devil")
		{
			std::string Map = " ---------------------------------------------------------------------------------------------------\n"
				"|  # MEANS YOU ARE IN THAT ROOM          --                                                         |\n"
				"|                                       |##|                                                        |\n"
				"|                                       |##|                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                         |  | = |  | = |  |                                                        |\n"
				"|                          --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                          --     --     --     --                                                  |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                         |  | = |  | = |  | = |  |                                                 |\n"
				"|                   --     --     --     --     --                                                  |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                  |  | = |  | = |  | = |  |                                                        |\n"
				"|                   --     --     --     --                                                         |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				"|                                |  |                                                               |\n"
				"|                                |  |                                                               |\n"
				"|                                 --                                                                |\n"
				" ---------------------------------------------------------------------------------------------------\n";

			console.writeOutput(Map);
		}
	}
	else
	{
		// Can't show the map cause the player is in battle
		console.outputByCharacter(inBattleErrorMessage);
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
	std::string doorLockedErrorMessage = "That door is currently locked dumbass.\nGo look for a key to open it.\n";
	std::string noRoomErrorMessage = "There is no room in this direction dumbass.\nTry and move another way.\n";
	std::string inBattleErrorMessage = "This funcionality is not allowed while in battle.\n";

	// As long as the player is not in battle, the player can move to a new room
	if (*inBattle == false)
	{
		// If the room in the direction the user entered is not null, change the room
		// in that direction to be the new current room
		if (direction == "left" && leftRoom->getName() != "")
		{
			console.outputByCharacter("You are now in the " + leftRoom->getName() + ".\n");
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
				console.outputByCharacter("You are now in the " + upRoom->getName() + ".\n");
				upRoom->setPlayer(*player);
				player = new Player();
				*currentRoom = &*upRoom;
				printBasicRoom(console, "up");
			}
			else
			{
				// Display that the room you are trying to enter is locked
				console.outputByCharacter(doorLockedErrorMessage);
			}

		}
		else if (direction == "right" && rightRoom->getName() != "")
		{
			console.outputByCharacter("You are now in the " + rightRoom->getName() + ".\n");
			rightRoom->setPlayer(*player);
			player = new Player();
			*currentRoom = &*rightRoom;
			printBasicRoom(console, "right");
		}
		else if (direction == "down" && downRoom->getName() != "")
		{
			// Change the grammar of our sentence if moving to the starting steps
			if (downRoom->getName() == "Starting Steps")
			{
				// Use at for starting steps
				console.outputByCharacter("You are now at the " + downRoom->getName() + ".\n");
			}
			else
			{
				// Use in for all other rooms
				console.outputByCharacter("You are now in the " + downRoom->getName() + ".\n");
			}
			downRoom->setPlayer(*player);
			player = new Player();
			*currentRoom = &*downRoom;
			printBasicRoom(console, "down");
		}
		else
		{
			// The direction the user entered was not a possible way to move.
			// Let them know about this and tell them to try again in a different direction.
			console.outputByCharacter(noRoomErrorMessage);
		}
	}
	else
	{
		// Cannot move room because the player is currently in battle
		console.outputByCharacter(inBattleErrorMessage);
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
	std::string itemNotInRoomText = "Are you dumb? That item is not in the current room.\nTry a different room or check your inventory.\n";
	std::string inBattleErrorMessage = "This funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot pick up any items
	if (*inBattle == false)
	{
		// If the item is in the room's inventory, then continue with picking it up
		if (inventory->searchItemInventory(item) == true)
		{
			// Let the user know that they picked up the item
			console.outputByCharacter(pickUpItemText);

			// Get the item from the room's inventory
			Item* itemPointer = inventory->getItem(console, item);

			// Add the item to the player's inventory
			player->getInventory()->addItem(*itemPointer);

			// Remove the item from the room's inventory
			inventory->removeItem(console, item);

			// Redisplay the player's and room's item inventories
			console.outputByCharacter(extraNewline);
			player->getInventory()->displayItemInventory(console, "Player");
			console.outputByCharacter(extraNewline);
			inventory->displayItemInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.outputByCharacter(itemNotInRoomText);
		}
	}
	else
	{
		// Cannot pick up item while in battle
		console.outputByCharacter(inBattleErrorMessage);
	}
}

// Lets the player pick up an attack out of the current room that they are in
void Room::pickupAttack(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string pickUpAttackText = "You have picked up the attack: " + attack + "\n";
	std::string tooManyAttacksText = "The player already has 4 attacks, which is the maximum amount of attacks allowed.\n"
									 "Drop an attack before trying to pick one up...... you imbecile.\n";
	std::string attackNotInRoomText = "Are you dumb? That attack is not in the current room.\nTry a different room or check your inventory.\n";
	std::string inBattleErrorMessage = "This funcionality is not allowed while in battle.\n";


	// If the player is currently in battle, they cannot pick up any attacks
	if (*inBattle == false)
	{
		// If the attack is in the room's inventory, then continue with picking it up
		if (inventory->searchAttackInventory(attack) == true && player->getInventory()->getAttackInventorySize() < 4)
		{
			// Let the used know that they picked up the attack
			console.outputByCharacter(pickUpAttackText);

			// Get the attack from the room's inventory
			Attack* attackPointer = inventory->getAttack(console, attack);

			// Add the attack to the player's inventory
			player->getInventory()->addAttack(console, *attackPointer);

			// Remove the item from the room's inventory
			inventory->removeAttack(console, attack);

			// Redisplay the player's and room's attack inventories
			console.outputByCharacter(extraNewline);
			player->getInventory()->displayAttackInventory(console, "Player");
			console.outputByCharacter(extraNewline);
			inventory->displayAttackInventory(console, "Room");
		}
		else
		{
			// Display error messages. Either the tooManyAttacks message or the noInRoom message
			if (player->getInventory()->getAttackInventorySize() == 4)
			{
				// If there are already 4 attacks in the player's inventory
				console.outputByCharacter(tooManyAttacksText);
			}
			else
			{
				// If the attack is not in the inventory, then let the user know it is not being deleted
				console.outputByCharacter(attackNotInRoomText);
			}
		}
	}
	else
	{
		// Cannot pick up attack while in battle
		console.outputByCharacter(inBattleErrorMessage);
	}
}

// Drops an item from the player and adds it to the room's inventory.
void Room::dropItem(GameUI console, std::string item, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string dropItemText = "You have dropped a " + item + "\n";
	std::string missingItemText = "That item ain't in your item inventory.\nYour dumbass can't drop that item.\n";
	std::string inBattleErrorMessage = "This funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot drop any items
	if (*inBattle == false)
	{
		// If the item is in the players's inventory, then continue with dropping it
		if (player->getInventory()->searchItemInventory(item) == true)
		{
			// Let the user know they are dropping the item
			console.outputByCharacter(dropItemText);

			// Get the item from the player's inventory
			Item* itemPointer = player->getInventory()->getItem(console, item);

			// Add the item to the room's inventory
			inventory->addItem(*itemPointer);

			// Remove the item from the player's inventory
			player->getInventory()->removeItem(console, item);

			// Redisplay the player's and room's room inventories
			console.outputByCharacter(extraNewline);
			player->getInventory()->displayItemInventory(console, "Player");
			console.outputByCharacter(extraNewline);
			inventory->displayItemInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.outputByCharacter(missingItemText);
		}
	}
	else
	{
		// Cannot drop item while in battle
		console.outputByCharacter(inBattleErrorMessage);
	}
}

// Drops the attack from the player to the floor of the current room
void Room::dropAttack(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string dropAttackText = "You have dropped the attack: " + attack + "\n";
	std::string missingAttackText = "That attack is not in your attack inventory.\nYour dumbass can't drop that attack.\n";
	std::string inBattleErrorMessage = "This funcionality is not allowed while in battle.\n";

	// If the player is currently in battle, they cannot drop any items
	if (*inBattle == false)
	{
		// If the item is in the players's inventory, then continue with dropping it
		if (player->getInventory()->searchAttackInventory(attack) == true)
		{
			console.outputByCharacter(dropAttackText);

			// Get the item from the player's inventory
			Attack* attackPointer = player->getInventory()->getAttack(console, attack);

			// Add the item to the room's inventory
			inventory->addAttack(console, *attackPointer);

			// Remove the item from the player's inventory
			player->getInventory()->removeAttack(console, attack);

			// Redisplay the player's and room's attack inventories
			console.outputByCharacter(extraNewline);
			player->getInventory()->displayAttackInventory(console, "Player");
			console.outputByCharacter(extraNewline);
			inventory->displayAttackInventory(console, "Room");
		}
		else
		{
			// If the item is not in the inventory, then let the user know it is not being deleted
			console.outputByCharacter(missingAttackText);
		}
	}
	else
	{
		// Cannot drop attack while in battle
		console.outputByCharacter(inBattleErrorMessage);
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

// Drops the attack the monster was holding to the ground
void Room::dropMonsterItem(GameUI console, std::string item)
{
	// Text message to the user
	std::string output = "The " + monster->getName() + " dropped a " + item + " to the ground.\n\n";
	std::string errorMessage = "The monster is not holding any items to drop.\n";

	// If the monster has an item... do this shit
	if (monster->getInventory()->getItemInventorySize() == 1)
	{
		// Get the item from the monster's inventory
		Item* itemPointer = monster->getInventory()->getItem(console, item);

		// Add the item to the room's inventory
		inventory->addItem(*itemPointer);

		// Remove the item from the monster's inventory
		monster->getInventory()->removeItem(console, item);

		// Display the message
		console.outputByCharacter(output);
	}
	else
	{
		// Display the error message
		console.outputByCharacter(errorMessage);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Functions used for battle
///////////////////////////////////////////////////////////////////////////////////////////

// Initiates the battle sequence with the monster and handles all of the error exceptions
void Room::battleMonster(GameUI console, std::string monsterName, bool* inBattle)
{
	// Text messages to the user
	std::string monsterAlreadyDeafeatedText = "The " + monster->getName() + " has already been defeated, you cannot go into battle with it you moron.\n";
	std::string enteringBattleText = player->getName() + " is now going into battle with the " + monster->getName() + ".\n";
	std::string monsterNotInRoom = "That monster is not in this room you fool, you cannot go into battle with it.\n";
	std::string noAttacks = "How you gonna battle a monster with no attacks.\nYou stupid, go find some and pick em up.\n";
	std::string alreadyInBattle = "You're already in battle, why is your stupid head tryna go into battle again?\n";

	// Make sure the player is not already in battle before entering battle
	if (*inBattle == false)
	{
		// Make sure the player has an attack before entering battle
		if (player->getInventory()->getAttackInventorySize() > 0)
		{
			// Make sure the correct monster is in the current room before turning inBattle to true
			if (monster->getName() == monsterName)
			{
				// If the monster is in the room and not already defeated, enter battle
				if (monster->getHealth() <= 0)
				{
					// Tell the user that the monster in the room was already defeated
					console.outputByCharacter(monsterAlreadyDeafeatedText);
				}
				else
				{
					// Let the player enter battle with the monster
					console.changeToBattleColors();
					console.outputByCharacter(enteringBattleText);
					*inBattle = true;
				}
			}
			else
			{
				// Tell the user that the monster they are trying to battle is not in the current room
				console.outputByCharacter(monsterNotInRoom);
			}
		}
		else
		{
			// Cannot enter battle because the player has no attacks
			console.outputByCharacter(noAttacks);
		}
	}
	else
	{
		// Tell the user they can't enter battle twice
		console.outputByCharacter(alreadyInBattle);
	}

	
}

// Performs a singular round of battle. 1 player attack and 1 monster attack (if needed)
void Room::battle(GameUI console, std::string attack, bool* inBattle)
{
	// Text messages to the user
	std::string extraNewline = "\n";
	std::string playerDefeatedText = "\n" + player->getName() + " has been defeated.\n";
	std::string monsterDefeatedText = "\nThe " + monster->getName() + " has been defeated.\n\n";
	std::string dropMonsterAttackText = "The " + monster->getName() + " has dropped his " + monster->getInventory()->getAttack(console)->getName() 
										+ " attack.\n\nThe battle has ended.\n";

	// Player attacks the monster
	playerAttacksMonster(console, attack);

	// If the monster dies, then do not let the monster attack again. Tell the user that the
	// monster has been defeated.
	if (monster->getHealth() > 0)
	{
		// Monster attacks the player
		console.outputByCharacter(extraNewline);
		monsterAttacksPlayer(console);

		// If the player dies, kill the player, let the user know they have been defeated and then
		// end the battle
		if (player->getHealth() <= 0)
		{
			// The player has been defeated. Kill it
			player->kill();

			// Let the user know the player has been defeated.
			console.outputByCharacter(playerDefeatedText);

			// Get out of the battle state
			*inBattle = false;
			
			// Revert to normal colors for the text
			console.changeToNormalColors();
		}
	}
	else
	{
		// The monster has been defeated. Kill it
		monster->kill();

		// Let the user know the monster has been defeated.
		console.outputByCharacter(monsterDefeatedText);

		// Hardcoded things - I ain't dealing with right now (I am making this shit work)
		// Drops the key when these monster's die
		if (monster->getName() == "hellhound")
		{
			// Drop the dragonkey to the ground
			dropMonsterItem(console, "dragonkey");
		}
		else if (monster->getName() == "spirit")
		{
			// Drop the devilkey to the ground
			dropMonsterItem(console, "devilkey");
		}
		else if (monster->getName() == "archdemon")
		{
			// Drop the devilkey to the ground
			dropMonsterItem(console, "ice");
		}

		// Drop the attack the monster was using to the ground of the room
		console.outputByCharacter(dropMonsterAttackText);
		dropMonsterAttack(console);

		// Get out of the battle state
		*inBattle = false;

		// Revert to normal colors for the text
		console.changeToNormalColors();
	}
}

// Performs the error checking when a player tries using an attack in battle
void Room::useAttack(GameUI console, std::string attack, bool* inBattle, Parser::InputStruct* parserOutput)
{
	std::string notInBattleMessage = "Your dumbass can only use attacks when in battle.\n";
	std::string doNotHaveAttackMessage = "Your sorryass does not currently have access to that attack.\n";

	// Only run the battle sequence if the player is currently in battle
	if (player->getInventory()->searchAttackInventory(attack) != false)
	{
		// If the player has the attack in their inventory, they can use it. Otherwise tell them
		// that they do not have access to that attack
		if (*inBattle == true)
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
			console.outputByCharacter(notInBattleMessage);
		}
	}
	else
	{
		// Tell the user they cannot use attacks when not in battle
		console.outputByCharacter(doNotHaveAttackMessage);
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
	if (player->checkParalyzed() == true && hitOrMiss(player->getStatusEffectHitChance()) == true)
	{
		// Display that the player cannot attack
		console.outputByCharacter(playerParalyzed);
	}
	else
	{
		// Display the attack the player used to the user
		console.outputByCharacter(attackPlayerUsedText);

		// If the attack is going to be a hit, take hitpoints from the monster and display the 
		// new health of the monster. Otherwise say the attack missed.
		if (hitOrMiss(player->getInventory()->getAttack(console, attack)->getHitChance()) == true)
		{
			// Make the damage affect the monster
			monster->changeHealth(console, hitPoints);

			// Output that the player's attack hit
			console.outputByCharacter(attackHitText);
			
			// Completes the check to see if the monster was paralyzed from this attack
			monsterGetsStatus(console, attack);

			// If the monster is burned.... Take the burn damage away
			if (monster->getStatusEffect() == 2)
			{
				// Take an extra 5 hp from the monster
				monster->performBurn(console);
			}

			// If the monster's health reaches 0 or below, output that they died with 0 health left
			if (monster->getHealth() <= 0)
			{
				// Output the health being 0
				console.outputByCharacter(monsterDiedHealthText);
			}
			else
			{
				// Output the monster's health after the player's attack has hit
				console.outputByCharacter("New Monster Health: " + std::to_string(monster->getHealth()) + ".\n");
			}
		}
		else
		{
			// Let the user know that the monster's attack missed and redisplay their health
			console.outputByCharacter(attackMissedText);
			if (monster->checkParalyzed() == true)
			{
				console.outputByCharacter(monsterAlreadyParalyzed);
			}
			console.outputByCharacter("Monster Health: " + std::to_string(monster->getHealth()) + ".\n");
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
	if (monster->checkParalyzed() == true && hitOrMiss(monster->getStatusEffectHitChance()) == true)
	{
		// Display that the player cannot attack
		console.outputByCharacter(monsterParalyzed);
	}
	else
	{
		// Display the attack the monster used to the user
		console.outputByCharacter(attackMonsterUsedText);

		// If the attack is going to be a hit, take hitpoints from the monster and display the 
		// new health of the monster. Otherwise say the attack missed.
		if (hitOrMiss(monster->getInventory()->getAttack(console)->getHitChance()) == true)
		{
			// Make the damage affect the player
			player->changeHealth(console, hitPoints);

			// Output that the player's attack hit
			console.outputByCharacter(attackHitText);

			// Completes the check to see if the player gets a status condition from this attack
			playerGetsStatus(console);

			// If the monster is burned.... Take the burn damage away
			if (player->getStatusEffect() == 2)
			{
				// Take an extra 5 hp from the monster
				player->performBurn(console);
			}


			// If the player's health reaches 0 or below, output that they died with 0 health left
			if (player->getHealth() <= 0)
			{
				// Output the health being 0
				console.outputByCharacter(playerDiedHealthText);
			}
			else
			{
				// Output the player's health after the monster's attack has hit
				console.outputByCharacter(player->getName() + "'s New Health: " + std::to_string(player->getHealth()) + ".\n");
			}
		}
		else
		{
			// Let the user know that the monster's attack missed and redisplay their health
			console.outputByCharacter(attackMissedText);

			if (player->checkParalyzed() == true)
			{
				console.outputByCharacter(playerAlreadyParalyzed);
			}
			console.outputByCharacter(player->getName() + "'s Health: " + std::to_string(player->getHealth()) + ".\n");
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

// Checks to see if the monster will get a status condition from an attack, if they do
// then the statusEffect variable of the monster is set to that status condition
void Room::monsterGetsStatus(GameUI console, std::string attack)
{
	// Get values we want into simpler variables
	int status = player->getInventory()->getAttack(console, attack)->getStatusEffect();
	int percentHit = player->getInventory()->getAttack(console, attack)->getStatusEffectHitChance();

	// Text messages to the user
	std::string monsterBurned = "The monster has been burned from the attack.\n";
	std::string monsterParalyzed = "The monster has been paralyzed from the attack.\n";
	std::string monsterAlreadyBurned = "The monster continues to be burned.\n";
	std::string monsterAlreadyParalyzed = "The monster continues to be paralyzed.\n";

	// Check to see if the monster already currently has a status condition or not
	if (monster->checkParalyzed() == true)
	{
		// Monster has paralysis currently
		console.outputByCharacter(monsterAlreadyParalyzed);
	}
	else if (monster->checkBurned() == true)
	{
		// Monster has burn currently
		console.outputByCharacter(monsterAlreadyBurned);
	}
	// Monster has no current status condition, lets see if they get one below
	else
	{
		// Check to see if the attack has the paralysis effect
		if (status == 1)
		{
			// If the attack has the burn effect, then check to see if the
			// monster will be burned or not
			if (hitOrMiss(percentHit) == true)
			{
				// Set the monster to be burned
				monster->setStatusEffect(1);
				console.outputByCharacter(monsterParalyzed);
			}
		} // Check to see if the attack has the burn effect
		else if (status == 2)
		{
			// If the attack has the burn effect, then check to see if the
			// monster will be burned or not
			if (hitOrMiss(percentHit) == true)
			{
				// Set the monster to be burned
				monster->setStatusEffect(2);
				console.outputByCharacter(monsterBurned);
			}
		}
	}
}

// Checks to see if the player will get a status condition from an attack, if they do
// then the statusEffect variable of the player is set to that status condition
void Room::playerGetsStatus(GameUI console)
{
	// Get values we want into simpler variables
	int status = monster->getInventory()->getAttack(console)->getStatusEffect();
	int percentHit = monster->getInventory()->getAttack(console)->getStatusEffectHitChance();

	// Text messages to the user
	std::string playerBurned = "The player has been burned from the attack.\n";
	std::string playerParalyzed = "The player has been paralyzed from the attack.\n";
	std::string playerAlreadyBurned = "The player continues to be burned.\n";
	std::string playerAlreadyParalyzed = "The player continues to be paralyzed.\n";

	// Check to see if the player already currently has a status condition or not
	if (player->checkParalyzed() == true)
	{
		// Player has paralysis currently
		console.outputByCharacter(playerAlreadyParalyzed);
	}
	else if (player->checkBurned() == true)
	{
		// Player has burn currently
		console.outputByCharacter(playerAlreadyBurned);
	}
	// Player has no current status condition, lets see if they get one below
	else
	{
		// Check to see if the attack has the paralysis effect
		if (status == 1)
		{
			// If the attack has the burn effect, then check to see if the
			// player will be burned or not
			if (hitOrMiss(percentHit) == true)
			{
				// Set the player to be burned
				player->setStatusEffect(1);
				console.outputByCharacter(playerParalyzed);
			}
		} // Check to see if the attack has the burn effect
		else if (status == 2)
		{
			// If the attack has the burn effect, then check to see if the
			// player will be burned or not
			if (hitOrMiss(percentHit) == true)
			{
				// Set the player to be burned
				player->setStatusEffect(2);
				console.outputByCharacter(playerBurned);
			}
		}
	}
}

// Heals the player from any status effect they have
void Room::healStatusEffect(GameUI console, int status, std::string item)
{
	// Text message to the user
	std::string healedMessage = "The player has been healed from their status effect.\n";
	std::string paralyzeMessage = "The player is not paralyzed, this item cannot be used.\n";
	std::string burnMessage = "The player is not burned, this item cannot be used.\n";

	// Check if the player is has a status effect before healing them
	if (player->checkParalyzed() == true || player->checkBurned() == true)
	{
		// Set the player to not have a status effect
		player->setStatusEffect(0);

		// Remove the item from the player
		player->getInventory()->removeItem(console, item);

		// Display that they were healed
		console.outputByCharacter(healedMessage);
	}
	else
	{
		// Output the correct error message based on the status effect
		if (status == 1)
		{
			// Paralyzed message
			console.outputByCharacter(paralyzeMessage);
		}
		else if (status == 2)
		{
			// Burned message
			console.outputByCharacter(burnMessage);
		}
		
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
void Room::useKey1(GameUI console, std::string key, bool* inBattle)
{
	// Error messages
	std::string inBattleText = "This funcionality is not allowed while in battle.\n";
	std::string openingDoorText = "You have opened the door to The " + getUpRoom()->getName() + ".\n";
	std::string doorIsAlreadyOpenText = "The door is already open ya dunce, no need to use the key.\n";
	std::string itemNotInInventoryText = "You do not currently have that item in your posession ya simpleton.\n";
	std::string wrongKey = "That key does not work on this door ya blockhead. Gotta find another one.\n";
	std::string doorNotLocked = "Come on bro. There ain't no lock on this door, just move.\n";

	// Check to make sure the player is not in battle before trying to use the key
	if (*inBattle == false)
	{
		// Make sure the user has the item in their inventory before trying to use it.
		if (player->getInventory()->searchItemInventory(key) == true)
		{
			// Make sure a key can actually be used because the door is locked
			if (upRoomLocked == true)
			{
				// Make sure the room is the correct one
				if (upRoom->getName() == "Room of Gold")
				{
					// If the upRoom door is locked, then you are allowed to use the key
					if (getUpRoomLocked() == true)
					{
						// Unlock the door that is locked
						unlockDoor();

						// Let the user know that they unlocked the door
						console.outputByCharacter(openingDoorText);
					}
					else
					{
						// Tell the user that the key cannot be used on an open door
						console.outputByCharacter(doorIsAlreadyOpenText);
					}
				}
				else
				{
					// Tell the user that the key cannot be used on this door (wrong door)
					console.outputByCharacter(wrongKey);
				}
			}
			else
			{
				// Tell the user that the door is not locked so they don't need to use a key
				console.outputByCharacter(doorNotLocked);
			}
		}
		else
		{
			// Tell the user that the item is not in their inventory
			console.outputByCharacter(itemNotInInventoryText);
		}
	}
	else
	{
		// The player cannot use the key to open the door when in battle
		console.outputByCharacter(inBattleText);
	}
}

// Tries to use the key to unlock the door
void Room::useKey2(GameUI console, std::string key, bool* inBattle)
{
	// Error messages
	std::string inBattleText = "This funcionality is not allowed while in battle.\n";
	std::string openingDoorText = "You have opened the door to The " + getUpRoom()->getName() + ".\n";
	std::string doorIsAlreadyOpenText = "The door is already open ya ignoramus, no need to use the key.\n";
	std::string itemNotInInventoryText = "You do not currently have that item in your posession you nincompoop.\n";
	std::string wrongKey = "That key does not work on this door ya ninny. Gotta find another one.\n";
	std::string doorNotLocked = "Come on bro. There ain't no lock on this door, just move.\n";

	// Check to make sure the player is not in battle before trying to use the key
	if (*inBattle == false)
	{
		// Make sure the user has the item in their inventory before trying to use it.
		if (player->getInventory()->searchItemInventory(key) == true)
		{
			// Make sure a key can actually be used because the door is locked
			if (upRoomLocked == true)
			{
				// Make sure the room is the correct one
				if (upRoom->getName() == "Room of The Devil")
				{
					// If the upRoom door is locked, then you are allowed to use the key
					if (getUpRoomLocked() == true)
					{
						// Unlock the door that is locked
						unlockDoor();

						// Let the user know that they unlocked the door
						console.outputByCharacter(openingDoorText);
					}
					else
					{
						// Tell the user that the key cannot be used on an open door
						console.outputByCharacter(doorIsAlreadyOpenText);
					}
				}
				else
				{
					// Tell the user that the key cannot be used on this door (wrong door)
					console.outputByCharacter(wrongKey);
				}
			}
			else
			{
				// Tell the user that the door is not locked so they don't need to use a key
				console.outputByCharacter(doorNotLocked);
			}
		}
		else
		{
			// Tell the user that the item is not in their inventory
			console.outputByCharacter(itemNotInInventoryText);
		}
	}
	else
	{
		// The player cannot use the key to open the door when in battle
		console.outputByCharacter(inBattleText);
	}
}