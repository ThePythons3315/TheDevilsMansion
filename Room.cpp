#include "Room.h"
#include <string.h>
using namespace std;

// Constructors
Room::Room() {
	name = "";
	roomDescription = "";
}

Room::Room(string name_input, string desc) {
	name = name_input;
	roomDescription = desc;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Room::setName(string n) {
	name = n;
}

void Room::setRoomDescription(string d) {
	roomDescription = d;
}

// Accessor Functions -- Functions that will return values of private functions
string Room::getName() {
	return name;
}

string Room::getRoomDescription() {
	return roomDescription;
}