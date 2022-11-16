#include "Parser.h"
#include <iostream>
#include <set>
#include <regex>
#include <algorithm>

// Text that will display what commands are available and their descriptions
std::string helpText =
"1 keyword commands:\n"
"\t- inventory \t\t-> Shows the player's current inventory\n"
"\t- health \t\t-> Shows the player's current health\n"
"\t- attacks \t\t-> Shows the player's current attacks\n"
"\t- quit \t\t\t-> Quits the application\n"
"\t- help \t\t\t-> Gives available commands and descriptions\n"
"2 keyword commands:\n"
"\t- move [direction]\t-> Moves the player to a different room\n"
"\t- collect [item name]\t-> Lets the player add an item from the room to their inventory\n"
"\t- use [item name]\t-> Lets the player use an item in their inventory\n"
"\t- drop [item name]\t-> Lets the player drop an object from their inventory\n"
"\t- battle [monster name]\t-> Lets the player go into battle with a monster\n";

Parser::Parser()
{
	// null constructor
}

// Parse user input into a useable format
Parser::InputStruct* Parser::parseInput(std::string userString)
{
	InputStruct* parsedInput = new InputStruct;

	// Standardize the input to a version we can work with
	std::string standardString = standardizeInput(userString);

	// Regex for 1 argument input, and 2 argument input
	// Only accepts [spaces, characters, spaces, characters, spaces]
	std::regex cmdRegex("^\\s*[a-zA-Z]+\\s*$");
	std::regex cmdRegexTwoArg("^\\s*[a-zA-Z]+\\s*[a-zA-Z]+\\s*$");

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
			else if (command2 == "center")
			{
				parsedInput->command2 = CENTER;
			}
			else if (command2 == "right")
			{
				parsedInput->command2 = RIGHT;
			}
			else if (command2 == "back")
			{
				parsedInput->command2 = BACK;
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
			else if (command2 == "bow")
			{
				parsedInput->command2 = BOW;
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
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
			}
			else
			{
				parsedInput->command2 = ERROR2;
			}
		}
		else if (command1 == "use") {
			parsedInput->command1 = USE;

			if (command2 == "blueberry")
			{
				parsedInput->command2 = BLUEBERRY;
			}
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
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
			else if (command2 == "bow")
			{
				parsedInput->command2 = BOW;
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
			else if (command2 == "devilskey")
			{
				parsedInput->command2 = DEVILSKEY;
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

// Knows how to print all elements of parser output structure
void Parser::displayParsedOutput(InputStruct* parsedOutput, GameUI console)
{
	switch (parsedOutput->command1) {
	case QUIT:
		console.writeOutput("QUIT");
		break;
	case HELP:
		console.writeOutput("HELP");
		break;
	case MOVE:
		console.writeOutput("MOVE");
		break;
	case COLLECT:
		console.writeOutput("COLLECT");
		break;
	case USE:
		console.writeOutput("USE");
		break;
	case DROP:
		console.writeOutput("DROP");
		break;
	case INVENTORY:
		console.writeOutput("INVENTORY");
		break;
	case HEALTH:
		console.writeOutput("HEATLH");
		break;
	case BATTLE:
		console.writeOutput("BATTLE");
		break;
	case ATTACKS:
		console.writeOutput("ATTACKS");
		break;
	default:
		console.writeOutput("\t*** Invalid Command -- Valid commands are ...\n");
		console.writeOutput(helpText);
		break;
	}
	console.writeOutput("\n");
}

// Displays the help text in the console
void Parser::displayHelpText(GameUI console)
{
	console.writeOutput(helpText);
}

// Display to the user that they made an incorrect command, redisplay commands
void Parser::incorrectMainCommand(GameUI console)
{
	console.writeOutput("\t*** Invalid Command -- Valid Commands Are ***\n");
	console.writeOutput(helpText);
}

// Display to the user that they made an incorrect direction command
void Parser::incorrectDirectionCommand(GameUI console)
{
	console.writeOutput("\t*** Invalid Direction - Directions Are ***\n"
		"\t      [left] [center] [right] [back]\n");
}

// Display to the user that they made an incorrect item command
void Parser::incorrectItemCommand(GameUI console)
{
	// ToDo: Add the possible items the player could be using right now
	// - Player inventory items
	// - Room inventory items
	console.writeOutput("\t*** Invalid Item - Try Again ***\n");
}

// Display to the user that they made an incorrect monster command
void Parser::incorrectMonsterCommand(GameUI console)
{
	// ToDo: Add the possible monster the player could be battling
	// - Current room you are in monster's only
	console.writeOutput("\t*** Invalid Monster - Try Again ***\n");
}

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

		// Pusht the current character onto the temp string
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