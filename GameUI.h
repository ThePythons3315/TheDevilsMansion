#pragma once

#include <string>

class GameUI
{
public:
	// Construtor
	GameUI();

	// Other functions
	int writeOutput(std::string output);
	int outputByCharacter(std::string output);
	std::string getUserInput(std::string prompt);

	// Change the colors of the console and text
	void changeToBattleColors();
	void changeToNormalColors();
	void changeColor(int color);
};