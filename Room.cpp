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
	lock = false;
	leftRoom = nullptr;
	centerRoom = nullptr;
	rightRoom = nullptr;
	backRoom = nullptr;
}
Room::Room(string name_input, string desc, bool lockStat) {
	name = name_input;
	roomDescription = desc;
	lock = lockStat;
	inventory;
	monster;
	attacks;
	leftRoom = nullptr;
	centerRoom = nullptr;
	rightRoom = nullptr;
	backRoom = nullptr;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Room::setName(string n)
{
	name = n;
}
void Room::setRoomDescription(string d)
{
	roomDescription = d;
}
void Room::setPlayer(Player character)
{
	player = character;
}
void Room::setInventory(Inventory invent)
{
	inventory = invent;
}
void Room::setAttacks(Attacks _attacks)
{
	attacks = _attacks;
}
void Room::setMonster(Monster _monster)
{
	monster = _monster;
}
void Room::setLeftRoom(Room& left)
{
	leftRoom = &left;
}
void Room::setCenterRoom(Room& center)
{
	centerRoom = &center;
}
void Room::setRightRoom(Room& right)
{
	rightRoom = &right;
}
void Room::setBackRoom(Room& back)
{
	backRoom = &back;
}

void Room::setLockStatus(bool lockStat)
{
	lock = lockStat;
}


void Room::dropMonsterInventoryToRoom(Room*& room)
{
	Monster tempMonster;
	Inventory roomInventory;
	Inventory monsterInventory;
	vector<Item> items;
	int size;

	// Set all of the variables to their corresponding values from the
	// room. Just doing this to make it the code simpler to look at
	roomInventory = room->getInventory();
	monsterInventory = room->getMonster().getInventory();
	size = monsterInventory.getSize();
	items = monsterInventory.getInventory();
	room->getMonster().getInventory().displayRoomInventory();
	monsterInventory.displayMonsterInventory();
	roomInventory.displayRoomInventory();

	// Add the item to the player and remove it from the room
	for (int i = 0; i < size; i++) {
			// Add the item to the room's inventory
			roomInventory.addItem(items.at(i));
			// Remove the item from the player
			monsterInventory.removeItem(i);
	}

	// Set the room's inventory to the updated room inventory
	room->setInventory(roomInventory);

	// Set the player's inventory to the updated player's inventory
	tempMonster.setInventory(monsterInventory);
	tempMonster.setName(room->getMonster().getName());
	tempMonster.setHealth(room->getMonster().getHealth());
	tempMonster.setAttacks(room->getMonster().getAttacks());
	room->setMonster(tempMonster);

	// Display the inventories of the room and the player
	cout << "\nThe " << room->getMonster().getName() << " has just dropped it's entire inventory." << endl;
	room->getInventory().displayRoomInventory();
	room->getMonster().getInventory().displayMonsterInventory();
}


// Accessor Functions -- Functions that will return values of private functions
string Room::getName()
{
	return name;
}
string Room::getRoomDescription()
{
	return roomDescription;
}
Player Room::getPlayer()
{
	return player;
}
Inventory Room::getInventory()
{
	return inventory;
}
Attacks Room::getAttacks()
{
	return attacks;
}
Monster Room::getMonster()
{
	return monster;
}
Room* Room::getLeftRoom()
{
	return leftRoom;
}
Room* Room::getCenterRoom()
{
	return centerRoom;
}
Room* Room::getRightRoom()
{
	return rightRoom;
}
Room* Room::getBackRoom()
{
	return backRoom;
}
bool Room::getLockStatus()
{
	return lock;
}

// Function that will display both room description and the inventory of the room
void Room::getRoomInformation()
{
	// Description of room - what the room actually looks like
	cout << getRoomDescription();

	// Display the items in the room
	inventory.displayRoomInventory();

	// Display the attacks available for the user to pick up
	if (attacks.getSize() != 0) {
		cout << "Attacks in the room that you can pickup\n";
		attacks.displayattacks();
		cout << endl;
	}

	if (monster.getHealth().getHealth() == -1) {
		cout << "You have already killed the " << monster.getName() << " monster\n\n";
	}
	else if (monster.getName() != "") {
		monster.displayMonster();
	}
	else {
		cout << "\nIt does not look like there is a monster in this room.\nContinue to be weary though\n";
	}
}

void Room::moveRoom(string direction)
{
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
		player = defaultPlayer;
	}
	else if (direction == "left") {
		leftRoom->setPlayer(player);
		player = defaultPlayer;
	}
	else if (direction == "right") {
		rightRoom->setPlayer(player);
		player = defaultPlayer;
	}
	else if (direction == "back") {
		backRoom->setPlayer(player);
		player = defaultPlayer;
	}
}

bool Room::validatePossibleRoom(string direction)
{
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