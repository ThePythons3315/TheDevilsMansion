#include "Health.h"
using namespace std;

//constructors
Health::Health() {
	health = 0;
	maxHealth = 0;
}
Health::Health(int hp, int maxHP) {
	health = hp;
	maxHealth = maxHP;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Health::setHealth(int hp) {
	health = hp;
}
void Health::setMaxHealth(int maxHP) {
	maxHealth = maxHP;
}
void Health::changeHealth(int change) {
	health = health + change;

	// If the change made the health attribute go higher than the max health allowed,
	// set the health attribute to the maxHealth
	if (health > maxHealth) {
		health = maxHealth;
	}
}

// Accessor Functions -- Functions that will return values of private functions
int Health::getHealth() {
	return health;
}
int Health::getMaxHealth() {
	return maxHealth;
}

void Health::displayHealth() {
	if (health == maxHealth) {
		cout << "You currently have full health: " << health << endl;
	}
	else {
		cout << "Max health is : " << maxHealth << endl;
		cout << "Current health is: " << health << endl;
	}
}