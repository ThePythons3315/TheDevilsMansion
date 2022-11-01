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

void Battle::runBattle() {
	vector <string> keyWords = {"q", "quit", "attack1", "attack2"};

	UserInterface ui;
	bool battleLoop = true;
	string input = "";

	// Display the battle opening line of the player versus the monster
	displayOpeningLine();

	// Main battle loop
	while (battleLoop == true) {
		// Get input from the user continuously until a correct
		// key word is entered
		do {
			input = ui.getStandardizedUserInput();
		} while (validateInput(keyWords, input) == false);

		// If the user enter's `q`, then break the main loop and end the game.
		if (input == "q" || input == "quit") {
			cout << "You are ending battle." << endl;
			break;
		}
	}
}

// Validate that the input from the user is a correct command.
// Correct commands will be in the keyWords vector.
bool Battle:: validateInput(vector<string>& vect, string sentence) {
	for (int i = 0; i < vect.size(); i++) {
		if (vect.at(i) == sentence) {
			return true;
		}
	}
	return false;
}