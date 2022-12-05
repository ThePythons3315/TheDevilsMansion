#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include "Inventory.h"
#include "Monster.h"
#include "Parser.h"

class Room
{
private:
	std::string name;
	std::string description;
	Room* leftRoom;
	Room* upRoom;
	Room* rightRoom;
	Room* downRoom;
	Player* player;
	Inventory* inventory;
	Monster* monster;
	bool upRoomLocked;
public:
	// Constructors
	Room();
	Room(std::string _name, std::string _description, bool _upRoomLocked);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDescription(std::string _description);
	void setLeftRoom(Room& _leftRoom); // Take the address of the room object
	void setUpRoom(Room& _upRoom); // Take the address of the room object
	void setRightRoom(Room& _rightRoom); // Take the address of the room object
	void setDownRoom(Room& _downRoom); // Take the address of the room object
	void setPlayer(Player& _player);
	void setInventory(Inventory& _inventory);
	void setMonster(Monster& _monster);
	void setUpRoomLocked(bool _upRoomLocked);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	std::string getDescription();
	Room* getLeftRoom();
	Room* getUpRoom();
	Room* getRightRoom();
	Room* getDownRoom();
	Player* getPlayer();
	Inventory* getInventory();
	Monster* getMonster();
	bool getUpRoomLocked();

	// Set all 4 of the rooms that can be moved to from this current room
	void setOrientations(Room& _leftRoom, Room& _upRoom, Room& _rightRoom, Room& _downRoom);

	// Displays certain attributes of the room
	void printRoomInfo(GameUI console, bool* inBattle);
	void printBasicRoom(GameUI console, std::string direction);
	void printPlayerAttributes(GameUI console, bool* inBattle);

	// Move the player in the direction the user wants to go to
	void moveRoom(GameUI console, Room** currentRoom, std::string direction, bool* inBattle);

	// Functions that involve items moving from one inventory to another
	void pickupItem(GameUI console, std::string item, bool* inBattle);
	void pickupAttack(GameUI console, std::string attack, bool* inBattle);
	void dropItem(GameUI console, std::string item, bool* inBattle);
	void dropAttack(GameUI console, std::string attack, bool* inBattle);
	void dropMonsterAttack(GameUI console);

	// Functions used for battle
	void battleMonster(GameUI console, std::string monsterName, bool* inBattle);
	void battle(GameUI console, std::string attack, bool* inBattle);
	void useAttack(GameUI console, std::string attack, bool* inBattle, Parser::InputStruct* parserOutput);
	void playerAttacksMonster(GameUI console, std::string attack);
	void monsterAttacksPlayer(GameUI console);
	bool hitOrMiss(int hitChance);

	// Status effect related functions
	void monsterWasParalyzed(GameUI console, std::string attack);
	void playerWasParalyzed(GameUI console);
	bool checkMonsterParalyzed();
	bool checkPlayerParalyzed();
	void healStatusEffect(GameUI console);

	// Functions related to the usage of doors
	void lockDoor();
	void unlockDoor();
	void useKey(GameUI console, std::string key, bool* inBattle);
};