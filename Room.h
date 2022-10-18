#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string.h>
#include "Player.h"
using namespace std;

class Room {
private:
	string name;
	string roomDescription;
	Player player;
	int roomLevel;
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
	// void setRoomID(int); - will be implemented later

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getRoomDescription();
	Player getPlayer();
	int getRoomLevel();
	// int getRoomID(); - will be implemented later
};
#endif // !ROOM_H