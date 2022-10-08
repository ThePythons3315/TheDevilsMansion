#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string.h>
using namespace std;

class Room {
private:
	string name;
	string roomDescription;
public:
	// Constructors
	Room();

	// Mutator Functions
	void setName(string);
	void setRoomDescription(string);

	// Accessor Functions
	string getName();
	string getRoomDescription();

};
#endif // !ROOM_H