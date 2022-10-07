#include "UserInterface.h"
#include <string.h>
using namespace std;

// Constructors for UserInterface Class
UserInterface::UserInterface() {
	startingDescription = "Hello there player.\n"
						  "You have just died and been sent down to The Devils Mansion.\n"
						  "Currently you are outside of the mansion and standing on the starting steps.\n";
}

// Mutator Functions
void UserInterface::setStartingDescription(string s) {
	startingDescription = s;
}

// Accessor Functions
string UserInterface::getStartingDescription() {
	return startingDescription;
}