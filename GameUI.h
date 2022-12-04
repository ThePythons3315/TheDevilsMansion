#pragma once

#include <string>

class GameUI
{
public:
	// Construtor
	GameUI();

	// Other functions
	int writeOutput(std::string output);
	std::string getUserInput(std::string prompt);
};