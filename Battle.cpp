#include "Battle.h"
using namespace std;

//constructors
Battle::Battle() {
	player;
	monster;
}
Battle::Battle(Player _player, Monster _monster) {
	player = _player;
	monster = _monster;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Battle::setPlayer(Player _player) {
	player = _player;
}
void Battle::setMonster(Monster _monster) {
	monster = _monster;
}

// Accessor Functions -- Functions that will return values of private functions
Player Battle::getPlayer() {
	return player;
}
Monster Battle::getMonster() {
	return monster;
}

void Battle::displayOpeningLine() {
	cout << player.getName() << " is now going into battle with " << monster.getName() << endl;
}