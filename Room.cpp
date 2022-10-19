#include "Room.h"
#include <string.h>
using namespace std;

// Constructors
Room::Room() {
	name = "";
	roomDescription = "";
	// Room level will be the determining factor for which rooms are allowed
	// to access other rooms. For one room to be able to access another room
	// the room level must be adjacent in value to the other room. Ex. rooms
	// with room level of 1 can access rooms of room level's 0 or 2
	roomLevel = 0;
	// roomID = 0;
}
Room::Room(string name_input, string desc, int level) {
	name = name_input;
	roomDescription = desc;
	roomLevel = level;
	// roomID = id;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Room::setName(string n) {
	name = n;
}
void Room::setRoomDescription(string d) {
	roomDescription = d;
}
void Room::setPlayer(Player character) {
	player = character;
}
void Room::setRoomLevel(int level) {
	roomLevel = level;
}
void Room::setInventory(Inventory invent) {
	inventory = invent;
}
/*void Room::setRoomID(int id) {
	roomID = id;
}*/


// Accessor Functions -- Functions that will return values of private functions
string Room::getName() {
	return name;
}
string Room::getRoomDescription() {
	return roomDescription;
}
Player Room::getPlayer() {
	return player;
}
int Room::getRoomLevel() {
	return roomLevel;
}
Inventory Room::getInventory() {
	return inventory;
}
/*int Room::getRoomID() {
	return roomID;
}*/