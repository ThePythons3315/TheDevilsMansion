// Version 2.05

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "UserInterface.h"
#include "Room.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
#include "Health.h"
#include <assert.h>
using namespace std;

// Definitions of functions -- initialized below
bool validateInput(vector<string>& vect, string sentence);
void itemFromRoomToPlayer(Room*& room, string itemName);
void itemFromPlayerToRoom(Room*& room, string itemName);
bool checkIfItemIsInRoom(Room*& room, string itemName);
void addItemHealthToPlayer(Room*& room, string itemName);

int testing()
{
	Player TestPlayer = Player();

	TestPlayer.setName("mike");

	assert("mike" == TestPlayer.getName());

	return 0;
}