#pragma once

#include <string>

class GameUI
{
public:
	GameUI();
	int writeOutput(std::string output);
	std::string getUserInput(std::string prompt);
};