#include "UserInterface.h"
#include <string.h>
#include <string>
using namespace std;

// Constructors for UserInterface Class
UserInterface::UserInterface() {
	startingDescription = "Hello there player.\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.\n";
}

// Mutator Functions -- Functions that will be allowed to change private variables
void UserInterface::setStartingDescription(string descrip) {
	startingDescription = descrip;
}
void UserInterface::setMainCharacter(Player character) {
	mainCharacter = character;
}

// Accessor Functions -- Functions that will return values of private functions
string UserInterface::getStartingDescription() {
	return startingDescription;
}
Player UserInterface::getMainCharacter() {
	return mainCharacter;
}

// Function that will accept input from the user. A prompt can be passed into the
// function and will be displayed before asking the user for the input. The input
// will be validated before it can be returned
string UserInterface::acceptInputFromUser(string prompt) {
	string input = "";
	cout << prompt;
	getline(cin, input);
	// ToDo: Validate the input from the user
	return input;
}

// Function that gets the main characters information from the user, creates
// the main character's object and sets their name to the proper name inputted
// by the user
void UserInterface::getPlayerInfo() {
	// Get the input from the user
	string prompt = "Hello there, please enter the name you would like your character to have: ";
	string name = "";
	name = acceptInputFromUser(prompt);

	// Create the main player object
	Player player(name);
	mainCharacter = player;

	// Set the starting description to address the player by their chosen name
	setStartingDescription("\nHello there " + mainCharacter.getName() + ".\n"
						   "You have just died and been sent down to The Devils Mansion.\n"
						   "Currently you are outside of the mansion and standing on the starting steps.\n");
}