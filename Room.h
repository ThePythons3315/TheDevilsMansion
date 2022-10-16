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
public:
	// Constructors
	Room();
	Room(string, string);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setRoomDescription(string);
	void setPlayer(Player);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getRoomDescription();
	Player getPlayer();
};
#endif // !ROOM_H