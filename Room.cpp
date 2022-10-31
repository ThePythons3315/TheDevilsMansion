#include "Room.h"
#include <string.h>
using namespace std;

// Constructors
Room::Room() {
	name = "";
	roomDescription = "";
	roomID = 0;
	leftRoom = nullptr;
	centerRoom = nullptr;
	rightRoom = nullptr;
	backRoom = nullptr;
}
Room::Room(string name_input, string desc, int id) {
	name = name_input;
	roomDescription = desc;
	roomID = id;
	leftRoom = nullptr;
	centerRoom = nullptr;
	rightRoom = nullptr;
	backRoom = nullptr;
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
void Room::setInventory(Inventory invent) {
	inventory = invent;
}
void Room::setRoomID(int id) {
	roomID = id;
}
void Room::setLeftRoom(Room& left) {
	leftRoom = &left;
}
void Room::setCenterRoom(Room& center) {
	centerRoom = &center;
}
void Room::setRightRoom(Room& right) {
	rightRoom = &right;
}
void Room::setBackRoom(Room& back) {
	backRoom = &back;
}



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
Inventory Room::getInventory() {
	return inventory;
}
int Room::getRoomID() {
	return roomID;
}
Room* Room::getLeftRoom() {
	return leftRoom;
}
Room* Room::getCenterRoom() {
	return centerRoom;
}
Room* Room::getRightRoom() {
	return rightRoom;
}
Room* Room::getBackRoom() {
	return backRoom;
}

// Function that will display both room description and the inventory of the room
void Room::getRoomInformation() {
	cout << getRoomDescription() << endl;
	cout << "Room inventory:\n";
	inventory.displayInventory();
	cout << "The Player's health is currently: " << player.getPlayerHealth().getHealth() << endl;
}

void Room::moveRoom(string direction) {
	// Default player object. This object will be placed in the current room
	// after passing the player object to the new room.
	Player defaultPlayer;

	// Move the player to the new room based off which direction they asked
	// to go. Only move the player as long as there is a room to move the 
	// player to. If the pointer to the room you would like to move to is 
	// null, then outprint that the room was not valid and the player stays in
	// the current room.
	if (direction == "center") {
		centerRoom->setPlayer(player);
		cout << "The player has been moved to the " << centerRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "left") {
		leftRoom->setPlayer(player);
		cout << "The player has been moved to the " << leftRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "right") {
		rightRoom->setPlayer(player);
		cout << "The player has been moved to the " << rightRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "back") {
		backRoom->setPlayer(player);
		cout << "The player has been moved to the " << backRoom->getName() << endl;
		player = defaultPlayer;
	}
}

bool Room::validatePossibleRoom(string direction) {
	if (direction == "center" && centerRoom != nullptr) {
		return true;
	}
	else if (direction == "left" && leftRoom != nullptr) {
		return true;
	}
	else if (direction == "right" && rightRoom != nullptr) {
		return true;
	}
	else if (direction == "back" && backRoom != nullptr) {
		return true;
	}
	return false;
}