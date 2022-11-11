#pragma once

#include <string>
#include "GameUI.h"

class Parser
{
public:

	// Possible first user entered commands
	enum MainCommandMenu
	{
		HELP, MOVE, COLLECT, USE, DROP, INVENTORY, HEALTH, BATTLE, ATTACKS, QUIT, ERROR1
	};
	// Possible second user entered commands
	enum SecondaryCommandMenu
	{ 
		LEFT, CENTER, RIGHT, BACK, BLUEBERRY, SKELETON, ERROR2 
	};

	struct InputStruct
	{
		MainCommandMenu command1;
		SecondaryCommandMenu command2;
	};

	// Constructor
	Parser();
	InputStruct* parseInput(std::string userString);

	// Helpful display functions
	void displayParsedOutput(InputStruct* parsedOutput, GameUI console);
	void displayHelpText(GameUI console);

	// Error message functions
	void incorrectMainCommand(GameUI console);
	void incorrectDirectionCommand(GameUI console);
	void incorrectItemCommand(GameUI console);
	void incorrectMonsterCommand(GameUI console);

	// Convert user input into a standardized version that we can use
	std::string convertLower(std::string sentence);
	std::string formatWithOneSpace(std::string sentence);
	std::string standardizeInput(std::string userString);

	// Get commands from the parsed string
	std::string getFirstCommand(std::string userString);
	std::string getSecondCommand(std::string userString);
};