#include "Parser.h"
#include <iostream>
#include <set>
#include <regex>
#include <algorithm>

// Text that will display what commands are available and their descriptions
std::string helpText =
"1 keyword commands:\n"
"\t- inventory \t\t\t-> Shows the player's current inventory.\n"
"\t- health \t\t\t-> Shows the player's current health.\n"
"\t- room \t\t\t\t-> Redisplays the current room.\n"
"\t- player \t\t\t-> Shows all of the player's attributes.\n"
"\t- attacks \t\t\t-> Shows the player's current attacks.\n"
"\t- help \t\t\t\t-> Gives available commands and descriptions.\n"
"\t- quit \t\t\t\t-> Quits the application.\n"
"2 keyword commands:\n"
"\t- move [direction]\t\t-> Moves the player to a different room.\n"
"\t- collect [item name]\t\t-> Lets the player add an item from the room to their inventory.\n"
"\t- use [attack/item name]\t-> Lets the player use an attack/item in their inventory.\n"
"\t- drop [item name]\t\t-> Lets the player drop an object from their inventory.\n"
"\t- battle [monster name]\t\t-> Lets the player go into battle with a monster.\n";

std::string battleHelpText =
"1 keyword commands:\n"
"\t- inventory \t\t\t-> Shows the player's current inventory.\n"
"\t- health \t\t\t-> Shows the player's current health.\n"
"\t- attacks \t\t\t-> Shows the player's current attacks.\n"
"\t- help \t\t\t\t-> Gives available commands and descriptions.\n"
"\t- quit \t\t\t\t-> Quits the application.\n"
"2 keyword commands:\n"
"\t- use [attack/item name]\t-> Lets the player use an attack/item in their inventory.\n";




Parser::Parser()
{
	// Null constructor
}

// Parse user input into a useable format
Parser::InputStruct* Parser::parseInput(std::string userString)
{
	// The struct that will hold the commands the user enters
	InputStruct* parsedInput = new InputStruct;

	// Standardize the input to a version we can work with
	std::string standardString = standardizeInput(userString);

	// Regex for 1 argument input, and 2 argument input
	// Only accepts [spaces, characters, spaces, characters, spaces]
	std::regex cmdRegex("^\\s*[a-zA-Z]+\\s*$");
	std::regex cmdRegexTwoArg("^\\s*[a-zA-Z]+\\s*[a-zA-Z]+\\s*$");

	// Use regex_match to make sure the text the user enters matches the form it should
	if (regex_match(standardString, cmdRegex))
	{
		std::string command1 = getFirstCommand(standardString);

		if (command1 == "help")
			parsedInput->command1 = HELP;
		else if (command1 == "inventory")
			parsedInput->command1 = INVENTORY;
		else if (command1 == "health")
			parsedInput->command1 = HEALTH;
		else if (command1 == "attacks")
			parsedInput->command1 = ATTACKS;
		else if (command1 == "room")
			parsedInput->command1 = ROOM;
		else if (command1 == "player")
			parsedInput->command1 = PLAYER;
		else if (command1 == "quit")
			parsedInput->command1 = QUIT;
		else
			parsedInput->command1 = ERROR1;
	}
	else if (regex_match(standardString, cmdRegexTwoArg))
	{
		std::string command1 = getFirstCommand(standardString);
		std::string command2 = getSecondCommand(standardString);

		if (command1 == "move")
		{
			parsedInput->command1 = MOVE;

			if (command2 == "left")
			{
				parsedInput->command2 = LEFT;
			}
			else if (command2 == "up")
			{
				parsedInput->command2 = UP;
			}
			else if (command2 == "right")
			{
				parsedInput->command2 = RIGHT;
			}
			else if (command2 == "down")
			{
				parsedInput->command2 = DOWN;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}
		}
		else if (command1 == "collect")
		{
			parsedInput->command1 = COLLECT;

			if (command2 == "blueberry")
			{
				parsedInput->command2 = BLUEBERRY;
			}
			else if (command2 == "paralysisheal")
			{
				parsedInput->command2 = PARALYSISHEAL;
			}
			else if (command2 == "burnheal")
			{
				parsedInput->command2 = BURNHEAL;
			}
			else if (command2 == "bowshot")
			{
				parsedInput->command2 = BOWSHOT;
			}
			else if (command2 == "punch")
			{
				parsedInput->command2 = PUNCH;
			}
			else if (command2 == "kick")
			{
				parsedInput->command2 = KICK;
			}
			else if (command2 == "bite")
			{
				parsedInput->command2 = BITE;
			}
			else if (command2 == "firebreath")
			{
				parsedInput->command2 = FIREBREATH;
			}
			else if (command2 == "flamethrower")
			{
				parsedInput->command2 = FLAMETHROWER;
			}
			else if (command2 == "fireball")
			{
				parsedInput->command2 = FIREBALL;
			}
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
			}
			else if (command2 == "slash")
			{
				parsedInput->command2 = SLASH;
			}
			else if (command2 == "slam")
			{
				parsedInput->command2 = SLAM;
			}
			else if (command2 == "shadowball")
			{
				parsedInput->command2 = SHADOWBALL;
			}
			else if (command2 == "eruption")
			{
				parsedInput->command2 = ERUPTION;
			}
			else if (command2 == "overheat")
			{
				parsedInput->command2 = OVERHEAT;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}
		}
		else if (command1 == "use")
		{
			parsedInput->command1 = USE;

			if (command2 == "blueberry")
			{
				parsedInput->command2 = BLUEBERRY;
			}
			else if (command2 == "paralysisheal")
			{
				parsedInput->command2 = PARALYSISHEAL;
			}
			else if (command2 == "burnheal")
			{
				parsedInput->command2 = BURNHEAL;
			}
			else if (command2 == "punch")
			{
				parsedInput->command2 = PUNCH;
			}
			else if (command2 == "kick")
			{
				parsedInput->command2 = KICK;
			}
			else if (command2 == "bowshot")
			{
				parsedInput->command2 = BOWSHOT;
			}
			else if (command2 == "bite")
			{
				parsedInput->command2 = BITE;
			}
			else if (command2 == "firebreath")
			{
				parsedInput->command2 = FIREBREATH;
			}
			else if (command2 == "flamethrower")
			{
				parsedInput->command2 = FLAMETHROWER;
			}
			else if (command2 == "fireball")
			{
				parsedInput->command2 = FIREBALL;
			}
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
			}
			else if (command2 == "slash")
			{
				parsedInput->command2 = SLASH;
			}
			else if (command2 == "slam")
			{
				parsedInput->command2 = SLAM;
			}
			else if (command2 == "shadowball")
			{
				parsedInput->command2 = SHADOWBALL;
			}
			else if (command2 == "eruption")
			{
				parsedInput->command2 = ERUPTION;
			}
			else if (command2 == "overheat")
			{
				parsedInput->command2 = OVERHEAT;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}
		}
		else if (command1 == "drop")
		{
			parsedInput->command1 = DROP;

			if (command2 == "blueberry")
			{
				parsedInput->command2 = BLUEBERRY;
			}
			else if (command2 == "paralysisheal")
			{
				parsedInput->command2 = PARALYSISHEAL;
			}
			else if (command2 == "burnheal")
			{
				parsedInput->command2 = BURNHEAL;
			}
			else if (command2 == "bowshot")
			{
				parsedInput->command2 = BOWSHOT;
			}
			else if (command2 == "punch")
			{
				parsedInput->command2 = PUNCH;
			}
			else if (command2 == "kick")
			{
				parsedInput->command2 = KICK;
			}
			else if (command2 == "bite")
			{
				parsedInput->command2 = BITE;
			}
			else if (command2 == "firebreath")
			{
				parsedInput->command2 = FIREBREATH;
			}
			else if (command2 == "flamethrower")
			{
				parsedInput->command2 = FLAMETHROWER;
			}
			else if (command2 == "fireball")
			{
				parsedInput->command2 = FIREBALL;
			}
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
			}
			else if (command2 == "slash")
			{
				parsedInput->command2 = SLASH;
			}
			else if (command2 == "slam")
			{
				parsedInput->command2 = SLAM;
			}
			else if (command2 == "shadowball")
			{
				parsedInput->command2 = SHADOWBALL;
			}
			else if (command2 == "eruption")
			{
				parsedInput->command2 = ERUPTION;
			}
			else if (command2 == "overheat")
			{
				parsedInput->command2 = OVERHEAT;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}

		}
		else if (command1 == "battle")
		{
			parsedInput->command1 = BATTLE;

			if (command2 == "skeleton")
			{
				parsedInput->command2 = SKELETON;
			}
			else if (command2 == "hellhound")
			{
				parsedInput->command2 = HELLHOUND;
			}
			else if (command2 == "chimera")
			{
				parsedInput->command2 = CHIMERA;
			}
			else if (command2 == "dragon")
			{
				parsedInput->command2 = DRAGON;
			}
			else if (command2 == "archdemon")
			{
				parsedInput->command2 = ARCHDEMON;
			}
			else if (command2 == "reaper")
			{
				parsedInput->command2 = REAPER;
			}
			else if (command2 == "mimic")
			{
				parsedInput->command2 = MIMIC;
			}
			else if (command2 == "spirit")
			{
				parsedInput->command2 = SPIRIT;
			}
			else if (command2 == "hydra")
			{
				parsedInput->command2 = HYDRA;
			}
			else if (command2 == "devil")
			{
				parsedInput->command2 = DEVIL;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}
		}
		else
		{
			parsedInput->command1 = ERROR1;
		}
	}
	else
	{
		std::cout << "Error from Regex" << std::endl;
	}
	return (parsedInput);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Helpful display functions
///////////////////////////////////////////////////////////////////////////////////////////

// Displays the help text in the console
void Parser::displayHelpText(GameUI console, bool* inBattle)
{
	// Print the regular help text if not in battle
	if (*inBattle == false)
	{
		// Print regular help text
		console.writeOutput(helpText);
	}
	else
	{
		// Print battle help text
		console.writeOutput(battleHelpText);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Error message functions
///////////////////////////////////////////////////////////////////////////////////////////

// Display to the user that they made an incorrect command, redisplay commands
void Parser::incorrectMainCommand(GameUI console, bool* inBattle)
{
	// Message for the user
	std::string errorMessage = "\t*** Invalid Command -- Valid Commands Are ***\n";

	// Display the errors
	console.writeOutput(errorMessage);
	displayHelpText(console, inBattle);
}

// Display to the user that they made an incorrect direction command
void Parser::incorrectDirectionCommand(GameUI console)
{
	// Message for the user
	std::string errorMessage = "\t*** Invalid Direction - Directions Are ***\n\t      [left] [up] [right] [down]\n";

	// Display the error
	console.writeOutput(errorMessage);
}

// Display to the user that they made an incorrect item command
void Parser::incorrectItemCommand(GameUI console)
{
	// ToDo: Add the possible items the player could be using right now
	// - Player inventory items
	// - Room inventory items

	// Message for the user
	std::string errorMessage = "\t*** Invalid Item - Try Again ***\n";

	// Display the error
	console.writeOutput(errorMessage);
}

// Display to the user that they made an incorrect monster command
void Parser::incorrectMonsterCommand(GameUI console)
{
	// ToDo: Add the possible monster the player could be battling
	// - Current room you are in monster's only

	// Message for the user
	std::string errorMessage = "\t*** Invalid Monster - Try Again ***\n";

	// Display the error
	console.writeOutput(errorMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Convert user input into a standardized version that we can use
///////////////////////////////////////////////////////////////////////////////////////////

// Function that takes a string and returns the string in all lowercase
std::string Parser::convertLower(std::string sentence)
{
	// Apply the toLower function to all characters in a string
	transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);
	return sentence;
}

// Function to format the string into just the command, or the two commands the user entered
// with the delimiter being a space. Ex. [`command1`] or  [`command1` `command2`]
std::string Parser::formatWithOneSpace(std::string sentence)
{
	// Set of possible white space characters in c++
	std::set <char> whiteSpaces = { ' ', '\t', '\n', '\f', '\r', '\v' };
	std::string newString = "";
	std::string temp = "x";

	for (char c : sentence)
	{
		// Search to find if the character is in the set or not. aka - is the character a whitespace character
		auto search1 = whiteSpaces.find(c);
		auto search2 = whiteSpaces.find(temp.back());

		// If the last element in temp string is not a whitespace, and the current char is a white space
		// then push a space onto the string that will be returned
		if (search2 != whiteSpaces.end() && search1 == whiteSpaces.end())
		{
			newString.push_back(' ');
		}

		// Push the current character onto the temp string
		temp.push_back(c);

		// If the current character is not white space, push it onto the string that will be returned
		if (search1 == whiteSpaces.end())
		{
			newString.push_back(c);
		}
	}

	// If there is an extra space at the beginning, get rid of it
	if (newString[0] == ' ')
	{
		newString.erase(0, 1);
	}

	return newString;
}

// Function to standardize user input
std::string Parser::standardizeInput(std::string userString)
{
	std::string newString = "";

	newString = convertLower(userString);
	newString = formatWithOneSpace(newString);

	return newString;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Get commands from the parsed string
///////////////////////////////////////////////////////////////////////////////////////////

// Get the first command word from a standardized user input
std::string Parser::getFirstCommand(std::string userString)
{
	std::string command = "";
	int spaceIndex = int(userString.find(' '));

	// Characters before space are attributed to command 1
	command = userString.substr(0, spaceIndex);

	return command;
}

// Get the second command word from a standardized user input
std::string Parser::getSecondCommand(std::string userString)
{
	std::string command = "";
	int lastElementIndex = int(userString.length());
	int spaceIndex = int(userString.find(' '));

	// Characters after space are attributed to command 2, hence start from a
	// character after the space
	command = userString.substr(spaceIndex + 1, lastElementIndex);

	return command;
}