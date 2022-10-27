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
	Inventory inventory;
	int roomID;
	Room* leftRoom; // pointer to a room object
	Room* centerRoom; // pointer to a room object
	Room* rightRoom; // pointer to a room object
	Room* backRoom; // pointer to a room object
public:
	// Constructors
	Room();
	Room(string, string, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setRoomDescription(string);
	void setPlayer(Player);
	void setInventory(Inventory);
	void setRoomID(int);
	void setLeftRoom(Room&); // Take the address of the room object
	void setCenterRoom(Room&); // Take the address of the room object
	void setRightRoom(Room&); // Take the address of the room object
	void setBackRoom(Room&); // Take the address of the room object
	//void setAssociatedRooms(Room&, Room&, Room&, Room&);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getRoomDescription();
	Player getPlayer();
	Inventory getInventory();
	int getRoomID();
	Room* getLeftRoom();
	Room* getCenterRoom();
	Room* getRightRoom();
	Room* getBackRoom();

	// Function that will display both room description and the inventory of the room
	void getRoomInformation();

	void moveRoom(string);

	bool validatePossibleRoom(string);
};
#endif // !ROOM_H