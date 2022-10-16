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

// Accessor Functions -- Functions that will return values of private functions
string UserInterface::getStartingDescription() {
	return startingDescription;
}

// Fucnction to get input from the user. It will ask the user what they would like to do
// and once they enter their input it will validate the input before proceeding.
// A different prompt can also be entered as a parameter if the default saying
// is not sufficient.
string UserInterface::getUserInput() {
	string input = "";
	string prompt = "What would you like to do: ";
	cout << prompt;
	getline(cin, input);
	// ToDo: Convert the user input to all lowercase
	// input = convertLower(input)
	// ToDo: Validate the input from the user
	return input;
}
string UserInterface::getUserInput(string prompt) {
	string input = "";
	cout << prompt;
	getline(cin, input);
	// ToDo: Convert the user input to all lowercase
	// input = convertLower(input)
	// ToDo: Validate the input from the user?? Maybe don't need right now
	return input;
}

// Function that takes a string and returns the string in all lowercase
string UserInterface::convertLower(string sentence) {
	// ToDo: Add code to this function to make sure all user input
	// is in lowercase, standardize user input
	return sentence;
}

// Function to print a string to the console. Whatever string is passed to the
// function will be displayed in the console.
void UserInterface::printString(string output) {
	cout << output << endl;
}