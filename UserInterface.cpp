#include "UserInterface.h"
#include <string.h>
using namespace std;

// Constructors for UserInterface Class
UserInterface::UserInterface() {
	startingDescription = "Hello there player.\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.\n";
}

// Mutator Functions -- Functions that will be allowed to change private variables
void UserInterface::setStartingDescription(string s) {
	startingDescription = s;
}

// Accessor Functions -- Functions that will return values of private functions
string UserInterface::getStartingDescription() {
	return startingDescription;
}