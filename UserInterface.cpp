#include "UserInterface.h"
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;

// Constructors for UserInterface Class
UserInterface::UserInterface() {
	/*startingDescription = "Hello there player.\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.\n";
	*/
}

// Function to get input from the user. It will ask the user what they would like to do
// and once they enter their input it will validate the input before proceeding.
// A different prompt can also be entered as a parameter if the default saying
// is not sufficient.
string UserInterface::getUserInput() {
	string input = "";
	string prompt = "What would you like to do: ";
	cout << prompt;
	getline(cin, input);
	input = convertLower(input);
	// ToDo: Validate the input from the user
	return input;
}
string UserInterface::getUserInput(string prompt) {
	string input = "";
	cout << prompt;
	getline(cin, input);
	input = convertLower(input);
	// ToDo: Validate the input from the user
	return input;
}

// Function that takes a string and returns the string in all lowercase
// This is done as a way to standardize all user input
string UserInterface::convertLower(string sentence) {
	// The transform function is part of the <algorithms> library
	// sequentially applies an operation to the elements of an array.
	// In this case we are applying the tolower function to the string to convert all
	// characters to lowercase.
	transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);
	return sentence;
}

// Function to print a string to the console. Whatever string is passed to the
// function will be displayed in the console.
void UserInterface::printString(string output) {
	cout << output << endl;
}