#include "Room.h"
#include <string.h>
using namespace std;

// Constructors
Room::Room() {
	name = "";
	roomDescription = "";
	inventory;
	monster;
	attacks;
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
	inventory;
	monster;
	attacks;
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
void Room::setAttacks(Attacks _attacks)
{
	attacks = _attacks;
}
void Room::setMonster(Monster _monster) {
	monster = _monster;
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
Attacks Room::getAttacks()
{
	return attacks;
}
Monster Room::getMonster() {
	return monster;
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
	// Description of room - what the room actually looks like
	cout << getRoomDescription() << endl;

	// Display the items in the room
	inventory.displayRoomInventory();

	// Display the player's health
	//cout << "The player's ";
	//player.getPlayerHealth().displayHealth();
	//cout << "Attacks in the room that you can pickup\n";
	//attacks.displayattacks();
	//cout << endl;
	if (monster.getHealth().getHealth() == -1) {
		cout << "You have already killed the " << monster.getName() << " monster\n\n";
	}
	else if (monster.getName() != "") {
		monster.displayMonster();
	}
	else {
		cout << "It does not look like there is a monster in this room.\nContinue to be weary though\n\n";
	}
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
		//cout << "The player has been moved to the " << centerRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "left") {
		leftRoom->setPlayer(player);
		//cout << "The player has been moved to the " << leftRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "right") {
		rightRoom->setPlayer(player);
		//cout << "The player has been moved to the " << rightRoom->getName() << endl;
		player = defaultPlayer;
	}
	else if (direction == "back") {
		backRoom->setPlayer(player);
		//cout << "The player has been moved to the " << backRoom->getName() << endl;
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