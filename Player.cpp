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

// Mutator Functions
void Player::setName(string n) {
	name = n;
}

// Accessor Functions
string Player::getName() {
	return name;
}