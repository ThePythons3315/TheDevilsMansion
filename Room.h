#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Inventory.h"
using namespace std;

class Room {
private:
	string name;
	string roomDescription;
	Player player;
	int roomLevel;
	Inventory inventory;
	// int roomID; - will be implemented later
public:
	// Constructors
	Room();
	Room(string, string, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setRoomDescription(string);
	void setPlayer(Player);
	void setRoomLevel(int);
	void setInventory(Inventory);
	// void setRoomID(int); - will be implemented later

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getRoomDescription();
	Player getPlayer();
	int getRoomLevel();
	Inventory getInventory();
	// int getRoomID(); - will be implemented later

	// Function that will display both room description and the inventory of the room
	void getRoomInformation();
};
#endif // !ROOM_H