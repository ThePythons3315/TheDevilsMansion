#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player() {
	name = "";
};
Player::Player(string n) {
	name = n;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(string n) {
	name = n;
}

// Accessor Functions -- Functions that will return values of private functions
string Player::getName() {
	return name;
}