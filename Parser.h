#pragma once

#include <string>
#include "GameUI.h"

class Parser
{
public:
	// Primary commands that will run the game
	enum MainCommandMenu
	{
		HELP, MOVE, COLLECT, USE, DROP, INVENTORY, HEALTH,
		BATTLE, ATTACKS, QUIT, ROOM, PLAYER, ERROR1
	};
	// Secondary Commands that can be used along side certain primary commands
	enum SecondaryCommandMenu
	{
		LEFT, UP, RIGHT, DOWN,
		SKELETON, HELLHOUND, CHIMERA, DRAGON, ARCHDEMON,REAPER,
		BLUEBERRY, DEVILSKEY, PARALYSISHEAL, BURNHEAL,
		BOWSHOT, PUNCH, KICK, BITE, FIREBREATH, FLAMETHROWER, FIREBALL,
		SLASH,ERROR2
	};

	// Struct of commands that will be filled when user input is parsed
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
	void displayHelpText(GameUI console, bool* inBattle);

	// Error message functions
	void incorrectMainCommand(GameUI console, bool* inBattle);
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